#include "stdafx.h"
#include "LogStorage.h"

LogRecord::LogRecord(const plog::Record& pr)
: plog::Record(pr.getSeverity(), pr.getFunc(), pr.getLine(), pr.getFile(), pr.getObject(), pr.getInstanceId())
, message(plog::util::toNarrow(pr.getMessage(), CP_UTF8))
{
}

LogRecord::LogRecord(const LogRecord& r)
: plog::Record(r.getSeverity(), r.getFunc(), r.getLine(), r.getFile(), r.getObject(), r.getInstanceId())
, message(r.StrMessage())
{
}

std::string LogRecord::StrTime() const
{
    char timeString[std::size("%H:%M:%S")];
    std::strftime(std::data(timeString), std::size(timeString), "%H:%M:%S", std::gmtime(&getTime().time));

    std::stringstream res;
    res << timeString << ":" << getTime().millitm;
    return res.str();
}

std::string LogRecord::StrLevel() const
{
    return plog::severityToString(getSeverity());
}

std::string LogRecord::StrMessage() const
{
    return message;
}
