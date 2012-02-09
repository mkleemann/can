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
 * bar.h
 *
 * Created: 04.02.2012 21:18:57
 *  Author: MKleemann
 */


#ifndef BAR_H_
#define BAR_H_

#include "bar_config.h"

/***************************************************************************/
/* TYPEDEFS                                                                */
/***************************************************************************/


/***************************************************************************/
/* PROTOTYPES                                                              */
/***************************************************************************/

/**
 * @brief initialize bargraph hardware and control structs
 */
void bar_init(void);

/**
 * @brief set bargraph to defined maximum value
 */
void bar_set_max(void);

/**
 * @brief set bargraph to any value
 */
void bar_set(uint8_t value);

/**
 * @brief clear bargraph
 */
void bar_clear(void);

/**
 * @brief calculate pins to be set
 */
uint8_t bar_calc_pins(uint8_t value);

/**
 * @brief init chip select, if available
 */
void bar_init_cs(void);

/**
 * @brief set chip select, if available
 *
 * This is done either set to HIGH level or LOW level, if inverted.
 */
void bar_set_cs(void);

/**
 * @brief reset chip select, if available
 *
 * This is done either set to LOW level or HIGH level, if inverted.
 */
void bar_reset_cs(void);

#endif /* BAR_H_ */