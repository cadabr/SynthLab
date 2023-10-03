#pragma once

#include "LogTableListBoxModel.h"

class LogWindow : public juce::DocumentWindow, public juce::TableHeaderComponent::Listener
{
public:
    LogWindow(juce::String name);

    void resized() override;

    void closeButtonPressed() override;

    void tableColumnsChanged(juce::TableHeaderComponent* tableHeader) override;

    void tableColumnsResized(juce::TableHeaderComponent* tableHeader) override;

    void tableSortOrderChanged(juce::TableHeaderComponent* tableHeader) override;

    void updateLog();

private:
    juce::TableListBox tableListBox;
    LogTableListBoxModel logTableListBoxModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LogWindow)
};
