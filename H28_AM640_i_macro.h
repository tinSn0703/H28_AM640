
/*
IO系のクラスや関数を使うためのマクロやtypdef
 H28 05 18 ver0.0.0
*/

#pragma once

#ifndef _H28_AM640_H_
#	error "Include <H28_AM640.h>"
#endif /*_H28_AM640_H_*/

#include "H28_AM640_u_macro.h"
#include "H28_AM640_t_macro.h"

typedef unsigned char T_PORT;

enum E_IO_PORT_ADDR
{
	EI_PORTA = 0x000,
	EI_PORTB = 0x003,
	EI_PORTC = 0x006,
	EI_PORTD = 0x009,
	EI_PORTE = 0x00c,
	EI_PORTF = 0x00f,
	EI_PORTG = 0x012,
	EI_PORTH = 0x100,
	EI_PORTJ = 0x103,
	EI_PORTK = 0x106,
	EI_PORTL = 0x109,
};

enum E_IO_NUM
{
	EI_IO0 = 0,
	EI_IO1 = 1,
	EI_IO2 = 2,
	EI_IO3 = 3,
	EI_IO4 = 4,
	EI_IO5 = 5,
	EI_IO6 = 6,
	EI_IO7 = 7,	
};

enum E_IO_MODE
{
	EI_IN  = 0,
	EI_OUT = 1,
};

enum E_AD_NUM
{
	EA_AD0 = 0b000000,
	EA_AD1 = 0b000001,
	EA_AD2 = 0b000010,
	EA_AD3 = 0b000011,
	EA_AD4 = 0b000100,
	EA_AD5 = 0b000101,
	EA_AD6 = 0b000110,
	EA_AD7 = 0b000111,
	EA_AD8 = 0b100000,
	EA_AD9 = 0b100001,
	EA_ADA = 0b100010,
	EA_ADB = 0b100011,
	EA_ADC = 0b100100,
	EA_ADD = 0b100101,
	EA_ADE = 0b100110,
	EA_ADF = 0b100111,
};

#define AD_ERROR 0xffff

#include "H28_AM640_i_class/H28_AM640_i_class.h"