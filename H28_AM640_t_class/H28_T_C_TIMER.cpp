
/*
カウント程度はできる。機能的にはStopWatchのようなもの
 H28 05 10 ver 0.0.0
 H28 05 20 ver 0.1.0 C_TIMER_baseのコンストラクタでコンストラクタの設定をすることにした.
 H28 05 20 ver 1.0.0 C_TOMER_baseに設定用の関数と変数を移し、動作系の関数の中身を持ってきた
*/

#ifndef _H28_T_C_TIMER_CPP_
#define _H28_T_C_TIMER_CPP_ 1

#include "H28_T_C_TIMER_base.cpp"

class C_TIMER : public virtual C_TIMER_base
{	
	protected:
	void Set(E_TIMER_NUM , E_TIMER_MODE , E_LOGIC );
	void Set(E_TIMER_NUM ,E_TIMER_MODE ,E_CLOCK ,T_VALUE ,E_LOGIC );
	
	public:
	C_TIMER()	{}
	C_TIMER(E_TIMER_NUM , E_TIMER_MODE , E_LOGIC );
	C_TIMER(E_TIMER_NUM ,E_TIMER_MODE ,E_CLOCK ,T_VALUE ,E_LOGIC );
	
	void Start();
	void Start(E_CLOCK ,T_VALUE );
	
	E_LOGIC Flag_timer(E_LOGIC );
	
	void Stop();
};

//protected
inline void C_TIMER::Set(E_TIMER_NUM _arg_timer_num, E_TIMER_MODE _arg_timer_mode, E_LOGIC _arg_timer_nf_isr = FALES)
{
	C_TIMER_base::Set_base(_arg_timer_num, _arg_timer_mode, _arg_timer_nf_isr);
}

inline void C_TIMER::Set(E_TIMER_NUM _arg_timer_num, E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, T_VALUE _arg_timer_counter, E_LOGIC _arg_timer_nf_isr = FALES)
{
	C_TIMER_base::Set_base(_arg_timer_num, _arg_timer_mode, _arg_timer_nf_isr);
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
}

//public
inline C_TIMER::C_TIMER(E_TIMER_NUM _arg_timer_num, E_TIMER_MODE _arg_timer_mode, E_LOGIC _arg_timer_nf_isr = FALES)
{
	Set(_arg_timer_num, _arg_timer_mode, _arg_timer_nf_isr);
}

inline C_TIMER::C_TIMER(E_TIMER_NUM _arg_timer_num, E_TIMER_MODE _arg_timer_mode, E_CLOCK _arg_timer_clock, T_VALUE _arg_timer_counter, E_LOGIC _arg_timer_nf_isr = FALES)
{
	Set(_arg_timer_num, _arg_timer_mode, _arg_timer_clock, _arg_timer_counter, _arg_timer_nf_isr);
}

inline void C_TIMER::Start()
{
	Stop();
	
	COUNTERH = ((_mem_timer_base_counter >> 8) & 0xff);
	COUNTERL = (_mem_timer_base_counter & 0xff);
	
	TCCRB |= _mem_timer_base_clock;
}

inline void C_TIMER::Start(E_CLOCK _arg_timer_clock, T_VALUE _arg_timer_counter)
{
	C_TIMER_base::Set_condition(_arg_timer_clock, _arg_timer_counter);
	
	Start();
}

E_LOGIC C_TIMER::Flag_timer(E_LOGIC _arg_timer_continue = TRUE)
{
	usint mode_bit = 0;
	
	switch (_mem_timer_base_mode)
	{
		case ET_CAPUTER:	mode_bit = ICF;		break;
		case ET_COMPARE:	mode_bit = OCFA;	break;
		case ET_OVERFLOW:	mode_bit = TOV;		break;
	}
	
	if (CHECK_BIT_TF(TIFR,mode_bit))
	{
		TIFR |= (1 << mode_bit);
		
		if (_arg_timer_continue)	Start();
		
		return TRUE;
	}
	
	return FALES;
}

inline void C_TIMER::Stop()
{
	TCCRB &= ~TIME_SET_BIT;
}

#endif