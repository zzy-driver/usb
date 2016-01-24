/*------------------------------------------------------------------------------
LCD_IO.C

uPSD LCD Display Device Driver Functions
06/2002 Ver 0.1 - Initial Version

Note: Some functions have been commented out so as to remove linker warnings
      for code segments that are not used.


Copyright 2002 STMicroelectrons Inc.

This example demo code is provided as is and has no warranty,
implied or otherwise.  You are free to use/modify any of the provided
code at your own risk in your applications with the expressed limitation
of liability (see below) so long as your product using the code contains
at least one uPSD products (device).

LIMITATION OF LIABILITY:   NEITHER STMicroelectronics NOR ITS VENDORS OR 
AGENTS SHALL BE LIABLE FOR ANY LOSS OF PROFITS, LOSS OF USE, LOSS OF DATA,
INTERRUPTION OF BUSINESS, NOR FOR INDIRECT, SPECIAL, INCIDENTAL OR
CONSEQUENTIAL DAMAGES OF ANY KIND WHETHER UNDER THIS AGREEMENT OR
OTHERWISE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
------------------------------------------------------------------------------*/


#include "uPSD3300.h"
#include "TurboLite_hardware.h"
#include "Turbo_timer.h"
#include "Turbo_LCD.h"

typedef xdata struct LCD_display_st {
    unsigned char LCD_CMD_WR;       //   LCD_BASE+0x00
    unsigned char LCD_CMD_RD;       //           +0x01
    unsigned char LCD_RAM_WR;       //           +0x02
    unsigned char LCD_RAM_RD;       //           +0x03
}  LCD_DISPLAY;

// XDATA address for display 
xdata LCD_DISPLAY LCD_reg _at_ LCD_BASE_ADDR;

static unsigned char Cursor_LCD;

//  These are the LCD functions.

code unsigned char cg_data[] = {

        0x1E,   //db    00011110b
        0x1C,   //db    00011100b
        0x18,   //db    00011000b
        0x11,   //db    00010001b
        0x13,   //db    00010011b
        0x1F,   //db    00011111b
        0x0F,   //db    00001111b
        0x06,   //db    00000110b

        0x0F,   //db    00001111b
        0x1E,   //db    00011110b
        0x1C,   //db    00011100b
        0x19,   //db    00011001b
        0x13,   //db    00010011b
        0x0F,   //db    00001111b
        0x0F,   //db    00001111b
        0x06,   //db    00000110b

        0x07,   //db    00000111b
        0x0F,   //db    00001111b
        0x1E,   //db    00011110b
        0x1C,   //db    00011100b
        0x18,   //db    00011000b
        0x13,   //db    00010011b
        0x03,   //db    00000011b
        0x03,   //db    00000011b

        0x00,   //db    00000000b
        0x01,   //db    00000001b
        0x03,   //db    00000011b
        0x07,   //db    00000111b
        0x0F,   //db    00001111b
        0x1E,   //db    00011110b
        0x1C,   //db    00011100b
        0x18,   //db    00011000b

        0x1E,   //db    00011110b
        0x1E,   //db    00011110b
        0x1E,   //db    00011110b
        0x10,   //db    00010000b
        0x00,   //db    00000000b
        0x00,   //db    00000000b
        0x00,   //db    00000000b
        0x00,   //db    00000000b

        0x1C,   //db    00011100b
        0x1C,   //db    00011100b
        0x1C,   //db    00011100b
        0x00,   //db    00000000b
        0x1C,   //db    00011100b
        0x1C,   //db    00011100b
        0x1C,   //db    00011100b
        0x1C,   //db    00011100b

        0x00,   //db    00000000b       // data for '\'
        0x10,   //db    00010000b
        0x08,   //db    00001000b
        0x04,   //db    00000100b
        0x02,   //db    00000010b
        0x01,   //db    00000001b
        0x00,   //db    00000000b
        0x00,   //db    00000000b

        -1
};
/*
void MoveCursor(char m_direction, unsigned char m_step)
{
    unsigned char i;
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x0C;//Close cursor
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x02;//Cursor home
    if(m_step>=16)
    {   
        m_step=m_step-16;
        printfLCD("\n");
    }
    for(i=0;i<m_step;i++)
    {
        BusyCheck();
        if(m_direction==1)LCD_reg.LCD_CMD_WR = 0x10;//Left shift
        else LCD_reg.LCD_CMD_WR = 0x14;             //Right shift
    }
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x0E;//Open Cursor
}
*/
void SetUserCG(unsigned char *data_ptr) // initialize user character pattern
{
    BusyCheck();
    LCD_reg.LCD_CMD_WR = CG_ADDR | (8*1);       //from character code 1

    while (*data_ptr != -1) {
        BusyCheck();
        LCD_reg.LCD_RAM_WR = *data_ptr++;
    }
}

void lcd_init(void)     // initialize LCD module per specs   
{
    delay_10ms();
    LCD_reg.LCD_CMD_WR = 0x30;
    delay_10ms();       
    LCD_reg.LCD_CMD_WR = 0x30;
    delay_10ms();       
    LCD_reg.LCD_CMD_WR = 0x30;
    delay_10ms();       

    LCD_reg.LCD_CMD_WR = 0x38;  // 8 bits, 2 lines, 5 x 7 font   
    delay_10ms();               // delay 4 ms   
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x0C;  //Display on, Cursor off, Non-Blink
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x01;  //Clear display
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x02;  //Cursor home
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x06;  //Cursor inc, no shift/cursor move
        
    SetUserCG(&cg_data);        //set user desfined character

    Cursor_LCD = DD_ADDR;       //Display from 1st row, 1st column
    BusyCheck();
    LCD_reg.LCD_CMD_WR = Cursor_LCD;
}


void BusyCheck(void)            // wait until BF is cleared
{
    unsigned char i;
    while (LCD_reg.LCD_CMD_RD & BF_BIT);
    // Add some delay for the slow LCD device - Do NOT Remove
    for (i=0; i<10; i++) i++;  // Add Delay 
}

/*
void setXY_LCD (unsigned char row, unsigned char col)
{
    Cursor_LCD = (DD_ADDR | ((row & 0x01) << 6)) + (col & LCD_LINE_LENGTH);
    BusyCheck();
    LCD_reg.LCD_CMD_WR = Cursor_LCD;
}


void putch_LCD(unsigned char ch)
{
    BusyCheck();
    LCD_reg.LCD_RAM_WR = ch;
}
*/

/*
 * putchar (basic version): expands '\n' into CR LF
 * This function is used to output Data to the LCD. It is used by printf, puts.
 */
char putchar (char c)
{
    BusyCheck();
    if (c == '\r') {
        Cursor_LCD &= 0xC0;                 //return to position 0 at current line
        LCD_reg.LCD_CMD_WR = Cursor_LCD;
    }
    else if (c == '\n')
    {
        Cursor_LCD ^= 0x40;                 //goto next line
        Cursor_LCD &= 0xC0;                 //return to position 0
        LCD_reg.LCD_CMD_WR = Cursor_LCD;
    }
    else {
        LCD_reg.LCD_RAM_WR = c;
    }
    return (c);
}


/*
void printfLCD(unsigned char *chr_ptr, ...) {

unsigned char *var_ptr=&chr_ptr+1;
unsigned char var;

    while (*chr_ptr != NULL) {
        
        BusyCheck();
        
        if (*chr_ptr == '\r') {
            chr_ptr++;
            Cursor_LCD &= 0xC0;                 //return to position 0 at current line
            LCD_reg.LCD_CMD_WR = Cursor_LCD;
        }
        else
        if (*chr_ptr == '\n') {
            chr_ptr++;
            Cursor_LCD ^= 0x40;                 //goto next line
            Cursor_LCD &= 0xC0;                 //return to position 0
            LCD_reg.LCD_CMD_WR = Cursor_LCD;
        }
        else
        if (*chr_ptr == '%') {
            chr_ptr++;
            if (*chr_ptr == 'd') {          // display 1 digit decimal 0-9
                chr_ptr++;

                    var = *var_ptr++;
                    LCD_reg.LCD_RAM_WR = (var & 0x0F)+'0';
            }
                else
                if (*chr_ptr == 'x') {              // display 1 byte hex 00-FF
                chr_ptr++;

                    var = *var_ptr++;
                    //LCD_reg.LCD_RAM_WR = Bin2Hex(var>>4);
                    LCD_reg.LCD_RAM_WR = htoa_hi(var);
                    BusyCheck();
                    //LCD_reg.LCD_RAM_WR = Bin2Hex(var&0x0F);
                    LCD_reg.LCD_RAM_WR = htoa_lo(var);
            }
            else
            if (*chr_ptr == 'w') {          // display 1 word hex 0000-FFFF
                chr_ptr++;

                    var = *var_ptr++;
                    //LCD_reg.LCD_RAM_WR = Bin2Hex(var>>4);
                    LCD_reg.LCD_RAM_WR = htoa_hi(var);
                    BusyCheck();
                    //LCD_reg.LCD_RAM_WR = Bin2Hex(var&0x0F);
                    LCD_reg.LCD_RAM_WR = htoa_lo(var);

                    BusyCheck();

                    var = *var_ptr++;
                    //LCD_reg.LCD_RAM_WR = Bin2Hex(var>>4);
                    LCD_reg.LCD_RAM_WR = htoa_hi(var);
                    BusyCheck();
                    //LCD_reg.LCD_RAM_WR = Bin2Hex(var&0x0F);
                    LCD_reg.LCD_RAM_WR = htoa_lo(var);
            }
            else {
                LCD_reg.LCD_RAM_WR = *chr_ptr++;    //out character to LCD Diaplay RAM
            }
        }
        else
        {
            LCD_reg.LCD_RAM_WR = *chr_ptr++;        //out character to LCD Diaplay RAM
        }
    }
}
*/

/*
char Bin2Hex(char temp)
{
    if (temp <= 9) temp += '0'; else temp=(temp-10)+'A';
    return (temp);
}
*/

//  These are the LCD functions.

/*
void lcd_clear(void)            // clear all characters from display
{
    BusyCheck();
    LCD_reg.LCD_CMD_WR = 0x01;
    Cursor_LCD = DD_ADDR;
}

void lcd_string_display(unsigned char row, unsigned char col, unsigned char *string)
                // send string to LCD   
                // row = 0 is top row   
                // row = 1 is bottom    
                // col = 0 to 15        
                // length = string length   
                // string points to char array   
{
    char k;
    k = 0;
    lcd_cursor_set(row,col);                    // position cursor
    while (k < LCD_LINE_LENGTH+1 && *string)    // truncate string to 16
    {                                           // or end of string
        BusyCheck();
        LCD_reg.LCD_RAM_WR = *string++;         // send character
        k++;
    }
}

void lcd_char_display(unsigned char row, unsigned char col, char ch)   // send single char to LCD
                    // row = 0 is top row   
                    // row = 1 is bottom    
                    // col = 0 to 15        
{
    lcd_cursor_set(row,col);    // position cursor   
    BusyCheck();
    LCD_reg.LCD_RAM_WR = ch;            // send character   
}



void lcd_cursor_set(unsigned char row, unsigned char col)    // move cursor to desired position
{
    BusyCheck();
    switch(row)
    {
        case 0:
                LCD_reg.LCD_CMD_WR = (0x80 + col);
                break;

        case 1:
                LCD_reg.LCD_CMD_WR = (0xC0 + col);
                break;
    }
}

*/

// this is a collection of conversion routines used in conjunction with the LCD display

/*
char htoa_lo(unsigned char byte)   // converts low nibble of unsigned byte (0-F hex) to ascii
{
    byte = byte & 0x0F; // keep lower nibble only   
    if (byte <= 0x09)
        return(byte + 0x30);
    else
        return (byte + 0x37);
}
*/
/*
char lhtoa_lo(unsigned int word)  // converts 2nd nibble of unsigned int (0-F hex) to ascii
{
    word = word >> 8;
    word = word & 0x000F;
    if (word <= 0x0009)
        return((char)word + 0x30);
    else
        return ((char)word + 0x37);
}
*/

/*
char htoa_hi(unsigned char byte)   // converts hi nibble of unsigned byte (0-F hex) to ascii
{
    byte = byte & 0xF0;            // keep upper nibble only
    byte = byte >> 4;
    if (byte <= 0x09)
        return(byte + 0x30);
    else
        return (byte + 0x37);
}
*/

/*
char lhtoa_hi(unsigned int word)  // converts 1st nibble of unsigned int (0-F hex) to ascii
{
    word = word >> 12;
    word = word & 0x000F;
    if (word <= 0x0009)
        return((char)word + 0x30);
    else
        return ((char)word + 0x37);
}

*/

/*
void copy_message(unsigned int msg_ptr, unsigned int destination)
{
    xdata unsigned char i;
    xdata unsigned char code * temp_add;
    xdata unsigned char src_code;
    xdata unsigned char xdata * dest_add;

    for (i=0; i<LCD_LINE_LENGTH; i++)
    {
        temp_add =  (unsigned char *) ( msg_ptr + i);     // get message byte
        src_code =  *  temp_add;
        dest_add = (unsigned char *) (destination + i);   // put message byte
        * dest_add = src_code;
    }
}
*/

