#ifndef _SR04_H
#define _SR04_H
#include "arduino.h"


// 声波的引脚 1 2是前面两个   3是左边  4是右边
#define EchoPin1  11
#define TrigPin1  12
#define EchoPin2  3
#define TrigPin2  4
#define EchoPin3  A1
#define TrigPin3  A2
#define EchoPin4  A3
#define TrigPin4  A4


void hcsr04_init();





















#endif
