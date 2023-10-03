#pragma once

#include "MainWindow.h"

class SynthLabApplication : public juce::JUCEApplication
{
public:
    SynthLabApplication();
    const juce::String getApplicationName() override;
    const juce::String getApplicationVersion() override;
    bool moreThanOneInstanceAllowed() override;

    void initialise(const juce::String& commandLine) override;

    void shutdown() override;

    void systemRequestedQuit() override;

    void anotherInstanceStarted(const juce::String& commandLine) override;

    static SynthLabApplication* JUCE_CALLTYPE getInstance() noexcept;

    juce::PropertiesFile* getPropsFile() const;

private:
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<juce::PropertiesFile> propsFile;
};
