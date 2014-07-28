/*
 * File:   main.c
 * Author: Gerardo
 *
 * Created on July 13, 2014, 9:28 PM
 */
#include "config.h"
#include "support.h"
#include "lcd.h"

int main(void) {
    int key;
    init();
    lcdInit();

    lcdSend(LCD_COMMAND, LCD_DISPLAYCONTROL + LCD_DISPLAYON + LCD_CURSORON + LCD_BLINKON);
    lcdPrint("Gerardo Ravago");

    for(;;) {
        MATRIX_REG = ROW_MASK;
        blockForKey();      //Press
        key = scanKeys();
        blockForKey();      //Release
        switch(key) {
            case 0:
                lcdClear();
                lcdHome();
                break;
            case 1:
                lcdSend(LCD_DATA, 0x31);
                break;
            case 2:
                lcdSend(LCD_DATA, 0x32);
                break;
            case 3:
                lcdSend(LCD_DATA, 0x30);
                break;
            default:
                break;
        }
    }
    return 0;
}
