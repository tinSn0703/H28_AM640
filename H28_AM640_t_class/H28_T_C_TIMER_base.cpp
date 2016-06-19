﻿
/*
TIMER系の基底クラス
 H28 05 18 ver0.0.0
 H28 05 20 ver0.1.0 Flag_timerの中身を書き換えた
 H28 05 20 ver0.2.0 コンストラクタを付けた。割り込みを基本OFFにした
 H28 05 20 ver1.0.0 実際の動作系の関数を削って、設定用の変数と関数を追加した。
 H28 05 20 ver1.0.1 _mam_timer_base_nf_isrが不要だったので削除した。
*/

#ifndef _H28_T_C_TIMER_BASE_CPP_
#define _H28_T_C_TIMER_BASE_CPP_ 1

class C_TIMER_base
{
	private:
	E_TIMER_NUM		_mem_timer_base_port_addr :9;
	T_NUM			_mem_timer_base_port_addr_plus :3;
	E_TIMER_MODE	_mem_timer_base_mode :4;
	T_VALUE			_mem_timer_base_counter :16;
	E_CLOCK	_mem_timer_base_clock :3;
	
	protected:
	
	void Set_base_addr(E_TIMER_NUM );	
	void Set_base_mode(E_TIMER_MODE );
	void Set_base_counter(T_VALUE );
	void Set_base_clock(E_CLOCK );
	
	E_TIMER_NUM Ret_base_addr()		{	return _mem_timer_base_port_addr;		}
	T_NUM Ret_base_addr_plus()		{	return _mem_timer_base_port_addr_plus;	}
	E_TIMER_MODE Ret_base_mode()	{	return _mem_timer_base_mode;			}
	T_VALUE Ret_base_counter()		{	return _mem_timer_base_counter;			}
	E_CLOCK Ret_base_clock()	{	return _mem_timer_base_clock;			}
	
	#define TCCRA		_SFR_MEM8(Ret_base_addr() + 0)
	#define TCCRB		_SFR_MEM8(Ret_base_addr() + 1)
	#define TCCRC		_SFR_MEM8(Ret_base_addr() + 2)
	#define TIMSK		_SFR_MEM8(Ret_base_addr_plus() + 0x6e)
	#define TIFR		_SFR_MEM8(Ret_base_addr_plus() + 0x35)
	#define COUNTERL	_SFR_MEM8(Ret_base_addr() + Ret_base_mode())
	#define COUNTERH	_SFR_MEM8(Ret_base_addr() + Ret_base_mode() + 1)
	
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
	
	/*bit TIFR*/
	#define TOV  0
	#define OCFA 1
	#define OCFB 2
	#define OCFC 3
	#define ICF  5
	
	#define TIME_SET_BIT ((1<<CS2)|(1<<CS1)|(1<<CS0))
	
	void Set_base(E_TIMER_NUM ,E_TIMER_MODE ,E_LOGIC );
	void Set_mode(E_TIMER_MODE , E_LOGIC );
	
	public:
	void Set_condition(E_CLOCK ,T_VALUE );
};

//protected
inline void C_TIMER_base::Set_base_addr(E_TIMER_NUM _arg_timer_base_addr)
{
	_mem_timer_base_port_addr = _arg_timer_base_addr;
	
	switch (_arg_timer_base_addr)
	{
		case ET_TIMER1:	_mem_timer_base_port_addr_plus = 1;	break;
		case ET_TIMER3:	_mem_timer_base_port_addr_plus = 3;	break;
		case ET_TIMER4:	_mem_timer_base_port_addr_plus = 4;	break;
		case ET_TIMER5:	_mem_timer_base_port_addr_plus = 5;	break;
	}
}

inline void C_TIMER_base::Set_base_mode(E_TIMER_MODE _arg_timer_base_mode)		{	_mem_timer_base_mode = _arg_timer_base_mode;			}
inline void C_TIMER_base::Set_base_counter(T_VALUE _arg_timer_base_counter)		{	_mem_timer_base_counter = _arg_timer_base_counter;	}
inline void C_TIMER_base::Set_base_clock(E_CLOCK _arg_timer_base_clock)	{	_mem_timer_base_clock = _arg_timer_base_clock;		}

inline void C_TIMER_base::Set_base(E_TIMER_NUM _arg_timer_base_num, E_TIMER_MODE _arg_timer_base_mode , E_LOGIC _arg_timer_base_nf_isr = FALES)
{
	Set_base_addr(_arg_timer_base_num);
	
	TCCRA = 0x00;
	
	Set_mode(_arg_timer_base_mode, _arg_timer_base_nf_isr);
	
	TCCRC = 0x00;
}

inline void C_TIMER_base::Set_mode(E_TIMER_MODE _arg_timer_base_mode, E_LOGIC _arg_timer_base_nf_isr = FALES)
{
	Set_base_mode(_arg_timer_base_mode);
	
	switch (_arg_timer_base_mode)
	{
		case ET_CAPUTER:	//比較
		{
			TCCRB = ((1<<WGM3) | (1<<WGM2));
			TIMSK = (_arg_timer_base_nf_isr << ICIE);
			break;
		}
		case ET_COMPARE:	//捕獲
		{
			TCCRB = (1<<WGM2);
			TIMSK = (_arg_timer_base_nf_isr << OCIEA);
			break;
		}
		case ET_OVERFLOW:	//溢れ
		{
			TCCRB = 0x00;
			TIMSK = (_arg_timer_base_nf_isr << TOIE);
			break;
		}
	}
}

//public
inline void C_TIMER_base::Set_condition(E_CLOCK _arg_timer_base_clock, T_VALUE _arg_timer_base_counter)
{
	Set_base_clock(_arg_timer_base_clock);
	Set_base_counter(_arg_timer_base_counter);
}

#endif