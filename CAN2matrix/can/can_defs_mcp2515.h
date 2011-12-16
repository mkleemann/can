/*
 * can_defs_mcp2515.h
 *
 * Created: 28.11.2011 18:36:26
 *  Author: MKleemann
 */


#ifndef CAN_DEFS_MCP2515_H_
#define CAN_DEFS_MCP2515_H_


/**************************************************************************/
/* MCP2515 COMMAND SET                                                    */
/**************************************************************************/
#define MCP2515_RESET         0xC0  // resets all registers to configuration mode
#define MCP2515_RX_STATUS     0xB0  // quick polling of filter match and message type
#define MCP2515_READ_STATUS   0xA0  // quick read status of RX/TX functions
#define MCP2515_READ_RX       0x90  // read a RX buffer indicated by bit 0..1
#define MCP2515_RTS           0x80  // begin TX sequence for a TX buffer (bit 0..2)
#define MCP2515_LOAD_TX       0x40  // load a TX buffer indicated by bit 0..2
#define MCP2515_BITMODIFY     0x05  // modifies bit in MCP2515 register
#define MCP2515_READ          0x03  // read data from MCP2515
#define MCP2515_WRITE         0x02  // write data to MCP2515

/**************************************************************************/
/* MCP2515 CONTROL REGISTERS                                              */
/**************************************************************************/
#define CNF1                  0x2A
#define CNF2                  0x29
#define CNF3                  0x28


#endif /* CAN_DEFS_MCP2515_H_ */