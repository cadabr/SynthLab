#pragma once

#include "Core/Singleton.h"
#include "Core/Log/LogRecord.h"

class LogStorage : public Singleton<LogStorage>
{
public:
    void Add(const plog::Record& rec);
    const LogRecord& Get(size_t index) const;
    size_t GetSize() const;

private:
    std::vector<LogRecord> records;
};
