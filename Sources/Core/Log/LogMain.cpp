#include "stdafx.h"
#include "LogMain.h"

JUCE_IMPLEMENT_SINGLETON(LogMain)

LogMain::LogMain()
{
}

LogMain::~LogMain()
{
    clearSingletonInstance();
}

void LogMain::initialize()
{
    logWindow.reset(new LogWindow("LOG"));
}

void LogMain::Show()
{
    logWindow->setVisible(true);
}

void LogMain::Hide()
{
    logWindow->setVisible(false);
}

const LogRecord& LogMain::Get(std::size_t index) const
{
    return records[index];
}

size_t LogMain::GetSize() const
{
    return records.size();
}

void LogMain::Add(const LogRecord& rec)
{
    records.emplace_back(rec);
    logWindow->updateLog();
}
