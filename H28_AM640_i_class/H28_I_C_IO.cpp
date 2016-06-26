
/*
IN,OUT両方できるIO系のクラス
 H28 05 18 ver0.0.0
*/

#ifndef _H28_I_C_IO_CPP_
#define _H28_I_C_IO_CPP_ 1

#include "H28_I_C_IO_IN.cpp"
#include "H28_I_C_IO_OUT.cpp"

class C_IO : public C_IO_IN , public C_IO_OUT
{
	protected:
	void Set(E_IO_PORT_ADDR ,E_IO_MODE ,T_PORT );
	
	public:
	C_IO(){}
	C_IO(E_IO_PORT_ADDR ,E_IO_MODE ,T_PORT );
};

//prptected
inline void C_IO::Set(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_set)
{
	switch (_arg_io_mode)
	{
		case EI_IN:
		{
			C_IO_IN::Set(_arg_io_addr,_arg_io_set);		break;
		}
		case EI_OUT:
		{
			C_IO_OUT::Set(_arg_io_addr,_arg_io_set);	break;
		}
	}
}

//public
C_IO::C_IO(E_IO_PORT_ADDR _arg_io_addr, E_IO_MODE _arg_io_mode, T_PORT _arg_io_set)
{
	Set(_arg_io_addr, _arg_io_mode, _arg_io_set);
}

#endif