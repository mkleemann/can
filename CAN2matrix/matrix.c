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
   uint8_t gearBox;     // gear box status (destination)
   uint8_t headlights;  // headlights status (destination) on/off
   uint8_t dimLevel;    // dimming of display (destination) 0..255
} storeVals_t;

volatile storeVals_t storage;


/***************************************************************************/
/* fetch/fill functions for CAN (check IDs)                                */
/***************************************************************************/

/**
 * @brief fetch information from CAN1 and put to storage
 * @param CAN message to extract
 */
void fetchInfoFromCAN1(can_t* msg)
{
   switch(msg->msgId)
   {
      case CANID_1_IGNITION:
      {
         transferIgnStatus(msg);
         break;
      } /* end of case CANID_1_IGNITION */
      case CANID_1_WHEEL_DATA:
      {
         transferWheelCount(msg);
         break;
      } /* end of case CANID_1_WHEEL_DATA */
      case CANID_1_REVERSE_GEAR:
      {
         transferGearStatus(msg);
         break;
      } /* end of case CANID_1_REVERSE_GEAR */
      default:
      {
         // do nothing!
         break;
      } /* end of default */
   } /* end of switch msgId */
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
void transferIgnStatus(can_t* msg)
{
   uint8_t status = 0;
   uint8_t byte1  = msg->data[0];

   // check key in event
   // Note: Byte2 (start status) is set to SNA (7) or normal start (1) when
   //       sending destination message.
   status |= byte1 & 0x01;    // bit 0 - Key In Ignition

   // check ACC status
   if(byte1 & 0b11000010)
   {
      status |= 0b01100000;   // bits 5-7 - IGN off and ACC on
   } /* end of if ACC */

   // check IGN start status
   if(byte1 & 0b00001000)
   {
      status |= 0b10100000;   // bits 5-7 - IGN start
   } /* end of if IGN start */

   // check IGN on status
   if(byte1 & 0b00000100)
   {
      status |= 0b10000000;   // bit 5-7 - IGN on
   } /* end of if IGN on */

   // store information
   storage.ignition = status;
}

/**
 * @brief transfer wheel count values to storage
 *
 * Direction from CAN1 to CAN2
 *
 * @param pointer to CAN message
 */
void transferWheelCount(can_t* msg)
{
   // only 10 bits per wheel for count value
   storage.wheel1U = msg->data[0];
   storage.wheel1L = msg->data[1] & 0x3;
   storage.wheel2U = msg->data[2];
   storage.wheel2L = msg->data[3] & 0x3;
   storage.wheel3U = msg->data[4];
   storage.wheel3L = msg->data[5] & 0x3;
   storage.wheel4U = msg->data[6];
   storage.wheel4L = msg->data[7] & 0x3;
}

/**
 * @brief transfer gear box status (reverse gear)
 *
 * Direction from CAN1 to CAN2
 *
 * @param pointer to CAN message
 */
void transferGearStatus(can_t* msg)
{
   uint8_t status = 0;  // position P
   uint8_t byte8  = msg->data[7];

   // get information (automatic PRND)
   if(7 == byte8)
   {
      status |= 0x01;
   } /* end of if R */
   else if(6 == byte8)
   {
      status |= 0x02;
   } /* end of else if N */
   else if(8 != byte8)
   {
      status |= 0x04;
   } /* end of else if D/S/tip (not P) */

   // store information
   storage.gearBox = status;
}


