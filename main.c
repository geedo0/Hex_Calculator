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
    changeBase(currentBase);

    for(;;) {
        MATRIX_REG |= ROW_MASK;
        blockForKey();      //Press
        key = scanKeys();
        blockForKey();      //Release
        MATRIX_REG &= ~RGB_MASK;
        lcdClear();
        lcdHome();
        switch(key) {
            case 3: //Button 0
                changeBase(BASE_BIN);
                break;
            case 1: //Button 1
                changeBase(BASE_OCT);
                break;
            case 2: //Button 2
                changeBase(BASE_DEC);
                break;
            case 0: //Button 3
                changeBase(BASE_HEX);
                break;
            default:
                break;
        }
    }
    return 0;
}
