
/*
TIMER系のクラスや関数を使うためのマクロやtypdef
 H28 05 18 ver0.0.0
*/

#ifndef _H28_AM640_T_MACRO_H_
#define _H28_AM640_T_MACRO_H_ 1

#ifndef _H28_AM640_H_
{
	#error "Include <H28_AM640.h>"
}
#endif /*_H28_AM640_H_*/

#include "H28_AM640_u_macro.h"
#include "H28_AM640_i_macro.h"

typedef float T_TIME;

/* MACRO TIMER ************************************************************/

enum E_TIMER_ADDR
//タイマーの番号。9bit
{
	ET_TIMER1 = 0x080,/*TIMER1*/
	ET_TIMER3 = 0x090,/*TIMER3*/
	ET_TIMER4 = 0x0a0,/*TIMER4*/
	ET_TIMER5 = 0x120,/*TIMER5*/
};

enum E_TIMER_MODE
//タイマーのモード。4bit
{
	ET_OVERFLOW = 4,/*溢れ*/
	ET_CAPUTER  = 6,/*捕獲*/
	ET_COMPARE  = 8,/*比較*/
};

enum E_CLOCK
//クロック。3bit
{
	EC_0    = 0x1,
	EC_8    = 0x2,
	EC_64   = 0x3,
	EC_256  = 0x4,
	EC_1024 = 0x5,
};

//bit TCCRA
#define WGM0  0
#define WGM1  1
#define COMC0 2
#define COMC1 3
#define COMB0 4
#define COMB1 5
#define COMA0 6
#define COMA1 7

//bit TCCRB
#define CS0  0
#define CS1  1
#define CS2  2
#define WGM2 3
#define WGM3 4
#define ICES 6
#define ICNC 7

//bit TCRRC
#define FOCC 5
#define FOCB 6
#define FOCA 7

//bit TIMSK
#define TOIE  0
#define OCIEA 1
#define OCIEB 2
#define OCIEC 3
#define ICIE  4

//bit TIFR
#define TOV  0
#define OCFA 1
#define OCFB 2
#define OCFC 3
#define ICF  5

#include "H28_AM640_t_class/H28_AM640_t_class.h"

#endif /*_H28_AM640_T_MACRO_H_*/