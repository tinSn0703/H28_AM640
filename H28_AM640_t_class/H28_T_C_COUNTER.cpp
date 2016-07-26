
/*
タイマを秒数以上にカウントするようの構造体。あのカチカチ数を数える奴みたいな感じに使ってね
 H28 05 07 ver0.0.0
 H28 05 16 ver1.0.0 classにした。何となく使いづらいので要改造。特にflagやcountを行うあたり
*/

#pragma once

class C_COUNTER
{
	private:
	T_COUNT _mem_counter_count;	//カウントの回数
	BOOL _mem_counter_nf :1;	//カウントのONOFF
	T_VALUE _mem_counter_limit;	//カウントの上限
	
	public:
	C_COUNTER()	{}	
	C_COUNTER(T_VALUE ,T_COUNT ,BOOL );
	
	BOOL Ret_flag()	{	return _mem_counter_nf;		}
	T_COUNT Ret_count()	{	return _mem_counter_count;	}
	T_VALUE Ret_limit()	{	return _mem_counter_limit;	}
	
	void On();
	void Off();
	
	BOOL Count();
	void Count_up();
	void Count_down();
	void Count_reset();	
	
	BOOL Check_limit();
	
	void End();
};

inline 
C_COUNTER::
C_COUNTER
(
	T_VALUE _arg_counter_limit, 
	T_COUNT _arg_counter_count = 0, 
	BOOL _arg_counter_nf = FALES
)
{
	_mem_counter_count = _arg_counter_count;
	_mem_counter_nf  = _arg_counter_nf;
	_mem_counter_limit = _arg_counter_limit;
}

inline void 
C_COUNTER::
On ()
{
	_mem_counter_nf = TRUE;
}

inline void 
C_COUNTER::
Off ()
{
	_mem_counter_nf = FALES;
}

BOOL 
C_COUNTER::
Count ()
{
	if (_mem_counter_nf == TRUE)
	{
		_mem_counter_count ++;
		
		if (_mem_counter_count == _mem_counter_limit)
		{
			End();
			
			return TRUE;
		}
	}
	
	return FALES;
}

inline void 
C_COUNTER::
Count_up ()
{
	_mem_counter_count ++;
}
	
inline void 
C_COUNTER::
Count_down ()
{
	_mem_counter_count --;
}

inline BOOL 
C_COUNTER::
Check_limit ()
{
	if (_mem_counter_count == _mem_counter_limit)	return TRUE;
	
	return FALES;
}

inline void 
C_COUNTER::
Count_reset ()
{
	_mem_counter_count = 0;
}

inline void 
C_COUNTER::
End ()
{
	_mem_counter_count = 0;
	_mem_counter_nf = FALES;
}