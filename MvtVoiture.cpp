#include <Arduino.h>
#include "MvtVoiture.h"

/*fct to move forward*/
void MvtVoitureD::forward(void)
{
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 105);
}

/*fct to turn left*/
void MvtVoitureD::left(void)
{
  Motor.speed(MOTOR1, 80);
  Motor.speed(MOTOR2, -75);
  delay(765);
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 105);
}

/*fct to turn right*/
void MvtVoitureD::right(void)
{
  Motor.speed(MOTOR1, -80);
  Motor.speed(MOTOR2, 85);
  delay(765);
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 105);
}

/*fct to stop the car*/
void MvtVoitureD::stopCar(void)
{
   Motor.stop(MOTOR1);
   Motor.stop(MOTOR2);
}

/*fct to find a path*/
void MvtVoitureD::seekingPath(void)
{
   Motor.speed(MOTOR1, 80);
   Motor.speed(MOTOR2, -75);
   delay(100);
   Motor.speed(MOTOR1, -80);
   Motor.speed(MOTOR2, 85);
   delay(100);
   Motor.speed(MOTOR1, 100);
   Motor.speed(MOTOR2, 105);
   delay(100);
   Motor.stop(MOTOR1);
   Motor.stop(MOTOR2);
}

/*fct to correct the path to the left*/
void MvtVoitureD::alignLeft(void)
{
    Motor.speed(MOTOR1, 60);
    Motor.speed(MOTOR2, -55);
    delay(50);
    Motor.speed(MOTOR1, 100);
    Motor.speed(MOTOR2, 105);
}

/*fct to correct the path to the right*/
void MvtVoitureD::alignRight(void)
{
    Motor.speed(MOTOR1, -60);
    Motor.speed(MOTOR2, 65);
    delay(50);
    Motor.speed(MOTOR1, 100);
    Motor.speed(MOTOR2, 105);
}

/*fct who return the type of crossroads*/
int MvtVoitureD::crossroads(int inter)
{
    return inter;
}
