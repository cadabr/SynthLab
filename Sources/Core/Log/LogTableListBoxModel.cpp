#include <JuceHeader.h>
#include "LogTableListBoxModel.h"
#include "Core/Log/LogMain.h"

LogTableListBoxModel::LogTableListBoxModel()
{
}

LogTableListBoxModel::~LogTableListBoxModel()
{
}

int LogTableListBoxModel::getNumRows()
{
    return static_cast<int>(LogMain::getInstance()->GetSize());
}

void LogTableListBoxModel::paintRowBackground(juce::Graphics& g, int rowNumber, [[maybe_unused]]int width, [[maybe_unused]]int height, bool rowIsSelected)
{
    //auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId).interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(juce::Colours::lightblue/*alternateColour*/);
}

void LogTableListBoxModel::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, [[maybe_unused]]bool rowIsSelected)
{
    //g.setColour(rowIsSelected ? juce::Colours::darkblue : getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setColour(juce::Colours::darkblue);
    g.setFont(font);

    std::string text;
    switch (columnId)
    {
    case 1:
        text = LogMain::getInstance()->Get(rowNumber).StrTime();
        break;
    case 2:
        text = LogMain::getInstance()->Get(rowNumber).StrLevel();
        break;
    case 3:
        text = LogMain::getInstance()->Get(rowNumber).StrMessage();
        break;
    default:
        break;
    }

    g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);

    //g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.setColour(juce::Colours::black);
    g.fillRect(width - 1, 0, 1, height);
}
