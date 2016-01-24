/*--------------------------------------------------------------------------
Title: Turbo_ADC.H
Date: 4, 2003
Author: Shao Qing

Header file for Turbo Lite ADC Device Driver
04/2003 Ver 0.1 - Initial Version

Copyright (c) 2002 ST Microelectronics
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
--------------------------------------------------------------------------*/

#ifndef _TurboLite_ADC_H_
#define _TurboLite_ADC_H_

// Turbo_ADC_Init(Channel) - Initialize uPSD ADC IP block and enable channel
// Channel is a value from 0 to 8 for the ADC channel to enable
// Must be called for each ADC Channel to enable
void Turbo_ADC_Init(unsigned char channel);
//void Turbo_ADC_EnableAll(); 
// Turbo_ADC_Read(Channel) - Reads the specified channel and returns value
// Channel is a value from 0 to 8
// ADC conversion time is approx 8us
// Note: Turbo_ADC_Init must be called first
unsigned int Turbo_ADC_Read(unsigned char channel);

#endif
