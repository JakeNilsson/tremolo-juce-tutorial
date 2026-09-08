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

  juce::Label waveformLabel{"waveform label", "Waveform"};
  juce::ComboBox waveformComboBox;
  juce::ComboBoxParameterAttachment waveformAttachment;

  juce::Label rateLabel{"rate label", "Rate"};
  juce::Slider rateSlider;
  juce::SliderParameterAttachment rateAttachment;

  juce::Slider mixSlider;
  juce::SliderParameterAttachment mixAttachment;

  juce::Label bypassLabel{"bypass label", "Bypass"};
  juce::ToggleButton bypassButton;
  juce::ButtonParameterAttachment bypassAttachment;

  juce::Slider widthSlider;

  juce::ComboBox lookAndFeelComboBox;

  LfoVisualizer lfoVisualizer;

  juce::LookAndFeel_V1 lookAndFeelv1;
  juce::LookAndFeel_V2 lookAndFeelv2;
  juce::LookAndFeel_V3 lookAndFeelv3;
  juce::LookAndFeel_V4 lookAndFeelv4;
  CustomLookAndFeel lookAndFeelCustom;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditor)
};
}  // namespace tremolo
