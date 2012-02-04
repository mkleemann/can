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
 * bar.c
 *
 * Created: 04.02.2012 21:19:14
 *  Author: MKleemann
 */

#include <avr/io.h>
#include "../util/util.h"
#include "bar.h"

/**
 * @brief initialize bargraph hardware and control structs
 */
void bar_init(void)
{
   // initialize bargraph port pins to output, low
   for(int i = 0; i < P_BAR_RANGE; ++i)
   {
      EXP_PORT(P_BAR) &= ~(1 << i);
      EXP_DDR(P_BAR)  |=  (1 << i);
   }

   // initialize chip select, if defined
#ifdef P_BAR_CS

   // set initial value of chip select port pin
#ifdef P_BAR_CS_NEGATED
   SET_PIN(P_BAR_CS);
#else
   RESET_PIN(P_BAR_CS);
#endif

   // setup pin
   PIN_SET_OUTPUT(P_BAR_CS);

#endif
}

