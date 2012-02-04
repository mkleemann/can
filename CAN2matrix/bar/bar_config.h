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
 * bar_config.h
 *
 * Created: 04.02.2012 21:18:18
 *  Author: MKleemann
 */


#ifndef BAR_CONFIG_H_
#define BAR_CONFIG_H_


/**
 * @brief define port to use for bargraph
 */
#define P_BAR        C

/**
 * @brief define range of port used for bargraph
 *
 * The bargraph uses the port pin range (pin 0..P_BAR_RANGE-1). Nothing else
 * should be connected to it than the hardware to use, e.g. LEDs.
 */
#define P_BAR_RANGE  5

/**
 * @brief definition of chip select
 *
 * If you need a chip select, define it here too. If the definition is not
 * set here, the pin won't be used.
 */
#define P_BAR_CS     D,5

/**
 * @brief define if chip select pin is negated
 *
 * To comment this define use a HIGH level for a CS. Set this define and the
 * /CS is set LOW active.
 */
#define P_BAR_CS_NEGATED


#endif /* BAR_CONFIG_H_ */