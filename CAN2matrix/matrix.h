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
 * matrix.h
 *
 * Created: 28.11.2011 18:25:36
 *  Author: MKleemann
 */


#ifndef MATRIX_H_
#define MATRIX_H_

#include <avr/io.h>
#include "can/can.h"

/****************************************************************************
 * Definition of global variables to store CAN values.
 ****************************************************************************/
typedef struct {
         uint8_t wheel1U,     // wheel signal 1 upper byte (as-is)
         uint8_t wheel1L,     // wheel signal 1 lower byte (as-is)
         uint8_t wheel2U,     // wheel signal 2 upper byte (as-is)
         uint8_t wheel2L,     // wheel signal 2 lower byte (as-is)
         uint8_t wheel3U,     // wheel signal 3 upper byte (as-is)
         uint8_t wheel3L,     // wheel signal 3 lower byte (as-is)
         uint8_t wheel4U,     // wheel signal 4 upper byte (as-is)
         uint8_t wheel4L,     // wheel signal 4 lower byte (as-is)
         uint8_t ignition,    // ignition key status (destination)
         uint8_t reverseGear, // reverse gear (destination)
         uint8_t headlights,  // headlights status (destination) on/off
         uint8_t dimLevel     // dimming of display (destination) 0..255
} storeVals_t;

volatile storeVals_t storage;

/****************************************************************************
 * Definition of Skoda CAN message ids
 ****************************************************************************/
#define CANID_1_IGNITION
#define CANID_1_WHEEL_DATA
#define CANID_1_REVERSE_GEAR
#define CANID_1_LIGHT_STATUS
//#define CANID_1_DIMMING
#define CANID_1_PDC_STATUS

/****************************************************************************
 * Definition of Chrysler CAN message ids
 ****************************************************************************/
#define CANID_2_IGNITION               0x20B    // ignition and key status
#define CANID_2_WHEEL_DATA             0x20E    // 4 wheels
#define CANID_2_REVERSE_GEAR           0x21E    // rearview camera
#define CANID_2_LIGHT_STATUS           0x309    // also dimming for unit keys
#define CANID_2_DIMMING                0x194    // display
#define CANID_2_METRIC_AND_LANG        0x2B0    // switches metric/languages

/****************************************************************************
 * Definition of getter methods to fetch information from messages.
 * CAN1: here Skoda
 * CAN2: here Chrysler
 ****************************************************************************/
void fetchInfoFromCAN1(can_t* msg);
void fetchInfoFromCAN2(can_t* msg);

/****************************************************************************
 * Definition of setter methods to get information to messages.
 * CAN1: here Skoda
 * CAN2: here Chrysler
 ****************************************************************************/
void fillInfoToCAN1(can_t* msg);
void fillInfoToCAN2(can_t* msg);


#endif /* MATRIX_H_ */