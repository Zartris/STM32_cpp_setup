#pragma once
#include "logger.hpp"

class App
{
public:
    // Singleton pattern
    static App &getInstance()
    {
        static App instance;
        return instance;
    }
    bool init();
    void run();

private:
    UARTLogger m_log();
};
