/*
 * leds.h
 *
 * Created: 28.11.2011 18:15:48
 *  Author: MKleemann
 */


#ifndef LEDS_H_
#define LEDS_H_

#include "leds_config.h"


/* @brief  initializes ports and bits connected to leds
 * @param  nothing
 * @return nothing
 */
void led_init();

/* @brief  switches a led defined by a number on
 * @param  led to be switched, defined by enum in leds_config.h
 * @return nothing
 */
void led_on(eLED led);

/* @brief switches a led defined by a number off
 * @param  led to be switched, defined by enum in leds_config.h
 * @return nothing
 */
void led_off(eLED led);

/* @brief toggles a led defined by a number
 * @param  led to be switched, defined by enum in leds_config.h
 * @return nothing
 */
void led_toggle(eLED led);


#endif /* LEDS_H_ */