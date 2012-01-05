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
 * uart.c
 *
 * Setup U(S)ART for debugging or communication. Can be used for
 * ATmega8
 * ATmega8515
 *
 * Created: 28.11.2011 18:17:02
 *  Author: MKleemann
 */

#include <avr/io.h>

#include "uart.h"


/* @brief initializes uart interface
 *
 */
void uart_init()
{
   // set USART baud rate register
   UBRRH = (R_UBRR >> 8);
   UBRRL = (R_UBRR & 0xFF);

   // USART transmitter and receiver
   UCSRB = (1 << RXEN) | (1 << TXEN);
   // data mode 8N1, asynchronuous
   UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

   // flush receive buffer (remove artefacts)
   do
   {
      UDR;
   }
   while (UCSRA & (1 << RXC));
}

/* @brief  put byte to uart interface
 * @param  byte to be transmitted to UART
 * @return nothing
 */
void uart_putc(const uint8_t data)
{
   // wait until UDR is ready for a new value
   while (!(UCSRA & (1 << UDRE)))
      ;

   // writing UDR starts transmission
   UDR = data;
}

/* @brief  put null terminated string to uart interface
 * @param  null terminated string
 * @return nothing
 */
void uart_puts(const char *data)
{
   do
   {
      uart_putc (*data);
   }
   while (*data++);
}

/* @brief  read byte from UART, wait until something happens
 * @param  nothing
 * @return received byte
 */
uint8_t uart_getc_wait (void)
{
   // wait until something is received
   while (!(UCSRA & (1 << RXC)))
      ;

   // return received byte
   return (UDR);
}

/* @brief  read byte from UART, but don't wait for it
 * @param  nothing
 * @return received byte, -1 otherwise
 */
int uart_getc_nowait(void)
{
   // returns received byte, -1 otherwise
   return(UCSRA & (1 << RXC)) ? (int) UDR : -1;
}



