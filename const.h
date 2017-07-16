#ifndef CONST_H
#define CONST_H
#endif

//program constants
#define ENCODER_PIN_M1 		    3
#define ENCODER_PIN_M2 		    5

#define SENSOR_PIN_C 		      1
#define SENSOR_PIN_L 		      2
#define SENSOR_PIN_SL 		    3
#define SENSOR_PIN_SR 		    4
#define SENSOR_PIN_R		      5
#define SENSOR_OFFSET         5

#define IDL                   0
#define FORWARD               1
#define TURN_RIGHT            2
#define TURN_LEFT             3
#define MREVERSE              4
#define BRAKE                 5
#define CALIBRATE             6


// MOVEMENT CONSTANTS
#define STRAIGHT_SPD_M1       350 //350
#define STRAIGHT_SPD_M2       350
#define TURN_SPD_M1           350
#define TURN_SPD_M2           350
#define ALIGN_SPD             62
#define ALIGNMVSPD            120
#define M1BRAKE               355
#define M2BRAKE               348



// PID VALUES
#define KP                  9.5      //8      //0.386f
#define KI                  0.00960      //0.0143
#define KD                  0.00


// COLLISION CHECK
#define BRAKE_DIST_TO_OBJECT        10
#define ALIGNMENT_DIST              7


