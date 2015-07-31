/* 
 * File:   timers_pic.h
 * Author: Manuel
 *
 * Created on July 29, 2015, 12:49 PM
 */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifndef TIMERS_PIC_H
#define	TIMERS_PIC_H

#define TMR3_16BIT_MODE     0x80
#define TMR3_PRESCALE_8     0x30
#define TMR3_PRESCALE_4     0x20
#define TMR3_PRESCALE_2     0x10
#define TMR3_PRESCALE_1     0x00
#define TMR3_NO_SYNC_CLK    0x04
#define TMR3_EXT_CLOCK      0x02
#define TMR3_TIMER_ON       0x01

void setup_timer3(uint8_t register_1);
void set_timer3(int16_t value);
void timer3_interrupt(bool toggle);
bool timer3_up(void);

#endif	/* TIMERS_PIC_H */

