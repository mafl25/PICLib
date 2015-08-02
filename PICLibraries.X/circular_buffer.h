#ifndef CIRCULAR_BUFFER_H
#define	CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 0x20  //Must always be 2^n, up to 128, otherwise increase
						  //the integer type in the structure

struct circular_buffer {
	uint8_t position;
    uint8_t count;
    uint8_t data[BUFFER_SIZE];
};

/*
 * The function "buffer_pop" takes a pointer to a circular_buffer struct 
 * and returns the next value. (FIFO buffer) If the buffer is empty, it will 
 * return a -1.
 */
int16_t buffer_pop(struct circular_buffer *buffer);

/*
 * The function "buffer_push" pushes a value to a circular_buffer struct.
 * If after the byte was pushed, the buffer is full, it will return false.
 * TODO: Unit test this change
 */
bool buffer_push(struct circular_buffer *buffer, uint8_t byte);

/*
 * The function "buffer_full" checks if a buffer is full. It returns true if 
 * it is full.
 */
bool buffer_full(const struct circular_buffer *buffer);

/*
 * The function "buffer_empty" checks if a buffer is empty. It returns true if 
 * it is empty.
 */
bool buffer_empty(const struct circular_buffer *buffer);

/*
 * The function "buffer_count" returns the amount of elements in a 
 * circular_buffer struct.
 */
uint8_t buffer_count(const struct circular_buffer *buffer);

/*
 * The function "buffer_space" returns the amount of space in a 
 * circular_buffer struct.
 */
uint8_t buffer_space(const struct circular_buffer *buffer);

/*
 *
 */
void buffer_clear(struct circular_buffer *buffer);
uint8_t buffer_peek(const struct circular_buffer *buffer);


#endif