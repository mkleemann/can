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
 * Note: It is assumed to use an ATmega8 here.
 *
 * Created: 28.11.2011 18:17:39
 *  Author: MKleemann
 */

#include <avr/io.h>

#include "timer.h"

/***************************************************************************/
/* TIMER 0                                                                 */
/***************************************************************************/

/**
 * @brief initializes Timer0
 */
void initTimer0()
{
   TIMSK |= (1 << TOIE0);        // overflow interrupt enable
   TCCR0  = 0;                   // init and stop timer
}

/**
 * @brief start Timer0
 */
void startTimer0()
{
   TCCR0 |= TIMER0_PRESCALER;
}

/**
 * @brief stop Timer0
 */
void stopTimer0()
{
   TCCR0 &= ~(TIMER0_STOP);
}

/***************************************************************************/
/* TIMER 1                                                                 */
/***************************************************************************/

/**
 * @brief initializes Timer1
 * @param mode of Timer1 (overflow, compare, ...)
 */
void initTimer1(eTimerMode mode)
{
   uint8_t ctrlRegValA = 0;
   uint8_t ctrlRegValB = 0;

   switch(mode)
   {
      case TimerOverflow:
      {
         TIMSK |= (1 << TOIE1);  // set overflow interrupt enable
         break;
      }

      case TimerCompare:
      {
         // use Fast PWM and ICR for 16-bit compare mode (14) to get long periods
         TIMSK       |= (1 << TICIE1);                   // set input capture interrupt enable
         ctrlRegValA |= (1 << WGM11);                    // set Fast PWM mode with ICR1 as compare register
         ctrlRegValB |= (1 << WGM13) | (1 << WGM12);     // set Fast PWM mode with ICR1 as compare register
         ICR1H        = (TIMER1_COMPARE_VALUE >> 8);     // set compare value for interrupt
         ICR1L        = (TIMER1_COMPARE_VALUE & 0xFF);   // set compare value for interrupt
         break;
      }

      case TimerPwm:
      {
         // TODO: fill in initialization for PWM mode of Timer1
         break;
      }

      case TimerFastPwm:
      {
         // TODO: fill in initialization for Fast PWM mode of Timer1
         break;
      }

      default:
      {
         // nothing to do...yet.
         break;
      }
   }

   TCCR1A = ctrlRegValA;         // init & stop timer
   TCCR1B = ctrlRegValB;         // init & stop timer
}

/**
 * @brief start Timer1
 */
void startTimer1()
{
   TCCR1B |= TIMER1_PRESCALER;   // use defined prescaler value
}

/**
 * @brief stop Timer1
 */
void stopTimer1()
{
   TCCR1B &= ~(TIMER1_STOP);
}

/**
 * @brief restart Timer1 (set counter register to 0)
 */
void restartTimer1()
{
   stopTimer1();
   setTimer1Count(0);            // reset counter register
   startTimer1();
}

/**
 * @brief set timer1 counter register to value
 * @param timer counter value
 */
void setTimer1Count(uint16_t value)
{
   TCNT1 = value;
}


/***************************************************************************/
/* TIMER 2                                                                 */
/***************************************************************************/

/**
 * @brief initializes Timer2
 * @param mode of Timer2 (overflow, compare, pwm, ...)
 */
void initTimer2(eTimerMode mode)
{
   uint8_t ctrlRegVal = 0;

   switch(mode)
   {
      case TimerOverflow:        // overflow interrupt
      {
         TIMSK |= (1 << TOIE2);  // set overflow interrupt enable
         break;
      }

      case TimerCompare:         // CTC
      {
         // phase correct PWM
         TIMSK       |= (1 << OCIE2);           // set output compare interrupt enable
         ctrlRegVal  |= (1 << WGM21);           // set CTC mode
         OCR2         = TIMER2_COMPARE_VALUE;   // set compare value for interrupt
         break;
      }
      case TimerPwm:
      {
         // TODO: fill in initialization for PWM mode of Timer2
         break;
      }

      case TimerFastPwm:         // Fast PWM
      {
         // TODO: fill in initialization for Fast PWM mode of Timer2
         break;
      }

      default:
      {
         // nothing to do...yet.
         break;
      }
   }

   TCCR2 = ctrlRegVal;           // init & stop timer
}

/**
 * @brief start Timer2
 */
void startTimer2()
{
   TCCR2 |= TIMER2_PRESCALER;    // use defined prescaler value
}

/**
 * @brief stop Timer2
 */
void stopTimer2()
{
   TCCR2 &= ~(TIMER2_STOP);
}

/**
 * @brief restart Timer2 (set counter register to 0)
 */
void restartTimer2()
{
   stopTimer2();
   setTimer2Count(0);            // reset counter register
   startTimer2();
}

/**
 * @brief set timer2 counter register to value
 * @param timer counter value
 */
void setTimer2Count(uint8_t value)
{
   TCNT2 = value;
}


