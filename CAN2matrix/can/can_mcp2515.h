/*
 * can_mcp2515.h
 *
 * Created: 28.11.2011 18:15:12
 *  Author: MKleemann
 */


#ifndef CAN_MCP2515_H_
#define CAN_MCP2515_H_

#include <avr/io.h>
#include "can_config_mcp2515.h"

/* @brief CAN message format - no extended frame support yet
 */
typedef struct
{
   uint16_t    msgId;      // message id (11 bits)
   struct
   {
      uint8_t rtr : 1;     // remote transmit request frame
      uint8_t len : 4;     // data length
   } header;
   uint8_t  data[8];       // data bytes
} can_t;


/* @brief CAN filter format - no extended frame support yet
 */
typedef struct
{
   uint16_t id;            // message id (11 bits)
   uint16_t mask;          // mask
   struct
   {
      uint8_t rtr : 2;     // remote transmit request frame
   } flags;
} can_filter_t;

/* @brief Calculate the values of CNFx registers of MCP2515.
 * @param  fosc - oscillator frequency of MCP2515
 * @param  cnf1 - pointer to CNF1
 * @param  cnf2 - pointer to CNF2
 * @param  cnf3 - pointer to CNF3
 * @return pos value of bit error rate, neg values if error
 */
int calcCNFx(uint16_t fosc,
             uint8_t* cnf1,
             uint8_t* cnf2,
             uint8_t* cnf3);


#endif /* CAN_MCP2515_H_ */
