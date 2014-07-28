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

#define LCD_REG         PORTA
#define MATRIX_REG      PORTB

#define COL_MASK        0xC000 //0xFC00;
#define ROW_MASK        0x0C

void init();
void delayCycles(int cycles);

#ifdef	__cplusplus
}
#endif

#endif	/* SUPPORT_H */

