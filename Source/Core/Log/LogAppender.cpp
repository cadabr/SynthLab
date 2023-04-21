#include "stdafx.h"
#include "LogAppender.h"
#include "LogStorage.h"

void LogAppender::write(const plog::Record& record)
{
    LogStorage::getInstance().Add(record);
}
