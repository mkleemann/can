/*
 * uart.h
 *
 * Created: 28.11.2011 18:16:09
 *  Author: MKleemann
 */


#ifndef UART_H_
#define UART_H_

#include "uart_config.h"

/* @brief initializes uart interface
 *
 */
void uart_init();

/* @brief  put byte to uart interface
 * @param  byte to be transmitted to UART
 * @return nothing
 */
void uart_putc(const uint8_t data);

/* @brief  put null terminated string to uart interface
 * @param  null terminated string
 * @return nothing
 */
void uart_puts(const char *data);

/* @brief  read byte from UART, wait until something happens
 * @param  nothing
 * @return received byte
 */
uint8_t uart_getc_wait (void);


/* @brief  read byte from UART, but don't wait for it
 * @param  nothing
 * @return received byte, -1 otherwise
 */
int uart_getc_nowait(void);


#endif /* UART_H_ */