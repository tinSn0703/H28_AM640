
/*
UART�n�̃N���X��֐����g�����߂̃}�N����typdef
 H28 05 18 ver0.0.0
*/

#ifndef _H28_AM640_U_MACRO_H_
#define _H28_AM640_U_MACRO_H_ 1

#ifndef _H28_AM640_H_
{
	#error "Include <H28_AM640.h>"
}
#endif //_H28_AM640_H_

#include "H28_AM640_i_macro.h"
#include "H28_AM640_t_macro.h"

/*USART*/
typedef unsigned char T_DATA_8;
typedef unsigned short int T_DATA;

#define IN_ERROR 0xfff 
//���̃}�N����12bit�ȏ�Ȃ��Ǝg���Ȃ�����ȋC��t�����Bby H28 May 13��Sn


enum E_UART_FLAG
//UART FLAG COMAND
{
	EU_NONE  = 0,	
	EU_SUCCE = 1,	//��M����
	EU_ERROR = 2,	//��M���s
};

enum E_UART_ADDR
//UART NUMBER SET COMAND
{
	EU_UART0 = 0xc0,
	EU_UART1 = 0xc8,
	EU_UART2 = 0xd0,
	EU_UART3 = 0x130,
};

enum E_UART_MODE
//UART MODE SET COMAND
{
	EU_TRA  = 0, //���M
	EU_REC  = 1, //��M
};

/************************************************************************/
#include "H28_AM640_u_class/H28_AM640_u_class.h"
/************************************************************************/

#endif /*_H28_AM640_U_MACRO_H_*/