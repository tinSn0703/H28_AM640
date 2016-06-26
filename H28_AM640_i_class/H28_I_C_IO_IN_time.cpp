
/*
一定時間確認してからHIGH/LOWの判断をするIO系のクラス
 
*/

#ifndef _H28_I_C_IO_IN_TIME_CPP_
#define _H28_I_C_IO_IN_TIME_CPP_ 1

#include "H28_I_C_IO_IN.cpp"

class C_IO_IN_time : protected C_IO_IN , public C_TIMER_inside
{
	private:
	E_LOGIC _mem_io_in_time_normal_bit :1;
	T_PORT _mem_io_in_time_normal_byte :8;
	
	public:
	C_IO_IN_time() {}
	C_IO_IN_time(E_IO_PORT_ADDR ,E_IO_NUM ,E_LOGIC );	
	C_IO_IN_time(E_IO_PORT_ADDR, T_PORT ,E_LOGIC );
	
	void Set_normal(T_PORT );
	
	T_PORT In();
	E_LOGIC In_num(E_IO_NUM );
};

//public member
C_IO_IN_time::C_IO_IN_time(E_IO_PORT_ADDR _arg_io_in_time_port_addr,E_IO_NUM _arg_io_in_time_num_bit,E_LOGIC _arg_io_in_time_normal = FALES)
: C_IO_IN(_arg_io_in_time_port_addr,_arg_io_in_time_num_bit)
{	
	C_TIMER_inside::Set(1);
	
	_mem_io_in_time_normal_bit = _arg_io_in_time_normal;
	
	if (_arg_io_in_time_normal == FALES)	_mem_io_in_time_normal_byte = 0x00;
	else							_mem_io_in_time_normal_byte = 0xff;
}

C_IO_IN_time::C_IO_IN_time(E_IO_PORT_ADDR _arg_io_in_time_port_addr,T_PORT _arg_io_in_time_num_byte ,E_LOGIC _arg_io_in_time_normal = FALES)
: C_IO_IN(_arg_io_in_time_port_addr,_arg_io_in_time_num_byte)
{
	C_TIMER_inside::Set(1);
	
	_mem_io_in_time_normal_bit = _arg_io_in_time_normal;
	
	if (_arg_io_in_time_normal == FALES)	_mem_io_in_time_normal_byte = 0x00;
	else							_mem_io_in_time_normal_byte = 0xff;
}

inline void C_IO_IN_time::Set_normal(T_PORT _arg_io_in_time_normal_byte)
{
	_mem_io_in_time_normal_byte = _arg_io_in_time_normal_byte;
}

T_PORT C_IO_IN_time::In()
{
	uint i = 0;
	uint j = 0;
	
	Start();
	
	while (j < 20)
	{
		if (Check() == TRUE)
		{
			j++;
			
			if (C_IO_IN::In() != _mem_io_in_time_normal_byte)	i++;
			
			Start();
		}
	}
	
	if (i > 10)	return ~_mem_io_in_time_normal_byte;
	
	return 0;
}

E_LOGIC C_IO_IN_time::In_num(E_IO_NUM _arg_io_in_num_bit)
{
	uint i = 0;
	uint j = 0;

	while (j < 20)
	{
		if (Check() == TRUE)
		{
			j++;
			
			if (C_IO_IN::In_num(_arg_io_in_num_bit) != _mem_io_in_time_normal_bit)	i++;
			
			Start();
		}
	}
	
	if (i > 10)	return TRUE;
	
	return FALES;
}

#endif