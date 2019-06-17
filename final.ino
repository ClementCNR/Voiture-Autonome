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
  Serial.begin(9600);
  pinMode(cptGauche, INPUT);
  pinMode(cptGaucheMilieu, INPUT);
  pinMode(cptDroiteMilieu, INPUT);
  pinMode(cptDroite, INPUT);
  Motor.begin(I2C_ADDRESS);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
  }

void loop()
{
  int valGauche = digitalRead(cptGauche);
  int valGaucheMilieu = digitalRead(cptGaucheMilieu);
  int valDroiteMilieu = digitalRead(cptDroiteMilieu);
  int valDroite = digitalRead(cptDroite);

  if(valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == LOW)
  {
    Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("Tout droit");
    MvtVoiture.forward();
    MvtVoiture.crossroads(1);
  }
  else if(valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == LOW)
  {
    MvtVoiture.alignRight();
    Serial.println("alignement vers la gauche");
  }
  else if(valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == LOW)
  {
    MvtVoiture.alignLeft();
    Serial.println("alignment vers la droite");
  }
  else if(valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == LOW && valDroite == HIGH)
  {
    Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("droite");
    MvtVoiture.right();
    MvtVoiture.crossroads(3);
  }
  else if(valGauche == HIGH && valGaucheMilieu == LOW && valDroiteMilieu == LOW && valDroite == LOW)
  {
    Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("gauche");
    MvtVoiture.left();
    MvtVoiture.crossroads(2);
  }
  else if(valGauche == HIGH && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == HIGH)
  {
    Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println(" Tout droit / gauche / droite");

    MvtVoiture.crossroads(7);

    int nbreAleatoire = random(1, 4);

    if (nbreAleatoire == 1){
     MvtVoiture.left();
     Serial.println("La voiture a choisi de tourner a gauche");
     
    }
    else if(nbreAleatoire == 2){
     MvtVoiture.right();
     Serial.println("La voiture a choisi de tourner a droite");
    }
    else{
     MvtVoiture.forward();
     Serial.println("La voiture a choisi d aller tout droit");
    }

  }
    else if(valGauche == HIGH && valGaucheMilieu == LOW && valDroiteMilieu == LOW && valDroite == HIGH)
  {
    Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("droite / gauche");

    MvtVoiture.crossroads(4);

    int nbreAleatoire = random(1, 3);

    if (nbreAleatoire == 1){
        MvtVoiture.left();
        Serial.println("La voiture a choisi de tourner a gauche");
    }
    else{
        MvtVoiture.right();
        Serial.println("La voiture a choisi de tourner a droite");
    }
  }
    else if((valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == HIGH) || (valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == HIGH) || (valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == HIGH))
  {
    Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("droite / tout droit");

    MvtVoiture.crossroads(6);

    int nbreAleatoire = random(1, 3);

    if (nbreAleatoire == 1){
      MvtVoiture.right();
      Serial.println("La voiture a choisi de tourner a droite");
    }
    else{
      MvtVoiture.forward();
      Serial.println("La voiture a choisi d aller tout droit");
    }

  }
      else if((valGauche == HIGH && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == LOW) || (valGauche == HIGH && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == LOW) || (valGauche == HIGH && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == LOW))
  {
        Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("gauche / tout droit");

    MvtVoiture.crossroads(5);

    int nbreAleatoire = random(1, 3);

    if (nbreAleatoire == 1){
       MvtVoiture.left();
       Serial.println("La voiture a choisi de tourner a gauche");
    }
    else{
        MvtVoiture.forward();
        Serial.println("La voiture a choisi de tourner a droite");
    }
  }
   else
  {
        Serial.print(valGauche);
    Serial.print(" : ");
    Serial.print(valGaucheMilieu);
    Serial.print(" : ");
    Serial.print(valDroiteMilieu);
    Serial.print(" : ");
    Serial.print(valDroite);
    Serial.print(" : ");
    Serial.println("Cherche un chemin");
    MvtVoiture.seekingPath();

    MvtVoiture.crossroads(0);    
  }
  
}
