#include <Arduino.h>
#include "MvtVoiture.h"

void MvtVoitureD::forward(void)
{
    //Serial.println("Tout droit");
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 100);
}

void MvtVoitureD::left(void)
{
    //Serial.println("Virage a gauche");
  Motor.speed(MOTOR1, 80);//80
  Motor.speed(MOTOR2, -80);//-80
  delay(765);
  Motor.speed(MOTOR1, 100);//100
  Motor.speed(MOTOR2, 100);//100
}

void MvtVoitureD::right(void)
{
    //Serial.println("Virage a droite");
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
    //Serial.println("Cherche un chemin");
   Motor.speed(MOTOR1, 80);//80
   Motor.speed(MOTOR2, -80);//-80
   delay(100);
   Motor.speed(MOTOR1, -80);//-80
   Motor.speed(MOTOR2, 80);//80
   delay(100);
   Motor.speed(MOTOR1, 100);//100
   Motor.speed(MOTOR2, 100);
   delay(100);
   Motor.stop(MOTOR1);
   Motor.stop(MOTOR2);
}
