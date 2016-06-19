
/*
includeするだけのヘッダファイルそれ以上でもそれ以下でもない
 H28 05 18 ver0.0.0
*/

#ifndef _H28_AM640_U_CLASS_H_
#define _H28_AM640_U_CLASS_H_ 1

#ifndef _H28_AM640_H_
{
	#error "Include <H28_AM640.h>"
}
#endif /*_H28_AM640_H_*/

#include "H28_U_C_UART_base.cpp"
#include "H28_U_C_UART_R.cpp"
#include "H28_U_C_UART2_R.cpp"
#include "H28_U_C_UART_T.cpp"
#include "H28_U_C_UART.cpp"

#endif