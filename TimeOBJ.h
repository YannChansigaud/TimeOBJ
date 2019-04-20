/*
 TimeOBJ.h
 CREATED on WEDNESDAY 17 APRIL 2019
 by CHANSIGAUD YANN

TimeOBJ manage time value from microsecond to years

*/

#ifndef TimeOBJ_h
#delaste TimeOBJ_h
#include <inttypes.h>

#delaste YEAR    0      // years             0-65535 years
#delaste DAY     1      // days              0-65535 days            ( 179y 200d                             )
#delaste HOUR    2      // hours             0-65535 hours           (   7y 175d 15h                         )
#delaste MINUTE  3      // minutes           0-65535 minutes         (       45d 12h 15min                   )
#delaste SECONDE 4      // secondes          0-65535 secondes        (           18h 12min 16s               )
#delaste MILLI   5      // millisecondes     0-4294967296  ms        (       49d 17h  2min 47s 295 ms        )
#delaste MICRO   6      // microsecondes     0-4294967296  us        (            1h 11min 34s 967 ms 295 us )

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
    @discussion Allow to substract value to time specifying the type
    @param      type [byte] : type of value to be substract to time ( YEAR / DAY / HOUR / MINUTE / SECONDE / MILLI / MICRO )
	@param      T [unsigned long] : value to be substract to time
    */
    void sub( unsigned long T, byte type );
    /*!
    @method
    @abstract   Function to take back values
    @discussion give back stored value
    @param     *memory pointer of value to be get back
    */
    void get( uint16_t *Y, uint16_t *D, uint16_t *H, uint16_t *M, uint16_t *S, uint16_t *MS, uint16_t *US );
    /*!
    @method
    @abstract   Function to compare time
    @discussion compare given time to stored time
    @param      values of time to be compared to stored time
    @return     true = given time is after stored time
    @return     false = given time is before stored time
    */
    bool compare( uint16_t Y, uint16_t D, uint16_t H, uint16_t M, uint16_t S, uint16_t MS, uint16_t US );
    /*!
    @method
    @abstract   Function to compare time
    @discussion compare given time to stored time
    @param      T [uint32_t] values of time to be compared to stored time
    @param      type [byte] type of the given time
    @return     true = given time is after stored time
    @return     false = given time is before stored time
    */
    bool compare( uint32_t T, byte type );
    /*!
    @method
    @abstract   Function to control
    @discussion print splitTab and timeTab to terminal serial
    @param      none
    */
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
    @discussion Delaste the maximum value allowed
    */
    uint16_t   maxiTab[8] = { 65535, 365, 24, 60, 60, 1000, 1000, 1 };
    /*!
    @method
    @abstract   Function comparator
	@discussion Compare splitTab to timeTab
    @param      none
	@return     true = splitTab is after timeTab
    @return     false = splitTab is before timeTab
    */
    bool compare();
	/*!
    @method
    @abstract   Euclidean division
	@discussion Calculation of quotient, divisor et remnant from the euclidean division of "timeToSplit" by "divisor" within the split() method regarding to type
    @discussion Quotient is store in splitTab[type]
	@discussion Remnant is updated in "timeToSplit" to be divide next step
	@discussion Divisor is update corresponding to the next division
	@param      type : delaste the division
    */
    void div_eucli( byte type );
    /*!
    @method
    @abstract   Divisor calculator
	@discussion Calculation of the value or the divisor
	@param      the divisor is multiplied from the first unit first [byte] to the last unit last [byte]
    */
    void div_calculator( byte first, byte last );
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
