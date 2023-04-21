#pragma once

#include "LogTableListBoxModel.h"

class LogWindow : public juce::DocumentWindow
{
public:
    LogWindow(juce::String name);

    void closeButtonPressed() override;

private:
    juce::TableListBox tableListBox;
    LogTableListBoxModel logTableListBoxModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LogWindow)
};
