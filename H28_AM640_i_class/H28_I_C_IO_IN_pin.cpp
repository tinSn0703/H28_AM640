
/*
1ピンのみ。センサなどに使えばいいんじゃないかな

 H28 06 12 ver0.0.0 
*/

#pragma once

#include "H28_I_C_IO_IN.cpp"

class C_IO_IN_pin : protected C_IO_IN
{
	private:
	E_IO_NUM _mem_io_in_pin_bit;
	
	protected:
	void Set(E_IO_PORT_ADDR ,E_IO_NUM );
	
	public:
	C_IO_IN_pin()	{}
	C_IO_IN_pin(E_IO_PORT_ADDR ,E_IO_NUM );
	
	BOOL In();
	BOOL In_turn();
	
	E_IO_NUM Ret_bit()	{	return _mem_io_in_pin_bit;	}
};

inline void 
C_IO_IN_pin::
Set
(
	E_IO_PORT_ADDR _arg_io_in_pin_addr, 
	E_IO_NUM _arg_io_in_pin_bit
)
{
	C_IO_base::Set_base(_arg_io_in_pin_addr,EI_IN);
	
	_mem_io_in_pin_bit = _arg_io_in_pin_bit;
	
	DDR  |=  (1 << _arg_io_in_pin_bit);
	PORT &= ~(1 << _arg_io_in_pin_bit);
}

//public
C_IO_IN_pin::
C_IO_IN_pin
(
	E_IO_PORT_ADDR _arg_io_in_pin_addr, 
	E_IO_NUM _arg_io_in_pin_bit
)
{
	Set(_arg_io_in_pin_addr, _arg_io_in_pin_bit);
}

inline BOOL 
C_IO_IN_pin::
In ()
{
	return C_IO_IN::In_num(_mem_io_in_pin_bit);
}

inline BOOL 
C_IO_IN_pin::
In_turn ()
{
	return TURN_TF(C_IO_IN::In_num(_mem_io_in_pin_bit));
}