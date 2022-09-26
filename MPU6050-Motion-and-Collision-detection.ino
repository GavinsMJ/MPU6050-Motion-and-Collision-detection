/*
  Accident detection and motion detection
 
  Author: Gavins Maragia 
  GITHUB: https://github.com/GavinsMJ
*/
#define  DEBUG_accel  1                  //debug statements 1 = ON, 0 = OFF 

#define MPU6050_ADDR              0x68 // Alternatively set AD0 to HIGH  --> Address = 0x69

#define MPU_int                   14   // pin connected to mpu6050 int pin 
#define accident_detect_threshold 255  //between 1 <-> 255 (1024 mg)


#include "Wire.h"
#include "mpuMotionn.h"

bool  Collision_Event = false;

void collision(){
  Serial.println(F("Accident detected"));
  Collision_Event = true;
  detachInterrupt(MPU_int);
}

void setup() {
  
  Serial.begin(115200);
  delay(100);
  Mpu6050::setup();
  attachInterrupt(digitalPinToInterrupt(MPU_int), collision, RISING);  // attach interrupt to accident detection pin
  
}

void loop(){

    Mpu6050::swings();
    // if collision is detected
    if(Collision_Event == true){  

        //function to be executed when collision is detected --for example send data to server or send sms
        //service_collision();

        Collision_Event = false;
        attachInterrupt(digitalPinToInterrupt(MPU_int), collision, RISING);  // attach interrupt to accident detection pin
    }
    // if motion is detected
    if (Mpu6050::motion == true){  

        //function to be executed when motion is detected 
        //service_motion();
        
        Serial.println(F("Motion detected"));

        Mpu6050::motion = false;
   }

   //add more code...

   

   // to read more data for x,y,z axis uncomment the below code
   //int16_t GyX,GyY,GyZ;
   //GyX = Mpu6050::GyX;
   //GyY = Mpu6050::GyY;
   //GyZ = Mpu6050::GyZ;

}

