/*
 * File:   main.c
 * Author: Gerardo
 *
 * Created on July 13, 2014, 9:28 PM
 */


// PIC24F08KL302 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>

void delay(unsigned int iters) {
    int i, j;
    for(j = 0; j < iters; j++)
        for(i = 0; i < 0xffff; i++);
}

int main(void) {
    int freq = 1;
    //Configure Clock
    OSCCON = 0x7000;    //FRC+PLL+Postscaler, Clock Lock, Lock PLL
    CLKDIV = 0x100;     //FRC /2, 1:1 CPU:Peripheral
    OSCTUN = 0x0000;    //Calibrate

    ANSA = 0x0000;
    ANSB = 0x0000;

    TRISA = 0;
    TRISB = 0;

    while(1) {
        PORTB = 0xaaaa;
        PORTA = 0xaaaa;
        delay(freq);
        PORTB = 0x5555;
        PORTA = 0x5555;
        delay(freq);
    }

    return 0;
}
