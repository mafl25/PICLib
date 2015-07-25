/* 
 * File:   encoding.h
 * Author: Manuel
 *
 * Created on July 25, 2015, 12:12 AM
 */

#include <stdint.h>

#ifndef ENCODING_H
#define	ENCODING_H


/* P_START_MASK is used when a packet of 15 or less byte is going to be sent.*
 * LP_START_MASK_1 and LP_START_MASK_2 are used if a packet of up to 255 bytes
 * is going to be sent.
 * DATA_MASK is the mask that will be used when encoding data.
 * END_BYTE indicates the end of a packet.
 * DUMMY_BYTE is used when filler bytes are needed.
 * ERROR_MASK is used when an error code needs to be sent.*/
#define P_START_MASK        0xA0
#define LP_START_MASK_1     0xB0
#define LP_START_MASK_2     0xC0
#define DATA_MASK           0xD0
#define END_BYTE            0xE0
#define DUMMY_BYTE          0xF0
#define ERROR_MASK          0x80  // TODO: Make error codes.

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

