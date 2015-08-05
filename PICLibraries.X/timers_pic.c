#include "timers_pic.h"

void setup_timer0(uint8_t T0CON_reg)
{
    T0CON = T0CON_reg;
}

void set_timer0(int16_t value)
{
    INTCONbits.TMR0IF = 0;
    TMR0 = value;
}

void timer0_interrupt(bool toggle)
{
    if (toggle)
        INTCON |= 0xC0;
    
    INTCONbits.TMR0IE = (toggle) ? 1: 0;
}

bool timer0_up(void)
{
    return (INTCONbits.TMR0IF) ? true : false;
}

//******************************

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