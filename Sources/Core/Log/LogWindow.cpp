#include <JuceHeader.h>
#include "LogWindow.h"
#include "SynthLab.h"

using namespace juce;

LogWindow::LogWindow(String name)
: DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId), DocumentWindow::allButtons)
{
    auto* propsFile = SynthLab::getInstance()->getPropsFile();
    tableListBox.setSize(propsFile->getIntValue("LogWndWidth", 1200) , propsFile->getIntValue("LogWndHeight", 600));
    tableListBox.getHeader().addColumn("Time", 1, propsFile->getIntValue("LogWndTimeColumnSize", 70));
    tableListBox.getHeader().addColumn("Level", 2, propsFile->getIntValue("LogWndLevelColumnSize", 70));
    tableListBox.getHeader().addColumn("Message", 3, propsFile->getIntValue("LogWndMessageColumnSize", 70));
    tableListBox.getHeader().addListener(this);
    tableListBox.autoSizeColumn(1);
    tableListBox.autoSizeColumn(2);
    tableListBox.setModel(&logTableListBoxModel);

    setUsingNativeTitleBar(true);
    setContentOwned(&tableListBox, true);
    setResizable(true, true);
    centreWithSize(getWidth(), getHeight());
}

void LogWindow::resized()
{
    DocumentWindow::resized();
    auto* propsFile = SynthLab::getInstance()->getPropsFile();
    propsFile->setValue("LogWndWidth", getWidth());
    propsFile->setValue("LogWndHeight", getHeight());
    propsFile->saveIfNeeded();
}

void LogWindow::closeButtonPressed()
{
}

void LogWindow::tableColumnsChanged([[maybe_unused]] TableHeaderComponent* tableHeader)
{
}

void LogWindow::tableColumnsResized(TableHeaderComponent* tableHeader)
{
    auto* propsFile = SynthLab::getInstance()->getPropsFile();
    propsFile->setValue("LogWndTimeColumnSize", tableHeader->getColumnWidth(1));
    propsFile->setValue("LogWndLevelColumnSize", tableHeader->getColumnWidth(2));
    propsFile->setValue("LogWndMessageColumnSize", tableHeader->getColumnWidth(3));
    propsFile->saveIfNeeded();
}

void LogWindow::tableSortOrderChanged([[maybe_unused]] TableHeaderComponent* tableHeader)
{
}

void LogWindow::updateLog()
{
    MessageManagerLock lock;
    tableListBox.updateContent();
    tableListBox.scrollToEnsureRowIsOnscreen(tableListBox.getNumRows() - 1);
}
