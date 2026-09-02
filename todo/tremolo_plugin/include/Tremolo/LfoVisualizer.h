namespace tremolo {
    class LfoVisualizer : public juce::Component {
    public:
        void paint(juce::Graphics& g) override {
            juce::Path sine;

            const auto strokeWidth = 2.f;

            const auto midpoint = getHeight() / 2;
            const auto amplitude = midpoint - strokeWidth / 2;

            sine.startNewSubPath(0, midpoint + amplitude * std::sin(0.f));

            for (const auto x : std::views::iota(-1, getWidth() + 2)) {
                sine.lineTo(x, midpoint + amplitude * std::sin(0.1f * x));
            }

            g.setColour(juce::Colours::orange);
            g.strokePath(sine, juce::PathStrokeType{strokeWidth});
        }
    };
}