#include "encoding.h"

void encode_data(uint8_t data, uint8_t *byte_1, uint8_t *byte_2)
{
    *byte_1 = DATA_MASK;
    *byte_2 = DATA_MASK;
    
    *byte_1 |= data >> 4;
    *byte_2 |= (data & 0x0F);
}

int8_t decode_data(uint8_t *data, uint8_t byte_1, uint8_t byte_2)
{
    if ((byte_1 & 0xF0) != DATA_MASK)
        return -1;
    else if ((byte_2 & 0xF0) != DATA_MASK)
        return -2;

    *data = (byte_1 << 4) | (byte_2 & 0x0F);
    
    return 0;
}
