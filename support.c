#include "support.h"

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
    TRISB = 0xFE00;
    LCD_REG = 0x0000;
    MATRIX_REG = 0x0000;

    //Timer1 module for general delays at 250khz
    T1CON = 0x10;  //(Fosc/2) /8
    TMR1 = 0;
    IFS0 &= ~_IFS0_T1IF_MASK;
    IPC0 |= 0x4000;
}



//250khz
void delayCycles(int cycles) {
    IFS0 &= ~_T1IF;
    TMR1 = 0;
    PR1 = cycles;
    IEC0bits.T1IE = 1;
    T1CON |= _T1CON_TON_MASK;
    Idle();
}


