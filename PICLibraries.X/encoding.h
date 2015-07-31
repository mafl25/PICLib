/* 
 * File:   encoding.h
 * Author: Manuel
 *
 * Created on July 25, 2015, 12:12 AM
 */

#include <stdint.h>

#ifndef ENCODING_H
#define	ENCODING_H


/*
 * DATA_MASK is the mask that will be used when encoding data.
 */

#define DATA_MASK           0xA0

/* 
 * The function "encode_data" takes a byte (variable "data") and encodes it. 
 * The result is stored  in two bytes: "byte_1" and "byte_2". The first nibble 
 * of these two bytes is DATA_MASK. The first nibble of "data" is stored on the 
 * second nibble of "byte_1"; the second nibble of "data" is stored on the 
 * second nibble of "byte_2".
 */
void encode_data(uint8_t data, uint8_t *byte_1, uint8_t *byte_2);

/* 
 * The function "decode_data" takes "byte_1" and "byte_2" and decodes them into 
 * one byte. It returns -1 if "byte_1" had incorrect encoding, -2 if "byte_2" 
 * did. The output is stored in "data".
 */
int8_t decode_data(uint8_t *data, uint8_t byte_1, uint8_t byte_2);



#endif	/* ENCODING_H */

