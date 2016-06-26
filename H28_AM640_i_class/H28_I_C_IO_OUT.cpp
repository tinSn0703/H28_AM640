
/*
OUTのみのIO系のクラス
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_baseのメンバの一部を映した
 H28 05 22 ver1.0.0 C_IO_baseのバージョンアップへの対応
 H28 06 12 ver1.1.0 EN_IO_NUMのコンストラクタを削除
 H28 06 12 ver1.2.0 C_IO_baseのバージョンアップへの対応
*/

#ifndef _H28_I_C_IO_OUT_CPP_
#define _H28_I_C_IO_OUT_CPP_ 1

#include "H28_I_C_IO_base.cpp"

class C_IO_OUT : public virtual C_IO_base
{
	protected:
	void Set(E_IO_PORT_ADDR ,T_PORT );
	
	public:
	C_IO_OUT(){}
	C_IO_OUT(E_IO_PORT_ADDR ,T_PORT );
	
	void Out(T_PORT );
	void Out_on();
	void Out_off();
	
	void Out_num_on(E_IO_NUM );
	void Out_num_off(E_IO_NUM );
};

//protected
inline void C_IO_OUT::Set(E_IO_PORT_ADDR _arg_io_out_addr, T_PORT _arg_io_out_num_byte)
{
	C_IO_base::Set_base(_arg_io_out_addr, EI_OUT, _arg_io_out_num_byte);
}

//public
C_IO_OUT::C_IO_OUT(E_IO_PORT_ADDR _arg_io_out_addr, T_PORT _arg_io_out_num_byte)
{
	Set(_arg_io_out_addr, _arg_io_out_num_byte);
}

inline void C_IO_OUT::Out(T_PORT _arg_io_out_num_byte)
{
	PORT = _arg_io_out_num_byte;
}

inline void C_IO_OUT::Out_on()
{
	Out(0xff);
}

inline void C_IO_OUT::Out_off()
{
	Out(0x00);
}

inline void C_IO_OUT::Out_num_on(E_IO_NUM _arg_io_out_on_num_bit)
{
	PORT |= (1 << _arg_io_out_on_num_bit);
}

inline void C_IO_OUT::Out_num_off(E_IO_NUM _arg_io_out_off_num_bit)
{
	PORT &= ~(1 << _arg_io_out_off_num_bit);
}

#endif