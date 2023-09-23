#pragma once

class LogTableListBoxModel : public juce::TableListBoxModel
{
public:
    LogTableListBoxModel();
    ~LogTableListBoxModel() override;

    int getNumRows() override;
    void paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

private:
    juce::Font font{ 14.0f };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LogTableListBoxModel)
};
