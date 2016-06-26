
/*
IOピン用クラスの基礎。宣言しないでね。
 H28 05 11 ver0.0.0
 H28 05 18 ver0.1.0 メンバを削減して派生先に移した
 H28 05 22 ver1.0.0 PORTH以降しか使えなかったバグを叩き潰したついでに抽象クラスにした。
 H28 05 22 ver1.0.1 抽象クラスの使い方がよくわからんかったからpublicのないクラスにした。宣言しても意味ないよ。
 H28 05 23 ver1.0.2 抽象クラスにした
 H28 05 23 ver1.0.3 やっぱりやめた
 H28 06 12 ver1.1.0 条件演算子を用いてPORTを使うときのめんどくさいのを無くした。
 H28 06 12 ver1.2.0 デストラクタを追加。これで、子クラス終了時に、レジスタの設定が消されます。
*/

#ifndef _H28_I_C_IO_BASE_CPP_
#define _H28_I_C_IO_BASE_CPP_ 1

class C_IO_base
{
	private:
	E_IO_PORT_ADDR _mem_io_base_addr :9;
	E_IO_MODE  _mem_io_base_mode :1;
	E_LOGIC	   _mem_io_base_addr_point :1;
	
	protected:
	void Set_base_addr(E_IO_PORT_ADDR );
	void Set_base_mode(E_IO_MODE );
	
	E_IO_PORT_ADDR Ret_base_addr()	{	return _mem_io_base_addr;	}
	E_IO_MODE  Ret_base_mode()	{	return _mem_io_base_mode;	}
	E_LOGIC Ret_base_addr_point()	{	return _mem_io_base_addr_point;	}
	
	#define PIN_T	_SFR_MEM8(Ret_base_addr() + 0)
	#define DDR_T	_SFR_MEM8(Ret_base_addr() + 1)
	#define PORT_T	_SFR_MEM8(Ret_base_addr() + 2)
	
	#define PIN_F	_SFR_IO8(Ret_base_addr() + 0)
	#define DDR_F	_SFR_IO8(Ret_base_addr() + 1)
	#define PORT_F	_SFR_IO8(Ret_base_addr() + 2)
	
	#define PIN		(Ret_base_addr_point() == TRUE ? PIN_T : PIN_F)
	#define DDR		(Ret_base_addr_point() == TRUE ? DDR_T : DDR_F)
	#define PORT	(Ret_base_addr_point() == TRUE ? PORT_T : PORT_F)
	
	void Set_base(E_IO_PORT_ADDR ,E_IO_MODE ,T_PORT );
	
	public:
	
	~C_IO_base()
	{
		switch (Ret_base_mode())
		{
			case EI_IN:	 DDR  &= ~DDR;	break;
			case EI_OUT: PORT &= ~PORT;	break;
		}
	}
};

//protected
inline void C_IO_base::Set_base_addr(E_IO_PORT_ADDR _arg_io_base_addr)
{
	_mem_io_base_addr = _arg_io_base_addr;
	_mem_io_base_addr_point = CHECK_BIT_TF(_arg_io_base_addr,8);
}

inline void C_IO_base::Set_base_mode(E_IO_MODE _arg_io_base_mode)
{
	_mem_io_base_mode = _arg_io_base_mode;
}

void C_IO_base::Set_base(E_IO_PORT_ADDR _arg_io_base_addr, E_IO_MODE _arg_io_base_mode, T_PORT _arg_io_base_num)
{	
	Set_base_addr(_arg_io_base_addr);
	Set_base_mode(_mem_io_base_mode);
	
	switch (_arg_io_base_mode)
	{
		case EI_IN:
		{
			DDR  =  _arg_io_base_num;
			PORT = ~_arg_io_base_num;
			
			break;
		}
		case EI_OUT:
		{
			DDR  = ~_arg_io_base_num;
			PORT =  _arg_io_base_num;
			
			break;
		}
	}
}

#endif