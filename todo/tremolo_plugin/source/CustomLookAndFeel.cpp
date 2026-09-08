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

        g.drawText(button.getButtonText(), bounds, juce::Justification::centred, false);
    }
}  // namespace tremolo
