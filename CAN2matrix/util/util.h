/*
 * util.h
 *
 * Created: 04.12.2011 17:48:24
 *  Author: MKleemann
 */


#ifndef UTIL_H_
#define UTIL_H_

#include <avr/io.h>

/* @brief definition port & pin operations
 *
 * Format of port or pin usage is x = port,pin.
 */
#define PIN(x)                   PIN ## x
#define DDR(x)                   DDR ## x
#define PORT(x)                  PORT ## x

// NOTE: To ensure that you can enter one argument (e.g. via #define)
//       which then brakes to two arguments (e.g. #define LED_PIN D,2)
//       these macro definitions are done the way they are. Otherwise
//       the preprocessor runs into trouble with the number of arguments.
#define PIN_SET_INPUT(x)         _PIN_SET_INPUT(x)
#define PIN_SET_OUTPUT(x)        _PIN_SET_OUTPUT(x)

#define SET_PIN(x)               _SET_PIN(x)
#define RESET_PIN(x)             _RESET_PIN(x)
#define TOGGLE_PIN(x)            _TOGGLE_PIN(x)

// NOTE: To get the arguments from definitions described above.
#define GET_PORT(x)              _GET_PORT(x)
#define GET_PIN(x)               _GET_PIN(x)

// NOTE: Here the part to split the arguments to the real meaning behind.
#define _PIN_SET_INPUT(x,y)      DDR(x) |= (1<<y)
#define _PIN_SET_OUTPUT(x,y)     DDR(x) &= ~(1<<y)

#define _SET_PIN(x,y)            PORT(x) |= (1<<y))
#define _RESET_PIN(x,y)          PORT(x) &= ~(1<<y)
#define _TOGGLE_PIN(x,y)         PORT(x) ^= (1<<y)

#define _GET_PORT(x,y)           x
#define _GET_PIN(x,y)            y

/* @brief definition of debug printouts
 *
 */
#ifdef ___DEBUG_LEVEL___

   #include "../uart/uart.h"
// initialize debug channel
   #define DEBUG_INIT()       uart_init()

// defintion of debug print
   #define DEBUG_PRINT(s)     uart_puts(s)

#else  // ___DEBUG_LEVEL___

// nothing to do...
   #define  DEBUG_PRINT(s)

#endif // not defined ___DEBUG_LEVEL___


#endif /* UTIL_H_ */