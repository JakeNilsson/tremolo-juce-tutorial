#pragma once

namespace tremolo {
class CustomLookAndFeel : public juce::LookAndFeel_V4 {
public:
    CustomLookAndFeel();

    enum class Colours : size_t {
        paleBlue,
        orange,
    };

    static juce::Colour getColour(Colours colourName);
    void drawToggleButton(juce::Graphics &, juce::ToggleButton &, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    void drawRotarySlider(juce::Graphics &, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &) override;

    void drawComboBox(juce::Graphics &, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox &) override;
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
