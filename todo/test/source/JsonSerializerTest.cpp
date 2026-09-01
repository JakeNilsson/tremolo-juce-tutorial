#include <tremolo_plugin/tremolo_plugin.h>
#include <gtest/gtest.h>

namespace tremolo {
TEST(JsonSerializer, SerializeToString) {
  PluginProcessor processor;
  auto& parameters = processor.getParameterRefs();

  parameters.rate = 10.f;
  parameters.bypass = true;
  parameters.waveform = 1;
  parameters.gain = -2;
  parameters.mix = 63.3;

  const juce::String expectedOutput =
      u8R"({
  "__version__": 1,
  "pluginName": "Tremolo",
  "modulationRateHz": 10.0,
  "bypass": true,
  "modulationWaveform": "Triangle",
  "gain": -2.0,
  "mix": 63.3
})";
  juce::MemoryBlock block;
  juce::MemoryOutputStream outputStream{block, false};

  JsonSerializer::serialize(parameters, outputStream);
  outputStream.flush();

  const auto result = outputStream.toUTF8().removeCharacters("\r");

  EXPECT_EQ(expectedOutput, result);
}

TEST(JsonSerializer, DeserializeFromString) {
  const juce::String savedParameters =
      u8R"({
  "__version__": 1,
  "pluginName": "Tremolo",
  "modulationRateHz": 10.0,
  "bypass": true,
  "modulationWaveform": "Triangle",
  "gain": -2.0,
  "mix": 63.3
})";

  juce::MemoryInputStream inputStream{
      savedParameters.getCharPointer(),
      static_cast<size_t>(savedParameters.length()), false};

  PluginProcessor processor;
  auto& parameters = processor.getParameterRefs();

  const auto result = JsonSerializer::deserialize(inputStream, parameters);

  EXPECT_TRUE(result.wasOk());
  EXPECT_FLOAT_EQ(parameters.rate, 10.f);
  EXPECT_TRUE(parameters.bypass);
  EXPECT_EQ(juce::String{"Triangle"},
            parameters.waveform.getCurrentChoiceName());
  EXPECT_FLOAT_EQ(parameters.gain, -2.f);
  EXPECT_FLOAT_EQ(parameters.mix, 63.3);
}

TEST(JsonSerializer, DontUpdateParametersWhenWaveformNameIsInvalid) {
  // given
  const juce::String savedParameters =
      u8R"({
  "__version__": 1,
  "pluginName": "Tremolo",
  "modulationRateHz": 10.0,
  "bypass": true,
  "modulationWaveform": "Foo",
  "gain": -2.0,
  "mix": 63.3
})";

  juce::MemoryInputStream inputStream{
      savedParameters.getCharPointer(),
      static_cast<size_t>(savedParameters.length()), false};

  PluginProcessor processor;
  auto& parameters = processor.getParameterRefs();

  parameters.waveform = 0;
  parameters.bypass = false;
  parameters.rate = 5.f;
  parameters.mix = 48.f;
  parameters.gain = 2.f;

  // when
  const auto result = JsonSerializer::deserialize(inputStream, parameters);

  // then
  EXPECT_TRUE(result.failed());
  EXPECT_FLOAT_EQ(parameters.rate.get(), 5.f);
  EXPECT_FALSE(parameters.bypass.get());
  EXPECT_EQ(0, parameters.waveform.getIndex());
  EXPECT_FLOAT_EQ(parameters.mix.get(), 48.f);
  EXPECT_FLOAT_EQ(parameters.gain.get(), 2.f);
}
}  // namespace tremolo
