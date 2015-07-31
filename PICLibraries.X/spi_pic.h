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

#define SAMPLING_MODE   0x80
#define CLK_SELECT      0x40

#define SPI_ENABLE      0x20
#define CLK_POLARITY    0x10
//Modes:
#define SLAVE_NO_SS     0x05
#define SLAVE_SS        0x04
#define MASTER_TMR2     0x03
#define MASTER_F64      0x02
#define MASTER_F16      0x01
#define MASTER_F4       0x00

void setup_spi(uint8_t register_1, uint8_t register_2);

//For both
uint8_t spi_send_get_byte(uint8_t byte);
bool spi_slave_peek_receive(bool get_byte, int16_t *byte);
//void spi_load_buffer(uint8_t byte);

//int8_t spi_send_data(uint8_t *data, int8_t size, uint8_t *returned_data);
//int8_t spi_master_get_data(uint8_t *data, int8_t size);

//void spi_set_dummy_byte(uint8_t byte);
//uint8_t spi_get_dummy_byte(void);

////For slave
//
int16_t spi_slave_get_byte(void);
//uint8_t spi_slave_get_data(uint8_t *data, int8_t size);

#endif	/* SPI_PIC_H */

