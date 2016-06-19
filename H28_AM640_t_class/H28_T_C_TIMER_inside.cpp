
/*
クラス内部とかでの内部タイマ用のイメージ。継承して使ってどうぞ
 H28 05 16 ver 0.0.0
 H28 05 23 ver 0.1.0 publicメンバないから宣言しても意味ないよ
*/

#ifndef _H28_C_TIMER_INSIDE_CPP_
#define _H28_C_TIMER_INSIDE_CPP_ 1

class C_TIMER_inside
{
	private:
	uchar _mem_timer_inside_count :8;
	uchar _mem_timer_inside_limit :8;
	E_LOGIC _mem_timer_inside_flag  :1;
	
	protected:
	void Set(T_VALUE ,T_COUNT ,E_LOGIC );
	void Start();
	E_LOGIC Check();
	void End();
	
	E_LOGIC Ret_flag()	{	return _mem_timer_inside_flag;	}
};

//protected
inline void C_TIMER_inside::Set(T_VALUE _arg_timer_inside_limit, T_COUNT _arg_timer_inside_count = 0, E_LOGIC _arg_timer_inside_flag = FALES)
{
	//overflow
	TCCR0A = 0;
	TCCR0B = 0;
	TIMSK0 = 0;

	_mem_timer_inside_limit = _arg_timer_inside_limit;
	_mem_timer_inside_count = _arg_timer_inside_count;
	_mem_timer_inside_flag  = _arg_timer_inside_flag;
}

inline void C_TIMER_inside::Start()
{
	TCNT0 = 130; //100us
	TCCR0B = (1<<CS01);
	
	_mem_timer_inside_flag = TRUE;
	_mem_timer_inside_count = 0;
}

inline E_LOGIC C_TIMER_inside::Check()
{
	if ((_mem_timer_inside_flag & CHECK_BIT_TF(TIFR0,TOV0)) == TRUE)
	{
		TIFR0 |= (1 << TOV0);
		
		if (_mem_timer_inside_count < _mem_timer_inside_limit)
		//カウント中
		{
			TCNT0  = 130; //100us
			TCCR0B = (1<<CS01);
			
			_mem_timer_inside_count++;
		}
		else
		//カウント完了
		{
			TCCR0B = 0;
			End();
			
			return TRUE;
		}
	}
	
	return FALES;
}

inline void C_TIMER_inside::End()
{
	TCCR0B = 0;
	
	_mem_timer_inside_count = 0;
	_mem_timer_inside_flag = FALES;
}

#endif