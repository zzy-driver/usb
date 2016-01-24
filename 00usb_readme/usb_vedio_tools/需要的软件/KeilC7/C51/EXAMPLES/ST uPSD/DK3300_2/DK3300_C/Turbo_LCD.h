// LCD_IO.h - Function prototypes for LCD I/O routines.

#ifndef _LCD_IO_H_
#define _LCD_IO_H_



// Read Only from Command register
#define  BF_BIT  0x80       // Busy flag

// Write Only to Command register
#define DD_ADDR 0x80        // set DDRAM address
#define CG_ADDR 0x40        // set CGRAM address

#define LCD_LINE_LENGTH  0x000F		// length of single line on lcd display



void SetUserCG(unsigned char*);
void lcd_init(void);
void BusyCheck(void);
void setXY_LCD(unsigned char,unsigned char);
void putch_LCD(unsigned char);
void printfLCD(unsigned char*,...);
char Bin2Hex(unsigned char);

void lcd_clear(void);
void lcd_string_display(unsigned char row, unsigned char col, char *); 
void lcd_char_display(unsigned char row, unsigned char col, char ch); 
void lcd_cursor_set(unsigned char row, unsigned char col);	
void copy_message(unsigned int, unsigned int);	

char htoa_lo(unsigned char byte);
char lhtoa_lo(unsigned int word);
char htoa_hi(unsigned char byte);
char lhtoa_hi(unsigned int word);
void MoveCursor(char m_direction, unsigned char m_step);

void PwmSetDuty_Mode1(unsigned char PwmDuty_Mode1);
void PwmInit_Mode1(unsigned char PwmDuty_Mode1);
#endif
