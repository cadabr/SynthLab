#pragma once

class AudioApp : public juce::AudioAppComponent
{
public:
    AudioApp();

    ~AudioApp() override;

    void prepareToPlay(int samplesPerBlockExpected, double newSampleRate) override;

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;

    void releaseResources() override;

    void paint(juce::Graphics& g) override;

    void mouseDown(const juce::MouseEvent& e) override;

    void mouseDrag(const juce::MouseEvent& e) override;

    void mouseUp(const juce::MouseEvent&) override;

    void resized() override;

private:
    float phase       = 0.0f;
    float phaseDelta  = 0.0f;
    float frequency   = 5000.0f;
    float amplitude   = 0.2f;

    double sampleRate = 0.0;
    int expectedSamplesPerBlock = 0;
    juce::Point<float> lastMousePosition;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioApp)
};
