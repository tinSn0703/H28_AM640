
/*
UART系のクラスや関数を使うためのマクロやtypdef
 H28 05 18 ver0.0.0
*/

#pragma once

#ifndef _H28_AM640_H_
#	error "Include <H28_AM640.h>"
#endif //_H28_AM640_H_

#include "H28_AM640_i_macro.h"
#include "H28_AM640_t_macro.h"

/*USART*/
typedef unsigned char T_DATA_8;
typedef unsigned short int T_DATA;

#define IN_ERROR 0xfff 
//このマクロは12bit以上ないと使えないからな気を付けろよ。by H28 May 13のSn


enum E_UART_FLAG
//UART FLAG COMAND
{
	EU_NONE  = 0,	
	EU_SUCCE = 1,	//受信成功
	EU_ERROR = 2,	//受信失敗
};

#if _H28_AVR_H_ == 640
enum E_UART_ADDR
//UART NUMBER SET COMAND
{
	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
	EU_UART2 = 0xd0,
	EU_UART3 = 0x130,
};
#elif _H28_AVR_H_ == 164
enum E_UART_ADDR
//UART NUMBER SET COMAND
{
	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
};
#endif

enum E_UART_MODE
//UART MODE SET COMAND
{
	EU_TRA  = 0, //送信
	EU_REC  = 1, //受信
};

/*bit UCSRA*/
#define RXC  7
#define TXC	 6
#define UDRE 5
#define FE	 4
#define DOR  3
#define UPE  2
#define U2X  1
#define MPCM 0

/*bit UCSRB*/
#define RXCIE 7
#define TXCIE 6
#define UDRIE 5
#define RXEN  4
#define TXEN  3
#define UCSZ2 2
#define RXB8  1
#define TXB8  0

/*bit UCSRC*/
#define UMSEL1 7
#define UMSEL0 6
#define UPM1   5
#define UPM0   4
#define USBS   3
#define UCSZ1  2
#define UCSZ0  1
#define UCPOL  0

/************************************************************************/
#include "H28_AM640_u_class/H28_AM640_u_class.h"
/************************************************************************/