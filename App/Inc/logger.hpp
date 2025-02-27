#pragma once
#include <cstdio>
#include <cstdarg>
#include <cstring>

enum class LogLevel
{
    log_DEBUG, // DEBUG is already defined somewhere, so we use log_DEBUG instead
    log_INFO,
    log_WARNING,
    log_ERROR
};

class Logger
{
public:
    Logger(LogLevel level) : logLevel(level) {}
    Logger() : logLevel(LogLevel::log_WARNING) {}

    void setLogLevel(LogLevel level)
    {
        logLevel = level;
    }

    void debug(const char *format, ...)
    {
        if (logLevel <= LogLevel::log_DEBUG)
        {
            va_list args;
            va_start(args, format);
            log("DEBUG", format, args);
            va_end(args);
        }
    }

    void info(const char *format, ...)
    {
        if (logLevel <= LogLevel::log_INFO)
        {
            va_list args;
            va_start(args, format);
            log("INFO", format, args);
            va_end(args);
        }
    }

    void warning(const char *format, ...)
    {
        if (logLevel <= LogLevel::log_WARNING)
        {
            va_list args;
            va_start(args, format);
            log("WARNING", format, args);
            va_end(args);
        }
    }

    void error(const char *format, ...)
    {
        if (logLevel <= LogLevel::log_ERROR)
        {
            va_list args;
            va_start(args, format);
            log("ERROR", format, args);
            va_end(args);
        }
    }

protected:
    LogLevel logLevel;

    virtual void log(const char *level, const char *format, va_list args)
    {
        printf("[%s] ", level);
        vprintf(format, args);
        printf("\n");
    }
};

class UARTLogger : public Logger
{
public:
    UARTLogger(UART_HandleTypeDef *uartHandle, LogLevel level = LogLevel::log_WARNING)
        : Logger(level), huart(uartHandle) {}

protected:
    void log(const char *level, const char *format, va_list args) override
    {
        char buffer[256];
        int len = snprintf(buffer, sizeof(buffer), "[%s] ", level);
        vsnprintf(&buffer[len], sizeof(buffer) - len, format, args);
        // Append newline if needed
        len = strlen(buffer);
        if (len < (int)sizeof(buffer) - 1)
        {
            buffer[len++] = '\n';
            // buffer[len++] = '\n';
            // buffer[len] = '\r';
        }
        // Transmit buffer over UART
        if (HAL_UART_Transmit(huart, reinterpret_cast<uint8_t *>(buffer), len, HAL_MAX_DELAY) != HAL_OK)
        {
            // Handle transmission error
            printf("UART transmission error\n");
        }
    }

private:
    UART_HandleTypeDef *huart;
};