#include "stdafx.h"
#include "LogWindow.h"

LogWindow::LogWindow(juce::String name)
    : DocumentWindow(
        name,
        juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
{
    tableListBox.setSize(1200, 600);
    tableListBox.getHeader().addColumn("Time", 1, 50);
    tableListBox.getHeader().addColumn("Level", 2, 50);
    tableListBox.getHeader().addColumn("Message", 3, 50);

    setUsingNativeTitleBar(true);

    tableListBox.setModel(&logTableListBoxModel);
    setContentOwned(&tableListBox, true);

#if JUCE_IOS || JUCE_ANDROID
    setFullScreen(true);
#else
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
#endif
}

void LogWindow::closeButtonPressed()
{
}

