/* 
 * File:   serial.h
 * Author: Manuel
 *
 * Created on July 25, 2015, 2:48 AM
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef SERIAL_H
#define	SERIAL_H

#define RX_AN        ANSELHbits.ANS11

/*
 * This first group of masks go in the "register_1" parameter. They need to be
 * OR'ed together.
 * SYNCHRONOUS will set the serial to synchronous mode. The default is 
 * asynchronous mode.
 * MASTER_MODE is used when in synchronous mode to choose between working as a 
 * master. The default when in synchronous mode is slave.
 * NINTH_BIT_TX is used to activate 9-bit transmission.
 * BRGH_BIT is used when  selecting the baudrate. Check the Excel file for help.
 * TX_ENABLE is used to activate the transmitter. The default value is inactive
 * transmitter.
 */
#define SYNCHRONOUS     0x10
#define MASTER_MODE     0x80
#define NINTH_BIT_TX    0x40
#define BRGH_BIT        0x04
#define TX_ENABLE       0x20

/*
 * This second group of masks go in the "register_2" parameter. They need to be
 * OR'ed together.
 * SERIAL_ENABLE is used to turn on the serial module. The default is off.
 * NINTH_BIT_RX enables 9-bit transmission.
 * SINGLE_RX_EN when in synchronous mode, this option enables a single receive.
 * RX_ENABLE when in asynchronous mode this enables reception. In synchronous
 * mode, it enables continuous receive (it will override SINGLE_RX_EN).
 * ADDRESS_EN is used to enable address detection.
 */

#define SERIAL_ENABLE   0x80
#define NINTH_BIT_RX    0x40
#define SINGLE_RX_EN    0x20
#define RX_ENABLE       0x10
#define ADDRESS_EN      0x08

/*
 * This third group of masks go in the "register_3" parameter. They need to be
 * OR'ed together.
 * DATA_RX_POL when in asynchronous mode, this option is used when the receive 
 * data polarity is active-low, otherwise it will be active-high. When in 
 * synchronous mode this option is used when the data polarity is active-low,
 * if not used, the polarity will be active-high.
 * CLK_TX_POL when in asynchronous mode, this option sets the idle state for 
 * transmit low, otherwise it will be high. When in synchronous mode, this 
 * option will cause data to change on the falling edge of the clock and is 
 * sampled on the rising edge of the clock, otherwise data changes on the rising
 * edge of the clock and is sampled on the falling edge of the clock.
 * BRG16_BIT is used when  selecting the baudrate. Check the Excel file for 
 * help.
 * WAKE_UP_EN when in asynchronous mode wakes up the device when a byte is 
 * received.
 * AUTO_BAUD when in asynchronous automatically selects a baudrate.
 */

#define DATA_RX_POL     0x20
#define CLK_TX_POL      0x10
#define BRG16_BIT       0x08
#define WAKE_UP_EN      0x02
#define AUTO_BAUD       0x01

/*
 * These to masks are used to select RX and/or TX.
 */

#define RX_INTERRUPT    0x01
#define TX_INTERRUPT    0x02

#define NONE            0x00


/*
 * The function "setup_serial" is used to initialize the serial port. To 
 * configure it, used the previous masks on the first three parameters. Use the 
 * provided Excel file to calculate the appropriate value for "baudrate_value".   
 */
void setup_serial(uint8_t register_1, uint8_t register_2, uint8_t register_3,
                  uint16_t baudrate_value);

/*
 * The function "setup_simple_serial" allows for a way to configure the serial
 * port for asynchronous serial communication. Use the BRG16_BIT, BRGH_BIT or 
 * NONE in the first parameter. Use the provided Excel file to calculate the 
 * appropriate value for "baudrate_value"
 */
void setup_simple_serial(uint8_t baudrate_bits, uint16_t baudrate_value);

/*
 * The function "serial_peek_receive" checks if the PIC has received data. As 
 * parameters, you can set "get_byte2 as true and pass a variable to "byte" if
 * you want to get the byte in case the PIC has received one. It return true or
 * false if there is or isn't a byte waiting to be read.
 */
bool serial_peek_receive(bool get_byte, uint8_t *byte);


/*
 * The function "serial_get_byte" waits to receive a byte and returns it.
 */
uint8_t serial_get_byte(void);

/*
 * The function "serial_get_data" waits until "size" amount of data has been 
 * received. The data is stored in "*data", so make sure you have the necessary 
 * memory. If "size" is -1, it will store data until a 0 byte is received. This
 * function returns the amount of bytes received.
 */
int8_t serial_get_data(uint8_t *data, int8_t size);


/*
 * The function "serial_send_byte" sends a single byte.
 */
void serial_send_byte(uint8_t byte);

/*
 * The function "serial_send_data" send "size" amount of bytes store in "*data".
 * If size is equal to -1, it will send data until a 0 byte is encountered. The
 * amount of bytes sent is returned.
 */
int8_t serial_send_data(uint8_t *data, int8_t size);


/*
 * The function "serial_interrupts" is used to activate serial interrupts. Use
 * the RX_INTERRUPT and TX_INTERRUPT masks to select which interrupts to 
 * activate. These masks should be OR'ed in the "interrupts" parameter.
 */
void serial_interrupts(uint8_t interrupts);

/*
 * The function "serial_disable_interrupts" disables the serial interrupts.
 * Use the RX_INTERRUPT and TX_INTERRUPT masks to select which interrupts to 
 * disable. These masks should be OR'ed in the "interrupts" parameter. The 
 * "all_interrupts" if you want to disable all interrupts in the PIC, not only 
 * serial related interrupts.
 */
void serial_disable_interrupts(uint8_t interrupts, bool all_interrupts);

/*
 * The function "serial_load_buffer" is used when transmit interrupts are 
 * enabled. It stores a pointer to some data and as each interrupt happens, the
 * function "serial_send_buffer" will send "size" amount of bytes. If size 
 * equals -1, then it will send bytes until a 0 byte is found.
 */
void serial_load_buffer(uint8_t *buffer, int8_t size);

/*
 * The function "serial_send_buffer" is to be used in the interrupt handler. It
 * will send the data loaded by "serial_load_buffer", one byte at the time. It
 * returns the amount of bytes sent so far.
 */
int8_t serial_send_buffer(void);


/*
 * The function "serial_receive_error" is used to check for serial receive 
 * errors. If a framing error occurs a 2 is returned, if a overrun error occurs
 * a 1 is returned, if both errors occurred, a 3 is returned, If "clear" is set 
 * to true, it will clear all errors.
 */
uint8_t serial_receive_error(bool clear);

#endif	/* SERIAL_H */