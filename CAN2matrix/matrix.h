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

#include "can/can_mcp2515.h"


/***************************************************************************/
/* Definition of car CAN message ids                                       */
/***************************************************************************/
// currently a mix of infotainment and convenience CAN bus signals
// TODO: verify CAN signals in car

// ignition by key status
// another id could be 0x2C3 - verify
#define CANID_1_IGNITION               0x271

// wheel count values for navigation
// also via gateway signal 0x351 (old!)
#define CANID_1_WHEEL_DATA             0x455

// gear box status via gateway signal
#define CANID_1_REVERSE_GEAR           0x351

// status of lights
// to be verified
#define CANID_1_LIGHT_STATUS           0x531

// automatic and manual dimming
#define CANID_1_DIMMING                0x635

// also a gateway signal
#define CANID_1_LANGUAGE_AND_UNIT      0x653

// park distance control values
// to be verified
#define CANID_1_PDC_STATUS             0x54B

// time and odometer
// to be verified, but may also available via cluster
#define CANID_1_TIME_AND_ODO           0x65D

// vehicle identification number
// to be verified
#define CANID_1_VIN                    0x65F

// steering wheel angle
// to be verified
#define CANID_1_STEERING_WHEEL         0x3C3

// switch status, e.g. lights, horn, wipers, BC, ...
// to be verified
#define CANID_1_TURN_SIGNAL_CTRL       0x2C1

// cruise control status
// to be verified
#define CANID_1_CRUISE_CONTROL         0x289

// instrument cluster status, e.g. warning lights
// to be verified
#define CANID_1_COM_CLUSTER_STATUS1    0x621

// instrument cluster status, e.g. date/time
// to be verified
#define CANID_1_COM_CLUSTER_STATUS2    0x623

// multi function display status (sent by display!)
// to be verified
#define CANID_1_COM_DISPLAY_STATUS     0x62F

// start signal for display communication
// to be verified
#define CANID_1_COM_DISP_START         0x2E8

// communication channels
// to be verified
#define CANID_1_COM_RADIO_CLUSTER1     0x680
#define CANID_1_COM_RADIO_CLUSTER2     0x681
#define CANID_1_COM_NAVI_CLUSTER1      0x682
#define CANID_1_COM_NAVI_CLUSTER2      0x683
#define CANID_1_COM_PHONE_CLUSTER      0x685
#define CANID_1_COM_COMPASS_CLUSTER    0x689

// radio status signal, e.g. on/off, locked, ...
// to be verified
#define CANID_1_RADIO_STATUS           0x661

// navigation status, e.g. wake up, bus sleep, ...
// to be verified
#define CANID_1_NAVI_STATUS            0x436

/***************************************************************************/
/* Definition of radio CAN message ids                                     */
/***************************************************************************/

// ignition and key status
#define CANID_2_IGNITION               0x20B

// wheel pulse counter
#define CANID_2_WHEEL_DATA             0x211

// gear box status, e.g. for rear view camera and navigation
#define CANID_2_REVERSE_GEAR           0x20E

// light status and dimming for keys
#define CANID_2_LIGHT_STATUS           0x309

// dimming for main display
#define CANID_2_DIMMING                0x194

// switches units and language
#define CANID_2_LANGUAGE_AND_UNIT      0x2B0

/***************************************************************************/
/* Bit Definitions                                                         */
/***************************************************************************/

// Ignition CAN1
#define IGN_1_CL_S                     0
#define IGN_1_CL_15                    1
#define IGN_1_CL_X                     2
#define IGN_1_CL_50                    3
#define IGN_1_CL_P                     4
#define IGN_1_CL_15SV                  6
#define IGN_1_CL_L                     7

// combinations for CAN1
#define IGN_1_KEY_Status       (1 << IGN_1_CL_S)
#define IGN_1_ACC_Status      ((1 << IGN_1_CL_L) | (1 << IGN_1_CL_15SV))
#define IGN_1_START_Status    ((1 << IGN_1_CL_50) | (1 << IGN_1_CL_X))
#define IGN_1_ON               (1 << IGN_1_CL_15)

// Ignition CAN2
#define IGN_2_KeyIn                    0
#define IGN_2_Stat1                    5
#define IGN_2_Stat2                    6
#define IGN_2_Stat3                    7

// combinations for CAN2
#define IGN_2_ACC_On_IGN_Off  ((1 << IGN_2_Stat2) | (1 << IGN_2_Stat1))
#define IGN_2_IGN_Start       ((1 << IGN_2_Stat3) | (1 << IGN_2_Stat2))
#define IGN_2_ON               (1 << IGN_2_Stat3)

/***************************************************************************/
/* functions for matrix operations                                         */
/***************************************************************************/

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


/***************************************************************************/
/* Helpers to match bytes and bits                                         */
/***************************************************************************/

/**
 * @brief match different IGN status messages
 *
 * Direction from CAN1 to CAN2!
 *
 * @param pointer to CAN message
 */
void transferIgnStatus(can_t* msg);

/**
 * @brief transfer wheel count values to storage
 *
 * Direction from CAN1 to CAN2
 *
 * @param pointer to CAN message
 */
void transferWheelCount(can_t* msg);

/**
 * @brief transfer gear box status (reverse gear)
 *
 * Direction from CAN1 to CAN2
 *
 * @param pointer to CAN message
 */
void transferGearStatus(can_t* msg);

#endif /* MATRIX_H_ */
