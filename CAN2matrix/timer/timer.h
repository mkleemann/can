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
   #define TIMER0_PRESCALER      0
#endif

#ifndef TIMER1_PRESCALER   // TIMER 1 off
   #define TIMER1_PRESCALER      0
#endif

#ifndef TIMER2_PRESCALER   // TIMER 2 off
   #define TIMER2_PRESCALER      0
#endif

// check compare values and set to 16bit MAX
#ifndef TIMER1_COMPARE_VALUE
   #define TIMER1_COMPARE_VALUE  0xFFFF
#endif

#ifndef TIMER2_COMPARE_VALUE
   #define TIMER2_COMPARE_VALUE  0xFF
#endif


/***************************************************************************/
/* TYPEDEFINITION                                                          */
/***************************************************************************/

/**
 * @brief mode of timer initialization
 *
 * Define mode of timer (interrupt) behaviour. Four modes are available:
 * - overflow
 * - output compare (CTC)
 * - phase correct PWM
 * - fast PWM
 *
 * Note: Currently no output pin for PWM is set.
 */
typedef enum
{
   TimerOverflow  = 0,     // overflow
   TimerCompare   = 1,     // output compare (CTC)
   TimerPwm       = 2,     // phase correct PWM
   TimerFastPwm   = 3      // fast PWM
} eTimerMode;

/***************************************************************************/
/* TIMER 0                                                                 */
/***************************************************************************/

// TODO: make timer functions inline, if possible/necessary

/**
 * @brief initializes Timer0 and stops
 *
 * There is no argument yet, since mode of Timer0 is overflow only at
 * ATmega8. This has to be adapted, if using another AVR.
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
 * @param mode of Timer1 (overflow, compare, pwm, ...)
 */
void initTimer1(eTimerMode mode);

/**
 * @brief start Timer1
 */
void startTimer1();

/**
 * @brief stop Timer1
 */
void stopTimer1();

/**
 * @brief restart Timer1 (set counter register to 0)
 */
void restartTimer1();


/***************************************************************************/
/* TIMER 2                                                                 */
/***************************************************************************/

/**
 * @brief initializes Timer2
 * @param mode of Timer2 (overflow, compare, pwm, ...)
 */
void initTimer2(eTimerMode mode);

/**
 * @brief start Timer2
 */
void startTimer2();

/**
 * @brief stop Timer2
 */
void stopTimer2();

/**
 * @brief restart Timer2, e.g. in compare mode
 */
void restartTimer2();

#endif /* TIMER_H_ */