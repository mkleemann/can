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
#include <util/delay.h>

#include "../util/util.h"
#include "../spi/spi.h"
#include "can_defs_mcp2515.h"
#include "can_config_mcp2515.h"

/**************************************************************************/
/* TYPE DEFINITIONS                                                       */
/**************************************************************************/

/* @brief index of internal CAN bitrate setup
 *
 * Any adaption here may need to adapt the source. If you keep the naming
 * scheme like CAN_BITRATE_xxx_KBPS, it's easier because of existing macros.
 */
typedef enum
{
   CAN_BITRATE_100_KBPS = 0,
   CAN_BITRATE_125_KBPS = 1,
   NUM_OF_CAN_BITRATES  = 2         // always the last one!
} eCanBitRate;


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
/* MCP2515 REGISTER/INIT FUNCTIONS                                        */
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


/*
 * @brief  reads MCP2515 status registers
 *
 * @param  chip select - chip to use
 * @param  command     - read quick status command of MCP2515
 * @return value of status register
 */
uint8_t read_status_mcp2515(eChipSelect  chip,
                            uint8_t      command);

/*
 * @brief  put MCP2515 (and attached MCP2551) to sleep
 *
 * To put MCP2551 also to sleep connect RX1BF pin to RS pin of MCP2551. It
 * is not always wanted to wakeup on any CAN activity. Sometimes, with
 * multiple interfaces, the "master bus" should only trigger the wakeup,
 * whereas the "slave" interfaces are woken up by wakeup signal from
 * atmega.
 *
 * @param  chip select - chip to use
 * @param  sleep mode  - when to activate MCP2515 again
 */
void mcp2515_sleep(eChipSelect   chip,
                   uint8_t       mode);

/*
 * @brief  wakeup MCP2515 (and attached MCP2551) from sleep mode
 *
 * @param  chip select - chip to use
 */
void mcp2515_wakeup(eChipSelect   chip);

/*
 * @brief  set MCP2515 mode of operation
 *
 * @param  chip select - chip to use
 * @param  mode of operation of MCP2515
 */
void set_mode_mcp2515(eChipSelect   chip,
                      uint8_t       mode);

/************************************************************************/
/* CAN FUNCTIONS                                                        */
/************************************************************************/

/*
 * @brief  send message via CAN
 *
 * @param  chip select - chip to use
 * @param  msg         - CAN message to send
 * @return address of buffer used to send
 */
uint8_t can_send_message(eChipSelect   chip,
                         can_t*         msg);

/*
 * @brief  get received CAN message
 *
 * @param  chip select - chip to use
 * @param  msg         - CAN message received
 * @return filter match status + 1
 */
uint8_t can_get_message(eChipSelect chip,
                        can_t*      msg);

/* @brief  checks if any messages are received (via MCP2515's interrupt pin)
 * @param  chip selected
 * @return true if message was received
 */
bool can_check_message_received(eChipSelect chip);

/* @brief  checks if any tx buffer is free to be loaded with a message
 * @param  chip selected
 * @return true if a buffer is free
 */
bool can_check_free_tx_buffers(eChipSelect chip);

/**************************************************************************/
/* HELPERS                                                                */
/**************************************************************************/

/* @brief setting up the interrupt pins
 * @param chip selected
 */
void setup_interrupt_pins(eChipSelect chip);

/* @brief setting up the chip select pins
 * @param chip selected
 */
void setup_cs_pins(eChipSelect chip);

/* @brief set chip select for the right chip
 * @param chip selected
 */
void set_chip_select(eChipSelect chip);

/* @brief unset chip select for the right chip
 * @param chip selected
 */
void unset_chip_select(eChipSelect chip);

/**
 * @brief clear filters
 * @param chip selected
 */
void clear_filters(eChipSelect chip);

#endif /* CAN_MCP2515_H_ */
