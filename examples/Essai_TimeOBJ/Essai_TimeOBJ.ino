#include <Wire.h>
#include "TimeOBJ.h"

TimeOBJ objTime        = TimeOBJ();
uint16_t years         = 0;
uint16_t days          = 0;
uint16_t hours         = 0;
uint16_t minutes       = 0;
uint16_t secondes      = 0;
uint16_t millisecondes = 0;
uint16_t microsecondes = 0;

void setup() {
  // put your setup code here, to run once:
  objTime.zero();                                                                               // on met à zéro
  objTime.add( 1000000, MICRO );                                                                // on met 1 seconde
  objTime.sub( micros(), MICRO );                                                               // on enlève micros
  objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    // on récupère la différence de 1s - micros()
  objTime.zero();                                                                               // on remet à zéro
  objTime.add( 1000000, MICRO );                                                                // on met 1 seconde
  objTime.sub( secondes, SECONDE );                                                             // on enlève le nb de seconde récupéré précédement
  objTime.sub( millisecondes, MILLI );                                                          // le nombre de milliseconde
  objTime.sub( microsecondes, MICRO );                                                          // le nombre de microseconde
  objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    // et on récupère la durée réelle
  
  Serial.begin( 115200 );                                                                       // On initialise le port série
  Serial.println( "L'opération 'ajouter des microsecondes' suivi de" );                         // 
  Serial.println( "l'opération 'soustraire des microsecondes' auront durées :" );               // 
  printVAR();                                                                                   // 
}

void loop() {
  // put your main code here, to run repeatedly:
}

void printVAR(){
  Serial.print( years );            Serial.print( "y " );
  Serial.print( days );             Serial.print( "d " );
  Serial.print( hours );            Serial.print( "h " );
  Serial.print( minutes );          Serial.print( "m " );
  Serial.print( secondes );         Serial.print( "s " );
  Serial.print( millisecondes );    Serial.print( "ms " );
  Serial.print( microsecondes );    Serial.print( "us " );
  Serial.println();
}
