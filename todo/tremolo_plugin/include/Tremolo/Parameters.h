#pragma once

namespace tremolo {
struct Parameters {
  explicit Parameters(juce::AudioProcessor&);

  juce::AudioParameterFloat& rate;
  juce::AudioParameterFloat& gain;
  juce::AudioParameterFloat& mix;

  juce::AudioParameterBool& bypass;

  JUCE_DECLARE_NON_COPYABLE(Parameters)

  JUCE_DECLARE_NON_MOVEABLE(Parameters)
};
}  // namespace tremolo
