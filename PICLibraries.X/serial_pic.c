#include "serial_pic.h"

struct interrupt_serial 
{
    bool tx_int_enable;
    uint8_t *data;
    int8_t length;
    int8_t position;
};

static struct interrupt_serial interrupt_data;

void setup_serial(uint8_t TXSTA_reg, uint8_t RCSTA_reg,  uint8_t BAUDCON_reg,
                  uint16_t baudrate_value)
{
    if (RCSTA_reg & SERIAL_ENABLE) {
        RX_AN = 0;
    }
    
    TXSTA = TXSTA_reg;
    RCSTA = RCSTA_reg;
    BAUDCON = BAUDCON_reg;
    
    SPBRGH = baudrate_value >> 8;
    SPBRG = baudrate_value;
}

void setup_simple_serial(uint8_t baudrate_bits, uint16_t baudrate_value)
{
    RX_AN = 0;
    TXSTA = (baudrate_bits & BRGH_BIT) ? 0x24: 0x20;
    RCSTA = 0x90;
    BAUDCON = (baudrate_bits & BRG16_BIT) ? 0x08 : 0x00;
    
    SPBRGH = baudrate_value >> 8;
    SPBRG = baudrate_value;
}

bool serial_peek_receive(bool get_byte, uint8_t *byte)
{
    if (get_byte) {
        if (RCIF) {
            *byte = RCREG;
            return true;
        } else {
            return false;
        }
    }
    
    return (RCIF) ? true : false;
}

uint8_t serial_get_byte(void)
{
    while (!RCIF);
    
    return RCREG;
}

int8_t serial_get_data(uint8_t *data, int8_t size)
{
    int8_t i;
    
    if (size < 0) {
        for (i = 0; data[i] != 0; i++)
            data[i] = serial_get_byte();
        data[i] = 0;
    } else {
        for (i = 0; i < size; i++)
            data[i] = serial_get_byte();
    }
    
    return i;
}

void serial_send_byte(uint8_t byte)
{
    while (!TXIF);
    TXREG = byte;
}

int8_t serial_send_data(uint8_t *data, int8_t size)
{
    int8_t i;
    
    if (size < 0) {
        for (i = 0; data[i] != 0; i++)
            serial_send_byte(data[i]);
        serial_send_byte(0);
    } else {
        for (i = 0; i < size; i++)
            serial_send_byte(data[i]);
    }
    
    return i;
}

void serial_interrupts(uint8_t interrupts)
{
    if (interrupts & (RX_INTERRUPT | TX_INTERRUPT)) {
        INTCON |= 0xC0;
        RCIE = (interrupts & RX_INTERRUPT) ? 1 : 0;
        interrupt_data.tx_int_enable = (interrupts & TX_INTERRUPT) ? true : false;
    }
}

void serial_disable_interrupts(uint8_t interrupts, bool all_interrupts)
{
    if (all_interrupts)
        INTCON &= 0x3F;
    
    if (interrupts & RX_INTERRUPT)
        RCIE = 0;
    
    if (interrupts & TX_INTERRUPT)
        interrupt_data.tx_int_enable = false;
}

void serial_load_buffer(uint8_t *buffer, int8_t size)
{
    if (interrupt_data.tx_int_enable) {
        interrupt_data.data = buffer;
        interrupt_data.length = size;
        interrupt_data.position = 0;
        
        TXIE  = 1;
    }
}

int8_t serial_send_buffer(void)
{   
    if (TXIF && TXIE) {
        if (interrupt_data.length < 0) {
            if (interrupt_data.data[interrupt_data.position] != 0) {
                serial_send_byte(interrupt_data.data[interrupt_data.position]);
                interrupt_data.position++;
            } else {
                TXIE  = 0;
            }
        } else if (interrupt_data.position < interrupt_data.length) {
            serial_send_byte(interrupt_data.data[interrupt_data.position]);
            interrupt_data.position++;
            if (interrupt_data.position == interrupt_data.length)
                TXIE  = 0;
        }
        
        return interrupt_data.position;
    } else {
        return -1;
    }
}

uint8_t serial_receive_error(bool clear)
{
    uint8_t error = 0;
    
    if (RCSTAbits.FERR && RCSTAbits.OERR) {
        error = 3;
    } else if (RCSTAbits.FERR) {
        error = 2;
    } else if (RCSTAbits.OERR) {
        error = 1;
    }
    
    if (clear) {
        RCSTAbits.SPEN  = 0;
        RCSTAbits.SPEN  = 1;
    }
    
    return error;
}