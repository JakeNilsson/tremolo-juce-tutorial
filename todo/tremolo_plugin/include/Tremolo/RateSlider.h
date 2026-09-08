#pragma once

namespace tremolo {
    class RateSlider : public juce::Slider {
    public:
        void paint(juce::Graphics& g) override {
            auto sliderPos = (float)valueToProportionOfLength(getValue());
            jassert(sliderPos >= 0 && sliderPos <= 1.0f);

            const auto rotaryParams = getRotaryParameters();
            const auto rotaryStartAngle = rotaryParams.startAngleRadians;
            const auto rotaryEndAngle = rotaryParams.endAngleRadians;

            auto outline = findColour (Slider::rotarySliderOutlineColourId);

            auto bounds = getLocalBounds().toFloat().reduced (10);

            //auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
            auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

            if (isEnabled())
            {
                juce::Path valueArc;
                valueArc.addPieSegment(bounds.getX(),
                                       bounds.getY(),
                                       bounds.getWidth(),
                                       bounds.getHeight(),
                                       rotaryParams.startAngleRadians,
                                       toAngle,
                                       1.14f);

                g.setColour (juce::Colours::orange);
                g.fillPath (valueArc);
            }
        }
    };
}