/*--------------------------------------------------------------------------
PSDregs.H

Header file for STM 3200 MicroPSD (uPSD) microcontroller.
06/2002 Ver 0.1 - Initial Version
08/2002 Ver 0.2 - Added Interrupt Vectors & Misc values

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

#ifndef _PSD_H_
#define _PSD_H_

typedef struct	// general structure of 8 bit register allowing bit access 
	{
	unsigned char bit0 : 1;
	unsigned char bit1 : 1;
	unsigned char bit2 : 1;
	unsigned char bit3 : 1;
	unsigned char bit4 : 1;
 	unsigned char bit5 : 1;
	unsigned char bit6 : 1;
	unsigned char bit7 : 1;
	} Register;    

typedef union	// allow bit or byte access to registers 
	{
	char byte;
	Register bits;
	} xdata Mix_Reg;

typedef union	// allow bit or byte access to registers 
	{
	char byte;
	Register bits;
	} SFR_Reg;


/* ------------------------------ */
/*      Standard PSD Registers    */
/* ------------------------------ */

typedef xdata struct REG_PSD_struct {
        unsigned char DATAIN_A;         // PSD_REG_BASE +0x00
        unsigned char DATAIN_B;         //              +0x01
        unsigned char CONTROL_A;        //              +0x02
        unsigned char CONTROL_B;        //              +0x03
        unsigned char DATAOUT_A;        //              +0x04
        unsigned char DATAOUT_B;        //              +0x05
        unsigned char DIRECTION_A;      //              +0x06
        unsigned char DIRECTION_B;      //              +0x07
        unsigned char DRIVE_A;          //              +0x08
        unsigned char DRIVE_B;          //              +0x09
        unsigned char IMC_A;            //              +0x0A
        unsigned char IMC_B;            //              +0x0B
        unsigned char OUTENABLE_A;      //              +0x0C
        unsigned char OUTENABLE_B;      //              +0x0D
        unsigned char res2[2];          //      spacer
        unsigned char DATAIN_C;         //              +0x10
        unsigned char DATAIN_D;         //              +0x11
        unsigned char DATAOUT_C;        //              +0x12 
        unsigned char DATAOUT_D;        //              +0x13
        unsigned char DIRECTION_C;      //              +0x14
        unsigned char DIRECTION_D;      //              +0x15
        unsigned char DRIVE_C;          //              +0x16
        unsigned char DRIVE_D;          //              +0x17
        unsigned char IMC_C;            //              +0x18
        unsigned char res1a;            //      spacer
        unsigned char OUTENABLE_C;      //              +0x1A
        unsigned char OUTENABLE_D;      //              +0x1B
        unsigned char res4[4];          //      spacer
        unsigned char OMC_AB;           //              +0x20
        unsigned char OMC_BC;           //              +0x21
        unsigned char OMCMASK_AB;       //              +0x22
        unsigned char OMCMASK_BC;       //              +0x23
        unsigned char res8c[0x8C];      //      spacer
        unsigned char PMMR0;            //              +0xB0
        unsigned char res1b;            //      spacer
        unsigned char PMMR1;            //              +0xB2
        unsigned char res1c;            //      spacer
        unsigned char PMMR2;            //              +0xB4
        unsigned char res0B[0x0B];      //      spacer
        unsigned char MAINPROTECT;      //              +0xC0
        unsigned char res1d;            //      spacer
        unsigned char ALTPROTECT;       //              +0xC2
        unsigned char res4a[4];         //      spacer
        unsigned char JTAG;             //              +0xC7
        unsigned char res18[0x18];      //      spacer
        unsigned char PAGE;             //              +0xE0
        unsigned char res1e;            //      spacer
        unsigned char VM;               //              +0xE2
	  unsigned char res29[0x1d];	    //    	spacer
} PSD_REGS;




//****************** PSD control register bit definitions *********

//PSD PORTA
#define PA0		bit0
#define PA1		bit1	
#define PA2		bit2	
#define PA3		bit3	
#define PA4		bit4	
#define PA5		bit5	
#define PA6		bit6	
#define PA7		bit7	

//PSD PORTB
#define PB0		bit0
#define PB1		bit1	
#define PB2		bit2	
#define PB3		bit3	
#define PB4		bit4	
#define PB5		bit5	
#define PB6		bit6	
#define PB7		bit7	

//PSD PORTC
#define PC0		bit0
#define PC1		bit1	
#define PC2		bit2	
#define PC3		bit3	
#define PC4		bit4	
#define PC5		bit5	
#define PC6		bit6	
#define PC7		bit7	

//PSD PORTD
#define PD0		bit0
#define PD1		bit1	
#define PD2		bit2	

//PSD JTAG
#define JEN		bit0   // JTAG enable

//PSD PMMR0
#define APD_ENABLE	bit1
#define PLD_TURBO		bit3
#define PLD_ARRAY_CLK	bit4
#define PLD_MCELL_CLK	bit5

//PSD PMMR2
#define PLD_CNTL0		bit2
#define PLD_CNTL1		bit3
#define PLD_CNTL2		bit4
#define PLD_ALE		bit5
#define PLD_DBE		bit6

//PSD VM
#define SRAM_CODE		bit0
#define EE_CODE		bit1
#define FL_CODE		bit2
#define EE_DATA		bit3
#define FL_DATA		bit4
#define PIO_EN		bit7

// Flash parameters

//#define NVM_DATA_POLL     0x80		// flash status "data poll" bit at DQ7   
//#define NVM_DATA_TOGGLE   0x40		// flash status "toggle poll" bit at DQ6
//#define NVM_ERROR         0x20 		// flash status "error" bit at DQ5   

#endif
