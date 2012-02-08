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

/***************************************************************************/
/* FUNCTIONS                                                               */
/***************************************************************************/

/**
 * @brief initialize bargraph hardware and control structs
 */
void bar_init()
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

/**
 * @brief set bargraph to defined maximum value
 */
void bar_set_max(void)
{
   uint8_t mask = ~0;
   EXP_PORT(P_BAR) |= ~(mask << P_BAR_RANGE);
}

/**
 * @brief set bargraph to any value
 */
void bar_set(uint8_t value)
{
   // remove old values
   bar_clear();
   EXP_PORT(P_BAR) |= bar_calc_pins(value);
}

/**
 * @brief clear bargraph
 */
void bar_clear(void)
{
   uint8_t mask = ~0;
   EXP_PORT(P_BAR) &= (mask << P_BAR_RANGE);
}

/**
 * @brief calculate pins to be set
 */
uint8_t bar_calc_pins(uint8_t value)
{
   uint8_t retVal = 0;
   uint8_t mask   = ~0;
   // divide range with maximum and multiply value to get bargraph steps
#ifdef BAR_REVERSE
   uint8_t step = (P_BAR_RANGE * (BAR_MAX_VALUE - value + 1) / BAR_MAX_VALUE);
#else
   uint8_t step = (P_BAR_RANGE * value / BAR_MAX_VALUE);
#endif
   // setup next value, but keep values > MAX out
   if(value <= BAR_MAX_VALUE)
   {
#ifdef BAR_INVERTED
      // mask out unused bits
      retVal |= (mask << step) & ~(mask << P_BAR_RANGE);
#else
      retVal |= ~(mask << step);
#endif
   }
   return retVal;
}

