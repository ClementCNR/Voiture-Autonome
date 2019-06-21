#include <MvtVoiture.h>
#include <Points.h>
#include <FreqCounter.h>
#include <VirtualWire.h> // On inclus la librairie VirtualWire
#include <VirtualWire_Config.h>
#define I2C_ADDRESS 0x0f
#define DEPARTURE_POINT 1
#define ARRIVAL_POINT 11 

//Initialisation des pin des capteur de ligne
const int cptGauche = 4;
const int cptGaucheMilieu = 8;
const int cptDroiteMilieu = 7;
const int cptDroite = 3;

//Initialisation liaison radio
const int RF_TX_PIN = 6;
//const char *msg = "Bonjour"; // Tableau qui contient notre message
float valeur = 0.0;


//Pin capteur vitesse
const int pinCptVitesse = 2;     //Sortie de la fourche pin2
//Capteur vitesse
const float roue = 20;          //nb de cran par roue
const float periRoue = 18.84;      //environ perimetre de la roue en cm
boolean EtatFourche = LOW;
boolean roueActive = false;
static int nbCran = 0;
float distParcourue = 0;
unsigned long t1 = micros();
unsigned long t2 = micros();
boolean temps = LOW;
unsigned long t3 = 0;
float v = 0.0;
float TTS = 0.0;
float rps = 0.0;


/*//FreqCounter
unsigned long frq;    //fréquence mesurée
int cnt;              //nombre de mesures réalisées
int encoches = 20; //nombre d encoches de la roue codeuse (1 ou plus)
float trmin;  //vitesse de rotation en tour/min
float ms; // vitesse en m/s*/


//Initialisation du pin du capteur IR
const int ir = 1;
int distObstacleIR = 0;
char msgIR = "";

//Initialisation des variables pour le pathfinding
const int autonomus = 1;
char* steps = NULL;
Point points[16];
char numberOfSteps = 0;
char stepNumber = 0;
char actualPoint = 0;
char nextPoint = 0;
char finished = 0;
char lastPoint14 = 0;

void setup()
{
  //connection au port série
  Serial.begin(9600);
  
  //initialisation des pin des capteurs
  pinMode(cptGauche, INPUT);
  pinMode(cptGaucheMilieu, INPUT);
  pinMode(cptDroiteMilieu, INPUT);
  pinMode(cptDroite, INPUT);
  
  //initialisation des moteurs
  Motor.begin(I2C_ADDRESS);
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);

  //Capteur vitesse
  pinMode(pinCptVitesse, INPUT);
  attachInterrupt(0, compterCran, CHANGE);

  //Capteur IR
  pinMode(ir, INPUT);

  //Liason radio
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);     // initialisation de la librairie VirtualWire à 2000 bauds
  
  if(autonomus == 0)
  {
    setPoints(points);
    steps = findPath(&numberOfSteps, DEPARTURE_POINT, ARRIVAL_POINT);
    actualPoint = DEPARTURE_POINT;
    int i = 0;

    for(i = 0;i < numberOfSteps;i++)
    {
       Serial.println((int)steps[i]);
    }
  }
}

//Fonction who drive the car forward until a crossroads
void Move()
{
  //Drive forward
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 105);
  boolean ok = true;
  
  while(ok)
  {
    int valGauche = digitalRead(cptGauche);
    int valGaucheMilieu = digitalRead(cptGaucheMilieu);
    int valDroiteMilieu = digitalRead(cptDroiteMilieu);
    int valDroite = digitalRead(cptDroite);

    //If the car isnt well align 
    if(valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == LOW)
    {
      MvtVoiture.alignRight();
    }
    //Same
    else if(valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == LOW)
    {
       MvtVoiture.alignLeft();
    }

    //If there is a crossroad
    else if((valGauche != LOW && valGaucheMilieu != HIGH && valDroiteMilieu != HIGH && valDroite != LOW) || (valGauche != LOW && valGaucheMilieu != HIGH && valDroiteMilieu != LOW && valDroite != LOW) || (valGauche != LOW && valGaucheMilieu != LOW && valDroiteMilieu != HIGH && valDroite != LOW) || (valGauche != LOW && valGaucheMilieu != LOW && valDroiteMilieu != LOW && valDroite != LOW))
    {
      ok = false;
    }
  }
  //Stop the car
  MvtVoiture.stopCar();
}



//fct qui compte le nombre de cran
void compterCran(){
  EtatFourche = digitalRead(pinCptVitesse);
  if (EtatFourche == HIGH) {     
        roueActive = true; 
  } 
  else 
  {
       if (roueActive == true)
       {
           nbCran++;
       }
  }
}




void loop()
{
  
  //INFRAROUGE
  distObstacleIR = analogRead(ir);
  if(distObstacleIR <= 300){
    Serial.print(distObstacleIR);
    Serial.println(" <= 300 : Je peut me garer");
      }
  else{
    Serial.print(distObstacleIR);
    Serial.println(" > 300 : Je ne peut pas me garer");
  }
  msgIR = (char)distObstacleIR;

  /*t3 = (t2 - t1);
  TTS = ((float)t3 / 1000000.0);
  v = (0.018 / (float)TTS);
  Serial.print("vitesse (en m/s) : ");
  Serial.println(v);
  //distParcourue PARCOURUE ET VITESSE
  distParcourue = ((nbCran / roue) * periRoue) / 100;
  Serial.print(distParcourue);
  Serial.println(" m");*/
  
  /*//Vérifie si un objet obture la fourche optique
  EtatFourche = digitalRead(pinCptVitesse);
  if (EtatFourche == HIGH) {     
        roueActive = true; 
  } 
  else 
  {
        if (roueActive == true)
        {
            nbCran = nbCran + 1;
            Serial.print("nombre d'encoche : ");
            Serial.println(nbCran);
            if (temps == LOW)
            {
                t1 = micros();
                temps = HIGH;
            }
            else
            {
               t2 = micros();
               temps = false;
            }
    }
  }*/
/*
  if (millis() - t1 >= 1000){
      rps = nbCran * 2 / roue;
      v = rps * periRoue;
      distParcourue = distParcourue + v;

      //Serial.print("vitesse : ");
      //Serial.println(v);
      roueActive = false;
      t1 = millis();
      nbCran = 0;
    }*/
/*
//compensation (étalonnage)
  FreqCounter::f_comp = 10; // Cal Value / Calibrate with professional Freq Counter
  // 10, 100 ou 1000 ms pour une résolution de 100, 10 et 1 Hz
  FreqCounter::start(100);  // 100 ms Gate Time

  // Attendre jusqu'à avoir un comptage terminé

  while (FreqCounter::f_ready == 0) {
    frq = FreqCounter::f_freq; // a ne pas supprimer permet de calculer le trmn

    trmin = frq / encoches * 60; //Vitesse de rotation en tour/min

    Serial.print("  tour/min: ");
    Serial.println(trmin);

    ms = (2 * PI * 0.032 * trmin / 60) * 10; // Calcul de la vitesse en m/s

    Serial.print(" vitesse en m/s: ");
    Serial.println(ms);
    delay(500);
  }*/
    
    //Serial.println(nbCran);
    v = ((nbCran / 20) * periRoue) / 100;
    Serial.print("Vitesse Instantané (m/s) : ");
    Serial.println(v);
    //distParcourue PARCOURUE ET VITESSE
    distParcourue = ((nbCran / roue) * periRoue) / 100;
    Serial.print("Distance Totale Parcourue : ");
    Serial.print(distParcourue);
    Serial.println(" m");
    nbCran = 0;
    delay(1000);


  //PATHFINDING
  if(autonomus == 1)
  {
    int valGauche = digitalRead(cptGauche);
    int valGaucheMilieu = digitalRead(cptGaucheMilieu);
    int valDroiteMilieu = digitalRead(cptDroiteMilieu);
    int valDroite = digitalRead(cptDroite);

    //Si la ligne noire est au milieu et  est droite
    if(valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == LOW)
    {
      MvtVoiture.forward();
      MvtVoiture.crossroads(1);
    }

    //Sinon si la ligne noire est légèrement sur la droite
    else if(valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == LOW)
    {
      MvtVoiture.alignRight();
    }

    //Sinon si la ligne noire est légèrement sur la gauche
    else if(valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == LOW)
    {
       MvtVoiture.alignLeft();
    }

    //Sinon si la ligne fais un virage a droite
    else if(valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == LOW && valDroite == HIGH)
    {
     MvtVoiture.right();
     MvtVoiture.crossroads(3);
    }

    //Sinon si la ligne fais un virage a gauche
    else if(valGauche == HIGH && valGaucheMilieu == LOW && valDroiteMilieu == LOW && valDroite == LOW)
    {
      MvtVoiture.left();
      MvtVoiture.crossroads(2);
    }
    
    // Sinon si la ligne noire se situe à gauche, à doite, et tout droit alors la voiture choisira le chemin à prendre
    else if(valGauche == HIGH && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == HIGH)
    {
      MvtVoiture.crossroads(7);

      //variable aléatoire pour décider le chemin a prendre
      //1 = gauche
      //2 = droite
      //3 = tout droit
      int nbreAleatoire = random(1, 4);

      if (nbreAleatoire == 1){
      MvtVoiture.left();
      }
      else if(nbreAleatoire == 2){
       MvtVoiture.right();
      }
      else{
       MvtVoiture.forward();
      }

    }

    //Sinon si la ligne noire et a gauche et a droite
    else if(valGauche == HIGH && valGaucheMilieu == LOW && valDroiteMilieu == LOW && valDroite == HIGH)
    {
      MvtVoiture.crossroads(4);

      int nbreAleatoire = random(1, 3);

      if (nbreAleatoire == 1){
          MvtVoiture.left();
       }
       else{
          MvtVoiture.right();
       }
    }

    //Sinon si la ligne noire est a droite et tout droit
    else if((valGauche == LOW && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == HIGH) || (valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == HIGH) || (valGauche == LOW && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == HIGH))
    {

      MvtVoiture.crossroads(6);

      int nbreAleatoire = random(1, 3);

      if (nbreAleatoire == 1){
        MvtVoiture.right();
      }
      else{
        MvtVoiture.forward();
     }

    }

    //Sinon si la ligne noire gauche et tout droit
    else if((valGauche == HIGH && valGaucheMilieu == HIGH && valDroiteMilieu == LOW && valDroite == LOW) || (valGauche == HIGH && valGaucheMilieu == HIGH && valDroiteMilieu == HIGH && valDroite == LOW) || (valGauche == HIGH && valGaucheMilieu == LOW && valDroiteMilieu == HIGH && valDroite == LOW))
    {
      MvtVoiture.crossroads(5);
      int nbreAleatoire = random(1, 3);
      if (nbreAleatoire == 1){
         MvtVoiture.left();
      }
      else{
          MvtVoiture.forward();
      }
   }

   //Sinon la voiture cherche un chemin
   else
   {
     MvtVoiture.seekingPath();
     MvtVoiture.crossroads(0);    
   }
 }
 else
 {
   //Mode pré-programmé

   //Si le trajet est fini, on ne fait rien
   if(finished == 0)
   {
      //On récupère le prochain point
      nextPoint = steps[stepNumber + 1];

      if(nextPoint == 14)
      {
        //S'il est égal à 14 on stocke l'ancien
        lastPoint14 = actualPoint;
      }

      if(actualPoint == 14 && lastPoint14 != 0 && lastPoint14 != 16)
      { 
         //Si le point actuel vaut 14, et que le point précédent est différent de 16 ou 0, il y a un comportement spécial
         //Comme le point 14, a plusieurs possibilité de point de départ, le robot peut avoir un référentiel droit gauche différent que celui-stocké (stocké : le robot pointe vers le haut)
        if(lastPoint14 == 4)
        {
          if(nextPoint == 11)
          {
            Move();
            stepNumber++;
            actualPoint = nextPoint;
          }
          else if(nextPoint == 6)
          {
            MvtVoiture.right();
            Move();
            stepNumber++;
            actualPoint = nextPoint;
          }
          else
          {
            //Sinon il y a bug, on stoppe tout
            finished = 1;
          }
        }
        else if(lastPoint14 == 6)
        {
          if(nextPoint == 11)
          {
            MvtVoiture.right();
            Move();
            stepNumber++;
            actualPoint = nextPoint;
          }
          else
          {
            //Sinon il y a bug, on stoppe tout
            finished = 1;
          }
        }
        else
        {
          //Sinon il y a bug, on stoppe tout
          finished = 1;
        }
      }
      else
      {
        //Sinon, c'est un comportement normal 
        //Les directions sont donnée par défaut dans chaque objet de type Point. b (sauf point 14)
        if(points[actualPoint - 1].droit == nextPoint)
        {
          Move();
          stepNumber++;
          actualPoint = nextPoint;
        }
        else if(points[actualPoint - 1].gauche == nextPoint)
        {
          MvtVoiture.left();
          Move();
          stepNumber++;
          actualPoint = nextPoint;
        }
        else if(points[actualPoint - 1].droite == nextPoint)
        {
          MvtVoiture.right();
          Move();
          stepNumber++;
          actualPoint = nextPoint;
        }

        if(actualPoint == ARRIVAL_POINT)
        {
          finished = 1;
        }
      }
   }
 }


      // Lit un nombre depuis le port série
        valeur = distObstacleIR;
  
    vw_send((byte *) &valeur, sizeof(valeur)); // On envoie le message
    vw_wait_tx(); // On attend la fin de l'envoi

        valeur = distParcourue;
  
    vw_send((byte *) &valeur, sizeof(valeur)); // On envoie le message
    vw_wait_tx(); // On attend la fin de l'envoi

        valeur = v;
  
    vw_send((byte *) &valeur, sizeof(valeur)); // On envoie le message
    vw_wait_tx(); // On attend la fin de l'envoi
}
