#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    void drawToggleButton(juce::Graphics &, juce::ToggleButton &, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawRotarySlider(juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &) override;
    static juce::FontOptions getInterMedium() {
        return interMedium().withPointHeight(10.f);
    }
    static juce::FontOptions getInterBold() {
        return interBold();
    }
private:
    static juce::FontOptions interMedium();
    static juce::FontOptions interBold();
};
}  // namespace tremolo
