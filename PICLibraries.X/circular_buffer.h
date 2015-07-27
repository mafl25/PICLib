#ifndef CIRCULAR_BUFFER_H
#define	CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 0x40  //Must always be 2^n, up to 128, otherwise increase
						  //the integer type in the structure

struct circular_buffer {
	uint8_t position;
    uint8_t count;
    uint8_t data[BUFFER_SIZE];
};

int16_t buffer_pop(struct circular_buffer *buffer);
bool buffer_push(struct circular_buffer *buffer, uint8_t byte);
bool buffer_full(const struct circular_buffer *buffer);
bool buffer_empty(const struct circular_buffer *buffer);
uint8_t buffer_count(const struct circular_buffer *buffer);
uint8_t buffer_space(const struct circular_buffer *buffer);

#endif