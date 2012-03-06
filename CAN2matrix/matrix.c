/**
 * ----------------------------------------------------------------------------
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
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
      }

      case CANID_1_WHEEL_DATA:
      {
         transferWheelCount(msg);
         break;
      }

      case CANID_1_REVERSE_GEAR:
      {
         transferGearStatus(msg);
         break;
      }

      default:
      {
         // do nothing!
         break;
      }
   }
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
   // remove any old values
   for(int i = 0; i < 8; ++i)
   {
      msg->data[i] = 0;
   }

   switch(msg->msgId)
   {
      case CANID_2_IGNITION:
      {
         // fill in length of message
         msg->header.len = 2;
         // main ignition status
         msg->data[0] = storage.ignition;
         // 0: start not active; 1: normal start
         msg->data[1] = (storage.ignition & 0x80) ? 1 : 0;
         break;
      }

      case CANID_2_WHEEL_DATA:
      {
         // message is 8 bytes long
         msg->header.len = 8;
         // byte 0/1: engine PRM    : not used here
         // byte 2/3: vehicle speed : not used here
         // byte 4/5: wheel count left
         // byte 6/7: wheel count right
         msg->data[4] = storage.wheel1U;
         msg->data[5] = storage.wheel1L;
         msg->data[6] = storage.wheel2U;
         msg->data[7] = storage.wheel2L;
         break;
      }

      case CANID_2_REVERSE_GEAR:
      {
         // message is 7 bytes long
         msg->header.len = 7;
         // gear box status
         msg->data[2] = storage.gearBox;
         break;
      }

      case CANID_2_DIMMING:
      {
         // message is 3 bytes long
         msg->header.len = 3;
         // byte 1 bit 0 - day/night switch
         msg->data[0] = (storage.dimLevel > CAN2_DIM_LEVEL_THRESHOLD) ? DIM_2_DAY_MODE : DIM_2_NIGHT_MODE;
         msg->data[1] = storage.dimLevel; // radio
         msg->data[2] = storage.dimLevel; // interior
         break;
      }

      default:
      {
         // do nothing!
         break;
      }
   }
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
   status |= (byte1 & IGN_1_KEY_Status);  // bit 0 - Key In Ignition (IGN_2_KeyIn)

   // check ACC status
   if(byte1 & IGN_1_ACC_Status)
   {
      status |= IGN_2_ACC_On_IGN_Off;     // bits 5-7 - IGN off and ACC on
   }

   // check IGN start status
   if(byte1 & IGN_1_START_Status)
   {
      status |= IGN_2_IGN_Start;          // bits 5-7 - IGN start
   }

   // check IGN on status
   if(byte1 & IGN_1_ON)
   {
      status |= IGN_2_ON;                 // bit 5-7 - IGN on
   }

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
   storage.wheel1U = msg->data[0] & 0x3;  // FL
   storage.wheel1L = msg->data[1];
   storage.wheel2U = msg->data[2] & 0x3;  // FR
   storage.wheel2L = msg->data[3];
   storage.wheel3U = msg->data[4] & 0x3;  // RL
   storage.wheel3L = msg->data[5];
   storage.wheel4U = msg->data[6] & 0x3;  // RR
   storage.wheel4L = msg->data[7];
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
   {  // reverse gear
      status |= 0x01;
   }
   else if(6 == byte8)
   {  // neutral
      status |= 0x02;
   }
   else if(8 != byte8)
   {  // drive/sport/tip/... (not parking)
      status |= 0x04;
   }
   // else status = 0 -> parking or manual gear box

   // store information
   storage.gearBox = status;
}

/***************************************************************************/
/* Helpers to be called by main routine                                    */
/***************************************************************************/

/**
 * @brief send CAN1 message every 100ms
 * @param pointer to message struct
 */
void sendCan1_100ms(can_t* msg)
{
}

/**
 * @brief send CAN1 message every 500ms
 * @param pointer to message struct
 */
void sendCan1_500ms(can_t* msg)
{
}

/**
 * @brief send CAN1 message every 1000ms
 * @param pointer to message struct
 */
void sendCan1_1000ms(can_t* msg)
{
}

/**
 * @brief send CAN2 message every 100ms
 * @param pointer to message struct
 */
void sendCan2_100ms(can_t* msg)
{
   msg->msgId = CANID_2_IGNITION;
   sendCan2Message(msg);

   msg->msgId = CANID_2_WHEEL_DATA;  // should be 50ms, but keep it
   sendCan2Message(msg);
}

/**
 * @brief send CAN2 message every 500ms
 * @param pointer to message struct
 */
void sendCan2_500ms(can_t* msg)
{
   // testing for now - message is not built up correctly
   msg->msgId = CANID_2_DIMMING;
   sendCan2Message(msg);

   msg->msgId = CANID_2_REVERSE_GEAR;
   sendCan2Message(msg);
}

/**
 * @brief send CAN2 message every 1000ms
 * @param pointer to message struct
 */
void sendCan2_1000ms(can_t* msg)
{
}

/**
 * @brief sends message to CAN2 and filling up converted data
 *
 * Note: Set message id before calling this function.
 *
 * @param pointer to CAN message with set msg id
 */
void sendCan2Message(can_t* msg)
{
   fillInfoToCAN2(msg);

   can_send_message(CAN_CHIP2, msg);
}

/**
 * @brief gets a dim value to be sent via CAN
 * @param dim value 0..255
 */
void setDimValue(uint8_t value)
{
   storage.dimLevel = value;
}


