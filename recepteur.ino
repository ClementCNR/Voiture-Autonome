#include <VirtualWire.h>
const int RF_RX_PIN = 7;  //pin pour recevoir
const int led_pin = 6; 


void setup() {
  Serial.begin(9600);
 
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_set_rx_pin(RF_RX_PIN);
  vw_setup(2000); //Bits par sec
  vw_rx_start(); // Déclenche le processus de réception du signal
}


void loop() {
  float valeur; //Msg recue
  byte taille_message = sizeof(float);


  // On attend de recevoir un message
  vw_wait_rx();

  int i = 0;  //nb de data recue
  int j = 0;  //nb de 3 data recue
  if (vw_get_message((byte*) &valeur, &taille_message)) {
    // On copie le message dans valeur avec la limite à ne pas dépasser qui est 'taille message', qu'il soit corrompu ou non
    digitalWrite(led_pin, HIGH); //Allume la led quand un msg est recu
    j++;
    Serial.print("Transmission [ ");
    Serial.print(j);
    Serial.print(" ] :");
    
    if(i == 0)
    {
      Serial.print("Transmission [ ");
      Serial.print(j);
      Serial.println(" ] :");
      Serial.print("Distance de l'obstacle : ");
      Serial.println(valeur); // Affiche le message
      i++;
    }
    else if(i == 1)
    {
      Serial.print("Distance totale parcourue : ");
      Serial.println(valeur); // Affiche le message
      i++;
    }
    else if(i == 2)
    {
      Serial.print("Vitesse instantané : ");
      Serial.println(valeur); // Affiche le message
      i = 0;     
    }

    digitalWrite(led_pin, LOW);
    

  }
}
