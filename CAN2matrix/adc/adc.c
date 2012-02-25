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
 * adc.c
 *
 * Created: 24.02.2012 19:59:06
 *  Author: MKleemann
 */

 #include <avr/io.h>
 #include "adc.h"

 /**
 * @brief initializes the ADC
 */
void adc_init(void)
{
   ADMUX  = ADC_REF_SELECT | ADC_INPUT_CHANNEL;
   ADCSRA = ADC_PRESCALER;
}

/**
 * @brief get ADC value
 */
uint16_t adc_get(void)
{


   uint16_t retVal = ADCL;
   retVal |= ADCH;
   return retVal;
}

/**
 * @brief enables ADC for power save
 */
void adc_enable()
{
   ADCSRA |= (1 << ADEN);
}

/**
 * @brief disables ADC for power save
 */
void adc_disable()
{
   ADCSRA &= ~(1 << ADEN);
}

