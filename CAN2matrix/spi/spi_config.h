/*
 * spi_config.h
 *
 * Created: 28.11.2011 18:16:39
 *  Author: MKleemann
 */


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_

/* @brief SPI_PRESCALER must have a value which is 2^n (n = 1..7)
 *
 * Start with 8 as default, which is always a good value. ;-)
 */
#ifndef SPI_PRESCALER
   #define SPI_PRESCALER   8
#endif

// now start calculating prescaler values. Start with SPI2X bit...
#if (SPI_PRESCALER == 2) || (SPI_PRESCALER == 8) || (SPI_PRESCALER == 32) || (SPI_PRESCALER == 64)
   #define R_SPSR          (1<<SPI2X)
   #define SPI_PRESCALER_  (SPI_PRESCALER * 2)  // to make it easier in the next step
#else
   #define R_SPSR       0
   #define SPI_PRESCALER_  SPI_PRESCALER
#endif

// ... and add SPR0/1.
#if (SPI_PRESCALER_ == 4)
   #define  R_SPCR   0
#elif (SPI_PRESCALER_ == 16)
   #define  R_SPCR   (1<<SPR0)
#elif (SPI_PRESCALER_ == 64)
   #define  R_SPCR   (1<<SPR1)
#elif (SPI_PRESCALER_ == 128)
   #define  R_SPCR   (1<<SPR1) | (1<<SPR0)
#else
   #error    SPI_PRESCALER must be one of the values of 2^n with n = 1..7!
#endif

/***************************************************************************/
/* PORT PINS FOR SPI - here ATmega8                                        */
/***************************************************************************/
#define SCK_PORT            PORTB
#define MISO_PORT           PORTB
#define MOSI_PORT           PORTB

#define SCK_DDR             DDRB
#define MISO_DDR            DDRB
#define MOSI_DDR            DDRB

#define SCK_BIT             5
#define MISO_BIT            4
#define MOSI_BIT            3

#endif /* SPI_CONFIG_H_ */