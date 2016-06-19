
/*
TIMER�n�̃N���X��֐����g�����߂̃}�N����typdef
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
enum E_TIMER_NUM
//�^�C�}�[�̔ԍ��B9bit
{
	ET_TIMER1 = 0x80,/*TIMER1*/
	ET_TIMER3 = 0x90,/*TIMER3*/
	ET_TIMER4 = 0xa0,/*TIMER4*/
	ET_TIMER5 = 0x120,/*TIMER5*/
};

enum E_TIMER_MODE
//�^�C�}�[�̃��[�h�B4bit
{
	ET_OVERFLOW = 4,/*���*/
	ET_CAPUTER  = 6,/*�ߊl*/
	ET_COMPARE  = 8,/*��r*/
};

enum E_CLOCK
//�N���b�N�B3bit
{
	EC_0    = 0x1,
	EC_8    = 0x2,
	EC_64   = 0x3,
	EC_256  = 0x4,
	EC_1024 = 0x5,
};

#include "H28_AM640_t_class/H28_AM640_t_class.h"

#endif /*_H28_AM640_T_MACRO_H_*/