/*
 TimeOBJ.h
 CREATED on WEDNESDAY 17 APRIL 2019
 by CHANSIGAUD YANN

TimeOBJ manage time value from microsecond to years

*/

#ifndef TimeOBJ_h
#define TimeOBJ_h
#include <inttypes.h>

#define YEAR    0      // years             0-65535 years
#define DAY     1      // days              0-65535 days            ( 179y 200d                             )
#define HOUR    2      // hours             0-65535 hours           (   7y 175d 15h                         )
#define MINUTE  3      // minutes           0-65535 minutes         (       45d 12h 15min                   )
#define SECONDE 4      // secondes          0-65535 secondes        (           18h 12min 16s               )
#define MILLI   5      // millisecondes     0-4294967296  ms        (       49d 17h  2min 47s 295 ms        )
#define MICRO   6      // microsecondes     0-4294967296  us        (            1h 11min 34s 967 ms 295 us )

class TimeOBJ{
  public :
    TimeOBJ();
    // ==================================================== // ============================================= // Opérateur mathématique
    // ==================================================== //       Surcharge d'opérateur en valeur
    uint16_t &operator[]( byte type );                      // []    récupération ou affectation directe
    void operator=(  uint32_t val );                        // =
    TimeOBJ &operator+(  uint32_t val  );                   // +
    TimeOBJ &operator-(  uint32_t val  );                   // -
    void operator+=( uint32_t val );                        // +=
    void operator-=( uint32_t val );                        // -=
	// ==================================================== //       Surcharge d'opérateur en d'objet
    void operator=(  const TimeOBJ &TimeToSetTo    );       // =
    TimeOBJ &operator+(  const TimeOBJ &TimeToAdd  );       // +
    TimeOBJ &operator-(  const TimeOBJ &TimeToSub  );       // -
    void operator+=( const TimeOBJ &TimeToAdd      );       // +=
    void operator-=( const TimeOBJ &TimeToSub      );       // -=
	// ==================================================== // ============================================= // Opérateur comparatif
    // ==================================================== //       Comparatif en valeur
    bool operator==( uint32_t val );                        // ==
    bool operator!=( uint32_t val );                        // !=
    bool operator>=( uint32_t val );                        // >=
    bool operator<=( uint32_t val );                        // <=
    bool operator>(  uint32_t val );                        // >
    bool operator<(  uint32_t val );                        // <
    // ==================================================== //       Comparateur d'objet
    bool operator==( const TimeOBJ &TimeToCompare );        // ==
    bool operator!=( const TimeOBJ &TimeToCompare );        // ==
    bool operator>=( const TimeOBJ &TimeToCompare );        // >=
    bool operator<=( const TimeOBJ &TimeToCompare );        // <=
    bool operator>(  const TimeOBJ &TimeToCompare );        // >
    bool operator<(  const TimeOBJ &TimeToCompare );        // <
    
    void add( uint32_t T, byte type );
	void sub( uint32_t T, byte type );
    void get( uint16_t *Y, uint16_t *D, uint16_t *H, uint16_t *M, uint16_t *S, uint16_t *MS, uint16_t *US );
    void print();
	
  private :
    uint16_t   TimeTab[7] = {     0,   0,  0,  0,  0,    0,    0 };
    uint16_t  splitTab[7] = {     0,   0,  0,  0,  0,    0,    0 };
	uint16_t   maxiTab[8] = { 65535, 365, 24, 60, 60, 1000, 1000, 1 };
    void div_eucli( byte type );
    void div_calculator( byte first, byte last );
	uint32_t diviseur    = 0;
    uint32_t timeToSplit = 0;
	byte typeToSplit = 0;
	void split();
	void add();
	void sub();
	void reset();
	
};

#endif
