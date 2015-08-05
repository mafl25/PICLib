/* 
 * File:   spi_pic.h
 * Author: Manuel
 *
 * Created on July 25, 2015, 7:55 PM
 */

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef SPI_PIC_H
#define	SPI_PIC_H

/*
 * This first group of masks go in the "register_1" parameter. They need to be
 * OR'ed together.
 * SAMPLING_MODE is used to sample data at the end of data output time,
 * otherwise he data is sampled at the middle of data output time.
 * CLK_SELECT is used to transmit the data on the transition from active to idle
 * clock state, otherwise the transmit occurs on the transition from idle to
 * active clock state.
 */
#define SAMPLING_MODE   0x80
#define CLK_SELECT      0x40

/*
 * This second group of masks go in the "register_2" parameter. They need to be
 * OR'ed together.
 * SPI_ENABLE is used to enable the PSI module, otherwise it will be configured
 * but not turned on.
 * CLK_POLARITY is used to set the idle state of the SPI clock at a high level,
 * otherwise the idle state of t he clock will be a low level.
 * The following are the available modes of SPI operation:
 * SLAVE_NO_SS -> Slave mod with no slave select.
 * SLAVE_SS -> Slave mode with slave select.
 * MASTER_TMR2 -> Master mode with the timer2 oscillator as clock.
 * MASTER_F64 -> Master mode with clock at Fosc/64 frequency.
 * MASTER_F16 -> Master mode with clock at Fosc/16 frequency.
 * MASTER_F4  -> Master mode with clock at Fosc/4 frequency.
 */
#define SPI_ENABLE      0x20
#define CLK_POLARITY    0x10
//Modes:
#define SLAVE_NO_SS     0x05
#define SLAVE_SS        0x04
#define MASTER_TMR2     0x03
#define MASTER_F64      0x02
#define MASTER_F16      0x01
#define MASTER_F4       0x00


/*
 * The function "setup_spi" is used to iniialized the SPI module. To configure
 * it, use the previous two mask on the two parameters. 
 */
void setup_spi(uint8_t register_1, uint8_t register_2);

/*
 * The function "spi_send_get_byte" sends a byte and returns the received byte.
 * If used in slave mode, it will wait until the master sends the data.
 */
uint8_t spi_send_get_byte(uint8_t byte);
bool spi_slave_peek_receive(bool get_byte, int16_t *byte);
void spi_load_buffer(uint8_t byte);

int8_t spi_send_data(uint8_t *data, int8_t size, uint8_t *returned_data);
int8_t spi_master_get_data(uint8_t *data, int8_t size);

void spi_set_dummy_byte(uint8_t byte);
uint8_t spi_get_dummy_byte(void);

int16_t spi_slave_get_byte(void);
uint8_t spi_slave_get_data(uint8_t *data, int8_t size);

#endif	/* SPI_PIC_H */

