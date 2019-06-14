#include <Arduino.h>
#include "MvtVoiture.h"

MvtVoiture_::MvtVoiture_(int pin1, int pin2)
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  leftengpin = pin1;  
  rightengpin = pin2;
}

void MvtVoiture_::forward(void)
{
  digitalWrite(leftengpin, HIGH);
  digitalWrite(rightengpin, HIGH);
}

void MvtVoiture_::left(void)
{
  digitalWrite(leftengpin, LOW);
  digitalWrite(rightengpin, HIGH);
}

void MvtVoiture_::right(void)
{
  digitalWrite(rightengpin, LOW);
  digitalWrite(leftengpin, HIGH);
}

void MvtVoiture_::stopCar(void)
{
  digitalWrite(leftengpin, LOW);
  digitalWrite(rightengpin, LOW);
}

void MvtVoiture_::seekingPath(void)
{
  digitalWrite(leftengpin, LOW);
  digitalWrite(rightengpin, HIGH);
}
