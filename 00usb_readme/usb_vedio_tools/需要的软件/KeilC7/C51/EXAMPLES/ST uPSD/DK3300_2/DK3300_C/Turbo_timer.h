/*--------------------------------------------------------------------------
Turbo_Timer.H

Header file for uPSD 3200 Timer0 Device Driver
06/2002 Ver 0.1 - Initial Version
08/2002 Ver 0.2 - Added reload value based off FREQ_OSC define

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

#ifndef _TIMER_H_
#define _TIMER_H_

// timer0_init - routine called to init timer interrupts every 10ms
void timer0_init (void);

// timer0_count - returns unsigned int that is count of 10ms timer ticks
unsigned int timer0_count (void);

// timer0_delay - waits for count timer 10ms ticks to pass, then returns
void timer0_delay (unsigned int count);

// delay_10ms - waits 10ms, then returns
void delay_10ms(void);

// delay_1sec - waits 1 sec, then returns
void delay_1sec(void);

// delay_2sec - waits 2 sec, then returns
void delay_2sec(void);

// delay_10sec - waits 10 sec, then returns
void delay_10sec(void);

// delay_05sec - waits 500ms, then returns
void delay_0_5sec(void);

// delay_01sec - waits 100ms, then returns
void delay_0_1sec(void);

#endif

