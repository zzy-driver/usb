/*------------------------------------------------------------------------------
Title: ADC-PWM Demo code for DK3300
Date: August, 2003


DK3300 Demo Code.
08/2003 Ver 0.1 - Initial Version


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
#include "PCA-PWM.h"
#include "stdio.h"


xdata PSD_REGS PSD8xx_reg _at_ PSD_REG_ADDR; 


void main(void)
{
    unsigned char k,ADC_channel;
    unsigned int ADC_result;

    //-----Enable peripheral I/O function-------------
    PSD8xx_reg.VM |= 0x80;                              //Enable peripheral I/O
    //-----Initiate Timter0-------------
    timer0_init(); 

    //-----Show demo information on LCD-------------
    lcd_init();                 
                
    printf("PWM to ADC DEMO\n");
    delay_1sec();

    ADC_channel=7;
    ACON |= 0x20;                               // Enable ADC
    k=0;
    while(1){
        if (k == 0) k = 0xff;                   // Fix over flow of 0H -> 0FFh
        if (k == 0xf) k = 0;                    // Fix over flow from 0FFh -> 0Fh
        PWM_Mode1_Init(0, k);                   //Set to PWM channel 0
        delay_1sec();                           // wait for voltage to settle
        printf("PWM=%02bX",k);                  //display adc channel and adc value on LCD

        Turbo_ADC_Init(ADC_channel);            // Init & read ADC channel
        ADC_result=Turbo_ADC_Read(ADC_channel);
        printf(" ADC=%03X\r",ADC_result);       //display adc channel and adc value on LCD
        k = k + 0x10;
   }
}
