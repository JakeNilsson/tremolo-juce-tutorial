namespace tremolo {
    PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p),
    waveformAttachment{p.getParameterRefs().waveform, waveformComboBox},
        rateAttachment{p.getParameterRefs().rate, rateSlider},
        mixAttachment{p.getParameterRefs().mix, mixSlider},
        bypassAttachment{p.getParameterRefs().bypass, bypassButton}
        {

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

        addAndMakeVisible(waveformLabel);
        waveformComboBox.addItemList(p.getParameterRefs().waveform.choices, 1);
        waveformAttachment.sendInitialUpdate();
        addAndMakeVisible(waveformComboBox);

        rateLabel.setJustificationType(juce::Justification::centred);
        rateLabel.setInterceptsMouseClicks(false, false);
        addAndMakeVisible(rateLabel);
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

        addAndMakeVisible(bypassLabel);
        bypassButton.onClick = [this]() {
            bypassButton.setButtonText(bypassButton.getToggleState() ? "On" : "Off");
        };
        bypassButton.onClick();
        addAndMakeVisible(bypassButton);

        addAndMakeVisible(lfoVisualizer);

        widthSlider.setRange(1, 10, 1);
        widthSlider.setValue(2);
        widthSlider.onValueChange = [this] {
            lfoVisualizer.setPath(widthSlider.getValue());
            lfoVisualizer.repaint();
        };
        addAndMakeVisible(widthSlider);

        lookAndFeelComboBox.addItemList({"LookAndFeel_V1",
                                                "LookAndFeel_V2",
                                                "LookAndFeel_V3",
                                                "LookAndFeel_V4",
                                                "CustomLookAndFeel"}, 1);
        lookAndFeelComboBox.setSelectedId(5);
        lookAndFeelComboBox.onChange = [this]() {
            switch (lookAndFeelComboBox.getSelectedId()) {
                case 1 : {
                    setLookAndFeel(&lookAndFeelv1);
                    break;
                } case 2 : {
                    setLookAndFeel(&lookAndFeelv2);
                    break;
                } case 3 : {
                    setLookAndFeel(&lookAndFeelv3);
                    break;
                } case 4 : {
                    setLookAndFeel(&lookAndFeelv4);
                    break;
                } case 5 : {
                    setLookAndFeel(&lookAndFeelCustom);
                    break;
                }
            }
        };
        addAndMakeVisible(lookAndFeelComboBox);

        // Make sure that before the constructor has finished, you've set the
        // editor's size to whatever you need it to be.
        setSize(540, 300);
    }

    PluginEditor::~PluginEditor() {
        setLookAndFeel(nullptr);
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

        auto waveformComboBoxBounds = setInversePos(getLocalBounds(), 16, 392, 66, 206);
        waveformComboBox.setBounds(waveformComboBoxBounds);

        auto waveformLabelBounds = waveformComboBoxBounds.translated(0, -waveformComboBoxBounds.getHeight());
        waveformLabel.setBounds(waveformLabelBounds);

        auto rateSliderBounds = setInversePos(getLocalBounds(), 230, 230, 40, 175);
        rateSlider.setBounds({rateSliderBounds});
        rateLabel.setBounds({rateSliderBounds});

        //auto mixSliderBounds = setInversePos(getLocalBounds(), 330, 130, 40, 175);
        //mixSlider.setBounds({mixSliderBounds});

        auto bypassButtonBounds = setInversePos(getLocalBounds(), 392, 16, 66, 206);
        bypassButton.setBounds({bypassButtonBounds});

        auto bypassLabelBounds = bypassButtonBounds.translated(0, -bypassButtonBounds.getHeight());
        bypassLabel.setBounds(bypassLabelBounds);

        lfoVisualizer.setBounds({18, 149, 504, 92});
        lfoVisualizer.setPath(2);

        widthSlider.setBounds({2, 271, 270, 30});

        lookAndFeelComboBox.setBounds({277, 273, 260, 25});

        //lfoVisualizer
    }
}  // namespace tremolo
