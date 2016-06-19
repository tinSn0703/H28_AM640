
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
	public:
	C_IO(){}
	C_IO(E_IO_PORT_ADDR ,E_MODE_IO );
	C_IO(E_IO_PORT_ADDR ,T_PORT );

};

#endif