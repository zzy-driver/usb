/*---------------------------------------------------------------------------- 
Title: upsd_st85.h
Date: October 7, 2002
Author: Alec Bath

Description:
Function prototypes for upsd_st85.c   M41ST85 Timekeeper Routines

Copyright 2002  ST Microelectronics
----------------------------------------------------------------------------*/ 

#ifndef _UPSD_ST85_H_
#define _UPSD_ST85_H_

void ST85_write (void);
void ST85_read (void);
void Adjust_time(char m_Menu_Index);
void Show_time(char m_Menu_Index);
unsigned char Conv_Int_to_BCD(int integ);
int Conv_BCD_to_Int(unsigned char BCD);
void ST85_config (void);
void ST87_tamper_init();
unsigned char ST87_tamper_check();
void ST87_tamper_save();
void ST87_tamper_Show(unsigned char Tamper_index);
void ST87_tamper_clear();

typedef struct 
{
	unsigned char second;
	unsigned char minute;
	unsigned char hour;
	unsigned char day;
	unsigned char month;
	unsigned char year;
} Time;

#endif

