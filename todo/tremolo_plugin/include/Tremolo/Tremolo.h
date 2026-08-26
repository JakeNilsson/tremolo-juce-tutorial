#pragma once

namespace tremolo {
  enum class ApplySmoothing{ no, yes };

class Tremolo {
public:
  enum class LfoWaveform : size_t {
    sine = 0,
    triangle = 1,
  };

  Tremolo() { setModulationRateHz(5.f, ApplySmoothing::no); }

  void prepare(double sampleRate, int expectedMaxFramesPerBlock) {
    const juce::dsp::ProcessSpec processSpec {
      .sampleRate = sampleRate,
      .maximumBlockSize = static_cast<juce::uint32>(expectedMaxFramesPerBlock),
      .numChannels = 1u,
    };
    for (auto& lfo : lfos) {
      lfo.prepare(processSpec);
    }

    lfoTransitionSmoother.reset(sampleRate, 0.025 /* 25 miliseconds */);

    //allocate defensively
    lfoSamples.resize(4u * static_cast<size_t>(expectedMaxFramesPerBlock));
  }

  void setModulationRateHz(float rateHz, ApplySmoothing applySmoothing = ApplySmoothing::yes) noexcept {
    const auto force = applySmoothing == ApplySmoothing::no;
    for (auto& lfo : lfos) {
      lfo.setFrequency(rateHz, force);
    }
  }

  void setLfoWaveform(LfoWaveform waveform, ApplySmoothing applySmoothing = ApplySmoothing::yes) {
    jassert(waveform == LfoWaveform::sine || waveform == LfoWaveform::triangle);

    lfoToSet = waveform;

    if (applySmoothing == ApplySmoothing::no) {
      currentLfo = waveform;
    }
  }

  void setModulationRate(float rateHz) {
    for (auto& lfo : lfos) {
      lfo.setFrequency(rateHz);
    }
  }

  void setMix(float mix) {
    depth = (mix / 100.f) * 0.5f;
  }

  void process(juce::AudioBuffer<float>& buffer) noexcept {
    updateLfoWaveform();

    // for each frame
    for (const auto frameIndex : std::views::iota(0, buffer.getNumSamples())) {
      // generate the LFO value
      const auto lfoValue = getNextLfoValue();

      // calculate the modulation value
      const auto modulationValue = (lfoValue * depth) + (1.f - depth);

      // for each channel sample in the frame
      for (const auto channelIndex :
           std::views::iota(0, buffer.getNumChannels())) {
        // get the input sample
        const auto inputSample = buffer.getSample(channelIndex, frameIndex);

        // modulate the sample
        const auto outputSample = inputSample * modulationValue;

        // set the output sample
        buffer.setSample(channelIndex, frameIndex, outputSample);
      }
    }
  }

  void reset() noexcept {
    for (auto& lfo : lfos) {
      lfo.reset();
    }
  }

private:
  float depth;

  static float triangle(float phase) {
    return std::abs(2 * phase / juce::MathConstants<float>::pi) - 1.f;
  }

  float getNextLfoValue() {
    if (lfoTransitionSmoother.isSmoothing()) {
      return lfoTransitionSmoother.getNextValue();
    }

    return lfos[juce::toUnderlyingType(currentLfo)].processSample(0.f);
  }

  std::array<juce::dsp::Oscillator<float>, 2u> lfos{
    juce::dsp::Oscillator<float>{[](const float phase) { return std::sin(phase); }},
    juce::dsp::Oscillator<float>{triangle},
  };

  void updateLfoWaveform() {
    if (lfoToSet != currentLfo) {
      // update the smoother
      lfoTransitionSmoother.setCurrentAndTargetValue(getNextLfoValue());

      currentLfo = lfoToSet;

      // initiate smoothing
      lfoTransitionSmoother.setTargetValue(getNextLfoValue());
    }
  }

  LfoWaveform currentLfo = LfoWaveform::sine;
  LfoWaveform lfoToSet = currentLfo;

  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear>
    lfoTransitionSmoother{0.f};
  std::vector<float> lfoSamples;
};
}  // namespace tremolo
