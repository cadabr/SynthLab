#include <JuceHeader.h>
#include "SynthLab.h"
#include "Core/Log/LogMain.h"

using namespace juce;

SynthLab::SynthLab()
: mainWindow(nullptr)
, propsFile(nullptr)
{
}

const String SynthLab::getApplicationName()
{
    return ProjectInfo::projectName;
}

const String SynthLab::getApplicationVersion()
{
    return ProjectInfo::versionString;
}

bool SynthLab::moreThanOneInstanceAllowed()
{
    return false;
}

void SynthLab::initialise ([[maybe_unused]] const String& commandLine)
{
    PropertiesFile::Options o;
    o.applicationName = "SynthLab";
    o.filenameSuffix = ".props";
    o.folderName = "SynthLab";
    o.osxLibrarySubFolder = "Application Support/SynthLab";
    o.millisecondsBeforeSaving = 2000;
    propsFile.reset(new PropertiesFile(o));

    auto* logMain = LogMain::getInstance();
    logMain->initialize();
    logMain->Show();

    LOGD("debug");
    LOGD("debug 2");

    mainWindow.reset (new MainWindow (getApplicationName()));
}

void SynthLab::shutdown()
{
    // Add your application's shutdown code here..

    mainWindow = nullptr; // (deletes our window)
    propsFile->save();
    propsFile.reset();
}

void SynthLab::systemRequestedQuit()
{
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
}

void SynthLab::anotherInstanceStarted ([[maybe_unused]] const juce::String& commandLine)
{
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
}

SynthLab* JUCE_CALLTYPE SynthLab::getInstance() noexcept
{
    return static_cast<SynthLab*>(JUCEApplication::getInstance());
}

PropertiesFile* SynthLab::getPropsFile() const
{
    return propsFile.get();
}

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (SynthLab)
