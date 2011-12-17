/*
 * can_mcp2515.h
 *
 * Created: 28.11.2011 18:15:12
 *  Author: MKleemann
 */


#ifndef CAN_MCP2515_H_
#define CAN_MCP2515_H_

#include <avr/io.h>
#include <stdbool.h>

#include "../util/util.h"
#include "can_config_mcp2515.h"


/**************************************************************************/
/* TYPEDEFINITIONS                                                        */
/**************************************************************************/

/* @brief CAN message format - no extended frame support yet
 */
typedef struct
{
   uint16_t    msgId;               // message id (11 bits)
   struct
   {
      uint8_t rtr : 1;              // remote transmit request frame
      uint8_t len : 4;              // data length
   } header;
   uint8_t  data[8];                // data bytes
} can_t;


/* @brief CAN filter format - no extended frame support yet
 */
typedef struct
{
   uint16_t id;                     // message id (11 bits)
   uint16_t mask;                   // mask
   struct
   {
      uint8_t rtr : 2;              // remote transmit request frame
   } flags;
} can_filter_t;




/**************************************************************************/
/* FUNCTIONS                                                              */
/**************************************************************************/

/*
 * @brief  initializes MCP2515 selected
 *
 * Note: All MCP2515 connected to AVR need to have the same clock speed when
 *       using the same bitrate! See array in can_init_mcp2515.c.
 *
 * @param  chip select - chip to set up
 * @param  bitrate     - CAN bitrate of chip selected
 * @return true if ok, false if error
 */
bool can_init_mcp2515(eChipSelect chip,
                      eCanBitRate bitrate);


/*
 * @brief  write to MCP2515 registers
 *
 * @param  chip select - chip to use
 * @param  address     - register address of MCP2515
 * @param  data        - data byte
 */
void write_register_mcp2515(eChipSelect   chip,
                            uint8_t       address,
                            uint8_t       data);

/*
 * @brief  read from MCP2515 registers
 *
 * @param  chip select - chip to use
 * @param  address     - register address of MCP2515
 * @return data        - data byte
 */
uint8_t read_register_mcp2515(eChipSelect chip,
                              uint8_t     address);

/*
 * @brief  write masked bits to MCP2515 registers
 *
 * Note: Not all registers are able to provide this functionality. Mostly
 *       configuration registers do. Read the datasheet for details.
 *
 * @param  chip select - chip to use
 * @param  address     - register address of MCP2515
 * @param  mask        - bit mask for modify
 * @param  data        - data byte
 */
void bit_modify_mcp2515(eChipSelect chip,
                        uint8_t     address,
                        uint8_t     mask,
                        uint8_t     data);




#endif /* CAN_MCP2515_H_ */
