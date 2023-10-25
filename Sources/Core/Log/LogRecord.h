#pragma once

#include <string>

class LogRecord
{
public:
    enum class Level
    {
        fatal,
        error,
        warning,
        info,
        debug,
    };

    LogRecord(Level lvl);

    LogRecord(const LogRecord&);

    template<typename T, typename... Args>
    void put(T t, Args... args)
    {
        buff << t << " ";
        static const int size = sizeof...(Args);
        if constexpr (size)
            put(args...);
        else
        {
            message = buff.str();
            buff.clear();
            flush();
        }
    }

    std::string StrTime() const;
    std::string StrLevel() const;
    std::string StrMessage() const;

private:
    void flush();

private:
    juce::Time    time;
    Level         level;
    std::string   message;
    std::stringstream buff;
};

#define LOGD(...) LogRecord(LogRecord::Level::debug).put(__VA_ARGS__)
#define LOGI(...) LogRecord(LogRecord::Level::info).put(__VA_ARGS__)
#define LOGW(...) LogRecord(LogRecord::Level::warning).put(__VA_ARGS__)
#define LOGE(...) LogRecord(LogRecord::Level::error).put(__VA_ARGS__)
#define LOGF(...) LogRecord(LogRecord::Level::fatal).put(__VA_ARGS__)
