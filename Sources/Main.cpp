#include "stdafx.h"
#include "MainComponent.h"
#include "AudioAppDemo.h"
#include "Core\Log\LogMain.h"
#include "Core\GlobPropsFile.h"

using namespace juce;

class SynthLabApplication  : public juce::JUCEApplication
{
public:
    SynthLabApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const String& commandLine) override
    {
        PropertiesFile::Options o;
        o.applicationName = "SynthLab";
        o.filenameSuffix = ".props";
        o.folderName = "SynthLab";
        o.osxLibrarySubFolder = "Application Support/SynthLab";
        o.millisecondsBeforeSaving = 2000;
        gPropsFile.reset(new PropertiesFile(o));

        mainWindow.reset (new MainWindow (getApplicationName()));
        logMain.reset(new LogMain());
        logMain->Show();
        LOGD << L"debug";
        LOGD << L"debug 2";
        LOGI << L"info message";
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
        gPropsFile->save();
        gPropsFile.reset();
    }

    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const juce::String& commandLine) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                          .findColour (juce::ResizableWindow::backgroundColourId),
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new AudioAppDemo(), true);

           #if JUCE_IOS || JUCE_ANDROID
            setFullScreen (true);
           #else
            setResizable (true, true);
            centreWithSize (getWidth(), getHeight());
           #endif

            setVisible (true);
        }

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
    std::unique_ptr<LogMain> logMain;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (SynthLabApplication)
