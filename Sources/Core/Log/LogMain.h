#pragma once

#include "Core/Log/LogMain.h"
#include "Core/Log/LogWindow.h"
#include "Core/Log/LogRecord.h"

class LogMain
{
public:
    JUCE_DECLARE_SINGLETON(LogMain, false)

    ~LogMain();

    void initialize();

    void Show();

    void Hide();

    const LogRecord& Get(std::size_t index) const;
    size_t GetSize() const;

    void Add(const LogRecord& rec);

protected:
    LogMain();

private:
    std::unique_ptr<LogWindow> logWindow;
    std::vector<LogRecord> records;
};

