/*
 * File:   main.c
 * Author: Gerardo
 *
 * Created on July 13, 2014, 9:28 PM
 */
#include "config.h"
#include "support.h"
#include "lcd.h"

#define RGB_MASK   0x1C0

int main(void) {
    int key;
    init();
    lcdInit();

    lcdSend(LCD_COMMAND, LCD_DISPLAYCONTROL + LCD_DISPLAYON + LCD_CURSORON + LCD_BLINKON);
    lcdPrint("Key Matrix + LCD");
    lcdSetCursor(0, 1);
    lcdPrint("Demo");

    for(;;) {
        MATRIX_REG |= ROW_MASK;
        blockForKey();      //Press
        key = scanKeys();
        blockForKey();      //Release
        MATRIX_REG &= ~RGB_MASK;
        lcdClear();
        lcdHome();
        switch(key) {
            case 0:
                lcdPrintSlow("Gerardo Ravago");
                break;
            case 1:
                lcdPrint("Red Selected");
                MATRIX_REG |= 0x40;
                break;
            case 2:
                lcdPrint("Green Selected");
                MATRIX_REG |= 0x100;
                break;
            case 3:
                lcdPrint("Blue Selected");
                MATRIX_REG |= 0x80;
                break;
            default:
                break;
        }
    }
    return 0;
}
