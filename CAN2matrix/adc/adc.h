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
 * adc.h
 *
 * Created: 24.02.2012 19:59:19
 *  Author: MKleemann
 */


#ifndef ADC_H_
#define ADC_H_

#include "adc_config.h"

/**
 * @brief initializes the ADC
 */
void adc_init(void);

/**
 * @brief get ADC value
 */
uint16_t adc_get(void);




#endif /* ADC_H_ */