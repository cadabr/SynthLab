#pragma once

#include "Core/Singleton.h"
#include "LogStorage.h"

class LogAppender : public plog::IAppender, public Singleton<LogAppender>
{
public:
    void write(const plog::Record& record) override;
};
