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
 * leds_config.h
 *
 * Created: 28.11.2011 18:18:23
 *  Author: MKleemann
 */


#ifndef LEDS_CONFIG_H_
#define LEDS_CONFIG_H_

/* @brief define LEDs connected to your controller - name them as you wish, but keep
 *        in mind that it matches the port/pin definitions below.
 */
typedef enum
{
   errCan1LED  = 0,
   errCan2LED  = 1,
   txCan2LED   = 2,
   rxCan1LED   = 3,
   sleepLed    = 4,
   NUM_OF_LEDS = 5         // always the last one
} eLED;

/* @brief type of led control struct
 */
typedef struct { pvuint8_t ddr;
                 pvuint8_t port;
                 uint8_t   pin;
               } ledType;

/**
 * @brief defines for global array to access port pins directly via port address
 */
#define P_LED0       {&DDR(C), &PORT(C), PINC0},    // 0
#define P_LED1       {&DDR(C), &PORT(C), PINC1},    // 1
#define P_LED2       {&DDR(C), &PORT(C), PINC2},    // 2
#define P_LED3       {&DDR(C), &PORT(C), PINC3},    // 3
#define P_LED4       {&DDR(C), &PORT(C), PINC4}     // NUM_OF_LEDS - 1


#endif /* LEDS_CONFIG_H_ */