
/*
複数のPORTにまたがったり、pin数を変えたりしてIOピンの設定ができる。
 H28 05 09 ver0.0.0
 H28 06 12 ver0.1.0 C_IO_pinから改名。これよりフォルダ変えます
*/

#ifndef _H28_I_C_IO_ADJU_CPP_
#define _H28_I_C_IO_ADJU_CPP_ 1

#include <stdlib.h>

class C_IO_adju
{
	protected:
	E_IO_PORT_ADDR *_mem_io_adju_addr;
	E_IO_NUM *_mem_io_adju_bit;
	E_IO_MODE _mem_io_adju_mode :1;
	T_NUM _mem_io_adju_num :8;
	
	#define	PINX(_def_io_adju_bit)  _SFR_MEM8( *(_mem_io_adju_addr + _def_io_adju_bit) + 0)
	#define DDRX(_def_io_adju_bit)  _SFR_MEM8( *(_mem_io_adju_addr + _def_io_adju_bit) + 1)
	#define PORTX(_def_io_adju_bit) _SFR_MEM8( *(_mem_io_adju_addr + _def_io_adju_bit) + 2)
	
	public:
	C_IO_adju(T_NUM ,E_IO_MODE );
	
	void Set(T_NUM ,E_IO_PORT_ADDR ,E_IO_NUM );
	
	void Out(T_NUM );
	void Out_num(T_NUM ,E_LOGIC );
	
	T_NUM In();
	E_LOGIC In_num(T_NUM );
	
	T_NUM Ret_pin_num();
	
	~C_IO_adju();
};

C_IO_adju::C_IO_adju(T_NUM _arg_io_adju_num,E_IO_MODE _arg_io_adju_mode)
{
	_mem_io_adju_addr = (E_IO_PORT_ADDR *)malloc(_arg_io_adju_num);
	_mem_io_adju_bit = (E_IO_NUM *)malloc(_arg_io_adju_num);
	
	_mem_io_adju_num = _arg_io_adju_num;
	_mem_io_adju_mode = _arg_io_adju_mode;
}

void C_IO_adju::Set(T_NUM _arg_io_adju_num,E_IO_PORT_ADDR _arg_io_adju_addr,E_IO_NUM _arg_io_adju_bit)
{	
	_mem_io_adju_addr[_arg_io_adju_num] = _arg_io_adju_addr;
	_mem_io_adju_bit[_arg_io_adju_num] = _arg_io_adju_bit;
	
	if(_mem_io_adju_mode == EI_IN)
	{
		DDRX(_arg_io_adju_num)  &= ~(1 << _arg_io_adju_bit);
		PORTX(_arg_io_adju_num) |=  (1 << _arg_io_adju_bit);
	}
	else
	{
		DDRX(_arg_io_adju_num)  |=  (1 << _arg_io_adju_bit);
		PORTX(_arg_io_adju_num) &= ~(1 << _arg_io_adju_bit);
	}
}

void C_IO_adju::Out(T_NUM _arg_io_adju_out)
{
	for(T_NUM i = 0; i < _mem_io_adju_num; i++)
	{
		Out_num(i,CHECK_BIT_TF(_arg_io_adju_out,i));
	}
}

inline void C_IO_adju::Out_num(T_NUM _arg_io_adju_out_bit,E_LOGIC _arg_io_adju_nf_out)
{
	if(_arg_io_adju_nf_out == TRUE)
	{
		PORTX(_arg_io_adju_out_bit) |= (1 << _mem_io_adju_bit[_arg_io_adju_out_bit]);
	}
	else
	{
		PORTX(_arg_io_adju_out_bit) &= ~(1 << _mem_io_adju_bit[_arg_io_adju_out_bit]);
	}
}

T_NUM C_IO_adju::In()
{
	T_NUM _ret_io_pin_in_data = 0;
	
	for(T_NUM i = 0; i< _mem_io_adju_num; i++)
	{
		_ret_io_pin_in_data |= (In_num(i) << i);
	}
	
	return _ret_io_pin_in_data;
}

inline E_LOGIC C_IO_adju::In_num(T_NUM _arg_io_adju_in_bit)
{
	return CHECK_BIT_TF(PINX(_arg_io_adju_in_bit),_mem_io_adju_bit[_arg_io_adju_in_bit]);
}

inline T_NUM C_IO_adju::Ret_pin_num()
{
	return _mem_io_adju_num;
}

C_IO_adju::~C_IO_adju()
{
	delete[] _mem_io_adju_addr;
	delete[] _mem_io_adju_bit;
}
#endif