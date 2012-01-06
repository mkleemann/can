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
 * leds.c
 *
 * Created: 28.11.2011 18:18:10
 *  Author: MKleemann
 */

#include <avr/io.h>

#include "../util/util.h"
#include "leds.h"

/**************************************************************************/
/* VARIABLES                                                              */
/**************************************************************************/

/**
 * @brief global array to access LEDs via port pins directly
 *
 * TODO: rework
 */
static ledType ledPins[NUM_OF_LEDS] = { P_LED0,
                                        P_LED1,
                                        P_LED2,
                                        P_LED3,
                                        P_LED4
                                      };


/**************************************************************************/
/* FUNCTIONS                                                              */
/**************************************************************************/

/* @brief  initializes ports and bits connected to leds
 * @param  nothing
 * @return nothing
 */
void led_init()
{
   int i;
   // set port pins to output
   for(i = 0; i < NUM_OF_LEDS; ++i)
   {
      *(ledPins[i].ddr) |= (1<<ledPins[i].pin);
   } /* end of for 0..NUM_OF_LEDS-1 */
}

/* @brief  switches a led defined by a number on
 * @param  led to be switched, defined by enum in leds_config.h
 * @return nothing
 */
void led_on(eLED led)
{
   *(ledPins[led].port) |= (1<<ledPins[led].pin);
}

/* @brief switches a led defined by a number off
 * @param  led to be switched, defined by enum in leds_config.h
 * @return nothing
 */
void led_off(eLED led)
{
   *(ledPins[led].port) &= ~(1<<ledPins[led].pin);
}

/* @brief toggles a led defined by a number
 * @param  led to be switched, defined by enum in leds_config.h
 * @return nothing
 */
void led_toggle(eLED led)
{
   *(ledPins[led].port) ^= (1<<ledPins[led].pin);
}

