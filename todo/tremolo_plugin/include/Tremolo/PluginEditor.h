#pragma once
#include "RateSlider.h"

namespace tremolo {
class PluginEditor : public juce::AudioProcessorEditor {
public:
  explicit PluginEditor(PluginProcessor&);
  ~PluginEditor() override;

  juce::Rectangle<int> setInversePos(juce::Rectangle<int> parentDimensions, int l, int r, int u, int d);

  void resized() override;

private:
  juce::ImageComponent background;
  juce::ImageComponent leftLogo;
  juce::ImageComponent midLogo;
  juce::ImageComponent rightLogo;

  juce::ComboBox waveformComboBox;
  juce::ComboBoxParameterAttachment waveformAttachment;

  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::Slider mixSlider;
  juce::SliderParameterAttachment mixAttachment;

  juce::Slider widthSlider;

  juce::ToggleButton bypassButton;
  juce::ButtonParameterAttachment bypassAttachment;

  LfoVisualizer lfoVisualizer;

  CustomLookAndFeel lookAndFeel;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
