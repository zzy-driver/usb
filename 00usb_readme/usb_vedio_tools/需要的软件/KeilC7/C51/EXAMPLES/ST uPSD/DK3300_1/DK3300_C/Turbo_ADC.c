/*------------------------------------------------------------------------------
Title: Turbo_ADC.C
Date: 4, 2003


uPSD ADC Device Driver Functions
06/2002 Ver 0.1 - Initial Version

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

#include <intrins.h>

#include "uPSD3300.h"
#include "TurboLite_hardware.h"
#include "Turbo_ADC.h"
#include "Turbo_LCD.h"
#include "Turbo_timer.h"
#define ADC_CLOCK_DIVIDER 7 // ADC clock pre-scaler from 0 to 7

/*---------------------------------------------------------
Setup I/O ports (channel #) and ADC Clock freq
----------------------------------------------------------*/
/*
void Turbo_ADC_EnableAll()
{
    P1SFS0 |= 0xFF;
    P1SFS1 |= 0xFF;                 // Setup P1 Port corresponding pin as AD input
    ADCPS |=(0x08+ADC_CLOCK_DIVIDER);                   // Enable ADC clock
                                    // ADC clock freq=Fosc/(2^ADCPS[2..0])=10Mhz at Fsoc=40MHz
    ACON&=0xBF;                     // Disable ADC interrupt
}
*/
/*---------------------------------------------------------
Setup I/O ports (channel #) and ADC Clock freq
----------------------------------------------------------*/
void Turbo_ADC_Init (unsigned char channel) 
{
    unsigned char temp_command;
    temp_command=(0x01)<<channel;
    P1SFS0 |= temp_command;         
    P1SFS1 |= temp_command;                     // Setup P1 Port corresponding pin as AD input
    ADCPS |=(0x08+ADC_CLOCK_DIVIDER);           // Enable ADC clock, setup ADC clock freq
    ACON&=0xBF;                                 // Disable ADC interrupt

}
/*-------------------------------------------------------------------------------------
Turbo_ADC_Read(): reads an analog signal from the channel specified in hex format,
            and returns the converted value in temp_ADC_result variable.  
            uPSD_ADC_Init must be called first.
    *Note that you must Start ADC conversion after enabling ADC 
--------------------------------------------------------------------------------------*/
unsigned int Turbo_ADC_Read( unsigned char channel )
{
    unsigned char channel_no;
    unsigned int  temp_ADC_result;

    ACON &= 0xE3;                           //Clears the input channels ~(00101110B) = (11010001B)
    channel_no = channel << 2;
    ACON |=  channel_no;                    //Setup Channel 
    _nop_ ();
    _nop_ ();   
    ACON |= 0x02;                           //Start ADC conversion
    P3=0x80;                                //Send a squere wave on P3.7 for measuring ADC conversion time 
    _nop_ ();
    _nop_ ();                               //delay 1 machine cycle: ADST: 1->0
    while( (ACON & 0x01) != 1 );            //Waits for Conversion complish
    P3=0x00;                                
    ACON &= 0xFE;                           //Clear ADSF bit
    temp_ADC_result=(ADAT1<<8)+ADAT0;       //Calculate ADC conversion result
    return(temp_ADC_result);
}



