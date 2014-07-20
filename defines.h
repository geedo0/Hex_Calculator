/* 
 * File:   defines.h
 * Author: Gerardo
 *
 * Created on July 20, 2014, 4:31 PM
 */

#ifndef DEFINES_H
#define	DEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LCD_REG         PORTA
#define MATRIX_REG      PORTB

#define LCD_RS          0x10
#define LCD_EN          0x40
#define LCD_PWR         0x80

#ifdef	__cplusplus
}
#endif

#endif	/* DEFINES_H */

