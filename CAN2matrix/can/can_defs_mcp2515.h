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
#define RXB1CTRL              0x70
#define RXB0CTRL              0x60
#define TXB2CTRL              0x50
#define TXB1CTRL              0x40
#define TXB0CTRL              0x30
#define EFLG                  0x2D
#define CANINTF               0x2C
#define CANINTE               0x2B
#define CNF1                  0x2A
#define CNF2                  0x29
#define CNF3                  0x28
#define REC                   0x1D
#define TEC                   0x1C
#define TXRTSCTRL             0x0D
#define BFPCTRL               0x0C
// multiple registers CANTSTATx - usually only one is used (sets all)
#define CANSTAT(x)            CANSTAT ## x
#define CANSTAT7              0x7E
#define CANSTAT6              0x6E
#define CANSTAT5              0x5E
#define CANSTAT4              0x4E
#define CANSTAT3              0x3E
#define CANSTAT2              0x2E
#define CANSTAT1              0x1E
#define CANSTAT0              0x0E

// multiple registers CANCTRLx - ususally only one is used (sets all)
#define CANCTRL(x)            CANCTRL ## x
#define CANCTRL7              0x7F
#define CANCTRL6              0x6F
#define CANCTRL5              0x5F
#define CANCTRL4              0x4F
#define CANCTRL3              0x3F
#define CANCTRL2              0x2F
#define CANCTRL1              0x1F
#define CANCTRL0              0x0F

// reception filter mask registers
#define RXM0SIDH              0x20
#define RXM0SIDL              0x21
#define RXM0EID8              0x22
#define RXM0EID0              0x23

#define RXM1SIDH              0x24
#define RXM1SIDL              0x25
#define RXM1EID8              0x26
#define RXM1EID0              0x27


/**************************************************************************/
/* MCP2515 BIT DEFINITIONS                                                */
/**************************************************************************/

// RXB0CTRL
#define BUKT2                 2
#define BUKT1                 1

// RXB1CTRL
#define FILHIT2               2
#define FILHIT1               1

// RXBxCTRL
#define RXM1                  6
#define RXM0                  5
#define RXRTR                 3
#define FILHIT0               0

// TXBxCTRL
#define ABTF                  6
#define MLOA                  5
#define TXERR                 4
#define TXREQ                 3
#define TXP1                  1
#define TXP0                  0

// EFLG
#define RX1OVR                7
#define RX0OVR                6
#define TXBO                  5
#define TXEP                  4
#define RXEP                  3
#define TXWAR                 2
#define RXWAR                 1
#define EWARN                 0

// CANINTE
#define MERRE                 7
#define WAKIE                 6
#define ERRIE                 5
#define TX2IE                 4
#define TX1IE                 3
#define TX0IE                 2
#define RX1IE                 1
#define RX0IE                 0

// CANINTF
#define MERRF                 7
#define WAKIF                 6
#define ERRIF                 5
#define TX2IF                 4
#define TX1IF                 3
#define TX0IF                 2
#define RX1IF                 1
#define RX0IF                 0

// CNF1
#define SJW1                  7
#define SJW0                  6
#define BRP5                  5
#define BRP4                  4
#define BRP3                  3
#define BRP2                  2
#define BRP1                  1
#define BRP0                  0

// CNF2
#define BTLMODE               7
#define SAM                   6
#define PHSEG12               5
#define PHSEG11               4
#define PHSEG10               3
#define PRSEG2                2
#define PRSEG1                1
#define PRSEG0                0

// CNF3
#define SOF                   7
#define WAKFIL                6
#define PHSEG22               2
#define PHSEG21               1
#define PHSEG20               0

// TXRTSCTRL
#define B2RTS                 5
#define B1RTS                 4
#define B0RTS                 3
#define B2RTSM                2
#define B1RTSM                1
#define B0RTSM                0

// BFPCRL
#define B1BFS                 5
#define B0BFS                 4
#define B1BFE                 3
#define B0BFE                 2
#define B1BFM                 1
#define B0BFM                 0

// multiple registers CANSTATx
#define OPMOD2                7
#define OPMOD1                6
#define OPMOD0                5
#define ICOD2                 3
#define ICOD1                 2
#define ICOD0                 1

// multiple registers CANCTRLx
#define REQOP2                7
#define REQOP1                6
#define REQOP0                5
#define ABAT                  4
#define OSM                   3
#define CLKEN                 2
#define CLKPRE1               1
#define CLKPRE0               0

#endif /* CAN_DEFS_MCP2515_H_ */