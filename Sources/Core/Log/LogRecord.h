#pragma once

struct LogRecord : public plog::Record
{
    LogRecord(const plog::Record&);
    LogRecord(const LogRecord&);

    std::string StrTime() const;
    std::string StrLevel() const;
    std::string StrMessage() const;

private:
    std::string message;
};
