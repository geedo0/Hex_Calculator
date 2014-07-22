#include "lcd.h"

void lcdClear() {
    lcdSend(LCD_COMMAND, LCD_CLEARDISPLAY);
    delayCycles(500);   //2ms
}

void lcdHome() {
    lcdSend(LCD_COMMAND, LCD_RETURNHOME);
    delayCycles(500);   //2ms
}

void lcdPrint(char *string) {
    while(*string != 0x00) {
        lcdSend(LCD_DATA, *string);
        string++;
    }
}

void lcdPrintSlow(char *string) {
    while(*string != 0x00) {
        lcdSend(1, *string);
        string++;
        delayCycles(0xffff);
    }
}

void lcdSetCursor(unsigned char col, unsigned char row) {
  int row_offsets[] = {0x00, 0x40};
  lcdSend(LCD_COMMAND, LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void lcdInit() {
    int i;
    LCD_REG = 0;

    delayCycles(12500); //50ms
    for(i = 0; i < 3; i++) {
        LCD_REG = 0x03;
        lcdLatch();
        delayCycles(1125);  //4.5ms
    }
    LCD_REG = 0x02;
    lcdLatch();

    lcdSend(LCD_COMMAND, LCD_FUNCTIONSET + LCD_4BITMODE + LCD_2LINE + LCD_5x8DOTS);
    lcdSend(LCD_COMMAND, LCD_ENTRYMODESET + LCD_ENTRYINCREMENT + LCD_SHIFTDISABLE);
    lcdSend(LCD_COMMAND, LCD_DISPLAYCONTROL + LCD_DISPLAYON + LCD_CURSOROFF + LCD_BLINKOFF);
    lcdClear();
}

void lcdSend(int address, unsigned char out) {
    //Assumes 4-bit mode is enabled
    //Address 0 = Instruction Register, 1 = Data Register
    if(address)
        LCD_REG = LCD_RS;
    else
        LCD_REG = 0;
    LCD_REG |= (out >> 4);
    lcdLatch();
    LCD_REG &= ~0xf;
    LCD_REG |= (out & 0xf);
    lcdLatch();
    delayCycles(25);    //100us
}

void lcdLatch() {
    LCD_REG |= LCD_EN;
    delayCycles(1);     //4us
    LCD_REG &= ~LCD_EN;
}
//250khz
void delayCycles(int cycles) {
    IFS0 &= ~_T1IF;
    TMR1 = 0;
    PR1 = cycles;
    T1CON |= _T1CON_TON_MASK;
    while(!(IFS0 & _IFS0_T1IF_MASK));
    IFS0 &= ~_IFS0_T1IF_MASK;
    T1CON &= ~_T1CON_TON_MASK;
}

