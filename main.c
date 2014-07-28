/*
 * File:   main.c
 * Author: Gerardo
 *
 * Created on July 13, 2014, 9:28 PM
 */
#include "config.h"
#include "support.h"
#include "lcd.h"


void _ISR _T1Interrupt(void) {
    IFS0 &= ~_IFS0_T1IF_MASK;
    T1CON &= ~_T1CON_TON_MASK;
    IEC0bits.T1IE = 0;
}

int main(void) {
    init();
    lcdInit();

    lcdSend(LCD_COMMAND, LCD_DISPLAYCONTROL + LCD_DISPLAYON + LCD_CURSORON + LCD_BLINKON);
    lcdPrint("Gerardo Ravago");
    return 0;
}
