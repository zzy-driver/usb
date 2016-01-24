/*------------------------------------------------------------------------------
TEST.C:  ISD51 Demo for TI MSC 1210

Copyright 2002 Keil Software, Inc.
------------------------------------------------------------------------------*/

#include <REG1210.H>
#include <intrins.h>
#include "ISD51.h"

unsigned char j;

unsigned char code testarray[] = "Some Text";


#if 0   // uncomment this function to verify serial communication

/*
 * Test Function: verify serial communication with HyperTerminal
 */
void TestSerial (void)  {
  char c = 'A';

  TI = 1;
  while (1)  {
    if (RI)  {
      c = SBUF;
      RI = 0;
    }
    while (!TI);
    TI = 0;
    SBUF = c;
  }
}

#endif


void delay2(void) {
  long i;
  
  i = 0x800;
  while(i--);
}

void AuxInterrupt (void) interrupt 8 {

  while (1)  {
    P3 ^= 0x20;
    delay2();
  }
}

void delay(void) {
  long i;
  
  i = 0x800;
  while(i--);
}

void main (void)  {
  unsigned int i;

// Setup Serial Interface
  T2CON   = 0x34;      /* Use Timer 2 as baudrate generator  */
  RCAP2H  = 0xFF;
#ifdef MHz12
  RCAP2L  = 0xD9;      /* 9615 baud @ 12.0000 MHz             */
#else
  RCAP2L  = 0xDC;      /* 9615 baud @ 11.0592 MHz             */
#endif
  SCON0   = 0x50;      /* enable serial uart & receiver      */
  P3DDRL &= 0xF0;      /* P3DDRL set port pins of UART to input/strong drive output */
  P3DDRL |= 0x07;      /* P3DDRL set port pins of UART to input/strong drive output */
  AIE   = 0x01;        /* enable DLV_B interrupt bit         */
  EICON = 0x20;        /* enable PFI                         */
  EA = 1;              /* Enable global interrupt flag       */

//TestSerial ();      // uncomment this function to verify serial communication
 
#if 0   // init ISD51 and start user program until the uVision2 Debugger connects
  ISDinit ();        // initialize uVision2 Debugger and continue program run
#endif

#if 0   // init ISD51 and wait until the uVision2 Debugger connects
  ISDwait ();        // wait for connection to uVision2 Debugger
#endif

  for (i = 0; i < sizeof (testarray); i++)  {
    j = testarray[i];
  }

  while (1)  {
#if 1   // init ISD51 only when the uVision2 Debugger tries to connect
    ISDcheck();      // initialize uVision2 Debugger and continue program run
#endif
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    P3 ^= 0x10;
    P3 ^= 0x20;
    _nop_();
    _nop_();
    _nop_();
    delay();
#if 0   // you may use ISDbreak when ISD51 is started with ISDcheck or ISDwait
    ISDbreak ();  // hard coded stop (breakpoint)
#endif
    _nop_();
    _nop_();
    _nop_();
  }
}


