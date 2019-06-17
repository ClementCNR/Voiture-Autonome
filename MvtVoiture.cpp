#include <Arduino.h>
#include "MvtVoiture.h"

void MvtVoitureD::forward(void)
{
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 100);
}

void MvtVoitureD::left(void)
{
  Motor.speed(MOTOR1, 80);
  Motor.speed(MOTOR2, -80);
  delay(765);
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 100);
}

void MvtVoitureD::right(void)
{
  Motor.speed(MOTOR1, -80);
  Motor.speed(MOTOR2, 80);
  delay(765);
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 100);
}

void MvtVoitureD::stopCar(void)
{
   Motor.stop(MOTOR1);
   Motor.stop(MOTOR2);
}

void MvtVoitureD::seekingPath(void)
{
   Motor.speed(MOTOR1, 80);
   Motor.speed(MOTOR2, -80);
   delay(100);
   Motor.speed(MOTOR1, -80);
   Motor.speed(MOTOR2, 80);
   delay(100);
   Motor.speed(MOTOR1, 100);
   Motor.speed(MOTOR2, 100);
   delay(100);
   Motor.stop(MOTOR1);
   Motor.stop(MOTOR2);
}

void MvtVoitureD::alignLeft(void)
{
    Motor.speed(MOTOR1, 60);
    Motor.speed(MOTOR2, -60);
    delay(50);
    Motor.speed(MOTOR1, 100);
    Motor.speed(MOTOR2, 100);
}

void MvtVoitureD::alignRight(void)
{
    Motor.speed(MOTOR1, -60);
    Motor.speed(MOTOR2, 60);
    delay(50);
    Motor.speed(MOTOR1, 100);
    Motor.speed(MOTOR2, 100);
}

int MvtVoitureD::crossroads(int inter)
{
    return inter;
}
