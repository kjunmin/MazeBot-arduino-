#include "const.h"
#include "sensor.h"
#include <SharpIR.h>

SharpIR sensor_C(SENSOR_PIN_C, 1080); 
SharpIR sensor_L(SENSOR_PIN_L, 1080); 
SharpIR sensor_SL(SENSOR_PIN_SL, 1080); 
SharpIR sensor_SR(SENSOR_PIN_SR, 1080); 
SharpIR sensor_R(SENSOR_PIN_R, 1080); 

int sensorDist_C = 0;
int sensorDist_R = 0;
int sensorDist_SL = 0;
int sensorDist_L = 0;
int sensorDist_SR = 0;

void readSensors() {
  sensorDist_C = sensor_C.distance();  
  if (sensorDist_C >= 60) {
    sensorDist_C = 60;
  }
  if (sensorDist_C <= 5) {
    sensorDist_C = 5;
  }
  sensorDist_L = sensor_L.distance();  
  if (sensorDist_L >= 60) {
    sensorDist_L = 60;
  }
  if (sensorDist_L <= 5) {
    sensorDist_L = 5;
  }
  sensorDist_SL = sensor_SL.distance();  
  if (sensorDist_SL >= 60) {
    sensorDist_SL = 60;
  }
  if (sensorDist_SL <= 5) {
    sensorDist_SL = 5;
  }
  sensorDist_SR = sensor_SR.distance(); 
  if (sensorDist_SR >= 60) {
    sensorDist_SR = 60;
  }
  if (sensorDist_SR <= 5) {
    sensorDist_SR = 5;
  } 
  sensorDist_R = sensor_R.distance(); 
  if (sensorDist_R >= 60) {
    sensorDist_R = 60;
  }
  if (sensorDist_R <= 5) {
    sensorDist_R = 5;
  } 
}

void printSensorData() {
  
  
  Serial.println(sensorDist_SL);
  Serial.println(sensorDist_L);
  Serial.println(sensorDist_C);
  Serial.println(sensorDist_R);
  Serial.println(sensorDist_SR);
  Serial.println();
  delay(2500);
}

int getObstacleC() {
  if (sensorDist_C <= 9+SENSOR_OFFSET) return 1;          //Distance away to sense 1 block for sensor x (higher than brake detection range in case of misalignment)
  else if (sensorDist_C <= 20+SENSOR_OFFSET) return 2;
  else if (sensorDist_C <= 33+SENSOR_OFFSET) return 3;
  else return -1;
}

int getObstacleR() {
  if (sensorDist_R <= 8+SENSOR_OFFSET) return 1;
  else if (sensorDist_R <= 18+SENSOR_OFFSET) return 2;
  else if (sensorDist_R <= 29+SENSOR_OFFSET) return 3;
  else return -1;
}

int getObstacleSR() {
  if (sensorDist_SR <= 8+SENSOR_OFFSET) return 1;
  else if (sensorDist_SR <= 18+SENSOR_OFFSET) return 2;
  else if (sensorDist_SR <= 29+SENSOR_OFFSET) return 3;
  else return -1;
}

int getObstacleL() {
  if (sensorDist_L <= 9+SENSOR_OFFSET) return 1;
  else if (sensorDist_L <= 20+SENSOR_OFFSET) return 2;
  else if (sensorDist_L <= 35+SENSOR_OFFSET) return 3;
  else return -1;
}

int getObstacleSL() {
  if (sensorDist_SL <= 7+SENSOR_OFFSET) return 1;
  else if (sensorDist_SL <= 14 +SENSOR_OFFSET) return 2;
  //else if (sensorDist_SL <= 29+SENSOR_OFFSET) return 3;
  else return -1;
}


