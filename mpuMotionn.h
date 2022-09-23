#pragma once

#include "mpuMotion.h"

namespace Mpu6050 {

bool motion = false;
int16_t GyX,GyY,GyZ;
int16_t GyXP,GyYP,GyZP;
bool f_data = false;

//////collision DETECTION//////
void writeRegister(uint16_t reg, byte value){
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void setInterrupt(byte threshold){
//writeRegister(MPU6050_INT_PIN_CFG, 1<<MPU6050_ACTL); // 1<<MPU6050_LATCH_INT_EN
  writeRegister(MPU6050_ACCEL_CONFIG, 0b00000001);
  writeRegister(MPU6050_WOM_THR, threshold); 
  writeRegister(MPU6050_MOT_DUR, 0b00000001);  // set duration (LSB = 1 ms)
  writeRegister(MPU6050_INT_ENABLE, 1<<MPU6050_WOM_EN);
}


void swings() {

  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(0x3B);  
  Wire.endTransmission(false);
  Wire.requestFrom(MPU6050_ADDR,6,true);
  
  ////uncomment abovve
  GyX=Wire.read()<<8|Wire.read();
  GyY=Wire.read()<<8|Wire.read();
  GyZ=Wire.read()<<8|Wire.read();
  
 
  int16_t GyXD,GyYD,GyZD;
  GyXD = abs(GyX - GyXP);
  GyYD = abs(GyY - GyYP);
  GyZD = abs(GyZ - GyZP);
  
  GyXP = GyX;
  GyYP = GyY;
  GyZP = GyZ;

  if(f_data == true){
  
    if (GyXD > 1000 || GyYD > 1000 || GyZD > 2000) {
      debugln(F("\t\t\t\tmovement detected")); 
      motion = false;  
    }else{
   //   debugln(" "); 
      }
  }else{
    f_data = true; 
  }
      
}
 
void setup(){

  debugln(F("MPU6050 Motion and Collision Detection"));
  debugln(F("by Gavins Maragia"));

  debugln(F("\nStarting I2C Communication"));
  Wire.begin();
  writeRegister(MPU6050_PWR_MGT_1, 0);

    #if accident_detect_threshold > 255
    #error "accident_detect_threshold must be less than 256"
    #endif

    #if accident_detect_threshold < 1
        #error "accident_detect_threshold must be greater than 0"
    #endif

  setInterrupt(accident_detect_threshold); // set threshold
}
  
}
