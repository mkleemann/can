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
 #include "../util/util.h"
 #include "adc.h"

 /**
 * @brief initializes the ADC
 */
void adc_init(void)
{
   PIN_SET_INPUT(ADC_INPUT_PIN);
   ADMUX  = ADC_REF_SELECT | ADC_INPUT_CHANNEL;
   ADCSRA = ADC_PRESCALER;
#ifdef ADC_8BIT_RESOLUTION
   ADMUX |= (1 < ADLAR);
#endif
}

/**
 * @brief get ADC value
 */
uint16_t adc_get(void)
{
   // start conversion
   ADCSRA |= (1 << ADSC);

   // wait for new conversion to be ready
   while (!(ADCSRA & (1 << ADIF)))
      ;

   // get value
   uint16_t retVal = ADCL;
#ifdef ADC_8BIT_RESOLUTION
   retVal  = ADCH;
#else
   retVal |= (uint16_t) (ADCH << 8);
#endif

   // clear interrupt flag by writing 1
   ADCSRA |= (1 << ADIF);

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

