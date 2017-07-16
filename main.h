#ifndef MAIN_H
#define MAIN_H
#endif
#include <Arduino.h> //needed for Serial.println
#include <string.h> //needed for memcpy

//global main var

extern volatile int encoder_Ticks_M1;
extern volatile int encoder_Ticks_M2;
extern volatile int mode;
extern bool isRunning;
extern int sensorDist_1;
extern int sensorDist_2;
extern int sensorDist_3;
extern int sensorDist_4;
extern int sensorDist_5;

void readInstruction();
void printSensorData();
