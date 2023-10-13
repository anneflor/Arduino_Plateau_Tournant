// https://www.brainy-bits.com/post/control-a-stepper-motor-using-an-arduino-and-potentiometer

//#include "AccelStepper.h"
#include <Stepper.h>
//#include <AccelStepper.h>
// Stepper Setup
//const int nbPas = 4096 //Si on fait des demi-pas avec le stepper motor
const int nbPas = 2048;
const int In_1 = 8; // In1
const int In_2 = 9; // In2
const int In_3 = 10; // In2
const int In_4 = 11; // In2

// On définit l'objet Stepper
Stepper myStepper(nbPas, In_1, In_3, In_2, In_4);
//Un moteur pas a pas ne peut pas dépasser les 10 tours par minute.

// Variables pour stocker les positions, actuelles et précédentes.
int val = 0;
int previous = 0;
int long newval = 0;    
int long previousval = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //valeur de la liaison série
  myStepper.setSpeed(9);//
}

void loop() {
  // put your main code here, to run repeatedly:
  val=analogRead(A0);
  newval = map(val, 0, 1023, 0, 2048);
  
  if (val > previous+6) {// Check that a move of the pot is at least > than 6
    newval = map(val, 0, 1023, 0, 2048);  // Map value (1600 = 1 stepper shaft rotation) Potentiometre donne entre 0 et 1023 
    myStepper.step(abs(newval-previousval));  // Move stepper to new position (nbr de steps)
    previous = val; 
    previousval = newval;
  }
  else if (val < previous-6){
    newval = map(val, 0, 1023, 0, 2048);  // Map value (1600 = 1 stepper shaft rotation)
    myStepper.step(-abs(newval-previousval));  // Move stepper to new position
    previous = val;
    previousval = newval; 
  }
  //myStepper.step(nbPas); (tourne dans le sens des aiguilles d'une montre de nbpas pas)
  //delay(10) //délai de 10ms
  //myStepper.step(-nbPas);
  
  Serial.println(val); //for debugging

} 

