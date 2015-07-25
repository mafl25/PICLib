/* 
 * File:   main.c
 * Author: Manuel
 *
 * Created on July 25, 2015, 12:10 AM
 */

#include <xc.h>
#include "encoding.h"
#include "serial.h"
#include "spi.h"

int main() {
    
    spi_peek_receive(false, 0);
    
    return (0);
}

