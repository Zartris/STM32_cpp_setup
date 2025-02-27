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

bool App::init()
{
    // Initialize both IMUs with different I2C addresses
    static BNO085_I2C imu1_i2c(&hi2c1, BNO085_I2C_ADDR_0); // IMU 1
    static BNO085_I2C imu2_i2c(&hi2c1, BNO085_I2C_ADDR_1); // IMU 2

    static BNO085 imu1_obj(&imu1_i2c);
    static BNO085 imu2_obj(&imu2_i2c);

    imu1 = &imu1_obj;
    imu2 = &imu2_obj;

    if (!imu1->begin() || !imu2->begin())
        return false;

    // Enable Acceleration, Gyro, and Quaternion at 100Hz (10,000µs interval)
    imu1->setFeature(BNO085_FEATURE_ACCELEROMETER, 10000);
    imu1->setFeature(BNO085_FEATURE_GYROSCOPE, 10000);
    imu1->setFeature(BNO085_FEATURE_ROTATION_VECTOR, 10000);

    imu2->setFeature(BNO085_FEATURE_ACCELEROMETER, 10000);
    imu2->setFeature(BNO085_FEATURE_GYROSCOPE, 10000);
    imu2->setFeature(BNO085_FEATURE_ROTATION_VECTOR, 10000);

    // Enable dynamic calibration
    imu1->enableDynamicCalibration();
    imu2->enableDynamicCalibration();
    printf("Dynamic Calibration Enabled!\n");

    return true;
}

void App::run()
{
    IMU_Data imu1_data, imu2_data;

    // Read IMU data
    imu1->getIMUData(imu1_data);
    imu2->getIMUData(imu2_data);

    // Print sensor values
    printf("IMU1 Accel: (%.2f, %.2f, %.2f) | Gyro: (%.2f, %.2f, %.2f)\n",
           imu1_data.accel_x, imu1_data.accel_y, imu1_data.accel_z,
           imu1_data.gyro_x, imu1_data.gyro_y, imu1_data.gyro_z);

    printf("IMU2 Accel: (%.2f, %.2f, %.2f) | Gyro: (%.2f, %.2f, %.2f)\n",
           imu2_data.accel_x, imu2_data.accel_y, imu2_data.accel_z,
           imu2_data.gyro_x, imu2_data.gyro_y, imu2_data.gyro_z);

    HAL_Delay(100); // 100ms delay
}
