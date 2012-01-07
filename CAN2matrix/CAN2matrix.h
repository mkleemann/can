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
 * CAN2matrix.h
 *
 * Created: 28.11.2011 18:13:35
 *  Author: MKleemann
 */


#ifndef CAN2MATRIX_H_
#define CAN2MATRIX_H_

/***************************************************************************/
/* DEFINITIONS                                                             */
/***************************************************************************/


/***************************************************************************/
/* INT0 trigger definition                                                 */
/*                                                                         */
/* ISC01 ISC00 Description                                                 */
/*     0     0 The low level of INT0 generates an interrupt request        */
/*     0     1 Any logical change on INT0 generates an interrupt request   */
/*     1     0 The falling edge of INT0 generates an interrupt request     */
/*     1     1 The rising edge of INT0 generates an interrupt request      */
/***************************************************************************/
#define EXTERNAL_INT0_TRIGGER    (1 << ISC01)
#define EXTERNAL_INT0_ENABLE     (1 << INT0)

/***************************************************************************/
/* INT1 trigger definition                                                 */
/*                                                                         */
/* ISC11 ISC10 Description                                                 */
/*     0     0 The low level of INT1 generates an interrupt request        */
/*     0     1 Any logical change on INT1 generates an interrupt request   */
/*     1     0 The falling edge of INT1 generates an interrupt request     */
/*     1     1 The rising edge of INT1 generates an interrupt request      */
/***************************************************************************/
//#define EXTERNAL_INT1_TRIGGER    (1 << ISC11)
//#define EXTERNAL_INT1_ENABLE     (1 << INT1)

/***************************************************************************/
/* AVR sleep modes: power down                                             */
/*                                                                         */
/* SM2 SM1 SM0 Sleep Mode                                                  */
/*   0   0   0 Idle                                                        */
/*   0   0   1 ADC Noise Reduction                                         */
/*   0   1   0 Power-down                                                  */
/*   0   1   1 Power-save                                                  */
/*   1   1   0 Standby                                                     */
/***************************************************************************/
//#define AVR_SLEEP_MODE           (1 << SM1)


/***************************************************************************/
/* HELPER ROUTINES                                                         */
/***************************************************************************/

/**
 * @brief sends message to CAN2 and filling up converted data
 *
 * Note: Set message id before calling this function.
 *
 * @param pointer to CAN message
 */
void sendCan2Message(can_t* msg);


#endif /* CAN2MATRIX_H_ */