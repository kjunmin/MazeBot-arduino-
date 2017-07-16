#ifndef MOVEMENT_H
#define MOVEMENT_H
#endif


//global movement var
extern unsigned long accelCount;
extern bool collisionFlag;

void brake();
void initializeMotor();
void turnRightDeg(int degree);
void turnLeftDeg(int degree);
void moveForward(int dist);
void moveForwardsWithoutRamp(int dist);
bool checkObstruction();
void alignAngle();
