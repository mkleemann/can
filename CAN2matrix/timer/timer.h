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
 * timer.h
 *
 * Note: It is assumed to use an ATmega8 here.
 *
 * Created: 28.11.2011 18:15:59
 *  Author: MKleemann
 */


#ifndef TIMER_H_
#define TIMER_H_

#include "timer_config.h"

// check prescaler settings - if not set, the timer is assumed off
#ifndef TIMER0_PRESCALER   // TIMER 0 off
   #define TIMER0_PRESCALER   0
#endif

#ifndef TIMER1_PRESCALER   // TIMER 1 off
   #define TIMER1_PRESCALER   0
#endif

#ifndef TIMER2_PRESCALER   // TIMER 2 off
   #define TIMER2_PRESCALER   0
#endif

/***************************************************************************/
/* TIMER 0                                                                 */
/***************************************************************************/

// TODO: make timer functions inline, if possible/necessary

/**
 * @brief initializes Timer0 and stops
 */
void initTimer0();

/**
 * @brief start Timer0
 */
void startTimer0();

/**
 * @brief stop Timer0
 */
void stopTimer0();


/***************************************************************************/
/* TIMER 1                                                                 */
/***************************************************************************/

/**
 * @brief initializes Timer1
 */
void initTimer1();


/***************************************************************************/
/* TIMER 2                                                                 */
/***************************************************************************/

/**
 * @brief initializes Timer2
 */
void initTimer2();

#endif /* TIMER_H_ */