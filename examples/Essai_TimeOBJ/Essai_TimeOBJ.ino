#include <Wire.h>
#include "TimeOBJ.h"

TimeOBJ objTime        = TimeOBJ();
TimeOBJ objTime5s      = TimeOBJ();
TimeOBJ objTime30s     = TimeOBJ();
TimeOBJ objTime2H24M   = TimeOBJ();
uint16_t years         = 0;
uint16_t days          = 0;
uint16_t hours         = 0;
uint16_t minutes       = 0;
uint16_t secondes      = 0;
uint16_t millisecondes = 0;
uint16_t microsecondes = 0;

void setup() {
  objTime5s  =  5000;
  objTime30s = 30000;
  objTime2H24M = 0;
  objTime2H24M.add(  2, HOUR   );
  objTime2H24M.add( 24, MINUTE );
  
  objTime = 0;
  objTime.add( 1000000, MICRO );                                                                // on met 1 seconde
  objTime.sub( micros(), MICRO );                                                               // on enlève micros
  objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    // on récupère la différence de 1s - micros()
  objTime = 0;
  objTime.add( 1000000, MICRO );                                                                // on met 1 seconde
  objTime.sub( secondes, SECONDE );                                                             // on enlève le nb de seconde récupéré précédement
  objTime.sub( millisecondes, MILLI );                                                          // le nombre de milliseconde
  objTime.sub( microsecondes, MICRO );                                                          // le nombre de microseconde
  objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    // et on récupère la durée réelle
  
  Serial.begin( 115200 );                                                                       // On initialise le port série
  Serial.println( "L'opération 'ajouter des microsecondes' suivi de" );                         // 
  Serial.println( "l'opération 'soustraire des microsecondes' auront durées :" );               // 
  printVAR();                                                                                   // 
  Serial.println( "Exemple d'utilisation des opérateurs surchargés :" );                        // 
  Serial.println( "objTime = 0 : " );
  objTime = 0;               objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on défini à zéro, on récupère et on imprime
  Serial.println( "objTime = 10000 (10s) : " );
  objTime = 10000;           objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on défini à 10s, on récupère et on imprime
  Serial.println( "objTime = un autre objTime : " );
  objTime = objTime2H24M;    objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on défini sur 2h24, on récupère et on imprime
  Serial.println( "objTime += un autre objTime : " );
  objTime += objTime2H24M;   objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on rajoute 2h24, on récupère et on imprime
  Serial.println( "objTime += 60'000 une valeur sera toujours considérée en milliseconde" );
  objTime += 60000;          objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on rajoute 60000, par défaut en milliseconde, soit 1min, on récupère et on imprime
  Serial.println( "objTime += millis()" );
  objTime += millis();       objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on rajoute 60000, par défaut en milliseconde, soit 1min, on récupère et on imprime
  Serial.println( "objTime[YEAR] = 2" );
  objTime[YEAR] = 2;         objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();   // on rajoute 2 ans en utilisant []

  objTime = 0;
  Serial.println( "Exemple d'addition à 2 termes :" );
  Serial.println( "2h24 + 30s - 5s + 500 qui sont 3 objets TimeOBJ et une valeur" );
  objTime = objTime2H24M + objTime30s - objTime5s + 500;
                             objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();
  objTime = 0;
  Serial.println( "Exemple d'utilisation des opérateurs de comparaison :" );
  Serial.println( "objTime30s = 30000 ?" );
  if( objTime30s == 30000 ){  Serial.println( "vrai" );    }
  else{                       Serial.println( "faux" );    }
  Serial.println( "objTime2H24M != objTime30s ?" );
  if( objTime2H24M != objTime30s ){  Serial.println( "vrai" );    }
  else{                              Serial.println( "faux" );    }
  Serial.println( "objTime=millis() puis objTime > objTime5s ? " );
}

void loop() {
  objTime = millis();
  if( objTime > objTime5s ){  Serial.println( "vrai" );    }
  else{                       Serial.println( "faux" );    }
  objTime.get( &years, &days, &hours, &minutes, &secondes, &millisecondes, &microsecondes );    printVAR();
  delay(1000);
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
  Serial.println();
}
