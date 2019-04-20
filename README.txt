TimeOBJ allow you to stock notion of time without type limitation.
uint32_t go from 0 to 4 294 967 295
- this correspond to 49d 17h  2min 47s 295 ms with milisecond unit
- this correspond to      1h 11min 34s 967 ms 295 us with microsecond unit

So, this class has 4 main method :
- add() allow you to add value with the unity of the value
- sub() allow you to substract value with the unity of the value
- zero() put all values stored to zéro
- get() allow to get back values stored


All values are stored in this format :
- YEAR    : number of year counted
- DAY     :  -        days  -
- HOUR    :  -        hours
- MINUTE  :  -        minutes
- SECONDE :  -        secondes
- MILLI   :  -        millisecondes
- MICRO   :  -        microsecondes
