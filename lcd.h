/* 
 * File:   lcd.h
 * Author: Gerardo
 *
 * Created on July 20, 2014, 8:02 PM
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "support.h"

#define LCD_RS          0x10
#define LCD_EN          0x40
#define LCD_PWR         0x80

#define LCD_COMMAND     0
#define LCD_DATA        1

//Commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

//Entry Mode Flags
#define LCD_ENTRYDECREMENT 0x00
#define LCD_ENTRYINCREMENT 0x02
#define LCD_SHIFTENABLE 0x01
#define LCD_SHIFTDISABLE 0x00

//Display Control Flags
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

//Display Shift Flags
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

//Function Set Flags
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

extern unsigned char displaySettings;

void lcdClear();
void lcdHome();

void lcdSetCursor(unsigned char col, unsigned char row);
void lcdPrint(char *string);
void lcdPrintSlow(char * string);

void lcdInit();
void lcdSend(int address, unsigned char out);

void lcdLatch();
void delayCycles(int cycles);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

