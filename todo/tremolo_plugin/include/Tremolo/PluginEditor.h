#pragma once

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);

  juce::Rectangle<int> setInversePos(juce::Rectangle<int> parentDimensions, int l, int r, int u, int d);

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent leftLogo;
  juce::ImageComponent midLogo;
  juce::ImageComponent rightLogo;

  juce::Slider rateSlider;
  juce::Slider widthSlider;

  LfoVisualizer lfoVisualizer;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
