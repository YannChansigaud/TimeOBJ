TimeOBJ allow you to stock notion of time without type limitation.
uint32_t go from 0 to 4 294 967 295
- this correspond to 49d 17h  2min 47s 295 ms with milisecond unit
- this correspond to      1h 11min 34s 967 ms 295 us with microsecond unit

So, this class has 4 main method :
- add() allow you to add value with the unity of the value
- sub() allow you to substract value with the unity of the value
- get() allow to get back values stored

Overloaded operators are availables :
- direct access operator : []
- mathematical operator : =, +, - +=, -=, 
- comparativ operator : ==, !=, <, >, <=, >=, 
- only *, /, *= and /= are not define because has no sens


All values are uint16_t and stored in this layout :
- YEAR    : number of year counted
- DAY     :  -        days
- HOUR    :  -        hours
- MINUTE  :  -        minutes
- SECONDE :  -        secondes
- MILLI   :  -        millisecondes
- MICRO   :  -        microsecondes

So this library allow counting from 1 microseconde to 65535y 364d 24h 59min 59s 999ms 999us

warning : it is NOT a RTC library, there is no kind of date, just unit of time
