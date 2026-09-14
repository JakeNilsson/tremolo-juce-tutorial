namespace tremolo {
    namespace {
        void drawButtonInset(juce::Graphics &g, const juce::Rectangle<int> borderBounds) {
            auto boxBorderGradient = juce::ColourGradient::vertical(juce::Colour{0xFF22232C},
                                                                    juce::Colour{0xFF263235},
                                                                    borderBounds);
            boxBorderGradient.addColour(0.35, juce::Colour{0xFF303538});
            g.setGradientFill(boxBorderGradient);
            g.fillRoundedRectangle(borderBounds.toFloat(), 6.f);
        }

        void drawBlueGradientButton(juce::Graphics &g, int alpha, const juce::Rectangle<int> bounds) {
            auto buttonGradient = juce::ColourGradient::vertical(juce::Colour::fromRGBA(0x4A, 0x70, 0x90, alpha),
                                                                 juce::Colour::fromRGBA(0x32, 0x42, 0x58, alpha),
                                                                 bounds);

            buttonGradient.addColour(0.73, juce::Colour{0xFF315160});
            g.setGradientFill(buttonGradient);
            g.fillRoundedRectangle(bounds.toFloat(), 4.f);
        }
    }

    CustomLookAndFeel::CustomLookAndFeel() {
        setColour(juce::PopupMenu::backgroundColourId, juce::Colour{0xFF153245});
        setColour(juce::PopupMenu::textColourId, getColour(Colours::paleBlue));
        setColour(juce::PopupMenu::highlightedBackgroundColourId, getColour(Colours::orange));
        setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour{0xFF0C131E});
        setColour(juce::ComboBox::textColourId, getColour(Colours::paleBlue));
        setColour(juce::Label::textColourId, juce::Colour{0xFF6EA0C7});
    }

    juce::Colour CustomLookAndFeel::getColour(Colours colourName) {
        static const std::array colours{
            juce::Colour{0xFFDDECFF},
            juce::Colour{0xFFFFAA00}
        };
        return colours.at(juce::toUnderlyingType(colourName));
    }

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

        drawButtonInset(g, borderBounds);
        drawBlueGradientButton(g, alpha, bounds);

        g.setColour(button.getToggleState() ? juce::Colour{0xFF501A0B} : getColour(Colours::paleBlue));

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

        g.setColour (getColour(Colours::orange));
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

    void CustomLookAndFeel::drawComboBox(juce::Graphics &g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox &box) {
        auto alpha = 255;

        //if (shouldDrawButtonAsHighlighted) {
        //    alpha *= 0.7f;
        //}

        const auto bounds = box.getLocalBounds().reduced(2);
        const auto borderBounds = box.getLocalBounds();

        drawButtonInset(g, borderBounds);
        drawBlueGradientButton(g, alpha, bounds);

        auto boxGradient = juce::ColourGradient::vertical(juce::Colour::fromRGBA(0x4A, 0x70, 0x90, alpha),
                                                             juce::Colour::fromRGBA(0x32, 0x42, 0x58, alpha),
                                                             bounds);

        boxGradient.addColour(0.73, juce::Colour{0xFF315160});
        g.setGradientFill(boxGradient);
        g.fillRoundedRectangle(bounds.toFloat(), 4.f);

        auto arrowBounds = bounds.reduced(8, 9);
        arrowBounds.removeFromLeft(104);

        juce::Path arrow;
        arrow.startNewSubPath(arrowBounds.getTopLeft().toFloat());
        arrow.lineTo(arrowBounds.getTopRight().toFloat());
        arrow.lineTo(arrowBounds.getCentreX(), arrowBounds.getBottom());
        arrow.closeSubPath();

        g.setColour(getColour(Colours::paleBlue));
        g.fillPath(arrow);
    }

    void CustomLookAndFeel::positionComboBoxText(juce::ComboBox &box, juce::Label &labelToPosition) {
        auto bounds = box.getLocalBounds().reduced(10, 6);
        bounds.removeFromRight(12);
        labelToPosition.setBounds(bounds);
        labelToPosition.setJustificationType(juce::Justification::centred);
        labelToPosition.setFont(interBold());
        labelToPosition.setFont(getComboBoxFont(box));
    }

    juce::PopupMenu::Options CustomLookAndFeel::getOptionsForComboBoxPopupMenu(juce::ComboBox &box, juce::Label &label) {
        return LookAndFeel_V4::getOptionsForComboBoxPopupMenu(box, label)
            .withStandardItemHeight(24)
            .withMinimumWidth(132);
    }

    juce::Font CustomLookAndFeel::getPopupMenuFont() {
        return interMedium().withPointHeight(12.f);
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
