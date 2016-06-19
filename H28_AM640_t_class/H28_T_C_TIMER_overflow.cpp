
#ifndef _H28_T_C_TIMER_OVERFLOW_CPP_
#define _H28_T_C_TIMER_OVERFLOW_CPP_ 1

class C_TIMER_overflow : protected C_TIMER
{
	protected:
	void Set(E_NUM_TIMER ,E_LOGIC );
	
	public:
	C_TIMER_overflow()	{}
	C_TIMER_overflow(E_NUM_TIMER ,E_LOGIC );
	C_TIMER_overflow(E_NUM_TIMER ,E_CLOCK_TIMER ,T_VALUE ,E_LOGIC );
	
	void Set_condition(E_CLOCK_TIMER ,T_VALUE );
	
	void Start();
	void Start(E_CLOCK_TIMER ,T_VALUE );

	E_LOGIC Flag_timer(E_LOGIC );
	
	void Stop();
};

//protected
inline void C_TIMER_overflow::Set(E_NUM_TIMER _arg_timer_addr, E_LOGIC _arg_timer_nf_isr = FALES)
{
	C_TIMER_base::Set_base_addr(_arg_timer_addr);
	
	TCCRA = 0x00;
	
	TCCRB = 0x00;
	TIMSK = (_arg_timer_nf_isr << TOIE);
	
	TCCRC = 0x00;
}

//public
inline C_TIMER_overflow::C_TIMER_overflow(E_NUM_TIMER _arg_timer_addr, E_LOGIC _arg_timer_nf_isr = FALES)
{
	Set(_arg_timer_addr,_arg_timer_nf_isr);	
}

inline C_TIMER_overflow::C_TIMER_overflow(E_NUM_TIMER _arg_timer_addr, E_CLOCK_TIMER _arg_timer_clock, T_VALUE _arg_timer_counter, E_LOGIC _arg_timer_nf_isr = FALES)
{
	Set_condition(_arg_timer_clock,_arg_timer_counter);
	Set(_arg_timer_addr,_arg_timer_nf_isr);
}

inline void C_TIMER_overflow::Set_condition(E_CLOCK_TIMER _arg_timer_clock, T_VALUE _arg_timer_counter)
{
	C_TIMER_base::Set_condition(_arg_timer_clock,_arg_timer_counter);
}

inline void C_TIMER_overflow::Start()
{
	C_TIMER::Start();
}

inline void C_TIMER_overflow::Start(E_CLOCK_TIMER _arg_timer_clock,T_VALUE _arg_timer_counter)
{
	C_TIMER::Start(_arg_timer_clock,_arg_timer_counter);
}

inline E_LOGIC C_TIMER_overflow::Flag_timer(E_LOGIC _arg_timer_continue = TRUE)
{
	if (CHECK_BIT_TF(TIFR,TOV) == TRUE)
	{
		TIFR |= (1 << TOV);
		
		if (_arg_timer_continue == TRUE)
		{
			Start();
		}
		
		return TRUE;
	}
	
	return FALES;
}

inline void C_TIMER_overflow::Stop()
{
	C_TIMER::Stop();
}

#endif