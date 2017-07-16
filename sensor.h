#ifndef SENSOR_H
#define SENSOR_H
#endif

extern int sensorDist_C;
extern int sensorDist_R;
extern int sensorDist_SR;
extern int sensorDist_L;
extern int sensorDist_SL;

void readSensors();
void printSensorData();
int getObstacleC();
int getObstacleR();
int getObstacleL();
int getObstacleSR();
int getObstacleSL();

