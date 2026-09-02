namespace tremolo {
    PluginEditor::PluginEditor(PluginProcessor& p) : AudioProcessorEditor(&p) {
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

        addAndMakeVisible(lfoVisualizer);

        // Make sure that before the constructor has finished, you've set the
        // editor's size to whatever you need it to be.
        setSize(540, 270);
    }

    void PluginEditor::resized() {
        const auto bounds = getLocalBounds();

        background.setBounds(bounds);

        leftLogo.setBounds({16, 16, 105, 24});
        midLogo.setBounds({217, 16, 105, 24});
        rightLogo.setBounds({419, 16, 105, 24});

        lfoVisualizer.setBounds({18, 149, 504, 92});
    }
}  // namespace tremolo
