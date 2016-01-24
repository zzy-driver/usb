/*------------------------------------------------------------------------------
Title: Demo code for DK3300
Date: August 2003


DK3300 Demo Code.
08/2003 Ver 0.1 - Initial Version

Reference platforms
PSM division
Copyright 2003 STMicroelectrons Inc.

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
#include "Turbo_ADC.h"
#include "Turbo_timer.h"
#include "Turbo_LCD.h"
#include "ISDcompanion.h"
#include "PCA-PWM.h"
#include "Turbo_I2C.h"
#include "Turbo_st85.h"
#include "Encoder.h"
#include "Turbo_SPI.h"
#include "math.h"
#include "Key.h"
#include <stdio.h>

xdata PSD_REGS PSD8xx_reg _at_ PSD_REG_ADDR; 
extern xdata unsigned char i2c_xmit_buf[256];
extern xdata unsigned char i2c_rcv_buf[256];
extern Time st85;

void Show_Menu(unsigned char m_Menu_Index)
{
    lcd_clear();
    //lcd_init();
    switch(m_Menu_Index)
    {
    case 0:
        printf(">PWM/ADC  I2CRTC\n"
               " IrDA     PWMLCD\n");
    break;
    case 1:
        printf(" PWM/ADC >I2CRTC\n"
               " IrDA     PWMLCD\n");
    break;
    case 2:
        printf(" PWM/ADC  I2CRTC\n"
               " IrDA    >PWMLCD\n");
    break;
    case 3:
        printf(" PWM/ADC  I2CRTC\n"
               ">IrDA     PWMLCD\n");
    break;
    }
}

void Tamper_check()
{
    unsigned char Tamper_sum,Tamper_No;
    char Menu_Index;
    unsigned char temp,temp_Dir;

    if((ST87_tamper_check())==1)
    {
        lcd_clear();
        printf("New Tamper event" );
        ST87_tamper_save();
        lcd_clear();
        printf("Turning Encoder\n"
               "for looking TR");
        delay_1sec();
        delay_1sec();
        Tamper_sum=Turbo_SPI_ReadByte(0x0000);
        Tamper_No=Turbo_SPI_ReadByte(0x0001);
        if(Tamper_sum>Tamper_No)temp=Tamper_sum;
        else temp=Tamper_No;
        Menu_Index=0;
        ST87_tamper_Show(Menu_Index);
        while((PSD8xx_reg.DATAIN_B&0x10)!=0)
        {
            temp_Dir=Polling_Encoder();
            if(temp_Dir==2) 
            {
                    Menu_Index++;
                    if(Menu_Index>=temp)Menu_Index=0;
                    ST87_tamper_Show(Menu_Index);
            }
            else if(temp_Dir==1)
            {
                    Menu_Index--;
                    if(Menu_Index<0)Menu_Index=temp-1;
                    ST87_tamper_Show(Menu_Index);
            }
            PSD8xx_reg.DIRECTION_B|=0x10;
            PSD8xx_reg.DATAOUT_B|=0x10;
            PSD8xx_reg.DIRECTION_B&=0xEF;   // IN direction
        }
        lcd_clear();
    }
    else
    {
        //printf("Old Tamper record" );  
    }
}

void main(void)
{
    unsigned char k,ADC_channel;
    char Menu_Index;
    unsigned int ADC_result;
    unsigned long Wait_set_time;
    unsigned char Update_time, temp_Dir;
    unsigned char LcdContrast;
    PSD8xx_reg.VM |= 0x80;                              //Enable peripheral I/O
    timer0_init(); 
    Turbo_ADC_Init(7);
    P4_0=0;
    lcd_init();                 
    printf("DK3300 Demo V0.9\n"
           "STMicroelectric");
    delay_1sec();
    delay_1sec();
    lcd_init();                 
    printf("Turn Encoder R/L\n"
           "Press to Select");
    delay_1sec();
    delay_1sec();
    delay_1sec();
    //-----Initiate PB[4] as MCU input for encoder (PB[2,3] as logic input)-------------
    PSD8xx_reg.CONTROL_B&=0xEF;     // MCU IO/Address OUT: mode 
    PSD8xx_reg.DRIVE_B&=0xEF;       // OpenDrain & SlewRate control
    PSD8xx_reg.DIRECTION_B|=0x10;
    PSD8xx_reg.DATAOUT_B|=0x10;
    PSD8xx_reg.DIRECTION_B&=0xEF;   // IN direction
    //-----Waiting user select a demo to run-----------------------------------------
    //  use OMC_AB[0,1] as a 2-bit counter to identify running of Encoder
    //  use OMC_AB[2] as a running direction indication of Encoder
    //-------------------------------------------------------------------------------
    Menu_Index=0;
    PSD8xx_reg.OMC_AB&=0xF8;
    PSD8xx_reg.OMC_AB|=0x04;
    Show_Menu (Menu_Index);
    while((PSD8xx_reg.DATAIN_B&0x10)!=0)
    {
        temp_Dir=Polling_Encoder();
        if(temp_Dir==2)
        {
            Menu_Index++;
            if(Menu_Index==4)Menu_Index=0;
            Show_Menu (Menu_Index);
        }
        else if(temp_Dir==1)
        {
            Menu_Index--;
            if(Menu_Index==-1)Menu_Index=3;
            Show_Menu (Menu_Index);
        }
        PSD8xx_reg.DIRECTION_B|=0x10;
        PSD8xx_reg.DATAOUT_B|=0x10;
        PSD8xx_reg.DIRECTION_B&=0xEF;   // IN direction
    }
    //-----Running the demo code user selected----------------------------------------
    switch(Menu_Index)
    {
    case 0: 
    //============================ Demo0: PWM ADC ====================================

    PSD8xx_reg.CONTROL_B&=0xF1;     // MCU IO/Address OUT: mode 
    PSD8xx_reg.DRIVE_B&=0xF1;       // OpenDrain & SlewRate control
    PSD8xx_reg.DIRECTION_B|=0x07;
    PSD8xx_reg.DATAOUT_B&=0xF1;

    lcd_init();
    printf("PWM/ADC Demo\n" );
    ADC_channel=7;
    ACON |= 0x20;              // Enable ADC
    k=0;
    while(1){
        if (k == 0) k = 0xff;  // Fix over flow of 0H -> 0FFh
        if (k == 0xf) k = 0;   // Fix over flow from 0FFh -> 0Fh
        PWM_Mode1_Init(0, k);
        delay_1sec();          // wait for voltage to settle

        printf("PWM=%02bX",k);                  //display adc channel and adc value on LCD

        Turbo_ADC_Init(ADC_channel);            // Init & read ADC channel
        ADC_result=Turbo_ADC_Read(ADC_channel);
        printf(" ADC=%03X\r", ADC_result);      // display adc channel and adc value on LCD
        k = k + 0x10;
}
    break;
    case 1:
    //============================ Demo1: I2C RTC =====================================

        //---------------------- Check RTC tamper function -----------------------------------------
        lcd_init();
        Turbo_i2c_init();
        ST87_tamper_init();
        Turbo_SPI_Init();
        Tamper_check();

        //---------------------- Waiting user set time -----------------------------------------
        lcd_init();
        printf("Turn Encoder to\n"
               "set Date & Time" );
        delay_1sec();
        delay_1sec();
        Turbo_i2c_init();
        ST85_read();
        st85.second=i2c_rcv_buf[1];
        st85.minute=i2c_rcv_buf[2];
        st85.hour=i2c_rcv_buf[3];
        st85.day=i2c_rcv_buf[5];
        st85.month=i2c_rcv_buf[6];
        st85.year=i2c_rcv_buf[7];
        lcd_init();
        Menu_Index=0;
        PSD8xx_reg.OMC_AB&=0xF8;
        PSD8xx_reg.OMC_AB|=0x04;
        PSD8xx_reg.DIRECTION_B|=0x10;
        PSD8xx_reg.DATAOUT_B|=0x10;
        PSD8xx_reg.DIRECTION_B&=0xEF;   // IN direction
        Show_time(Menu_Index);
        Wait_set_time=0;
        Update_time=0;
        while((PSD8xx_reg.DATAIN_B&0x10)!=0)
        {
            temp_Dir=Polling_Encoder();
            if(temp_Dir==2) 
            {
                    Menu_Index++;
                    if(Menu_Index==6)Menu_Index=0;
                    Show_time(Menu_Index);
                    Update_time=1;
            }
            else if(temp_Dir==1)
            {
                Adjust_time(Menu_Index);
                Show_time(Menu_Index);
                Update_time=1;
            }
            PSD8xx_reg.DIRECTION_B|=0x10;
            PSD8xx_reg.DATAOUT_B|=0x10;
            PSD8xx_reg.DIRECTION_B&=0xEF;   // IN direction
            if(Update_time==0)Wait_set_time++;
            if(Wait_set_time>200000)break;
        }
        //----------------------------Save time into ST85-------------------------------------
        if(Update_time==1)
        {
            i2c_xmit_buf[2]=st85.second;
            i2c_xmit_buf[3]=st85.minute;
            i2c_xmit_buf[4]=st85.hour;
            i2c_xmit_buf[6]=st85.day;
            i2c_xmit_buf[7]=st85.month;
            i2c_xmit_buf[8]=st85.year;
            ST85_write();
        }
        else
        {
            ST85_config();
        }
        lcd_init();                                 // initialize LCD. 8 bits, 2 lines, 5x7 font,
        while (TRUE){
            ST85_read();                            // Read & Print ST85
            printf("Turbo I2C Demo\n"
                   "Time: %02bX:%02bX:%02bX\n",i2c_rcv_buf[3],i2c_rcv_buf[2],i2c_rcv_buf[1]);
            Tamper_check();
            if(Key_check()==3)
            {
                ST87_tamper_clear();
                lcd_clear();
                printf("Tamper record \n"
                       "has been removed!");
                delay_1sec();
                delay_1sec();
                lcd_clear();
            }
        }
    break;
    case 2:
    //============================ Demo2: PWMLCD =================================================
        lcd_init();                 
        printf("JP3:PWM\n"
               "JP14:Open\n");
        delay_1sec();
        while((PSD8xx_reg.DATAIN_B&0x10)!=0);
        lcd_clear();        
        printf("PWMLCD Demo\n");
        PwmInit_Mode1(0xC0);
        LcdContrast=0xC0;
        while (1)
        {

            temp_Dir=Polling_Encoder();
            if(temp_Dir==2)
            {
                if (++LcdContrast==0) LcdContrast=255;

            }
            else if(temp_Dir==1)
            {
                if (--LcdContrast==0xff) LcdContrast=0;
            }
            PwmSetDuty_Mode1(LcdContrast);
            printf("Brightness:%02bX\r",LcdContrast);
        }
    break;

    case 3:
    //============================ Demo3: IrDA ================================================
        lcd_init(); 
        printf("Under\n"
               "construction...");
        while(1);
    break;

    }
}
