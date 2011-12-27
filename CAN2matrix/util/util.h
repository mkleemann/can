/**
 * ----------------------------------------------------------------------------
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <m.kleemann@gmx.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 * ----------------------------------------------------------------------------
 **/

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

#define IS_SET(x)                _IS_SET(x)

// NOTE: To get the arguments from definitions described above.
#define GET_PORT(x)              _GET_PORT(x)
#define GET_PIN(x)               _GET_PIN(x)

// NOTE: Here the part to split the arguments to the real meaning behind.
#define _PIN_SET_INPUT(x,y)      DDR(x) &= ~(1<<y)
#define _PIN_SET_OUTPUT(x,y)     DDR(x) |= (1<<y)

#define _SET_PIN(x,y)            PORT(x) |= (1<<y)
#define _RESET_PIN(x,y)          PORT(x) &= ~(1<<y)
#define _TOGGLE_PIN(x,y)         PORT(x) ^= (1<<y)

#define _GET_PORT(x,y)           x
#define _GET_PIN(x,y)            y

// almost same as BIT_IS_SET, but as bool with PORT, PIN settings
#define _IS_SET(x,y)              (0 != (PORT(x) & (1<<y)))

/* @brief check status of bits set
 *
 * BIT_IS_SET(value, bit)     checks if bit in value is set - returns (1<<bit) if true
 * BIT_IS_UNSET(value, bit)   checks if bit in value is not set - returns (1<<bit) if true
 */
#define BIT_IS_SET(value, bit)   (value & (1<<bit))
#define BIT_IS_UNSET(value, bit) (!(value & (1<<bit)))

/* @brief access types
 */
typedef volatile uint8_t   vuint8_t;
typedef vuint8_t*          pvuint8_t;

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