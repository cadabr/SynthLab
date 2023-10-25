#include <JuceHeader.h>
#include "MainWindow.h"
#include "AudioApp.h"
#include "SynthLab.h"

using namespace juce;

MainWindow::MainWindow (String name)
: DocumentWindow (name, Desktop::getInstance().getDefaultLookAndFeel().findColour (ResizableWindow::backgroundColourId), DocumentWindow::closeButton)
{
    setUsingNativeTitleBar (true);
    setContentOwned (new AudioApp(), true);
    setResizable (true, true);
    centreWithSize (getWidth(), getHeight());
    setVisible (true);
}

void MainWindow::closeButtonPressed()
{
    SynthLab::getInstance()->systemRequestedQuit();
}
