/* 
 * File:   support.h
 * Author: Gerardo
 *
 * Created on July 27, 2014, 9:02 PM
 */

#ifndef SUPPORT_H
#define	SUPPORT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "lcd.h"

#define LCD_REG             PORTA
#define MATRIX_REG          PORTB

#define COL_MASK            0xC000 //0xFC00;
#define ROW_MASK            0x0C

#define BASE_BIN            0x00
#define BASE_OCT            0x01
#define BASE_DEC            0x02
#define BASE_HEX            0x04

extern int currentBase;
extern char currentInput[];

void init();
void delayCycles(int cycles);
int scanKeys();
void blockForKey();

void changeBase(int base);
unsigned int parseInput();
void updateInput(unsigned int number);

void _T1Interrupt(void);
void _CNInterrupt(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SUPPORT_H */

