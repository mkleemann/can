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
 * adc_config.h
 *
 * Created: 24.02.2012 19:59:37
 *  Author: MKleemann
 */


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/**
 * @brief set voltage reference
 *
 * REFS1 REFS0 Voltage Reference Selection
 *     0     0 AREF, Internal Vref turned off
 *     0     1 AVCC with external capacitor at AREF pin
 *     1     0 Reserved
 *     1     1 Internal 2.56V Voltage Reference with external capacitor at
 *             AREF pin
 */
#define ADC_REF_SELECT        (1 << REFS0)

/**
 * @brief input channel selection
 *
 * MUX3..0 Single Ended Input
 *    0000 ADC0
 *    0001 ADC1
 *    0010 ADC2
 *    0011 ADC3
 *    0100 ADC4
 *    0101 ADC5
 *    0110 ADC6
 *    0111 ADC7
 *    1000
 *    1001
 *    1010
 *    1011
 *    1100
 *    1101
 *    1110 1.30V (VBG)
 *    1111 0V (GND)
 */
#define ADC_INPUT_CHANNEL     0
#define ADC_INPUT_PIN         C,ADC_INPUT_CHANNEL

/**
 * @brief prescaler value between Fosc and CLKadc
 *
 * ADPS2 ADPS1 ADPS0 Division Factor
 *     0     0     0 2
 *     0     0     1 2
 *     0     1     0 4
 *     0     1     1 8
 *     1     0     0 16
 *     1     0     1 32
 *     1     1     0 64
 *     1     1     1 128
 */
#define ADC_PRESCALER         (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)

/**
 * @brief use only upper 8bit of ADC value
 */
#define ADC_8BIT_RESOLUTION

#endif /* ADC_CONFIG_H_ */