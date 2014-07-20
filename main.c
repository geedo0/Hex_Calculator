/*
 * File:   main.c
 * Author: Gerardo
 *
 * Created on July 13, 2014, 9:28 PM
 */


// PIC24F08KL302 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include "config.h"
#include "lcd.h"

#define MATRIX_REG      PORTB

void init() {
    OSCCON = 0x7000;    //FRC+PLL+Postscaler
    CLKDIV = 0x100;     //FRC /2
    OSCTUN = 0x0000;    //Calibration

    //Port A = LCD_REG
    //Port B = MATRIX_REG
    // RB2 to RB8 = Rows = Outputs, RB9 to RB15 = Cols = Inputs
    ANSA = 0x0000;
    ANSB = 0x0000;
    TRISA = 0x0000;
    TRISB = 0x01FC;
    LCD_REG = 0x0000;
    MATRIX_REG = 0x0000;
}

void delay(unsigned int iters) {
    int i, j;
    for(j = 0; j < iters; j++)
        for(i = 0; i < 0xffff; i++);
}

int main(void) {
    int freq = 2;
    init();

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
