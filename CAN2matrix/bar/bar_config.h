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

/***************************************************************************/
/* GENERAL CONFIGURATION                                                   */
/***************************************************************************/

/**
 * @brief maximum value which causes all bargraph pins to be high
 *
 * 0..BAR_MAX_VALUE -> 0..P_BAR_RANGE-1
 */
#define BAR_MAX_VALUE   254

/**
 * @brief reverse bargraph (MAX -> 0; 0 -> P_BAR_RANGE-1)
 *
 * Sometimes it is wanted to set all pins when the value is 0, but clear
 * them when the value is near maximum. This is used e.g. in park distance
 * control units to visualize the measured values as a warning to the user.
 */
#define BAR_REVERSE

/**
 * @brief invert bits, e.g. to show value left
 *
 * This means, the bargraph reacts like normal, but the 1s and 0s are
 * inverted.
 */
//#define BAR_INVERTED

/***************************************************************************/
/* PORT/PIN DEFINITIONS                                                    */
/***************************************************************************/

/**
 * @brief define port to use for bargraph
 */
#define P_BAR           C

/**
 * @brief define range of port used for bargraph
 *
 * The bargraph uses the port pin range (pin 0..P_BAR_RANGE-1). Nothing else
 * should be connected to it than the hardware to use, e.g. LEDs.
 */
#define P_BAR_RANGE     5

/**
 * @brief adds an offset to the port pins used (not starting at pin0)
 *
 * Note: Adds to P_BAR_RANGE, so P_BAR_OFFSET + P_BAR_RANGE must not
 *       exceed port range. Set to 0, if unused.
 */
#define P_BAR_OFFSET    1

/**
 * @brief definition of chip select
 *
 * If you need a chip select, define it here too. If the definition is not
 * set here, the pin won't be used.
 */
//#define P_BAR_CS        D,5

/**
 * @brief define if chip select pin is inverted
 *
 * To comment this define use a HIGH level for a CS. Set this define and the
 * /CS is set LOW active.
 */
//#define P_BAR_CS_INVERTED


#endif /* BAR_CONFIG_H_ */