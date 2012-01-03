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
 * matrix.c
 *
 * Created: 03.01.2012 07:38:54
 *  Author: MKleemann
 */

#include <avr/io.h>
#include "matrix.h"

/***************************************************************************/
/* Definition of global variables to store CAN values.                     */
/***************************************************************************/
typedef struct
{
   uint8_t wheel1U;     // wheel signal 1 upper byte (as-is)
   uint8_t wheel1L;     // wheel signal 1 lower byte (as-is)
   uint8_t wheel2U;     // wheel signal 2 upper byte (as-is)
   uint8_t wheel2L;     // wheel signal 2 lower byte (as-is)
   uint8_t wheel3U;     // wheel signal 3 upper byte (as-is)
   uint8_t wheel3L;     // wheel signal 3 lower byte (as-is)
   uint8_t wheel4U;     // wheel signal 4 upper byte (as-is)
   uint8_t wheel4L;     // wheel signal 4 lower byte (as-is)
   uint8_t ignition;    // ignition key status (destination)
   uint8_t reverseGear; // reverse gear (destination)
   uint8_t headlights;  // headlights status (destination) on/off
   uint8_t dimLevel;    // dimming of display (destination) 0..255
} storeVals_t;

volatile storeVals_t storage;


/**
 * @brief fetch information from CAN1 and put to storage
 * @param CAN message to extract
 */
void fetchInfoFromCAN1(can_t* msg)
{
}

/**
 * @brief fetch information from CAN2 and put to storage
 * @param CAN message to extract
 */
void fetchInfoFromCAN2(can_t* msg)
{
}

/**
 * @brief put information from storage to CAN1
 * @param CAN message to fill
 */
void fillInfoToCAN1(can_t* msg)
{
}

/**
 * @brief put information from storage to CAN2
 * @param CAN message to fill
 */
void fillInfoToCAN2(can_t* msg)
{
}

