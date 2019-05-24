#include "sr04.h"

void hcsr04_init(){
  // 声波引脚声明
  pinMode(EchoPin1, INPUT);
  pinMode(TrigPin1, OUTPUT);
  pinMode(EchoPin2, INPUT);
  pinMode(TrigPin2, OUTPUT);
  pinMode(EchoPin3, INPUT);
  pinMode(TrigPin3, OUTPUT);
  pinMode(EchoPin4, INPUT);
  pinMode(TrigPin4, OUTPUT);

}

