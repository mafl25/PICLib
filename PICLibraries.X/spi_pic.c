#include "spi_pic.h"

#define SDI_TRIS    TRISBbits.RB4
#define SDI_AN      ANSELHbits.ANS10
#define SDO_TRIS    TRISCbits.RC7
#define SCK_TRIS    TRISBbits.RB6
#define SS_TRIS     TRISCbits.RC6 
#define SS_AN       ANSELHbits.ANS8

static uint8_t dummy_byte;

void setup_spi(uint8_t SSPSTAT_reg, uint8_t SSPCON1_reg)
{
    SDO_TRIS = 0;
    SDI_AN = 0;
    SDI_TRIS = 1;
    
    SSPSTAT = SSPSTAT_reg;
    SSPCON1 = SSPCON1_reg;
    
    if (SSPCON1bits.SSPM == SLAVE_NO_SS || SSPCON1bits.SSPM == SLAVE_SS) {
        SCK_TRIS = 1;
        if (SSPCON1bits.SSPM == SLAVE_SS) {
            SS_AN = 0;
            SS_TRIS = 1;
        }
        SSPSTATbits.SMP = 0;
    } else {
        SCK_TRIS = 0;
    }
}

uint8_t spi_send_get_byte(uint8_t byte)
{
    SSPBUF = byte;
    while (!SSPSTATbits.BF);
    if (SSPCON1bits.WCOL)
        SSPCON1bits.WCOL = 0;
    return SSPBUF;
}

bool spi_slave_peek_receive(bool get_byte, int16_t *byte)
{
    if (get_byte) {
        if (SSPSTATbits.BF) {
            *byte = spi_slave_get_byte();
            return true;
        } else {
            return false;
        }
    }
        
    return (SSPSTATbits.BF) ? true : false;
}

void spi_load_buffer(uint8_t byte)
{
    SSPBUF = byte;
}

int8_t spi_send_data(uint8_t *data, int8_t size, uint8_t *returned_data)
{
    int8_t i;
    uint8_t returned;
    
    if (size < 0) {
        for (i = 0; data[i] != 0; i++) {
            returned = spi_send_get_byte(data[i]);
            if (returned_data)
                returned_data[i] = returned;
        }
        returned = spi_send_get_byte(dummy_byte);
        if (returned_data)
                returned_data[i] = returned;
    } else {
        for (i = 0; i < size; i++) {
            returned = spi_send_get_byte(data[i]);
            if (returned_data)
                returned_data[i] = returned;
        }
    }
    
    return i;
}

int8_t spi_master_get_data(uint8_t *data, int8_t size)
{
    int8_t i;
    
    if (size < 0) {
        for (i = 0; data[i] != 0; i++)
            data[i] = spi_send_get_byte(dummy_byte);
        data[i] = 0;
    } else {
        for (i = 0; i < size; i++)
            data[i] = spi_send_get_byte(dummy_byte);
    }
    
    return i;
}

void spi_set_dummy_byte(uint8_t byte)
{
    dummy_byte = byte;
}
uint8_t spi_get_dummy_byte(void)
{
    return dummy_byte;
}

int16_t spi_slave_get_byte(void)
{
    while (!SSPSTATbits.BF);
    uint8_t byte = SSPBUF;
    SSPBUF = dummy_byte;
    if (SSPCON1bits.SSPOV) {
        SSPCON1bits.SSPOV = 0;
        byte = -1;
    }
    return byte;
}

uint8_t spi_slave_get_data(uint8_t *data, int8_t size)
{
    int8_t i;
    
    if (size < 0) {
        for (i = 0; data[i] != 0; i++)
            data[i] = spi_slave_get_byte();
        data[i] = 0;
    } else {
        for (i = 0; i < size; i++)
            data[i] = spi_slave_get_byte();
    }
    
    return i;
}