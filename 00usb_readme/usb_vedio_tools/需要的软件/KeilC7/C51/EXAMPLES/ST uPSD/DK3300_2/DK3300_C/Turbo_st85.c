/*---------------------------------------------------------------------------- 
Title: upsd_st85.c
Date: October 8, 2002

Description: ST85 Read/Write Routines for DK3200 Board
10/18/02 PCL  Modified to utlize Switches 1 and 2 to set the clock on the DK3200 board

Copyright 2002 ST Microelectronics
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
----------------------------------------------------------------------------*/ 

#include "uPSD3300.h"
#include "TurboLite_hardware.h"
#include "Turbo_st85.h"
#include "Turbo_i2c.h"
#include "Turbo_timer.h"
#include "Turbo_LCD.h"
#include "Turbo_SPI.h"
#include <stdio.h>

Time st85;
extern xdata unsigned char i2c_xmit_buf[256];                        // message xmit buffer
extern xdata unsigned char i2c_rcv_buf[256];                         // message rcv buffer



/******************************************************************************/
/* function:     Conv_Int_to_BCD                                              */ 
/* descripition: Convers an integer number to timekeeper BCD format           */  
/* input:        int integ                                                    */
/* output:       unsigned char                                                */
/******************************************************************************/
unsigned char Conv_Int_to_BCD(int integ)
{
    char tmp_buf;

    tmp_buf = (unsigned char)(integ);
    if (integ <=9) return(tmp_buf);
    if ((integ >= 10) & (integ <= 19)) return (tmp_buf+0x06);
    if ((integ >= 20) & (integ <= 29)) return (tmp_buf+0x0c);
    if ((integ >= 30) & (integ <= 39)) return (tmp_buf+0x12);
    if ((integ >= 40) & (integ <= 49)) return (tmp_buf+0x18);
    if ((integ >= 50) & (integ <= 59)) return (tmp_buf+0x1E);
    if ((integ >= 60) & (integ <= 69)) return (tmp_buf+0x24);
    if ((integ >= 70) & (integ <= 79)) return (tmp_buf+0x2A);
    if ((integ >= 80) & (integ <= 89)) return (tmp_buf+0x30);
    if ((integ >= 90) & (integ <= 99)) return (tmp_buf+0x36);
}

/******************************************************************************/
/* function:     Conv_BCD_to_Int                                             */ 
/* descripition: Convers BCD format to an integer number                      */  
/* input:        unsigned char BCD                                            */
/* output:       integer                                                    */
/******************************************************************************/
int Conv_BCD_to_Int(unsigned char BCD)
{
    int tmp_buf1;

    tmp_buf1 = (int)(BCD);
    if (BCD <=0x9) return(tmp_buf1);
    if ((BCD >= 0x10) & (BCD <= 0x19)) return (tmp_buf1-6);
    if ((BCD >= 0x20) & (BCD <= 0x29)) return (tmp_buf1-12);
    if ((BCD >= 0x30) & (BCD <= 0x39)) return (tmp_buf1-18);
    if ((BCD >= 0x40) & (BCD <= 0x49)) return (tmp_buf1-24);
    if ((BCD >= 0x50) & (BCD <= 0x59)) return (tmp_buf1-30);
    if ((BCD >= 0x60) & (BCD <= 0x69)) return (tmp_buf1-36);
    if ((BCD >= 0x70) & (BCD <= 0x79)) return (tmp_buf1-42);
    if ((BCD >= 0x80) & (BCD <= 0x89)) return (tmp_buf1-48);
    if ((BCD >= 0x90) & (BCD <= 0x99)) return (tmp_buf1-54);
    //if ((BCD >= 0x100) & (BCD <= 0xFF)) return (60);
}
//--------------------------------
//   Test M41ST85 I2C interface
//--------------------------------
void ST85_write (void){                                               // set up xmit buffer, and send chars via i2c
    i2c_xmit_buf[0] = 0x00;                                           // Set up ST85 start address
    i2c_xmit_buf[1] = 0x00;                                           // ST85 msecs=00
    //i2c_xmit_buf[2] = 0x02;                                             // ST85 secs=00
    //i2c_xmit_buf[3] = 0x53;                                             // ST85 mins
    //i2c_xmit_buf[4] = 0x11;                                             // ST85 hours
    i2c_xmit_buf[5] = 0x03;                                           // ST85 dow
    //i2c_xmit_buf[6] = 0x15;                                             // ST85 date
    //i2c_xmit_buf[7] = 0x10;                                             // ST85 month
    //i2c_xmit_buf[8] = 0x02;                                             // ST85 year
    i2c_xmit_buf[9] = 0x00;                                           // ST85 control=00
    i2c_xmit_buf[10] = 0x00;                                           // ST85 watchdog=0x00
    i2c_xmit_buf[11] = 0x1f;                                          // ST85 alm month=0x1f (enable alarm int.)
    i2c_xmit_buf[12] = 0xff;                                          // ST85 alm date=0x3f
    i2c_xmit_buf[13] = 0x3f;                                          // ST85 alm hour=0x3f (clr HT bit)
    i2c_xmit_buf[14] = 0x7f;                                          // ST85 alm min=0x7f
    i2c_xmit_buf[15] = 0x7f;                                          // ST85 alm sec=0x7f
    Turbo_i2c_MX (0xD0,16);                                             // send 16 bytes for st85: addr 0xD0, @ 0x00-0x0E
    }
void ST85_config (void){                                              // set up xmit buffer, and send chars via i2c
    i2c_xmit_buf[0] = 0x08;                                           // Set up ST85 start address 0x08
    i2c_xmit_buf[1] = 0x00;                                           // ST85 control=00
    i2c_xmit_buf[2] = 0x00;                                        // ST85 watchdog=0x00
    i2c_xmit_buf[3] = 0x1f;                                       // ST85 alm month=0x1f (enable alarm int.)
    i2c_xmit_buf[4] = 0xff;                                       // ST85 alm date=0x3f
    i2c_xmit_buf[5] = 0x3f;                                       // ST85 alm hour=0x3f (clr HT bit)
    i2c_xmit_buf[6] = 0x7f;                                       // ST85 alm min=0x7f
    i2c_xmit_buf[7] = 0x7f;                                       // ST85 alm sec=0x7f
    Turbo_i2c_MX (0xD0,8);                                              // send 16 bytes for st85: addr 0xD0, @ 0x00-0x0E
    }
void ST85_read (void){
    i2c_xmit_buf[0] = 0x00;                                           // Set up ST85 start address
    Turbo_i2c_MX (0xD0,1);                                      // send 1 bytes for st85: addr 0xD0, @ 0x00
    Turbo_i2c_MR (0xD0,10);

}

void Adjust_time(char m_Menu_Index)
{
    unsigned char temp;
    switch(m_Menu_Index)
    {
    case 3:
        temp=Conv_BCD_to_Int(st85.hour);
        temp++;
        if(temp>=24)temp=0;
        st85.hour=Conv_Int_to_BCD(temp);
    break;
    case 4:
        temp=Conv_BCD_to_Int(st85.minute);
        temp++;
        if(temp>=60)temp=0;
        st85.minute=Conv_Int_to_BCD(temp);
    break;
    case 5:
        temp=Conv_BCD_to_Int(st85.second);
        temp++;
        if(temp>=60)temp=0;
        st85.second=Conv_Int_to_BCD(temp);
    break;
    case 0:
        temp=Conv_BCD_to_Int(st85.day);
        temp++;
        if(temp>=32)temp=0;
        st85.day=Conv_Int_to_BCD(temp);
    break;
    case 1:
        temp=Conv_BCD_to_Int(st85.month);
        temp++;
        if(temp>=13)temp=0;
        st85.month=Conv_Int_to_BCD(temp);
    break;
    case 2:
        temp=Conv_BCD_to_Int(st85.year);
        temp++;
        if(temp>=100)temp=0;
        st85.year=Conv_Int_to_BCD(temp);
    break;
    }
}
void Show_time(char m_Menu_Index)
{
    lcd_clear();
    //lcd_init();
    //MoveCursor(0,0);
    printf("DMY %02bX:%02bX:%02bX\n",st85.day,st85.month,st85.year);
    printf("HMS %02bX:%02bX:%02bX\n",st85.hour,st85.minute,st85.second);

    switch(m_Menu_Index)
    {
    case 3:
        MoveCursor(0, 16+5);
    break;
    case 4:
        MoveCursor(0, 16+8);
    break;
    case 5:
        MoveCursor(0, 16+11);
    break;
    case 0:
        MoveCursor(0, 5);
    break;
    case 1:
        MoveCursor(0, 8);
    break;
    case 2:
        MoveCursor(0, 11);
    break;  
    }
}
//-------------------------------------------------------------------------------
//  Tamper control register define:
//  Address 14H:{TEB1,TIE1,TCM1,TPM1,TDS1,TCHI/TCLO1,CLR1ext,CLR1}
//  Address 15H:{TEB2,TIE2,TCM2,TPM2,TDS2,TCHI/TCLO2,CLR2ext,CLR2}
//  Address 0FH:{,,,,,,TB1,TB2} 
//-------------------------------------------------------------------------------

void ST87_tamper_init()
{

    i2c_xmit_buf[0] = 0x14;     // Set up ST87 start address
    i2c_xmit_buf[1] = 0x84;     // Tamper_1 configuration
                                // Address 14H=[10110100] for Nornmally open
                                // or Address 14H=[10000100] for Nornmally close
    i2c_xmit_buf[2] = 0xA4;     // Tamper_2 configuration
                                // Address 15H=[10100100] for Nornmally open
                                // or Address 15H=[10010100] for Nornmally close
    Turbo_i2c_MX (0xD0,3);      // send 16 bytes for st85: addr 0xD0, @ 0x00-0x0E   
}

void ST87_tamper_Reset()
{

    i2c_xmit_buf[0] = 0x14;     // Set up ST87 start address
    i2c_xmit_buf[1] = 0x34;     // Tamper_1 configuration
                                // Address 14H=[00110100] for Nornmally open
                                // or Address 14H=[00000100] for Nornmally close
    i2c_xmit_buf[2] = 0x24;     // Tamper_2 configuration
                                // Address 15H=[00100100] for Nornmally open
                                // or Address 15H=[00010100] for Nornmally close
    Turbo_i2c_MX (0xD0,3);      // send 16 bytes for st85: addr 0xD0, @ 0x00-0x0E   
}



unsigned char ST87_tamper_check()
{
    i2c_xmit_buf[0] = 0x0F;     // Setup ST87 start address
    Turbo_i2c_MX (0xD0,1);      // send 1 bytes for st85: addr 0xD0, @ 0x00
    Turbo_i2c_MR (0xD0,1);      // Read address 0x0F for check TB1 and TB2 bits
    if((i2c_rcv_buf[0]&0x03)!=0)return(1);
    else return(0);
}

void ST87_tamper_save()
{

    unsigned char Tamper_sum,Tamper_No;

    i2c_xmit_buf[0] = 0x00;     // Setup ST87 start address
    Turbo_i2c_MX (0xD0,1);      // send 1 bytes for st85: addr 0xD0, @ 0x00
    Turbo_i2c_MR (0xD0,10);     // Read address 0x0F for check TB1 and TB2 bits
    Tamper_sum=Turbo_SPI_ReadByte(0x0000);
    Tamper_No=Turbo_SPI_ReadByte(0x0001);
    Tamper_sum++;
    if(Tamper_sum>=10)Tamper_sum=10;
    Tamper_No++;
    if(Tamper_No>9)Tamper_No=0;
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0000, Tamper_sum);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0001, Tamper_No);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0002+Tamper_No*6, i2c_rcv_buf[1]); 
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0003+Tamper_No*6, i2c_rcv_buf[2]);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0004+Tamper_No*6, i2c_rcv_buf[3]);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0005+Tamper_No*6, i2c_rcv_buf[5]);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0006+Tamper_No*6, i2c_rcv_buf[6]);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0007+Tamper_No*6, i2c_rcv_buf[7]);
    delay_1sec();
    delay_1sec();
    ST87_tamper_Reset();
    ST87_tamper_init();
}

void ST87_tamper_Show(unsigned char Tamper_index)
{
    Time ST87_tamper_time;
    unsigned char Tamper_No;
    char temp; 
    Tamper_No=Turbo_SPI_ReadByte(0x0001);
    temp=Tamper_No-Tamper_index;
    if(temp<0)temp=temp+10;
    //i2c_rcv_buf[1]=Turbo_SPI_ReadByte(0x0002+temp*6);
    //i2c_rcv_buf[2]=Turbo_SPI_ReadByte(0x0003+temp*6);
    //i2c_rcv_buf[3]=Turbo_SPI_ReadByte(0x0004+temp*6);     
    //i2c_rcv_buf[5]=Turbo_SPI_ReadByte(0x0005+temp*6);
    //i2c_rcv_buf[6]=Turbo_SPI_ReadByte(0x0006+temp*6);
    //i2c_rcv_buf[7]=Turbo_SPI_ReadByte(0x0007+temp*6);

    ST87_tamper_time.second=Turbo_SPI_ReadByte(0x0002+temp*6);
    ST87_tamper_time.minute=Turbo_SPI_ReadByte(0x0003+temp*6);
    ST87_tamper_time.hour=Turbo_SPI_ReadByte(0x0004+temp*6);    
    ST87_tamper_time.day=Turbo_SPI_ReadByte(0x0005+temp*6);
    ST87_tamper_time.month=Turbo_SPI_ReadByte(0x0006+temp*6);
    ST87_tamper_time.year=Turbo_SPI_ReadByte(0x0007+temp*6);

    lcd_clear();
    printf("TR%02bX  %02bX:%02bX:%02bX\n",Tamper_index,ST87_tamper_time.day,ST87_tamper_time.month,ST87_tamper_time.year);
    printf("      %02bX:%02bX:%02bX\n",ST87_tamper_time.hour,ST87_tamper_time.minute,ST87_tamper_time.second);
}


void ST87_tamper_clear()
{
    unsigned char Tamper_sum,Tamper_No;
    Tamper_sum=0;
    Tamper_No=0;
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0000, Tamper_sum);
    Turbo_SPI_WriteEnable();
    Turbo_SPI_WriteByte(0x0001, Tamper_No);
}
