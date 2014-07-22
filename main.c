/*
 * File:   main.c
 * Author: Gerardo
 *
 * Created on July 13, 2014, 9:28 PM
 */


// PIC24F08KL302 Configuration Bit Settings

// 'C' source line config statements

#include "config.h"
#include "lcd.h"
#include <xc.h>

#define MATRIX_REG      PORTB

void init() {
    //Clock settings, Internal oscillator = 8Mhz/2 = 4Mhz
    OSCCON = 0x7000;    //FRC+Postscaler
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

    //Timer1 module for general delays at 250khz
    T1CON = _T1CON_TSIDL_MASK + 0x10;  //(Fosc/2) /8
    TMR1 = 0;
    IFS0 &= ~_IFS0_T1IF_MASK;

    lcdInit();
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
