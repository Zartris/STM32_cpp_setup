#pragma once
#include "BNO085.hpp"
#include "BNO085_I2C.hpp"
#include "BNO085_Registers.hpp"

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
    BNO085 *imu1;
    BNO085 *imu2;
};
