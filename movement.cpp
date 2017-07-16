#include "movement.h"
#include "const.h"
#include "pid.h"
#include "main.h"
#include "DualVNH5019MotorShield.h"
#include "sensor.h"

DualVNH5019MotorShield md;


int outputSpeed_M1;
int outputSpeed_M2;
bool rightFlag = false;
bool leftFlag = false;
bool forwardFlag = false;
bool backwardFlag = false;

int target_Tick  = 0;
int target_Tick2  = 0;


void initializeMotor() {
  md.init();
}

void resetPid() {
  error = 0;
  integral = 0;
  encoder_Ticks_M1 = 0;
  encoder_Ticks_M2 = 0;
}

void alignBackward() {
  if (!backwardFlag) {
    isRunning = true;
    resetPid();
    target_Tick = 300;
    backwardFlag = true;
  }
  if (encoder_Ticks_M1 < target_Tick) {
    md.setSpeeds(ALIGNMVSPD, -ALIGNMVSPD);
  }
  else {
    backwardFlag = false;
  }
}


void resetState() {
  forwardFlag = false;
  rightFlag = false;
  leftFlag = false;
  isRunning = false;
}

void idle() {
  mode = IDL;
  resetState();
  isRunning = false;
}

void brake() {
  mode = BRAKE;
  md.setSpeeds(0 ,0);
  md.setBrakes(M1BRAKE,M2BRAKE);
  delay(120);
  idle();
}


bool checkObstruction() {   //Checks for any obstacle 1 grid away in front of any front sensor for braking
  readSensors();
  if (sensorDist_C <= BRAKE_DIST_TO_OBJECT || sensorDist_R <= BRAKE_DIST_TO_OBJECT || sensorDist_L <= BRAKE_DIST_TO_OBJECT) {
    return true;
  }
  else
    return false;
}

void turnRightDeg(int degree) {
  
  int output = 0;
  
  if (!rightFlag) {
    resetPid();
    isRunning = true;
    if (degree <= 5) target_Tick = degree * 4.07;
    else if (degree <= 10) target_Tick = degree * 4.07;
    else if (degree <= 15) target_Tick = degree * 4.07;
    else if (degree <= 30) target_Tick = degree * 4.07; //7.72
    else if (degree <= 45) target_Tick = degree * 4.07; //8.635
    else if (degree <= 60) target_Tick = degree * 4.07;
    else if (degree <= 90) target_Tick = degree * 3.84;//3.86;//4.14
    else if (degree <=180 ) target_Tick = degree * 4.35;    //tune 180
    else if (degree <=360 ) target_Tick = degree * 4.40;
    else if (degree <= 720) target_Tick = degree * 4.43;
    else if (degree <= 900) target_Tick = degree * 4.44;
    else if (degree <= 1080) target_Tick = degree * 4.44;
    else target_Tick = degree * 4.44;
    rightFlag = true;
  }

  if (encoder_Ticks_M1 < target_Tick) {
    output = PID();
    md.setSpeeds(-(TURN_SPD_M1 - output), -(TURN_SPD_M2 + output));
  }
  else {
    rightFlag = false;
    brake();
  }
}

void turnLeftDeg(int degree) {
  int output = 0;
  if (!leftFlag) {
    //Serial.println("LEFT");
    resetPid();
    isRunning = true;
    if (degree <= 5) target_Tick = degree * 4.16;
    else if (degree <= 10) target_Tick = degree * 4.16;
    else if (degree <= 15) target_Tick = degree * 4.16;
    else if (degree <= 30) target_Tick = degree * 4.16; //7.72
    else if (degree <= 45) target_Tick = degree * 4.16; //8.635
    else if (degree <= 60) target_Tick = degree * 4.16;
    else if (degree <= 90) target_Tick = degree * 3.96; //4.11
    else if (degree <=180 ) target_Tick = degree * 4.35;    //tune 180
    else if (degree <=360 ) target_Tick = degree * 4.39;
    else if (degree <= 720) target_Tick = degree * 4.41;
    else if (degree <= 900) target_Tick = degree * 4.43;
    else if (degree <= 1080) target_Tick = degree * 4.42;
    else target_Tick = degree * 4.44;
    leftFlag = true;
  }
  if (encoder_Ticks_M1 < target_Tick) {
    output = PID();
    md.setSpeeds(TURN_SPD_M1 - output, TURN_SPD_M2 + output);
  }
  else {
    leftFlag = false;
    brake();
  }
}


void moveForward(int dist) {
  int output = 0; 
  if (!forwardFlag) {
    // Loop initilization
    isRunning = true;
    resetPid();
    int cmDis = dist;
    if (cmDis<= 10) target_Tick = cmDis * 24.5; //25.5  
    else if(cmDis<=20) target_Tick = cmDis * 28.3;    
    else if(cmDis<=30) target_Tick = cmDis * 29.1;  
    else if(cmDis<=40) target_Tick = cmDis * 29.1;  
    else if(cmDis<=50) target_Tick = cmDis * 29.1; 
    else if(cmDis<=60) target_Tick = cmDis * 29.1;  
    else if(cmDis<=70) target_Tick = cmDis * 29.3;   //done
    else if(cmDis<=80) target_Tick = cmDis * 29.3; 
    else if(cmDis<=90) target_Tick = cmDis * 29.2;  
    else if(cmDis<=100) target_Tick = cmDis * 29.3;   
    else if(cmDis<=110) target_Tick = cmDis * 29.3; //done
    else if(cmDis<=120) target_Tick = cmDis * 29.5;  //done 
    else if(cmDis<=130) target_Tick = cmDis * 29.5; //done
    else if(cmDis<=140) target_Tick = cmDis * 29.6;  //done
    else if(cmDis<=150) target_Tick = cmDis * 29.5; //done
    else if(cmDis<=160) target_Tick = cmDis * 29.5; 
    else if(cmDis<=170) target_Tick = cmDis * 29.0;  
    else target_Tick = cmDis * 29.0;
    forwardFlag = true;
  }
  if (encoder_Ticks_M1 < 5)  {
    output = PID();
    md.setSpeeds(-(100 - output), 100 + output);
  }
  
  else if (encoder_Ticks_M1 < 10)  {
    output = PID(); 
    md.setSpeeds(-(200 - output), 200 + output);
  }

  else if (encoder_Ticks_M1 < 50)  {
    output = PID();
    md.setSpeeds(-(300 - output), 300 + output);
  }

  else if (encoder_Ticks_M1 < (target_Tick - 40))  {
    output = PID();
    md.setSpeeds(-(STRAIGHT_SPD_M1 - output), STRAIGHT_SPD_M2 + output);
  }
  
  else if (encoder_Ticks_M1 < target_Tick)  {
    output = PID();
    md.setSpeeds(-(180 - output), 180 + output);
  }
  else {
    forwardFlag = false;
    brake();
  }
}

void moveForwardsWithoutRamp(int dist) {
  int output; 
  if (!forwardFlag) {
   // Loop initilization
    isRunning = true;
    //Serial.println("Forwards");
    resetPid();
    int cmDis = dist;
    if (cmDis<= 10) {
    target_Tick = cmDis * 24.3; //55.4
    }
//    else if(cmDis<=20) target_Tick = cmDis * 28.3;    //done
//    else if(cmDis<=30) target_Tick = cmDis * 28.3;  //done
//    else if(cmDis<=40) target_Tick = cmDis * 28.3;  //done
//    else if(cmDis<=50) target_Tick = cmDis * 28.3;  //done
//    else if(cmDis<=60) target_Tick = cmDis * 28.3;  //done
//    else if(cmDis<=70) target_Tick = cmDis * 29.0;  //done
//    else if(cmDis<=80) target_Tick = cmDis * 29.0;  //done
//    else if(cmDis<=90) target_Tick = cmDis * 29.0;  //done
//    else if(cmDis<=100) target_Tick = cmDis * 29.0;   //
//    else if(cmDis<=110) target_Tick = cmDis * 29.0;
//    else if(cmDis<=120) target_Tick = cmDis * 29.0;   //done   max
//    else if(cmDis<=130) target_Tick = cmDis * 29.0; 
//    else if(cmDis<=140) target_Tick = cmDis * 29.0;  
//    else if(cmDis<=150) target_Tick = cmDis * 29.0;
//    else if(cmDis<=160) target_Tick = cmDis * 29.0; 
//    else if(cmDis<=170) target_Tick = cmDis * 29.0;  
//    else target_Tick = cmDis * 29.0;
    forwardFlag = true;
  }

  if(encoder_Ticks_M1 < target_Tick) {
      output = PID();
      md.setSpeeds(-(STRAIGHT_SPD_M1-output), STRAIGHT_SPD_M2+output);
  }
  else {
    forwardFlag = false;
    alignAngle();
  }
}


void alignLeft() {
  int output = 0;
  isRunning = true;
  if (!leftFlag) {   
    resetPid();
    target_Tick = 3;
    leftFlag = true;
  }
  if (encoder_Ticks_M1 < target_Tick) {
     md.setSpeeds(ALIGN_SPD, ALIGN_SPD);
  }
  else {
    leftFlag = false;
  }
}

void alignRight() {
  int output = 0;
  isRunning = true;
  if (!rightFlag) {  
    resetPid();
    target_Tick = 3;
    rightFlag = true;
  }
  if (encoder_Ticks_M1 < target_Tick) {
    md.setSpeeds(-ALIGN_SPD, -ALIGN_SPD);
  }
  else {
    rightFlag = false;
  }
}

void alignForward() {
  if (!forwardFlag) {
    isRunning = true;
    resetPid();
    target_Tick = 3;
    forwardFlag = true;
  }
  if (encoder_Ticks_M1 < target_Tick) {
    md.setSpeeds(-ALIGNMVSPD, ALIGNMVSPD);
  }
  else {
    forwardFlag = false;
  }
}



void alignAngle() {
  mode = CALIBRATE;
  int error;
  isRunning = true;
  readSensors();
  error = sensorDist_L - sensorDist_R;
      if (error >= 1){
        alignRight();
      }
      else if (error <= -1){
        alignLeft();
      }    
      else {
        if (sensorDist_L < ALIGNMENT_DIST) {
          alignBackward();
        }
        else if (sensorDist_L > ALIGNMENT_DIST) {
          alignForward();
        }        
        else {
           readSensors();
           error = sensorDist_L - sensorDist_R;
           if (error >= 1){
            alignRight();
           }
           else if (error <= -1){
             alignLeft();
          }   
            else 
             brake();
         }
      }  
     
}





