#include <MvtVoiture.h>
#define I2C_ADDRESS 0x0f

//instantiation des pin des capteur de lignes
const int cptGauche = 4;
const int cptGaucheMilieu = 8;
const int cptDroiteMilieu = 7;
const int cptDroite = 3;
//instantiation du pin du capteur IR
const int ir = 7;

void setup()
{
  pinMode(cptGauche, INPUT);
  pinMode(cptGaucheMilieu, INPUT);
  pinMode(cptDroiteMilieu, INPUT);
  pinMode(cptDroite, INPUT);
  Motor.begin(I2C_ADDRESS);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  /*int cpt1val = digitalRead(cpt1);
  int cpt2val = digitalRead(cpt2);
  int cpt3val = digitalRead(cpt3);
  int cpt4val = digitalRead(cpt4);*/
}

void loop()
{
  int valGauche = digitalRead(cptGauche);
  int valGaucheMilieu = digitalRead(cptGaucheMilieu);
  int valDroiteMilieu = digitalRead(cptDroiteMilieu);
  int valDroite = digitalRead(cptDroite);

  if(valGaucheMilieu == HIGH || valDroiteMilieu == HIGH)
  {
    MvtVoiture.forward();
  }
  else if(valDroite == HIGH)
  {
    MvtVoiture.right();
  }
  else if(valGauche == HIGH)
  {
    MvtVoiture.left();
  }
  else
  {
    MvtVoiture.seekingPath();
  }
  
}
