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

/**
 * timer.c
 *
 * Note: It is assumed to use an ATmega8.
 *
 * Created: 28.11.2011 18:17:39
 *  Author: MKleemann
 */

#include <avr/io.h>

#include "timer.h"

/**
 * @brief initializes Timer0
 */
void initTimer0()
{
   TIMSK |= (1 << TOIE0);                    // interrupt enable - here overflow
   TCCR0  = 0;                               // init and stop timer
}

/**
 * @brief start Timer0
 */
void startTimer0()
{
   TCCR0 |= TIMER0_PRESCALER;                // use defined prescaler value
}

/**
 * @brief stop Timer0
 */
void stopTimer0()
{
   TCCR0 = 0;  // stops timer
}

/**
 * @brief initializes Timer1
 */
void initTimer1()
{
}

/**
 * @brief initializes Timer2
 */
void initTimer2()
{
}




