#include "stdafx.h"
#include "MainWindow.h"
#include "AudioAppDemo.h"
#include "SynthLabApplication.h"

using namespace juce;

MainWindow::MainWindow (String name)
: DocumentWindow (name, Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId), DocumentWindow::closeButton)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new AudioAppDemo(), true);
    setResizable (true, true);
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void MainWindow::closeButtonPressed()
{
    SynthLabApplication::getInstance()->systemRequestedQuit();
}
