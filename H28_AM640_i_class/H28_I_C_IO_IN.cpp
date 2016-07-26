
/*
INのみ可能なIO系のクラス
 H28 05 18 ver0.0.0
 H28 05 18 ver0.1.0 C_IO_baseのメンバの一部を映した
 H28 05 22 ver1.0.0 C_IO_baseのバージョンアップへの対応
 H28 06 12 ver1.1.0 E_IO_NUMのコンストラクタを削除
 H28 06 12 ver1.2.0 C_IO_baseのバージョンアップへの対応
*/

#pragma once

#include "H28_I_C_IO_base.cpp"

class C_IO_IN : public virtual C_IO_base
{
	protected:
	void Set(E_IO_PORT_ADDR ,T_PORT );
	
	public:
	C_IO_IN(){}
	C_IO_IN(E_IO_PORT_ADDR ,T_PORT );

	T_PORT In();
	BOOL In_num(E_IO_NUM );
};

//protected
inline void 
C_IO_IN::
Set
(
	E_IO_PORT_ADDR _arg_io_in_addr, 
	T_PORT _arg_io_in_num_byte
)
{
	C_IO_base::Set_base(_arg_io_in_addr, EI_IN, _arg_io_in_num_byte);
}

//public
C_IO_IN::
C_IO_IN
(
	E_IO_PORT_ADDR _arg_io_in_addr, 
	T_PORT _arg_io_in_num_byte
)
{
	Set(_arg_io_in_addr, _arg_io_in_num_byte);
}

inline T_PORT 
C_IO_IN::
In ()
{
	return PIN;
}

inline BOOL 
C_IO_IN::
In_num (E_IO_NUM _arg_io_in_num_bit)
{		
	return CHECK_BIT_TF(PIN, _arg_io_in_num_bit);
}