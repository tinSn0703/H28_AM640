
/*
TIMER系のクラスをincludeするためだけのファイル
 H28 05 18 ver0.0.0
*/

#ifndef _H28_AM640_T_CLASS_H_
#define _H28_AM640_T_CLASS_H_ 1

#ifndef _H28_AM640_H_
{
	#error "Include <H28_AM640.h>"
}
#endif

#include "H28_T_C_COUNTER.cpp"

#include "H28_T_C_TIMER_base.cpp"
#include "H28_T_C_TIMER.cpp"
//#include "H28_T_C_TIMER_overflow.cpp"
#include "H28_T_C_TIMER_inside.cpp"

#endif