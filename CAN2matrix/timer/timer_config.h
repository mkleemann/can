/**
 * ----------------------------------------------------------------------------
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 * ----------------------------------------------------------------------------
 **/

/**
 * timer_config.h
 *
 * We are using an ATmega8 right now - values for other AVRs might differ.
 *
 * Created: 28.11.2011 18:17:28
 *  Author: MKleemann
 */


#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

//**************************************************************************
// TIMER0 prescaler settings
//
// CS02 CS01 CS00 Description
//    0    0    0 No clock source (Timer/Counter stopped)
//    0    0    1 clkI/O/(No prescaling)
//    0    1    0 clkI/O/8 (From prescaler)
//    0    1    1 clkI/O/64 (From prescaler)
//    1    0    0 clkI/O/256 (From prescaler)
//    1    0    1 clkI/O/1024 (From prescaler)
//    1    1    0 External clock source on T0 pin. Clock on falling edge
//    1    1    1 External clock source on T0 pin. Clock on rising edge
//**************************************************************************

// TIMER0 with prescaler clkI/O/1024
//#define TIMER0_PRESCALER      (1 << CS02) | (1 << CS00)

//**************************************************************************
// TIMER1 prescaler settings
//
// CS12 CS11 CS10 Description
//    0    0    0 No clock source (Timer/Counter stopped)
//    0    0    1 clkI/O/(No prescaling)
//    0    1    0 clkI/O/8 (From prescaler)
//    0    1    1 clkI/O/64 (From prescaler)
//    1    0    0 clkI/O/256 (From prescaler)
//    1    0    1 clkI/O/1024 (From prescaler)
//    1    1    0 External clock source on T1 pin. Clock on falling edge
//    1    1    1 External clock source on T1 pin. Clock on rising edge
//**************************************************************************
// TIMER1 with prescaler clkI/O/1024
#define TIMER1_PRESCALER      (1 << CS12) | (1 << CS10)

// ~15s (4MHz@1024 prescale value)
#define TIMER1_COMPARE_VALUE  0xE4E1

//**************************************************************************
// TIMER2 prescaler settings
//
// CS22 CS21 CS20 Description
//    0    0    0 No clock source (Timer/Counter stopped)
//    0    0    1 clkT2S/(No prescaling)
//    0    1    0 clkT2S/8 (From prescaler)
//    0    1    1 clkT2S/32 (From prescaler)
//    1    0    0 clkT2S/64 (From prescaler)
//    1    0    1 clkT2S/128 (From prescaler)
//    1    1    0 clkT2S/256 (From prescaler)
//    1    1    1 clkT2S/1024 (From prescaler)
//**************************************************************************

// TIMER2 with prescaler clkT2S/1024
#define TIMER2_PRESCALER      (1 << CS22) | (1 << CS21) | (1 << CS20)

// TIMER2 output compare value - default is max. 0xFF (255)
// --> value 99 is ~25ms (4MHz@1024 prescale factor)
#define TIMER2_COMPARE_VALUE  99

#endif /* TIMER_CONFIG_H_ */

