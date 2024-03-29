#include <JuceHeader.h>
#include "AudioApp.h"
#include "Core/Log/LogRecord.h"

using namespace juce;
using namespace std;

AudioApp::AudioApp()
{
    setAudioChannels(0, 2);
    setSize(800, 600);
}

AudioApp::~AudioApp()
{
    shutdownAudio();
}

void AudioApp::prepareToPlay(int samplesPerBlockExpected, double newSampleRate)
{
    sampleRate = newSampleRate;
    expectedSamplesPerBlock = samplesPerBlockExpected;
}

void AudioApp::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    auto originalPhase = phase;
    LOGD("asd");

    for (auto chan = 0; chan < bufferToFill.buffer->getNumChannels(); ++chan)
    {
        phase = originalPhase;

        auto* channelData = bufferToFill.buffer->getWritePointer(chan, bufferToFill.startSample);

        for (auto i = 0; i < bufferToFill.numSamples; ++i)
        {
            int c = 300;
            float g = 0.f;
            for (auto k = 1; k < c; k++)
            {
                g += sin(k * phase) / k;
            }

            channelData[i] = amplitude * 2.f * g / MathConstants<float>::pi;

            // increment the phase step for the next sample
            phase = fmod(phase + phaseDelta, MathConstants<float>::twoPi);
        }
    }
}

void AudioApp::releaseResources()
{
}

void AudioApp::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    auto centreY = (float)getHeight() / 2.0f;
    auto radius = amplitude * 200.0f;

    if (radius >= 0.0f)
    {
        // Draw an ellipse based on the mouse position and audio volume
        g.setColour(Colours::lightgreen);

        g.fillEllipse(jmax(0.0f, lastMousePosition.x) - radius / 2.0f,
            jmax(0.0f, lastMousePosition.y) - radius / 2.0f,
            radius, radius);
    }

    // Draw a representative sine wave.
    Path wavePath;
    wavePath.startNewSubPath(0, centreY);

    for (auto x = 1.0f; x < (float)getWidth(); ++x)
        wavePath.lineTo(x, centreY + amplitude * (float)getHeight() * 2.0f
            * sin(x * frequency * 0.0001f));

    g.setColour(getLookAndFeel().findColour(Slider::thumbColourId));
    g.strokePath(wavePath, PathStrokeType(2.0f));
}

void AudioApp::mouseDown(const MouseEvent& e)
{
    mouseDrag(e);
}

void AudioApp::mouseDrag(const MouseEvent& e)
{
    lastMousePosition = e.position;

    frequency = (float)(getHeight() - e.y) * 10.0f;
    amplitude = jmin(0.9f, 0.2f * e.position.x / (float)getWidth());

    phaseDelta = (float)(MathConstants<double>::twoPi * frequency / sampleRate);

    repaint();
}

void AudioApp::mouseUp(const MouseEvent&)
{
    //amplitude = 0.0f;
    repaint();
}

void AudioApp::resized()
{
}
