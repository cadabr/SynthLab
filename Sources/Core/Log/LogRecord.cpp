#include "stdafx.h"
#include "LogRecord.h"
#include "LogMain.h"

using namespace std;
using namespace juce;

LogRecord::LogRecord(Level lvl)
: time(Time::getCurrentTime())
, level(lvl)
{
}

LogRecord::LogRecord(const LogRecord& r)
: time(r.time)
, level(r.level)
, message(r.message)
{
}

std::string LogRecord::StrTime() const
{
    std::stringstream res;
    res << time.getHours() << ":" << time.getMinutes() << ":" << time.getSeconds() << ":" << time.getMilliseconds();
    return res.str();
}

std::string LogRecord::StrLevel() const
{
    switch (level)
    {
    case Level::fatal:   return "fatal";
    case Level::error:   return "error";
    case Level::warning: return "warning";
    case Level::info:    return "info";
    case Level::debug:   return "debug";
    }
    return "UNKNOWN";
}

std::string LogRecord::StrMessage() const
{
    return message;
}

void LogRecord::flush()
{
    LogMain::getInstance()->Add(*this);
}
