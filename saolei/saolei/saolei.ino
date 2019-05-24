#include "motor.h"
#include "JY901.h"
#include "sr04.h"
#include <Wire.h>
#include "PID_v1.h"
#define Speed  150

// b用来记录偏航角的差值，flag用来判断朝向，numflag标记位，用来判断雷的数量
int b, flag = 1, numflag = 1;
int judgeDirection = 0;   // 用来判断小车转向的
float yaw_value, Y_aw;
double duration, abs_duration, Setpoint, Setpoint1, val_output, val1_output; //the number of the pulses
double Kp = 5.5, Ki = 0, Kd = 0;
PID myPID(&abs_duration, &val_output, &Setpoint, Kp, Ki, Kd, DIRECT);
PID PID1(&abs_duration, &val1_output, &Setpoint1, Kp, Ki, Kd, DIRECT);

// 超声波的距离
int dis2 = 100;

// 两个时间
float start = 0;
float now = 0;

// rfid卡读出来的值
int val = -1;
// 读到多少雷了
int num = 0;

void data()
{
  JY901.GetAngle();   //角度获取
  Y_aw = (float)JY901.stcAngle.Angle[2] / 32768 * 180;
}

// 函数功能：输入超声波的引脚，返回距离
float distance(int trig , int echo) {
  float distance;
  digitalWrite(trig, HIGH); //产生一个10US的高脉冲去
  delayMicroseconds(2);
  digitalWrite(trig, LOW);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  distance = pulseIn(echo, HIGH) / 58.00; //检测脉冲宽度，并计算出距离
  return distance;
}

// 输入参数，然后就可以转什么弯
void turnfun(int judgeDirection) {
  //  Serial1.println("enter the turn function");
  int juageValue;
  if (judgeDirection % 4 == 0 || judgeDirection % 4 == 2)
    juageValue = 90;
  if (judgeDirection % 4 == 1)
    juageValue = 180;
  if (judgeDirection % 4 == 3)
    juageValue = 0;

  data();
  yaw_value = Y_aw;
  do {
    if (judgeDirection % 4 < 2)
      turnleft();
    if (judgeDirection % 4 >= 2)
      turnright();
    data();
    yaw_value = Y_aw;
    //Serial.print(33);
    b = (abs)((int)yaw_value - (int)Setpoint);
    //    Serial.print("  ");
    //    Serial.println(a);
  }
  while (b < juageValue - 3 || b > juageValue + 3); //while (b < 87 || a > 93 || a < 267 || a > 273)
}

// 函数功能：用来判断扫到雷没有以及扫到的个数
void judge() {
  val = Serial3.read(); // read the input pin
  if (val != -1 && val != 0) {
    num++;
  }
  if (num % 10 == 0) {
    num = num / 10;
  }
}


//=======================================主函数部分==========================================

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial3.begin(9600);
  JY901.StartIIC();
  for (int i = 0; i < 500; i++)data(); //滤波
  yaw_value = Y_aw;
  Setpoint = yaw_value;
  myPID.SetTunings(Kp, Ki, Kd);
  myPID.SetOutputLimits(-105, 105);
  myPID.SetMode(AUTOMATIC);//设置PID为自动模式
  myPID.SetSampleTime(100);//设置PID采样频率为100ms
  start = millis();
  // 让小车缓缓  不然就乱走了
  delay(1000);
}

void loop()
{
  // 判断雷的部分
  judge();
  if (num == numflag) {
    numflag++;
    Stop(1000);
  }
  if (num == 4)
    Stop(10000);

  now = millis();

  // 使小车直走
  data();
  abs_duration = (double)Y_aw;
  if (flag % 2 != 0) {
    myPID.Compute();
    goforward(Speed - val_output, Speed + val_output);
  }
  else if (flag % 2 == 0) {
    PID1.Compute();
    goforward(Speed - val1_output, Speed + val1_output);
  }

//  用来判断小车转弯
  dis2 = distance(TrigPin1, EchoPin1);
  if (dis2 > 0 && dis2 < 20  && (now - start) > 6000) {
    turnfun(judgeDirection);
    judgeDirection++;
    goforward(150, 165);
    delay(1000);
    turnfun(judgeDirection);
    judgeDirection++;
    flag++;
    start = millis();
    goforward(Speed, Speed + 10);
    delay(100);
    data();
    yaw_value = Y_aw;
    Setpoint1 = yaw_value;
    PID1.SetTunings(Kp, Ki, Kd);
    PID1.SetOutputLimits(-105, 105);
    PID1.SetMode(AUTOMATIC);//设置PID为自动模式
    PID1.SetSampleTime(100);//设置PID采样频率为100ms
  }

}
