namespace tremolo {
    void CustomLookAndFeel::drawToggleButton(juce::Graphics& g,
                                             juce::ToggleButton& button,
                                             bool shouldDrawButtonAsHighlighted,
                                             bool shouldDrawButtonAsDown) {
        auto alpha = 255;

        if (shouldDrawButtonAsHighlighted) {
            alpha *= 0.7f;
        }

        const auto bounds = button.getLocalBounds().reduced(2);
        const auto borderBounds = button.getLocalBounds();

        auto buttonBorderGradient = juce::ColourGradient::vertical(juce::Colour{0xFF22232C},
                                                                   juce::Colour{0xFF263235},
                                                                   borderBounds);
        buttonBorderGradient.addColour(0.35, juce::Colour{0xFF303538});
        g.setGradientFill(buttonBorderGradient);
        g.fillRoundedRectangle(borderBounds.toFloat(), 6.f);

        if(button.getToggleState()) {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour::fromRGBA(0xFF, 0x90, 0x1A, alpha),
                                                                 juce::Colour::fromRGBA(0xFF, 0xC3, 0x00, alpha),
                                                                 bounds);

            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(), 4.f);

            g.setColour(juce::Colour{0xFF501A0B});
        } else {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour::fromRGBA(0x4A, 0x70, 0x90, alpha),
                                                                 juce::Colour::fromRGBA(0x32, 0x42, 0x58, alpha),
                                                                 bounds);

            buttonGradient.addColour(0.73, juce::Colour{0xFF315160});
            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(), 4.f);

            g.setColour(juce::Colour{0xFFDDECFF});
        }
        g.setFont(interBold().withPointHeight(12.f));
        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);
    }
    void CustomLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &) {
        auto bounds = juce::Rectangle(x, y, width, height).toFloat().reduced(3.75f);
        g.setColour(juce::Colour{0xFF2A3A3B});
        g.fillEllipse(bounds);

        juce::Path valueArc;
        auto toAngle = rotaryStartAngle + sliderPosProportional * (rotaryEndAngle - rotaryStartAngle);
        valueArc.addPieSegment(bounds.reduced(0.25f),
                               rotaryStartAngle,
                               toAngle,
                               0.f);

        g.setColour (juce::Colour{0xFFFFAA00});
        g.fillPath (valueArc);

        bounds.reduce(4.f, 4.f);
        auto knobBorderGradient = juce::ColourGradient::vertical(juce::Colour{0xFF4A7090},
                                                               juce::Colour{0xFF060F1C}, bounds);
        knobBorderGradient.addColour(0.33f, juce::Colour{0xFF396086});
        knobBorderGradient.addColour(0.66f, juce::Colour{0xFF2C3648});
        g.setGradientFill(knobBorderGradient);
        g.fillEllipse(bounds);

        bounds.reduce(1.5f, 1.5f);
        g.setColour(juce::Colour{0x08EFC833});
        g.fillEllipse(bounds);

        bounds.reduce(5.5f, 5.5f);
        g.setGradientFill({juce::Colour{0xFF648BBC},
                                 bounds.getCentreX(),
                                 0.0f,
                                 juce::Colour{0xFF22364D}, //0xFF233750
                                 bounds.getCentreX(),
                                 bounds.getBottom(),
                                 true});
        g.fillEllipse(bounds);

        g.setColour(juce::Colour{0x0AEFF3F6});
        g.fillEllipse(bounds);

        bounds.reduce(-0.5f, -0.5f);
        auto topKnobBorderGradient = juce::ColourGradient::vertical(juce::Colour{0x1A8FFFFF},
                                                              juce::Colour{0x1A1A0F4E}, bounds);
        topKnobBorderGradient.addColour(0.5f, juce::Colour{0x1A8078F4});
        g.setGradientFill(topKnobBorderGradient);
        g.drawEllipse(bounds, 1);
    }
    juce::FontOptions CustomLookAndFeel::interMedium() {
        static const auto medium = juce::Typeface::createSystemTypefaceFor(
            assets::InterMedium_ttf,
            assets::InterMedium_ttfSize);

        return juce::FontOptions{medium};
    }
    juce::FontOptions CustomLookAndFeel::interBold() {
        static const auto bold = juce::Typeface::createSystemTypefaceFor(
            assets::InterBold_ttf,
            assets::InterBold_ttfSize);

        return juce::FontOptions{bold};
    }
}  // namespace tremolo
