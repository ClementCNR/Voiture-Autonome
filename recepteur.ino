#include <VirtualWire.h>
int RF_RX_PIN = 7;  //pin pour recevoir 
void setup() {
  Serial.begin(9600);
 vw_set_rx_pin(RF_RX_PIN);
 
  // Initialisation de la bibliothèque VirtualWire
  // Vous pouvez changez les broches RX/TX/PTT avant vw_setup() si nécessaire
  vw_setup(2000);
  vw_rx_start(); // Déclenche le processus de réception du signal
 
  
}

void loop() {
  float valeur;
  byte taille_message = sizeof(float);


  // On attend de recevoir un message
  vw_wait_rx();

  if (vw_get_message((byte*) &valeur, &taille_message)) {
    // On copie le message dans valeur avec la limite à ne pas dépasser qui est 'taille message', qu'il soit corrompu ou non
    
    Serial.println(valeur); // Affiche le message
  }
}
