#include "main.h"
#include "app.hpp"
#include "i2c.h"

#ifdef __cplusplus
extern "C"
{
#endif
    void mainCpp(void)
    {
        App &app = App::getInstance();
        if (!app.init())
        {
            Error_Handler();
        }
        while (1)
        {
            app.run();
        }
    }
    void handleErrorCpp(void)
    {
        Error_Handler();
    }
#ifdef __cplusplus
}
#endif

// This is the C++ code that will run in the main loop.
bool App::init()
{
    m_log.setLogLevel(LogLevel::log_DEBUG);
    m_log.info("Starting init");
    // Place your initialization code here.
    return true;
}

void App::run()
{
    
    // Place your main application loop logic here.
    HAL_Delay(100);
}