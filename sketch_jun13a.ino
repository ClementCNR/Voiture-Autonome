#include <MvtVoiture.h>

//instantiation des pin des moteurs
const int leftengpin = 5;
const int rightengpin = 6;
//instantiation des pin des capteur de lignes
const int cpt1 = 1;
const int cpt2 = 2;
const int cpt3 = 3;
const int cpt4 = 4;
//instantiation du pin du capteur IR
const int ir = 7;
MvtVoiture_(12, 13);

void setup()
{
  pinMode(leftengpin, OUTPUT);
  pinMode(rightengpin, OUTPUT);
  pinMode(cpt1, INPUT);
  pinMode(cpt2, INPUT);
  pinMode(cpt3, INPUT);
  pinMode(cpt4, INPUT);
  /*int cpt1val = digitalRead(cpt1);
  int cpt2val = digitalRead(cpt2);
  int cpt3val = digitalRead(cpt3);
  int cpt4val = digitalRead(cpt4);*/
}

void loop()
{
  int cpt1val = digitalRead(cpt1);
  int cpt2val = digitalRead(cpt2);
  int cpt3val = digitalRead(cpt3);
  int cpt4val = digitalRead(cpt4);

  if ((cpt1val) == 0 && (cpt2val) == 1 && (cpt3val) == 1 && (cpt4val) == 0)//ligne au millieu
    {
      Serial.println("Forward");
      MvtVoiture_.forward();
    }
    else if ((cpt1val) == 1 && (cpt2val) == 0 && (cpt3val) == 0 && (cpt4val) == 0)
    {
      Serial.println("Left");
      MvtVoiture_.left();
    }
    else if ((cpt1val) == 0 && (cpt2val) == 0 && (cpt3val) == 0 && (cpt4val) == 1)
    {
      Serial.println("Right");
      MvtVoiture_.right();
    }
    else
    {
      Serial.println("Unknow Path");
      MvtVoiture_.seekingPath();
    }
}
