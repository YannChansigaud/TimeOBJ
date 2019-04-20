/*
 * TimeOBJ.cpp
 * CREATED on TUESDAY 16 AUGUST 2018
 * by CHANSIGAUD YANN
 */


#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include <inttypes.h>

#include "TimeOBJ.h"

TimeOBJ::TimeOBJ(){}
void TimeOBJ::zero(){ reset(); }

void TimeOBJ::add( unsigned long T, byte type ){
	timeToSplit = T;
	typeToSplit = type;
	split();
	add();
}

void TimeOBJ::sub( unsigned long T, byte type ){
	timeToSplit = T;
	typeToSplit = type;
	split();
	sub();
}

void TimeOBJ::split(){
	if( typeToSplit < MILLI ){    timeToSplit &= 0xFFFF;    }
	
	byte debut = 0;
	byte fin = 0;
	diviseur = 1;

	switch( typeToSplit ){
		case YEAR    :{    debut = YEAR;  fin = YEAR;      break;   }
		case DAY     :{    debut = YEAR;  fin = DAY;       break;   }
		case HOUR    :{    debut = YEAR;  fin = HOUR;      break;   }
		case MINUTE  :{    debut = DAY;   fin = MINUTE;    break;   }
		case SECONDE :{    debut = HOUR;  fin = SECONDE;   break;   }
		case MILLI   :{    debut = DAY;   fin = MILLI;     break;   }
		case MICRO   :{    debut = HOUR;  fin = MICRO;     break;   }
	}
	div_calculator( debut, fin );
	switch( debut ){
		case YEAR    :{  div_eucli( YEAR    );  if( fin == YEAR    ){    break;	}  }
		case DAY     :{  div_eucli( DAY     );  if( fin == DAY     ){    break;	}  }
		case HOUR    :{  div_eucli( HOUR    );  if( fin == HOUR    ){    break;	}  }
		case MINUTE  :{  div_eucli( MINUTE  );  if( fin == MINUTE  ){    break;	}  }
		case SECONDE :{  div_eucli( SECONDE );  if( fin == SECONDE ){    break;	}  }
		case MILLI   :{  div_eucli( MILLI   );  if( fin == MILLI   ){    break;	}  }
		case MICRO   :{  div_eucli( MICRO   );  if( fin == MICRO   ){    break;	}  }
	}
}
void TimeOBJ::print(){
	Serial.print( "TimeTab  : " );
	Serial.print( TimeTab[YEAR] );      Serial.print( "y " );
	Serial.print( TimeTab[DAY] );       Serial.print( "d " );
	Serial.print( TimeTab[HOUR] );      Serial.print( "h " );
	Serial.print( TimeTab[MINUTE] );    Serial.print( "m " );
	Serial.print( TimeTab[SECONDE] );   Serial.print( "s " );
	Serial.print( TimeTab[MILLI] );     Serial.print( "m " );
	Serial.print( TimeTab[MICRO] );     Serial.print( "u " );
	Serial.println();
	Serial.print( "splitTab : " );
	Serial.print( splitTab[YEAR] );     Serial.print( "y " );
	Serial.print( splitTab[DAY] );      Serial.print( "d " );
	Serial.print( splitTab[HOUR] );     Serial.print( "h " );
	Serial.print( splitTab[MINUTE] );   Serial.print( "m " );
	Serial.print( splitTab[SECONDE] );  Serial.print( "s " );
	Serial.print( splitTab[MILLI] );    Serial.print( "m " );
	Serial.print( splitTab[MICRO] );    Serial.print( "u " );
	Serial.println();
}


void TimeOBJ::get( uint16_t *Y, uint16_t *D, uint16_t *H, uint16_t *M, uint16_t *S, uint16_t *MS, uint16_t *US ){
	*Y = TimeTab[YEAR];  *D = TimeTab[DAY];  *H = TimeTab[HOUR];  *M = TimeTab[MINUTE];  *S = TimeTab[SECONDE];  *MS = TimeTab[MILLI];  *US = TimeTab[MICRO];  
}

void TimeOBJ::add(){                                                                     // Add step by step splitTab to timeTab
	for( byte i=0 ; i<7 ; i++ ){                                                         // 
        TimeTab[6-i] += splitTab[6-i] ;                                                  // Add one value 
        if( TimeTab[6-i] >= maxiTab[6-i] ){                                              //   EXAMPLE : minutes has a maximum         ex : maxi = 60
            TimeTab[6-(i+1)] ++;                                                         //   IF maximum is overpass                  ex : M = 65 
            TimeTab[6-i] -= maxiTab[6-i];                                                //     Increase the next step                ex : H = H + 1
        }                                                                                //     Decrease this step by maximum         ex : M = 65-60 = 5
		splitTab[6-i] = 0;                                                               //   resetting this splitTab value
	}                                                                                    // 
}                                                                                        // 
void TimeOBJ::sub(){                                                                     // Substract step by step splitTab to timeTab
	for( byte i=0 ; i<7 ; i++ ){                                                         // 
        if( splitTab[6-i] > TimeTab[6-i] ){                                              // If sub value is bigger than time
			TimeTab[6-i]      = (maxiTab[6-i] - splitTab[6-i]) + TimeTab[6-i];           //   include corresponding maximum 
			splitTab[6-(i+1)] ++;                                                        //   increase the next value to substract
		}                                                                                // 
		else{                                                                            // If not
			TimeTab[6-i] -= splitTab[6-i];                                               //   just substract split to time
		}                                                                                // 
        splitTab[6-i] = 0;                                                               // resseting this splitTab value
	}                                                                                    // 
}                                                                                        // 
void TimeOBJ::reset(){                                                                   // RESET all tabs to zero
	for( byte i=0 ; i<7 ; i++ ){                                                         // 
		TimeTab[i]  = 0;                                                                 // 
		splitTab[i] = 0;                                                                 // 
	}                                                                                    // 
}                                                                                        // 
void TimeOBJ::div_eucli( byte type ){                                                    // SEQUENTIAL DIVISION by type
/*
	Serial.print( "div_eucli   =" );   Serial.println( type) ;
	Serial.print( "timeToSplit =" );   Serial.println( timeToSplit );    
	Serial.print( "diviseur    =" );   Serial.println( diviseur );    
*/	
	splitTab[ type ] = timeToSplit / diviseur ;                                          // quotient to corresponding split value
	timeToSplit -= splitTab[ type ] * diviseur;                                          // timeToSplit updated 
	diviseur    /= maxiTab[type+1];                                                      // divisor updated corresponding to the next division
}                                                                                        // 

void TimeOBJ::div_calculator( byte debut, byte fin ){
	diviseur = 1;
	switch( debut ){
		case YEAR     :{  diviseur *= maxiTab[DAY];      if( fin == DAY       ){    break;    }  }
		case DAY      :{  diviseur *= maxiTab[HOUR];     if( fin == HOUR      ){    break;    }  }
		case HOUR     :{  diviseur *= maxiTab[MINUTE];   if( fin == MINUTE    ){    break;    }  }
		case MINUTE   :{  diviseur *= maxiTab[SECONDE];  if( fin == SECONDE   ){    break;    }  }
		case SECONDE  :{  diviseur *= maxiTab[MILLI];    if( fin == MILLI     ){    break;    }  }
		case MILLI    :{  diviseur *= maxiTab[MICRO];    if( fin == MICRO     ){    break;    }  }
		case MICRO    :{  diviseur *= 1;                 if( fin == MICRO     ){    break;    }  }
	}
}