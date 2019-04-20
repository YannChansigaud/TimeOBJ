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
    /*!
    @method
    @abstract   Class constructor. 
    @discussion Default constructor
    @param      none
    */
    TimeOBJ();
	/*!
    @method
    @abstract   Function reset
    @discussion Resetting all tabs to zero
    @param      none
    */
    void zero();
	/*!
    @method
    @abstract   Function adding value to time
    @discussion allow adding a value to time specifying the type
    @param      type [byte] : type of value to be added to time ( YEAR / DAY / HOUR / MINUTE / SECONDE / MILLI / MICRO )
	@param      T [unsigned long] : value to be added to time
    */
    void add( unsigned long T, byte type );
	/*!
    @method
    @abstract   Function substrating value to time
    @discussion Permet d'ajouter une quantité de temps de type
    @param      type [byte] : type of value to be substract to time ( YEAR / DAY / HOUR / MINUTE / SECONDE / MILLI / MICRO )
	@param      T [unsigned long] : value to be substract to time
    */
    void sub( unsigned long T, byte type );

    void get( uint16_t *Y, uint16_t *D, uint16_t *H, uint16_t *M, uint16_t *S, uint16_t *MS, uint16_t *US );

    void print();
	
  private :
    /*!
    @variable
    @abstract   Time Array
    @discussion Stock value of time with format YEAR / DAY / HOUR / MINUTE / SECONDE / MILLI / MICRO 
    */
    uint16_t   TimeTab[7] = {     0,   0,  0,  0,  0,    0,    0 };
	/*!
    @variable
    @abstract   Time Array
    @discussion Stock value of time to be added or substracted to time
    */
    uint16_t  splitTab[7] = {     0,   0,  0,  0,  0,    0,    0 };
	/*!
    @variable
    @abstract   Value Array
    @discussion Define the maximum value allowed
    */
    uint16_t   maxiTab[8] = { 65535, 365, 24, 60, 60, 1000, 1000, 1 };
	/*!
    @method
    @abstract   Euclidean division
	@discussion Calculation of quotient, divisor et remnant from the euclidean division of "timeToSplit" by "divisor" within the split() method regarding to type
    @discussion Quotient is store in splitTab[type]
	@discussion Remnant is updated in "timeToSplit" to be divide next step
	@discussion Divisor is update corresponding to the next division
	@param      type : define the division
    */
    void div_eucli( byte type );
    void div_calculator( byte debut, byte fin );
	/*!
    @variable
    @abstract   Value
    @discussion divisor of "timeToSplit" within the euclidean division of div_eucli() calling by split()
    */
    unsigned long diviseur    = 0;
	/*!
    @variable
    @abstract   Value
    @discussion value to be split
    */
    unsigned long timeToSplit = 0;
	/*!
    @variable
    @abstract   Value
    @discussion type of value to be split
    */
    byte typeToSplit = 0;
	/*!
    @method
    @abstract   Sequential Divisor 
    @discussion Manage the divisition of "timeToSplit" 
    */
    void split();
	/*!
    @method
    @abstract   Function adding time
    @discussion Add splitTab to timeTab.
	@discussion From MICRO to YEAR, add value by value, increasing the next if value>max
    @param      none
	*/
    void add();
	/*!
    @method
    @abstract   Function substrating time
    @discussion Substract splitTab to timeTab
	@discussion From MICRO to YEAR, sub value by value, decreasing the next one if result < 0
    @param      none
	*/
    void sub();
	/*!
    @method
    @abstract   Function reset
    @discussion Resetting all tabs to zero
	@param      none
    */
    void reset();
	
};

#endif