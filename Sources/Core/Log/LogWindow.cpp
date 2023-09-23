#include "stdafx.h"
#include "LogWindow.h"
#include "Core/GlobPropsFile.h"

LogWindow::LogWindow(juce::String name)
    : DocumentWindow(
        name,
        juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
{
    tableListBox.setSize(gPropsFile->getIntValue("LogWndWidth", 1200) , gPropsFile->getIntValue("LogWndHeight", 600));
    tableListBox.getHeader().addColumn("Time", 1, gPropsFile->getIntValue("LogWndTimeColumnSize", 70));
    tableListBox.getHeader().addColumn("Level", 2, gPropsFile->getIntValue("LogWndLevelColumnSize", 70));
    tableListBox.getHeader().addColumn("Message", 3, gPropsFile->getIntValue("LogWndMessageColumnSize", 70));

    tableListBox.getHeader().addListener(this);

    tableListBox.autoSizeColumn(1);
    tableListBox.autoSizeColumn(2);

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

void LogWindow::resized()
{
    DocumentWindow::resized();
    gPropsFile->setValue("LogWndWidth", getWidth());
    gPropsFile->setValue("LogWndHeight", getHeight());
    gPropsFile->saveIfNeeded();
}

void LogWindow::closeButtonPressed()
{
}

void LogWindow::tableColumnsChanged(juce::TableHeaderComponent* tableHeader)
{
}

void LogWindow::tableColumnsResized(juce::TableHeaderComponent* tableHeader)
{
    gPropsFile->setValue("LogWndTimeColumnSize", tableHeader->getColumnWidth(1));
    gPropsFile->setValue("LogWndLevelColumnSize", tableHeader->getColumnWidth(2));
    gPropsFile->setValue("LogWndMessageColumnSize", tableHeader->getColumnWidth(3));
    gPropsFile->saveIfNeeded();
}

void LogWindow::tableSortOrderChanged(juce::TableHeaderComponent* tableHeader)
{
}

