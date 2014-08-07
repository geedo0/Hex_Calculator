#include "support.h"

int currentBase = BASE_DEC;
char currentInput[17] = "12345";

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

    //Change Notification
    CNPD1bits.CN11PDE = 1;
    CNPD1bits.CN12PDE = 1;
    CNEN1bits.CN11IE = 1;
    CNEN1bits.CN12IE = 1;
    IPC4 = 0x4000;
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

int scanKeys() {
    unsigned int testRow = 0x04;
    unsigned int testCol;
    unsigned int key = 0;
    for(testRow = 0x04; testRow <= 0x08; testRow <<= 1){
        MATRIX_REG |= testRow;
        for(testCol = 0x8000; testCol >= 0x4000; testCol >>= 1) {
            if(testCol & MATRIX_REG) {
                return key;
            }
            key++;
        }
        MATRIX_REG &= ~testRow;
    }
    return -1;
}

void blockForKey() {
    IFS1bits.CNIF = 0;
    Nop();
    IEC1bits.CNIE = 1;
    Sleep();
}

void changeBase(int base) {
    unsigned int oldInput;
    oldInput = parseInput();
    lcdClear();
    currentBase = base;
    switch(base) {
        case BASE_BIN:
            lcdSetCursor(10,1);
            lcdPrint("Binary");
            break;
        case BASE_OCT:
            lcdSetCursor(11,1);
            lcdPrint("Octal");
            break;
        case BASE_DEC:
            lcdSetCursor(9,1);
            lcdPrint("Decimal");
            break;
        case BASE_HEX:
            lcdSetCursor(5,1);
            lcdPrint("Hexadecimal");
            break;
    }
    lcdHome();
    updateInput(oldInput);
    lcdPrint(currentInput);
}

unsigned int parseInput() {
    char* pInput = currentInput;
    char digit;
    unsigned int output = 0;

    while(*pInput != 0) {
        digit = *pInput;
        pInput++;
        switch(currentBase) {
            case BASE_BIN:
                output <<= 1;
                output |= digit - 48;
                break;
            case BASE_OCT:
                output <<= 3;
                output |= digit - 48;
                break;
            case BASE_DEC:
                output *= 10;
                output += digit - 48;
                break;
            case BASE_HEX:
                output <<= 4;
                if((digit >= '0') && (digit <= '9'))
                    output |= digit - 48;
                else
                    output |= digit - 55;
                break;
        }
    }
    return output;
}

void updateInput(unsigned int number) {
    char buffer[16];
    char *pBuffer = buffer;
    char digit;

    if(number == 0) {
        *pBuffer = '0';
        pBuffer++;
    }
    else {
        while(number != 0) {
            switch(currentBase) {
                case BASE_BIN:
                    digit = number & 0x1;
                    number >>= 1;
                    *pBuffer = digit + 48;
                    pBuffer++;
                    break;
                case BASE_OCT:
                    digit = number & 0x7;
                    number >>= 3;
                    *pBuffer = digit + 48;
                    pBuffer++;
                    break;
                case BASE_DEC:
                    digit = number % 10;
                    number /= 10;
                    *pBuffer = digit + 48;
                    pBuffer++;
                    break;
                case BASE_HEX:
                    digit = number & 0xf;
                    number >>= 4;
                    if(digit <= 9)
                        digit += 48;
                    else
                        digit += 55;
                    *pBuffer = digit;
                    pBuffer++;
                    break;
            }
        }
    }
    //Reuse digit variable as an iterator
    digit = 0;
    pBuffer--;
    while(pBuffer >= buffer) {
        currentInput[digit++] = *pBuffer;
        pBuffer--;
    }
    currentInput[digit] = 0x00;
}

void _ISR _T1Interrupt(void) {
    IFS0 &= ~_IFS0_T1IF_MASK;
    T1CON &= ~_T1CON_TON_MASK;
    IEC0bits.T1IE = 0;
}

void _ISR _CNInterrupt(void) {
    IEC1bits.CNIE = 0;
    IFS1bits.CNIF = 0;
    MATRIX_REG &= ~ROW_MASK;
    //Debounce 40ms
    delayCycles(10000);
}