/**
 * ----------------------------------------------------------------------------
 *
 * "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware license):
 * <dev@layer128.net> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a be(ve)er(age) in return. (I don't
 * like beer much.)
 *
 * Matthias Kleemann
 *
 * ----------------------------------------------------------------------------
 *
 * \file can_defs_mcp2515.h
 *
 * \date Created: 28.11.2011 18:36:26
 * \author Matthias Kleemann
 *
 **/



#ifndef CAN_DEFS_MCP2515_H_
#define CAN_DEFS_MCP2515_H_


/**************************************************************************/
/* MCP2515 COMMAND SET                                                    */
/**************************************************************************/

/**
 * \addtogroup mcp_command_set MCP2515 Command Set
 * This is the command set used to control the MCP2515 CAN controller.
 * @{
 */

/*! \brief resets all registers to configuration mode */
#define MCP2515_RESET         0xC0
/*! \brief quick polling of filter match and message type */
#define MCP2515_RX_STATUS     0xB0
/*! \brief quick read status of RX/TX functions */
#define MCP2515_READ_STATUS   0xA0
/*! \brief read a RX buffer indicated by bit 0..1 */
#define MCP2515_READ_RX       0x90
/*! \brief begin TX sequence for a TX buffer (bit 0..2) */
#define MCP2515_RTS           0x80
/*! \brief load a TX buffer indicated by bit 0..2 */
#define MCP2515_LOAD_TX       0x40
/*! \brief modifies bit in MCP2515 register */
#define MCP2515_BITMODIFY     0x05
/*! \brief read data from MCP2515 */
#define MCP2515_READ          0x03
/*! \brief write data to MCP2515 */
#define MCP2515_WRITE         0x02

/*! @} */


/**************************************************************************/
/* MCP2515 CONTROL REGISTERS                                              */
/**************************************************************************/

/**
 * \addtogroup mcp_control_registers MCP2515 Control Registers
 * These are the registers the MCP2515 CAN controller provides to read and
 * write status, control and data information.
 * @{
 */

/*! \brief Receive Buffer 1 Control Register */
#define RXB1CTRL              0x70
/*! \brief Receive Buffer 0 Control Register */
#define RXB0CTRL              0x60
/*! \brief Transmit Buffer 2 Control Register */
#define TXB2CTRL              0x50
/*! \brief Transmit Buffer 1 Control Register */
#define TXB1CTRL              0x40
/*! \brief Transmit Buffer 0 Control Register */
#define TXB0CTRL              0x30
/*! \brief Error Flag Register */
#define EFLG                  0x2D
/*! \brief CAN Interrupt Flag Register */
#define CANINTF               0x2C
/*! \brief CAN Interrupt Enable Register */
#define CANINTE               0x2B
/*! \brief Configuration Register 1 */
#define CNF1                  0x2A
/*! \brief Configuration Register 2 */
#define CNF2                  0x29
/*! \brief Configuration Register 3 */
#define CNF3                  0x28
/*! \brief Receive Error Counter */
#define REC                   0x1D
/*! \brief Transmit Error Counter */
#define TEC                   0x1C
/*! \brief TXnRTS Pin Control and Status Register */
#define TXRTSCTRL             0x0D
/*! \brief RXnBF Pin Control and Status Register */
#define BFPCTRL               0x0C

/*!
 * \def CANSTAT(x)
 * \brief CAN Status Register(s)
 *
 * Multiple registers CANSTATx. Only one needs to be used (sets all), since
 * they are in the same location physically.
 */
#define CANSTAT(x)            CANSTAT ## x
/*! \sa CANSTAT(x) */
#define CANSTAT7              0x7E
/*! \sa CANSTAT(x) */
#define CANSTAT6              0x6E
/*! \sa CANSTAT(x) */
#define CANSTAT5              0x5E
/*! \sa CANSTAT(x) */
#define CANSTAT4              0x4E
/*! \sa CANSTAT(x) */
#define CANSTAT3              0x3E
/*! \sa CANSTAT(x) */
#define CANSTAT2              0x2E
/*! \sa CANSTAT(x) */
#define CANSTAT1              0x1E
/*! \sa CANSTAT(x) */
#define CANSTAT0              0x0E

/*!
 * \def CANCTRL(x)
 * \brief CAN Control Register(s)
 *
 * Multiple registers CANCTRLx. Only one needs to be used (sets all), since
 * they are in the same location physically.
 */
#define CANCTRL(x)            CANCTRL ## x
/*! \sa CANCTRL(x) */
#define CANCTRL7              0x7F
/*! \sa CANCTRL(x) */
#define CANCTRL6              0x6F
/*! \sa CANCTRL(x) */
#define CANCTRL5              0x5F
/*! \sa CANCTRL(x) */
#define CANCTRL4              0x4F
/*! \sa CANCTRL(x) */
#define CANCTRL3              0x3F
/*! \sa CANCTRL(x) */
#define CANCTRL2              0x2F
/*! \sa CANCTRL(x) */
#define CANCTRL1              0x1F
/*! \sa CANCTRL(x) */
#define CANCTRL0              0x0F

// reception filter mask registers

/**
 * \def RXM0SIDH
 * \brief Reception Mask Register 0 Standard ID Highbyte
 *
 * \def RXM0SIDL
 * \brief Reception Mask Register 0 Standard ID Lowbyte
 *
 * \def RXM0EID8
 * \brief Reception Mask Register 0 Extended ID Highbyte
 *
 * \def RXM0EID0
 * \brief Reception Mask Register 0 Extended ID Lowbyte
 */
#define RXM0SIDH              0x20
#define RXM0SIDL              0x21
#define RXM0EID8              0x22
#define RXM0EID0              0x23

/**
 * \def RXM1SIDH
 * \brief Reception Mask Register 1 Standard ID Highbyte
 *
 * \def RXM1SIDL
 * \brief Reception Mask Register 1 Standard ID Lowbyte
 *
 * \def RXM1EID8
 * \brief Reception Mask Register 1 Extended ID Highbyte
 *
 * \def RXM1EID0
 * \brief Reception Mask Register 1 Extended ID Lowbyte
 */
#define RXM1SIDH              0x24
#define RXM1SIDL              0x25
#define RXM1EID8              0x26
#define RXM1EID0              0x27

// reception filter registers

/**
 * \def RXF0SIDH
 * \brief Reception Filter Register 0 Standard ID Highbyte
 *
 * \def RXF0SIDL
 * \brief Reception Filter Register 0 Standard ID Lowbyte
 *
 * \def RXF0EID8
 * \brief Reception Filter Register 0 Extended ID Highbyte
 *
 * \def RXF0EID0
 * \brief Reception Filter Register 0 Extended ID Lowbyte
 */
#define RXF0SIDH              0x00
#define RXF0SIDL              0x01
#define RXF0EID8              0x02
#define RXF0EID0              0x03

/**
 * \def RXF1SIDH
 * \brief Reception Filter Register 1 Standard ID Highbyte
 *
 * \def RXF1SIDL
 * \brief Reception Filter Register 1 Standard ID Lowbyte
 *
 * \def RXF1EID8
 * \brief Reception Filter Register 1 Extended ID Highbyte
 *
 * \def RXF1EID0
 * \brief Reception Filter Register 1 Extended ID Lowbyte
 */
#define RXF1SIDH              0x04
#define RXF1SIDL              0x05
#define RXF1EID8              0x06
#define RXF1EID0              0x07

/**
 * \def RXF2SIDH
 * \brief Reception Filter Register 2 Standard ID Highbyte
 *
 * \def RXF2SIDL
 * \brief Reception Filter Register 2 Standard ID Lowbyte
 *
 * \def RXF2EID8
 * \brief Reception Filter Register 2 Extended ID Highbyte
 *
 * \def RXF2EID0
 * \brief Reception Filter Register 2 Extended ID Lowbyte
 */
#define RXF2SIDH              0x08
#define RXF2SIDL              0x09
#define RXF2EID8              0x0A
#define RXF2EID0              0x0B

/**
 * \def RXF3SIDH
 * \brief Reception Filter Register 3 Standard ID Highbyte
 *
 * \def RXF3SIDL
 * \brief Reception Filter Register 3 Standard ID Lowbyte
 *
 * \def RXF3EID8
 * \brief Reception Filter Register 3 Extended ID Highbyte
 *
 * \def RXF3EID0
 * \brief Reception Filter Register 3 Extended ID Lowbyte
 */
#define RXF3SIDH              0x10
#define RXF3SIDL              0x11
#define RXF3EID8              0x12
#define RXF3EID0              0x13

/**
 * \def RXF4SIDH
 * \brief Reception Filter Register 4 Standard ID Highbyte
 *
 * \def RXF4SIDL
 * \brief Reception Filter Register 4 Standard ID Lowbyte
 *
 * \def RXF4EID8
 * \brief Reception Filter Register 4 Extended ID Highbyte
 *
 * \def RXF4EID0
 * \brief Reception Filter Register 4 Extended ID Lowbyte
 */
#define RXF4SIDH              0x14
#define RXF4SIDL              0x15
#define RXF4EID8              0x16
#define RXF4EID0              0x17

/**
 * \def RXF5SIDH
 * \brief Reception Filter Register 5 Standard ID Highbyte
 *
 * \def RXF5SIDL
 * \brief Reception Filter Register 5 Standard ID Lowbyte
 *
 * \def RXF5EID8
 * \brief Reception Filter Register 5 Extended ID Highbyte
 *
 * \def RXF5EID0
 * \brief Reception Filter Register 5 Extended ID Lowbyte
 */
#define RXF5SIDH              0x18
#define RXF5SIDL              0x19
#define RXF5EID8              0x1A
#define RXF5EID0              0x1B

/*! @} */

/**************************************************************************/
/* MCP2515 BIT DEFINITIONS                                                */
/**************************************************************************/

/**
 * \addtogroup mcp_bit_definitions MCP2515 Bit Definitions
 * All named bits to be used writing and reading from MCP2515 registers.
 * @{
 */


/*!
 * \def BUKT2
 * Rollover enable bit. If set RXB0 message will rollover and be written to
 * RXB1 if RXB0 is full
 * \sa RXB0CTRL
 *
 * \def BUKT1
 * Copy of BUKT2 and used only internally by MCP2515. Read-Only
 * \sa RXB0CTRL
 * \sa BUKT2
 */
#define BUKT2                 2
#define BUKT1                 1

/**
 * \def FILHIT2
 * \brief Filter Hit bits.
 *
 * Indicates which acceptance filter enabled reception of message.
 *
 * \code
 * FILHIT 2 1 0
 *        1 0 1 = Acceptance Filter 5 (RXF5)
 *        1 0 0 = Acceptance Filter 4 (RXF4)
 *        0 1 1 = Acceptance Filter 3 (RXF3)
 *        0 1 0 = Acceptance Filter 2 (RXF2)
 *        0 0 1 = Acceptance Filter 1 (RXF1) (Only if BUKT bit set in RXB0CTRL)
 *        0 0 0 = Acceptance Filter 0 (RXF0) (Only if BUKT bit set in RXB0CTRL)
 * \endcode
 *
 * \sa RXB1CTRL, RXB0CTRL
 * \sa FILHIT1, FILHIT0
 * \sa BUKT1, BUKT2
 *
 * \def FILHIT1
 * \brief Filter Hit bits.
 *
 * For a detailed documentation, see FILHIT2
 * \sa FILHIT2, FILHIT0
 */
#define FILHIT2               2
#define FILHIT1               1

/**
 * \def RXM1
 * \brief Receive Buffer Operating Mode
 *
 * \code
 * RXM 1 0
 *     1 1 = Turn mask/filters off; receive any message
 *     1 0 = Receive only valid messages with extended identifiers that meet filter criteria
 *     0 1 = Receive only valid messages with standard identifiers that meet filter criteria
 *     0 0 = Receive all valid messages using either standard or extended identifiers that meet filter criteria
 * \endcode
 *
 * \sa RXM0
 * \sa RXB1CTRL, RXB0CTRL
 *
 * \def RXM0
 * \brief Receive Buffer Operating Mode bits
 *
 * \sa RXM1 for detailed description
 * \sa RXB1CTRL, RXB0CTRL
 *
 * \def RXRTR
 * \brief Received Remote Transfer Request
 *
 * \code
 * 1 = Remote Transfer Request Received
 * 0 = No Remote Transfer Request Received
 * \endcode
 *
 * \def FILHIT0
 * \brief Filter Hit bits.
 *
 * For a detailed documentation, see FILHIT2
 * \sa FILHIT2, FILHIT1
 * \sa RXB1CTRL, RXB0CTRL
 */
#define RXM1                  6
#define RXM0                  5
#define RXRTR                 3
#define FILHIT0               0

// TXBxCTRL

/*!
 * \def ABTF
 * \brief Message Abborted Flag
 *
 * Message was aborted when det to 1, otherwise transmission completed
 * successfully.
 *
 * \def MLOA
 * \brief Message Lost Arbitration
 *
 * When set to 1, the message lost arbitration while being sent.
 *
 * \def TXERR
 * \brief Transmission Error Detected
 *
 * A bus error occurrance while the message was being transmitted causes
 * this bit to be set to 1.
 *
 * \def TXREQ
 * \brief Message Transmit Request
 *
 * When this bit is set to 1 by MCU, the message in the tx buffer requests
 * transmission. The bit is automatically cleared when message is sent. To
 * abort a message, this bit can be set to 0 by MCU.
 *
 * \def TXP1
 * \brief Transmit Buffer Priority bit 1
 *
 * These two bits set the priority of the tx buffer.
 *
 * \code
 * TXP 1 0
 *     1 1 = Highest Message Priority
 *     1 0 = High Intermediate Message Priority
 *     0 1 = Low Intermediate Message Priority
 *     0 0 = Lowest Message Priority
 * \endcode
 *
 * \def TXP0
 * \brief Transmit Buffer Priority bit 0
 * \sa TXP1 for detailed documentation
 *
 */
#define ABTF                  6
#define MLOA                  5
#define TXERR                 4
#define TXREQ                 3
#define TXP1                  1
#define TXP0                  0

// EFLG

/*!
 * \def RX1OVR
 * \brief Receive Buffer 1 Overflow Flag
 *
 * Set when a valid message is received for RXB1 and CANINTF.RX1IF = 1.
 * Must be reset by MCU.
 *
 * \sa CANINTF
 * \sa RX1IF
 *
 * \def RX0OVR
 * \brief Receive Buffer 0 Overflow Flag
 *
 * Set when a valid message is received for RXB0 and CANINTF.RX0IF = 1.
 * Must be reset by MCU.
 *
 * \sa CANINTF
 * \sa RX0IF
 *
 * \def TXBO
 * \brief Bus-Off Error Flag
 *
 * Bit set when TEC reaches 255. Must be reset after a successful bus
 * recovery sequence.
 *
 * \def TXEP
 * \brief Transmit Error-Passive Flag
 *
 * Set when TEC is equal to or greater than 128. Reset when TEC is less
 * than 128.
 *
 * \sa TEC
 *
 * \def RXEP
 * \brief Receive Error-Passive Flag
 *
 * Set when REC is equal to or greater than 128. Reset when REC is less
 * than 128.
 *
 * \sa REC
 *
 * \def TXWAR
 * \brief Transmit Error Warning Flag
 *
 * Set when TEC is equal to or greater than 96. Reset when TEC is less
 * than 96.
 *
 * \sa TEC
 *
 * \def RXWAR
 * \brief Receive Error Warning Flag
 *
 * Set when REC is equal to or greater than 128. Reset when REC is less
 * than 128.
 *
 * \sa REC
 *
 * \def EWARN
 * \brief Error Warning Flag
 *
 * Set when TEC or REC is equal to or greater than 96 (TXWAR or RXWAR = 1).
 * reset when both REC and TEC are less than 96.
 *
 * \sa TXWAR, RXWAR
 * \sa TEC, REC
 *
 */
#define RX1OVR                7
#define RX0OVR                6
#define TXBO                  5
#define TXEP                  4
#define RXEP                  3
#define TXWAR                 2
#define RXWAR                 1
#define EWARN                 0

// CANINTE

/*!
 * \def MERRE
 * \brief Message Error Interrupt Enable
 *
 * If set to 1, interrupt on error during message reception or transmission.
 *
 * \sa MERRF
 *
 * \def WAKIE
 * \brief Wakeup Interrupt Enable
 *
 * If set to 1, interrupt on CAn bus activity. This is used to signal wake-up
 * on CAN towards MCU.
 *
 * \sa WAKIF
 *
 * \def ERRIE
 * \brief Error Interrupt Enable
 *
 * There are multiple sources located in EFLG register. Set to 1 results in
 * an interrupt on EFLG error condition change.
 *
 * \sa ERRIF
 * \sa EFLG
 *
 * \def TX2IE
 * \brief Transmit Buffer 2 Empty Interrupt Enable
 *
 * Set to 1, interrupt when tx buffer 2 (TXB2) becomes empty.
 *
 * \sa TX2IF
 *
 * \def TX1IE
 * \brief Transmit Buffer 1 Empty Interrupt Enable
 *
 * Set to 1, interrupt when tx buffer 1 (TXB1) becomes empty.
 *
 * \sa TX1IF
 *
 * \def TX0IE
 * \brief Transmit Buffer 0 Empty Interrupt Enable
 *
 * Set to 1, interrupt when tx buffer 0 (TXB0) becomes empty.
 *
 * \sa TX0IF
 *
 * \def RX1IE
 * \brief Receive Buffer 1 Full Interrupt Enable
 *
 * Set to 1, interrupt when message received in RXB1.
 *
 * \sa RX1IF
 *
 * \def RX0IE
 * \brief Receive Buffer 0 Full Interrupt Enable
 *
 * Set to 1, interrupt when message received in RXB0.
 *
 * \sa RX0IF
 */
#define MERRE                 7
#define WAKIE                 6
#define ERRIE                 5
#define TX2IE                 4
#define TX1IE                 3
#define TX0IE                 2
#define RX1IE                 1
#define RX0IE                 0

// CANINTF

/*!
 * \def MERRF
 * \brief Message Error Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa MERRE
 *
 * \def WAKIF
 * \brief Wakeup Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa WAKIE
 *
 * \def ERRIF
 * \brief Error Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa ERRIE
 *
 * \def TX2IF
 * \brief Transmit Buffer 2 Empty Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa TX2IE
 *
 * \def TX1IF
 * \brief Transmit Buffer 1 Empty Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa TX1Ie
 *
 * \def TX0IF
 * \brief Transmit Buffer 0 Empty Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa TX0IE
 *
 * \def RX1IF
 * \brief Receive Buffer 1 Full Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa RX1IE
 *
 * \def RX0IF
 * \brief Receive Buffer 0 Full Interrupt Flag
 *
 * Set to 1, an interrupt is pending. Must be cleared by MCU to reset
 * interrupt condition.
 *
 * \sa RX0IE
 */
#define MERRF                 7
#define WAKIF                 6
#define ERRIF                 5
#define TX2IF                 4
#define TX1IF                 3
#define TX0IF                 2
#define RX1IF                 1
#define RX0IF                 0


/*!
 * \def SJW1
 * \brief Synchronization Jump Width Length bit 1
 *
 * The SJW<1:0> bits select the Synchronization Jump Width Length in
 * terms of number of TQs.
 *
 * \code
 * SJW1 SJW0
 *    1    1 = Length = 4 x TQ
 *    1    0 = Length = 3 x TQ
 *    0    1 = Length = 2 x TQ
 *    0    0 = Length = 1 x TQ
 * \endcode
 *
 * \sa CNF1
 *
 * \def SJW0
 * \brief Synchronization Jump Width Length bit 0
 *
 * \sa CNF1
 * \sa SJW1
 *
 * \def BRP5
 * \brief Baud Rate Prescaler bit 5
 *
 * The BRP<5:0> bits control the baud rate prescaler. These bits set
 * the length of TQ relative to the OSC1 input frequency, with the
 * minimum TQ length being 2 TOSC (when BRP<5:0> = 'b000000').
 *
 * \code
 * TQ = 2 x (BRP + 1)/Fosc
 * \endcode
 *
 * \sa CNF1
 *
 * \def BRP4
 * \brief Baud Rate Prescaler bit 4
 *
 * \sa CNF1
 * \sa BRP5
 *
 * \def BRP3
 * \brief Baud Rate Prescaler bit 3
 *
 * \sa CNF1
 * \sa BRP5
 *
 * \def BRP2
 * \brief Baud Rate Prescaler bit 2
 *
 * \sa CNF1
 * \sa BRP5
 *
 * \def BRP1
 * \brief Baud Rate Prescaler bit 1
 *
 * \sa CNF1
 * \sa BRP5
 *
 * \def BRP0
 * \brief Baud Rate Prescaler bit 0
 *
 * \sa CNF1
 * \sa BRP5
 */
#define SJW1                  7
#define SJW0                  6
#define BRP5                  5
#define BRP4                  4
#define BRP3                  3
#define BRP2                  2
#define BRP1                  1
#define BRP0                  0

/**
 * \def BTLMODE
 * \brief PS2 Bit Time Length
 *
 * The BTLMODE bit controls how the length of PS2 is determined. If this
 * bit is set to a '1', the length of PS2 is determined by the PHSEG2<2:0>
 * bits of CNF3. If the BTLMODE bit is set to a '0', the length of PS2
 * is greater than that of PS1 and the information processing time (which
 * is fixed at 2 TQ for the MCP2515).
 *
 * \code
 * 1 = Length of PS2 determined by PHSEG22:PHSEG20 bits of CNF3
 * 0 = Length of PS2 is the greater of PS1 and IPT (2 TQ)
 * \endcode
 *
 * \sa CNF2
 * \sa PHSEG21
 * \sa PHSEG20
 *
 * \def SAM
 * \brief Sample Point Configuration
 *
 * The SAM bit controls how many times the RXCAN pin is sampled. Setting
 * this bit to a '1' causes the bus to be sampled three times: twice at
 * TQ/2 before the sample point and once at the normal sample point (which
 * is at the end of PS1). The value of the bus is determined to be the
 * majority sampled. If the SAM bit is set to a '0', the RXCAN pin is
 * sampled only once at the sample point.
 *
 * \code
 * 1 = Bus line is sampled three times at the sample point
 * 0 = Bus line is sampled once at the sample point
 * \endcode
 *
 * \sa CNF2
 *
 * \def PHSEG12
 * \brief PS1 Length bit 2
 *
 * The PHSEG1<2:0> bits set the length (in TQ's) of PS1.
 *
 * \code
 * (PHSEG1 + 1) x TQ
 * \endcode
 *
 * \sa CNF2
 *
 * \def PHSEG11
 * \brief PS1 Length bit 1
 *
 * \sa CNF2
 * \sa PHSEG12
 *
 * \def PHSEG10
 * \brief PS1 Length bit 0
 *
 * \sa CNF2
 * \sa PHSEG12
 *
 * \def PRSEG2
 * \brief Propagation Segment Length bit 2
 *
 * The PRSEG<2:0> bits set the length (in TQ's) of the propagation segment.
 *
 * \code
 * (PRSEG + 1) x TQ
 * \endcode
 *
 * \sa CNF2
 *
 * \def PRSEG1
 * \brief Propagation Segment Length bit 1
 *
 * \sa CNF2
 * \sa PRSEG2
 *
 * \def PRSEG0
 * \brief Propagation Segment Length bit 0
 *
 * \sa CNF2
 * \sa PRSEG2
 */
#define BTLMODE               7
#define SAM                   6
#define PHSEG12               5
#define PHSEG11               4
#define PHSEG10               3
#define PRSEG2                2
#define PRSEG1                1
#define PRSEG0                0

/*!
 * \def SOF
 * \brief Start-of-Frame signal bit
 *
 * \code
 * If CANCTRL.CLKEN = 1:
 * 1 = CLKOUT pin enabled for SOF signal
 * 0 = CLKOUT pin enabled for clockout function
 *
 * If CANCTRL.CLKEN = 0, Bit is don't care.
 * \endcode
 *
 * \sa CNF3
 * \sa CLKEN
 * \sa CANCTRL
 *
 * \def WAKFIL
 * \brief Wake-up Filter bit
 *
 * \code
 * 1 = Wake-up filter enabled
 * 0 = Wake-up filter disabled
 * \endcode
 *
 * \sa CNF3
 *
 * \def PHSEG22
 * \brief PS2 Length bit 2
 *
 * The PHSEG2<2:0> bits set the length (in TQ's) of PS2, if the CNF2.BTLMODE
 * bit is set to a '1'. If the BTLMODE bit is set to a '0', the PHSEG2<2:0>
 * bits have no effect.
 *
 * \code
 * (PHSEG2 + 1) x TQ
 * Minimum valid setting for PS2 is 2 TQ
 * \endcode
 *
 * \sa CNF3
 * \sa BTLMODE
 *
 * \def PHSEG21
 * \brief PS2 Length bit 1
 *
 * \sa CNF3
 * \sa PHSEG22
 *
 * \def PHSEG20
 * \brief PS2 Length bit 0
 *
 * \sa CNF3
 * \sa PHSEG22
 */
#define SOF                   7
#define WAKFIL                6
#define PHSEG22               2
#define PHSEG21               1
#define PHSEG20               0

/**
 * \def B2RTS
 * \brief TX2RTS Pin State
 *
 * - Reads state of TX2RTS pin when in Digital Input mode
 * - Reads as '0' when pin is in 'Request-to-Send' mode
 *
 * \sa TXRTSCTRL
 *
 * \def B1RTS
 * \brief TX1RTS Pin State
 *
 * - Reads state of TX1RTS pin when in Digital Input mode
 * - Reads as '0' when pin is in 'Request-to-Send' mode
 *
 * \sa TXRTSCTRL
 *
 * \def B0RTS
 * \brief TX0RTS Pin State
 *
 * - Reads state of TX0RTS pin when in Digital Input mode
 * - Reads as '0' when pin is in 'Request-to-Send' mode
 *
 * \sa TXRTSCTRL
 *
 * \def B2RTSM
 * \brief TX2RTS Pin mode
 *
 * \code
 * 1 = Pin is used to request message transmission of TXB2 buffer (on falling edge)
 * 0 = Digital input
 * \endcode
 *
 * \sa TXRTSCTRL
 *
 * \def B1RTSM
 * \brief TX1RTS Pin mode
 *
 * \code
 * 1 = Pin is used to request message transmission of TXB1 buffer (on falling edge)
 * 0 = Digital input
 * \endcode
 *
 * \sa TXRTSCTRL
 *
 * \def B0RTSM
 * \brief TX0RTS Pin mode
 *
 * \code
 * 1 = Pin is used to request message transmission of TXB0 buffer (on falling edge)
 * 0 = Digital input
 * \endcode
 *
 * \sa TXRTSCTRL
 */
#define B2RTS                 5
#define B1RTS                 4
#define B0RTS                 3
#define B2RTSM                2
#define B1RTSM                1
#define B0RTSM                0

/**
 * \def B1BFS
 * \brief RX1BF Pin State (Digital Output mode only)
 *
 * Reads as '0' when RX1BF is configured as interrupt pin
 *
 * \sa BFPCTRL
 *
 * \def B0BFS
 * \brief RX0BF Pin State (Digital Output mode only)
 *
 * Reads as '0' when RX0BF is configured as interrupt pin
 *
 * \sa BFPCTRL
 *
 * \def B1BFE
 * \brief RX1BF Pin Function Enable
 *
 * \code
 * 1 = Pin function enabled, operation mode determined by B1BFM bit
 * 0 = Pin function disabled, pin goes to high-impedance state
 * \endcode
 *
 * \sa BFPCTRL
 *
 * \def B0BFE
 * \brief RX0BF Pin Function Enable
 *
 * \code
 * 1 = Pin function enabled, operation mode determined by B0BFM bit
 * 0 = Pin function disabled, pin goes to high-impedance state
 * \endcode
 *
 * \sa BFPCTRL
 *
 * \def B1BFM
 * \brief RX1BF Pin Operation Mode
 *
 * \code
 * 1 = Pin is used as interrupt when valid message loaded into RXB1
 * 0 = Digital Output mode
 * \endcode
 *
 * \sa BFPCTRL
 *
 * \def B0BFM
 * \brief RX0BF Pin Operation Mode
 *
 * \code
 * 1 = Pin is used as interrupt when valid message loaded into RXB0
 * 0 = Digital Output mode
 * \endcode
 *
 * \sa BFPCTRL
 */
#define B1BFS                 5
#define B0BFS                 4
#define B1BFE                 3
#define B0BFE                 2
#define B1BFM                 1
#define B0BFM                 0

// multiple registers CANSTATx

/**
 * \def OPMOD2
 * \brief Operation Mode bit 2
 *
 * \code
 * OPMOD2 OPMOD1 OPMOD0
 *      0      0      0 = Device is in the Normal operation mode
 *      0      0      1 = Device is in Sleep mode
 *      0      1      0 = Device is in Loopback mode
 *      0      1      1 = Device is in Listen-only mode
 *      1      0      0 = Device is in Configuration mode
 * \endcode
 *
 * \sa CANSTAT
 *
 * \def OPMOD1
 * \brief Operation Mode bit 1
 *
 * \sa CANSTAT
 * \sa OPMOD2
 *
 * \def OPMOD0
 * \brief Operation Mode bit 0
 *
 * \sa CANSTAT
 * \sa OPMOD2
 *
 * \def ICOD2
 * \brief Interrupt Flag Code bit 2
 *
 * \code
 * ICOD2 ICOD1 ICOD0
 *     0     0     0 = No Interrupt
 *     0     0     1 = Error Interrupt
 *     0     1     0 = Wake-up Interrupt
 *     0     1     1 = TXB0 Interrupt
 *     1     0     0 = TXB1 Interrupt
 *     1     0     1 = TXB2 Interrupt
 *     1     1     0 = RXB0 Interrupt
 *     1     1     1 = RXB1 Interrupt
 * \endcode
 *
 * \sa CANSTAT
 *
 * \def ICOD1
 * \brief Interrupt Flag Code bit 1
 *
 * \sa CANSTAT
 * \sa ICOD2
 *
 * \def ICOD0
 * \brief Interrupt Flag Code bit 0
 *
 * \sa CANSTAT
 * \sa ICOD2
 *
 */
#define OPMOD2                7
#define OPMOD1                6
#define OPMOD0                5
#define ICOD2                 3
#define ICOD1                 2
#define ICOD0                 1

// multiple registers CANCTRLx

/**
 * \def REQOP2
 * \brief Request Operation Mode bit 2
 *
 * \code
 * REQOP2 REQOP1 REQOP0
 *      0      0      0 = Set Normal Operation mode
 *      0      0      1 = Set Sleep mode
 *      0      1      0 = Set Loopback mode
 *      0      1      1 = Set Listen-only mode
 *      1      0      0 = Set Configuration mode
 * \endcode
 *
 * \note All other values for REQOP bits are invalid and should not be used
 * \note On power-up, REQOP = b'111'
 *
 * \sa CANCTRL
 *
 * \def REQOP1
 * \brief Request Operation Mode bit 1
 *
 * \sa CANCTRL
 * \sa REQOP2
 *
 * \def REQOP0
 * \brief Request Operation Mode bit 0
 *
 * \sa CANCTRL
 * \sa REQOP2
 *
 * \def ABAT
 * \brief Abort All Pending Transmissions
 *
 * \code
 * 1 = Request abort of all pending transmit buffers
 * 0 = Terminate request to abort all transmissions
 * \endcode
 *
 * \sa CANCTRL
 *
 * \def OSM
 * \brief One Shot Mode
 *
 * \code
 * 1 = Enabled. Message will only attempt to transmit one time
 * 0 = Disabled. Messages will reattempt transmission, if required
 * \endcode
 *
 * \sa CANCTRL
 *
 * \def CLKEN
 * \brief CLKOUT Pin Enable
 *
 * \code
 * 1 = CLKOUT pin enabled
 * 0 = CLKOUT pin disabled (Pin is in high-impedance state)
 * \endcode
 *
 * \sa CANCTRL
 *
 * \def CLKPRE1
 * \brief CLKOUT Pin Prescaler bit 1
 *
 * \code
 * CLKPRE1 CLKPRE0
 *       0       0 = Fclkout = System Clock/1
 *       0       1 = Fclkout = System Clock/2
 *       1       0 = Fclkout = System Clock/4
 *       1       1 = Fclkout = System Clock/8
 * \endcode
 *
 * \sa CANCTRL
 *
 * \def CLKPRE0
 * \brief CLKOUT Pin Prescaler bit 0
 *
 * \sa CANCTRL
 * \sa CLKPRE1
 */
#define REQOP2                7
#define REQOP1                6
#define REQOP0                5
#define ABAT                  4
#define OSM                   3
#define CLKEN                 2
#define CLKPRE1               1
#define CLKPRE0               0

/**
 * \def TXB2CNTRL_TXREQ
 * \brief Message Transmit Request buffer 2
 *
 * <b>Request-To-Send (RTS) Instruction</b>
 *
 * The RTS command can be used to initiate message transmission for one
 * or more of the transmit buffers. The MCP2515 is selected by lowering
 * the CS pin. The RTS command byte is then sent. The last 3 bits of
 * this command indicate which transmit buffer(s) are enabled to send.
 *
 * This command will set the TxBnCTRL.TXREQ bit for the respective
 * buffer(s). Any or all of the last three bits can be set in a single
 * command. If the RTS command is sent with nnn = 000, the command will
 * be ignored.
 *
 * \note The TXBnCTRL.TXREQ bit must be clear (indicating the transmit
 *       buffer is not pending transmission) before writing to the
 *       transmit buffer
 *
 * \code
 * 1 = Buffer is currently pending transmission (MCU sets this bit to
 *     request message be transmitted - bit is automatically cleared when
 *     the message is sent)
 * 0 = Buffer is not currently pending transmission (MCU can clear
 *     this bit to request a message abort)
 * \endcode
 *
 * \sa MCP2515_READ_STATUS
 *
 * \def TXB1CNTRL_TXREQ
 * \brief Message Transmit Request buffer 1
 *
 * \sa TXB2CNTRL_TXREQ
 * \sa MCP2515_READ_STATUS
 *
 * \def TXB0CNTRL_TXREQ
 * \brief Message Transmit Request buffer 0
 *
 * \sa TXB2CNTRL_TXREQ
 * \sa MCP2515_READ_STATUS
 */
#define TXB2CNTRL_TXREQ       6
#define TXB1CNTRL_TXREQ       4
#define TXB0CNTRL_TXREQ       2

// load TX buffer addresses

/**
 * \def TXB2ADDR
 * \brief Address Offset to TXB2
 *
 * <b>Message Request-To-Send (RTS)</b>
 *
 * Instructs controller to begin message transmission sequence for
 * any of the transmit buffers.
 *
 * \code
 * 1000 0nnn
 *       ^^^
 *       ||+- TXB0
 *       |+-- TXB1
 *       +--- TXB2
 * \endcode
 *
 * \def TXB1ADDR
 * \brief Address Offset to TXB1
 *
 * \sa TXB2ADDR
 *
 * \def TXB0ADDR
 * \brief Address Offset to TXB0
 *
 * \sa TXB2ADDR
 */
#define TXB2ADDR              4
#define TXB1ADDR              2
#define TXB0ADDR              0

/**
 * \def RXB_STATUSMASK
 * \brief RX buffer status mask
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB1
 * \brief Bit indicates message in RXB1
 *
 * Buffer information as bit - CANINTF.RXnIF bits are mapped to
 * bits 7 and 6
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB0
 * \brief Bit indicates message in RXB0
 *
 * \sa MCP2515_RX_STATUS
 * \sa RXB1
 */
#define RXB_STATUSMASK        0x60
#define RXB1                  7
#define RXB0                  6

/**
 * \def RXB_EXT
 * \brief Extended type frame received
 *
 * Msg type as value - the extended ID bit is mapped to bit 4.
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RTR
 * \brief RTR type frame received
 *
 * The RTR bit is mapped to bit 3.
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_MSGTYPEMASK
 * \brief Mask of the message type in RXBn.
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_STDFRAME
 * \brief Standard frame received
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_STDREMOTEFRAME
 * \brief Standard Remote frame received
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_EXTDATAFRAME
 * \brief Extended Data frame received
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_EXTREMOTEFRAME
 * \brief Extended Remote received
 *
 * \sa MCP2515_RX_STATUS
 */
#define RXB_EXT               4
#define RXB_RTR               3
#define RXB_MSGTYPEMASK       0x18
#define RXB_STDFRAME          0x00
#define RXB_STDREMOTEFRAME    0x01
#define RXB_EXTDATAFRAME      0x02
#define RXB_EXTREMOTEFRAME    0x03

/**
 * \def RXB_FILTERMATCHMASK
 * \brief RXBn filter match mask
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF0
 * \brief Acceptance Filter 0 indicator
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF1
 * \brief Acceptance Filter 1 indicator
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF2
 * \brief Acceptance Filter 2 indicator
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF3
 * \brief Acceptance Filter 3 indicator
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF4
 * \brief Acceptance Filter 4 indicator
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF5
 * \brief Acceptance Filter 5 indicator
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF0_RO_RXB1
 * \brief Acceptance Filter 0 indicator (rollover to RXB1)
 *
 * \sa MCP2515_RX_STATUS
 *
 * \def RXB_RXF1_RO_RXB1
 * \brief Acceptance Filter 1 indicator (rollover to RXB1)
 *
 * \sa MCP2515_RX_STATUS
 */
#define RXB_FILTERMATCHMASK   0x07
#define RXB_RXF0              0x00
#define RXB_RXF1              0x01
#define RXB_RXF2              0x02
#define RXB_RXF3              0x03
#define RXB_RXF4              0x04
#define RXB_RXF5              0x05
#define RXB_RXF0_RO_RXB1      0x06
#define RXB_RXF1_RO_RXB1      0x07


// RXBnSIDL (n = 0, 1)

/**
 * \def SRR
 * \brief Standard Frame Remote Transmit Request
 *
 * Only valid if IDE bit is set to 0. Indicates if the frames received
 * is a remote transmit request (1) or a normal data frame (0).
 *
 * \sa IDE Extended Identifier Flag
 *
 * \def IDE
 * \brief Extended Identifier Flag
 *
 * Indicates whether the received message is a standard frame (0) or a
 * extended frame (1).
 */
#define SRR                   4
#define IDE                   3

// TXBnDLC and RXBxDLC

/*!
 * \def RTR
 * \brief Remote Transmit Request
 * \par TXBnDLC
 * If set to 1 the frame transmitted will be a remote transmit request. If
 * it is set to 0, the frame will be a data message.
 *
 * \par RXBnDLC
 * On the reception side the bit means Extended Frame Remote Transmission
 * Request, which is only valid when RXBnSIDL.IDE is set to 1.
 *
 * \sa IDE Extended Identifier Flag
 *
 * \def DLC3
 * \brief Bit 3 of Data Length Code
 * \par TXBnDLC
 * Bit 0..3 of the DLC sets the number of data bytes (0..8) to be transmitted
 * when using TXBnDLC.
 *
 * \par RXBnDLC
 * When receiving a message the DLC bits show the length of the received
 * message.
 *
 * \note It is possible to set the DLC to a value greater than 8, however
 * only 8 bytes are transmitted
 *
 * \def DLC2
 * \brief Bit 2 of Data Length Code
 * \sa DLC3 for detailed description
 *
 * \def DLC1
 * \brief Bit 1 of Data Length Code
 * \sa DLC3 for detailed description
 *
 * \def DLC0
 * \brief Bit 0 of Data Length Code
 * \sa DLC3 for detailed description
 */
#define RTR                   6
#define DLC3                  3
#define DLC2                  2
#define DLC1                  1
#define DLC0                  0

/*! @} */

/**************************************************************************/
/* MCP2515 MODES OF OPERATION                                             */
/**************************************************************************/

/**
 * \addtogroup mcp_mode_of_operation MCP2515 Modes of Operation
 * \brief MCP2515 supports different modes of operation
 * @{
 */

/*!
 * \def MODE_SELECT_MASK
 * \brief selection mask for any mode settings
 *
 * The mask is used to prvide easy access to the operation mode bits
 * of the CANCTRL register.
 *
 * \sa CANCTRL(x)
 */
#define MODE_SELECT_MASK      ((1 << REQOP2) | (1 << REQOP1) | (1 << REQOP0))

/**
 * \def NORMAL_MODE
 * \brief standard operation mode
 *
 * This is the standard operation mode. In this mode the controller actively
 * monitors and reacts to the CAN stream. This is the only mode to transmit
 * CAN frames to the bus.
 * \sa CANCTRL(x)
 *
 * \def SLEEP_MODE
 * \brief mode to reduce power consumption
 *
 * During sleep mode the power consumption is reduced to a minimum.
 * Nevertheless the controller registers can be accessed via SPI the
 * whole time, to allow wake up and other operations while the chip
 * sleeps (on CAN).
 *
 * The internal oscillator is stopped during sleep.
 *
 * When setting up the wakup interrupt, any activity on the bus can wake up
 * the controller.
 * \sa CANCTRL(x)
 * \sa WAKIE, WAKIF
 * \sa CANINTE, CANINTF
 *
 * \def LOOPBACK_MODE
 * \brief internal CAN loopback
 *
 * This mode is used for testing during development. The transmit buffer
 * will be put directly to the receive buffer without actually sending
 * anything on the bus. Filters can be applied too.
 * \sa CANCTRL(x)
 *
 * \def LISTEN_ONLY_MODE
 * \brief listen only to the bus
 *
 * This mode can be used for monitoring or baud rate detection applications.
 *
 * The mode is also set, when waking up. So no messages are accidentally sent
 * to the CAN bus after sleep mode.
 * \sa CANCTRL(x)
 * \sa SLEEP_MODE
 *
 * \def CONFIG_MODE
 * \brief mode to configure the controller
 *
 * This mode can be entered anytime and automatically after power-up. The
 * controller needs to be configured prior activation. It's the only mode
 * to set the following control registers:
 * - CNF1, CNF2, CNF3
 * - TXRTSCTRL
 * - Filter registers
 * - Mask registers
 *
 * \sa CANCTRL(x)
 * \sa CNF1, CNF2, CNF3
 * \sa TXRTSCTRL
 */
#define NORMAL_MODE           0
#define SLEEP_MODE            (1 << REQOP0)
#define LOOPBACK_MODE         (1 << REQOP1)
#define LISTEN_ONLY_MODE      (1 << REQOP1) | (1 << REQOP0)
#define CONFIG_MODE           (1 << REQOP2)

/*! @} */



#endif /* CAN_DEFS_MCP2515_H_ */
