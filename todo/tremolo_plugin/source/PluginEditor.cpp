namespace tremolo {
    PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p),
        rateAttachment{p.getParameterRefs().rate, rateSlider},
        mixAttachment{p.getParameterRefs().mix, mixSlider}{

        background.setImage(juce::ImageCache::getFromMemory(
            assets::Background_png, assets::Background_pngSize));

        leftLogo.setImage(
            juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

        midLogo.setImage(
            juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

        rightLogo.setImage(
            juce::ImageCache::getFromMemory(assets::Logo_png, assets::Logo_pngSize));

        addAndMakeVisible(background);
        addAndMakeVisible(leftLogo);
        addAndMakeVisible(midLogo);
        addAndMakeVisible(rightLogo);

        rateSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        rateSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        rateSlider.setPopupDisplayEnabled(true, true, this);
        rateSlider.setTextValueSuffix(" Hz");
        addAndMakeVisible(rateSlider);

        mixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
        mixSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        mixSlider.setPopupDisplayEnabled(true, true, this);
        mixSlider.setTextValueSuffix("%");
        addAndMakeVisible(mixSlider);

        widthSlider.setRange(1, 10, 1);
        widthSlider.setValue(2);
        widthSlider.onValueChange = [this] {
            lfoVisualizer.setPath(widthSlider.getValue());
            lfoVisualizer.repaint();
        };
        addAndMakeVisible(widthSlider);

        addAndMakeVisible(lfoVisualizer);

        // Make sure that before the constructor has finished, you've set the
        // editor's size to whatever you need it to be.
        setSize(540, 300);
    }

    juce::Rectangle<int> PluginEditor::setInversePos(juce::Rectangle<int> parentDimensions,
                                                  int left,
                                                  int right,
                                                  int top,
                                                  int bottom) {
        auto bounds = parentDimensions;

        bounds.removeFromLeft(left);
        bounds.removeFromRight(right);
        bounds.removeFromTop(top);
        bounds.removeFromBottom(bottom);

        return bounds;
    }

    void PluginEditor::resized() {
        const auto bounds = getLocalBounds();

        background.setBounds({0, 0, 540, 270});

        leftLogo.setBounds({16, 16, 105, 24});
        midLogo.setBounds({217, 16, 105, 24});
        rightLogo.setBounds({419, 16, 105, 24});

        auto rateSliderBounds = setInversePos(getLocalBounds(), 230, 230, 40, 175);
        rateSlider.setBounds({rateSliderBounds});

        auto mixSliderBounds = setInversePos(getLocalBounds(), 330, 130, 40, 175);
        mixSlider.setBounds({mixSliderBounds});

        widthSlider.setBounds({16, 271, 270, 30});

        lfoVisualizer.setBounds({18, 149, 504, 92});
        lfoVisualizer.setPath(2);

        //lfoVisualizer
    }
}  // namespace tremolo
