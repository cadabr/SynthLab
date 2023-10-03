#include "stdafx.h"
#include "SynthLabApplication.h"
#include "Core/Log/LogMain.h"

using namespace juce;

SynthLabApplication::SynthLabApplication()
: mainWindow(nullptr)
, propsFile(nullptr)
{
}

const String SynthLabApplication::getApplicationName()
{
    return ProjectInfo::projectName;
}

const String SynthLabApplication::getApplicationVersion()
{
    return ProjectInfo::versionString;
}

bool SynthLabApplication::moreThanOneInstanceAllowed()
{
    return false;
}

void SynthLabApplication::initialise (const String& commandLine)
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

void SynthLabApplication::shutdown()
{
    // Add your application's shutdown code here..

    mainWindow = nullptr; // (deletes our window)
    propsFile->save();
    propsFile.reset();
}

void SynthLabApplication::systemRequestedQuit()
{
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
}

void SynthLabApplication::anotherInstanceStarted (const juce::String& commandLine)
{
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
}

SynthLabApplication* JUCE_CALLTYPE SynthLabApplication::getInstance() noexcept
{
    return dynamic_cast<SynthLabApplication*> (JUCEApplication::getInstance());
}

PropertiesFile* SynthLabApplication::getPropsFile() const
{
    return propsFile.get();
}

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (SynthLabApplication)
