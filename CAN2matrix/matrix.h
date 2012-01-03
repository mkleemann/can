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


/***************************************************************************/
/* Definition of Skoda CAN message ids                                     */
/***************************************************************************/
#define CANID_1_IGNITION
#define CANID_1_WHEEL_DATA
#define CANID_1_REVERSE_GEAR
#define CANID_1_LIGHT_STATUS
//#define CANID_1_DIMMING
#define CANID_1_PDC_STATUS

/***************************************************************************/
/* Definition of Chrysler CAN message ids                                  */
/***************************************************************************/
#define CANID_2_IGNITION               0x20B    // ignition and key status
#define CANID_2_WHEEL_DATA             0x20E    // 4 wheels
#define CANID_2_REVERSE_GEAR           0x21E    // rearview camera
#define CANID_2_LIGHT_STATUS           0x309    // also dimming for unit keys
#define CANID_2_DIMMING                0x194    // display
#define CANID_2_METRIC_AND_LANG        0x2B0    // switches metric/languages

/**
 * @brief fetch information from CAN1 and put to storage
 * @param CAN message to extract
 */
void fetchInfoFromCAN1(can_t* msg);

/**
 * @brief fetch information from CAN2 and put to storage
 * @param CAN message to extract
 */
void fetchInfoFromCAN2(can_t* msg);

/**
 * @brief put information from storage to CAN1
 * @param CAN message to fill
 */
void fillInfoToCAN1(can_t* msg);

/**
 * @brief put information from storage to CAN2
 * @param CAN message to fill
 */
void fillInfoToCAN2(can_t* msg);


#endif /* MATRIX_H_ */