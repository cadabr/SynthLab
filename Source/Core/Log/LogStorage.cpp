#include "stdafx.h"
#include "LogStorage.h"

void LogStorage::Add(const plog::Record& rec)
{
	records.push_back(rec);
}

const LogRecord& LogStorage::Get(size_t index) const
{
	return records[index];
}

size_t LogStorage::GetSize() const
{
	return records.size();
}