#include "const.h"
#include "main.h"

double error = 0.0;
double integral = 0.0;


double PID() {
  double calcResult, last_tick_M1;
  double kp, ki, kd, p, i, d;

  kp = KP;
  ki = KI;
  kd = KD;

  error = encoder_Ticks_M1 - encoder_Ticks_M2;
  integral += error;

  p = error * kp;
  i = integral * ki;
  d = (last_tick_M1 - encoder_Ticks_M1) * kd;
  calcResult = p + i + d;

  last_tick_M1 = encoder_Ticks_M1;

  return calcResult;
}

