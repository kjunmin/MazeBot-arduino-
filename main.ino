#include "PinChangeInterrupt.h"
#include "const.h"
#include "movement.h"
#include "main.h"
#include "sensor.h"
#include <QueueList.h>

volatile int encoder_Ticks_M1 = 0;
volatile int encoder_Ticks_M2 = 0;
volatile int mode;
bool isRunning = false;
bool printFlag = false;
char prevCommand = '\0';
int arg = 0;
int stepCM = 0;

QueueList <int> instQueue;

void setup() {
   Serial.begin(9600);
   initializeMotor();
   instQueue.setPrinter(Serial);
   Serial.setTimeout(100);
   pinMode(ENCODER_PIN_M1, INPUT);
   pinMode(ENCODER_PIN_M2, INPUT);
   attachPCINT(digitalPinToPCINT(ENCODER_PIN_M1), countRevolutions_M1, RISING);
   attachPCINT(digitalPinToPCINT(ENCODER_PIN_M2), countRevolutions_M2, RISING);
   mode = IDL;
   delay(2500);
}

void loop() {
  readInstruction();
  //printSensorData();
  getNextInstruction();
  switch(mode) {
    case IDL: 
        break;
    case FORWARD:
        //moveForward(stepCM);
        moveForward(arg);
        break;   
    case TURN_LEFT:
        turnLeftDeg(90);
        break;
    case TURN_RIGHT:
        turnRightDeg(90);
        break;
    case CALIBRATE:
        alignAngle();
        break;
    default:
        Serial.println("Incorrent mode");
  }
}



void countRevolutions_M1() {
  encoder_Ticks_M1++;
}

void countRevolutions_M2() {
  encoder_Ticks_M2++;
}

void readInstruction() {
  if (Serial.available()) {
    int numOfMovs;
    char charBuffer[3];
    charBuffer[2] = '\0';
    Serial.readBytes(charBuffer, 3);
    char command = charBuffer[0];
    //command2 = Serial.parseInt();
    switch (command) {
      case 'F':
          //numOfMovs = charBuffer[1]-48; //ASCII value is +48
          if (charBuffer[2] != '\0') {
            stepCM = (charBuffer[1]-48)*100 + (charBuffer[2] - 48)*10;
          }
          else
            stepCM = (charBuffer[1]-48)*10;
          instQueue.push(FORWARD);    
          break;
    case 'A':
          instQueue.push(TURN_LEFT);
          break;
    case 'D':
          instQueue.push(TURN_RIGHT);
          break;
    case 'S':
          readSensors();
          Serial.println(String(getObstacleL()) + ":" +getObstacleC() + ":" + getObstacleR() + ":" + getObstacleSL() + ":" + getObstacleSR());
          break;
    case 'C':
          instQueue.push(CALIBRATE);
          break;
    case 'R':
          Serial.print(prevCommand);
          if (arg != 0)  
            Serial.print(arg);
          Serial.println('D');
          break;
    case 'P':
          readSensors();
          printSensorData();
          break;
    default:
          Serial.println("Command Error");
          break;
    }
    if (command != '\0') prevCommand = command;
    if (stepCM != 0) arg = stepCM;
    command = '\0';
    stepCM = 0;
  }
}

void getNextInstruction() {
   if (!isRunning) {
     if (instQueue.isEmpty()) {
       if (printFlag){
        Serial.print(prevCommand);
        if (arg != 0)  
          Serial.print(arg/10);
        Serial.println('D');
        arg = 0;
       printFlag = false;
       }
       mode = IDL;
       stepCM=0;
     }
     else {
       mode = instQueue.pop();
       printFlag = true;
     }
   }
}





