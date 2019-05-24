#ifndef _MOTOR_H
#define _MOTOR_H
#include "arduino.h"
#define left_motor1     7
#define left_motor2     8
#define right_motor1    9
#define right_motor2    10

void motor_init();
void goforward(int move_speed);
void goforward(int Lmotor_speed, int Rmotor_speed);
void turnleft();
void turnleft(int move_time);
void turnleft(int move_speed,int move_time);
void turnright();
void turnright(int move_time);
void turnright(int move_speed,int move_time);
void Stop(int move_time);
void Stop();
#endif
