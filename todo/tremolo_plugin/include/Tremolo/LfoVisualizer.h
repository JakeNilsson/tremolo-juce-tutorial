#include "Tremolo.h"

enum class LfoWaveforms : size_t {
    sine = 0,
    triangle = 1,
  };

namespace tremolo {
    class LfoVisualizer : public juce::Component {
    public:
        void paint(juce::Graphics& g) override {
            g.setColour(juce::Colours::orange);
            g.strokePath(waveform, juce::PathStrokeType{strokeWidth});
        }
        void setStrokeWidth(float width) {
            strokeWidth = width;
        }
        void setMidpointAndAmplitude(int mid) {
            midpoint = mid;
            amplitude = midpoint - (strokeWidth / 2);
        }
        void setLfoWaveform(LfoWaveforms newWaveform) {
            currentWaveform = newWaveform;
        }
        void setPath(const float strWidth, const float scale = 0.1f) {
            waveform.clear();

            setStrokeWidth(strWidth);
            setMidpointAndAmplitude(getHeight() / 2);

            if (currentWaveform == LfoWaveforms::sine) {
                waveform.startNewSubPath(0, midpoint + (amplitude * std::sin(0.f)));

                for (const auto x : std::views::iota(-1, getWidth() + 2)) {
                    waveform.lineTo(x, midpoint + (amplitude * std::sin(scale * x)));
                }
            } else if (currentWaveform == LfoWaveforms::triangle) {
                waveform.startNewSubPath(0, midpoint + (amplitude * Tremolo::triangle(0.f)));

                const float amplitude2 = getHeight() * 0.4f;
                const float centreY = getHeight() * 0.5f;

                for (const auto x : std::views::iota(-1, getWidth() + 2)) {
                    constexpr float period = 60.0f;
                    const float phase = std::fmod(static_cast<float>(x), period) / period; // wraps to [0, 1)
                    const float triangle = (std::abs((2.0f * phase) - 1.0f) * 2.0f) - 1.0f; // [-1, 1]
                    waveform.lineTo(static_cast<float>(x), centreY - (triangle * amplitude2));
                }
            }
        }

    private:
        juce::Path waveform;
        float strokeWidth = 0;
        int midpoint = 0;
        float amplitude = 0;

        LfoWaveforms currentWaveform = LfoWaveforms::sine;
    };
}
