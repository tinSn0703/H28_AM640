
#ifndef _H28_I_C_AD_MEM_CPP_
#define _H28_I_C_AD_MEM_CPP_ 1

#include "H28_I_C_AD.cpp"

class C_AD_mem : protected C_AD
{
	private:
	usint _mem_ad_mem_data :10;
	
	protected:
	void Set_data(usint );
	void Set(E_AD_NUM ,E_LOGIC );
	
	public:
	C_AD_mem()	{}	
	C_AD_mem(E_AD_NUM ,E_LOGIC );
	
	usint Do();
	
	void Recet();
	usint Ret_data()	{	return _mem_ad_mem_data;	}
};

//protected
inline void C_AD_mem::Set_data(usint _arg_ad_mem_data)
{
	_mem_ad_mem_data = _arg_ad_mem_data;
}

inline void C_AD_mem::Set(E_AD_NUM _arg_ad_mem_num,E_LOGIC _arg_ad_mem_io_turn = TRUE)
{
	C_AD::Set(_arg_ad_mem_num,_arg_ad_mem_io_turn);
	_mem_ad_mem_data = 0;
}

//public
inline C_AD_mem::C_AD_mem(E_AD_NUM _arg_ad_mem_num,E_LOGIC _arg_ad_mem_io_turn = TRUE)
: C_AD(_arg_ad_mem_num,_arg_ad_mem_io_turn)
{
	_mem_ad_mem_data = 0;
}

inline void C_AD_mem::Recet()
{
	_mem_ad_mem_data = 0;
}

usint C_AD_mem::Do()
{
	_mem_ad_mem_data = C_AD::Do();
	
	return _mem_ad_mem_data;
}

#endif