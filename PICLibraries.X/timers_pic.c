#include "timers_pic.h"

void setup_timer3(uint8_t T3CON_reg)
{
    T3CON = T3CON_reg;
}

void set_timer3(int16_t value)
{
    PIR2bits.TMR3IF = 0;
    TMR3 = value;
}

void timer3_interrupt(bool toggle)
{
    if (toggle)
        INTCON |= 0xC0;
    
    PIE2bits.TMR3IE = (toggle) ? 1: 0;
}

bool timer3_up(void)
{
    return (PIR2bits.TMR3IF) ? true : false;
}