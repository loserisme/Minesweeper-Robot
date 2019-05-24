#include "motor.h"

void motor_init()
{
  pinMode(left_motor1,OUTPUT);
  pinMode(left_motor2,OUTPUT);
  pinMode(right_motor1,OUTPUT);
  pinMode(right_motor2,OUTPUT);
  }

/*
 * @brief 前进函数，重载
 * @param move_speed pwm
 * @retval
 */
void goforward(int move_speed)
{
  digitalWrite(left_motor1,LOW);
  analogWrite(left_motor2,move_speed);
  digitalWrite(right_motor1,LOW);
  analogWrite(right_motor2,move_speed);
  }
 void goforward(int Lmotor_speed, int Rmotor_speed) 
 {
  analogWrite(left_motor1, 0);
  analogWrite(left_motor2, Lmotor_speed);
  digitalWrite(right_motor1, 0);
  analogWrite(right_motor2, Rmotor_speed);
  //delay_(move_time);
}

/*
 * @brief 左转函数
 * @param move_time运行时间
 * @retval
 */
 void turnleft()
 {
  analogWrite(left_motor2, 0);
  analogWrite(left_motor1, 150);
  analogWrite(right_motor1, 0);
  analogWrite(right_motor2, 150);
  }
 void turnleft(int move_speed,int move_time)
 {
  analogWrite(left_motor2, 0);
  analogWrite(left_motor1, move_speed);
  analogWrite(right_motor1, 0);
  analogWrite(right_motor2, move_speed);
  delay(move_time);
  }
 void turnleft(int move_time)
 {
  analogWrite(left_motor2, 0);
  analogWrite(left_motor1, 255);
  analogWrite(right_motor1, 0);
  analogWrite(right_motor2, 255);
  delay(move_time);
  }

/*
 * @brief 右转函数
 * @param move_time运行时间
 * @retval
 */
  void turnright(int move_speed,int move_time)
 {
  analogWrite(left_motor1, 0);
  analogWrite(left_motor2, move_speed);
  analogWrite(right_motor2, 0);
  analogWrite(right_motor1, move_speed);
  delay(move_time);
  }
 void turnright(int move_time)
 {
  analogWrite(left_motor1, 0);
  analogWrite(left_motor2, 255);
  analogWrite(right_motor2, 0);
  analogWrite(right_motor1, 255);
  delay(move_time);
  }
void turnright()
 {
  analogWrite(left_motor1, 0);
  analogWrite(left_motor2, 150);
  analogWrite(right_motor2, 0);
  analogWrite(right_motor1, 150);
  }
  /*
 * @brief 停车函数
 * @param move_time运行时间
 * @retval
 */
  void Stop(int move_time)
 {
  analogWrite(left_motor1, 1);
  analogWrite(left_motor2,0);
  analogWrite(right_motor2, 1);
  analogWrite(right_motor1, 0);
  delay(move_time);
  }
  void Stop()
 {
  analogWrite(left_motor1, 1);
  analogWrite(left_motor2,0);
  analogWrite(right_motor2, 1);
  analogWrite(right_motor1, 0);
  }
  
