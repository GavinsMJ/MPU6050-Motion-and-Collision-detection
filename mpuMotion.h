#pragma once 

//by GM 
//GITHUB https://github.com/GavinsMJ

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#if DEBUG_accel == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif


 //MPU6050
#define MPU6050_ACCEL_CONFIG      0x1C // Accelerometer Configuration Register
#define MPU6050_PWR_MGT_1         0x6B // Power Management 1 Register 
#define MPU6050_INT_PIN_CFG       0x37 // Interrupt Pin / Bypass Enable Configuration Register
#define MPU6050_INT_ENABLE        0x38 // Interrupt Enable Register
#define MPU6050_LATCH_INT_EN      0x05 // Latch Enable Bit for Interrupt 
#define MPU6050_ACTL              0x07 // Active-Low Enable Bit
#define MPU6050_WOM_EN            0x06 // Wake on Motion Enable bit
#define MPU6050_WOM_THR           0x1F // Wake on Motion Threshold Register
#define MPU6050_MOT_DUR           0x20 // Motion Detection Duration Register
#define MPU6050_ACCEL_INTEL_CTRL  0x69 // Accelaration Interrupt Control Register
#define MPU6050_SIGNAL_PATH_RESET 0x68 // Signal Path Reset Register

