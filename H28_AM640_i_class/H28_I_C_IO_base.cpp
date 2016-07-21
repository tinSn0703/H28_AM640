
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
	protected:
	
	E_IO_PORT_ADDR _mem_io_base_addr :9;
	E_IO_MODE  _mem_io_base_mode :1;
	
#if defined(_AVR_IOM640_H_)
	E_LOGIC	   _mem_io_base_addr_point :1;
	
	#define PIN		(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 0) : _SFR_IO8(_mem_io_base_addr + 0))
	#define DDR		(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 1) : _SFR_IO8(_mem_io_base_addr + 1))
	#define PORT	(_mem_io_base_addr_point == TRUE ? _SFR_MEM8(_mem_io_base_addr + 2) : _SFR_IO8(_mem_io_base_addr + 2))
#elif defined(_AVR_IOM164_H_)	
	#define	PIN  _SFR_IO8(_mem_io_base_addr + 0)
	#define DDR  _SFR_IO8(_mem_io_base_addr + 1)
	#define PORT _SFR_IO8(_mem_io_base_addr + 2)
#endif	
	
	void Set_base(E_IO_PORT_ADDR ,E_IO_MODE );
	void Set_base(E_IO_PORT_ADDR ,E_IO_MODE ,T_PORT );
	
	public:
	
	~C_IO_base()
	{
		switch (_mem_io_base_mode)
		{
			case EI_IN:	 DDR  &= ~DDR;	break;
			case EI_OUT: PORT &= ~PORT;	break;
		}
	}
};

//protected

inline void 
C_IO_base::
Set_base
(
	E_IO_PORT_ADDR _arg_io_base_addr, 
	E_IO_MODE _arg_io_base_mode
)
{
	_mem_io_base_addr = _arg_io_base_addr;
	
#ifndef _AVR_IOM640_H_
	_mem_io_base_addr_point = CHECK_BIT_TF(_arg_io_base_addr,8);
#endif
	
	_mem_io_base_mode = _arg_io_base_mode;
}

inline void 
C_IO_base::
Set_base
(
	E_IO_PORT_ADDR _arg_io_base_addr, 
	E_IO_MODE _arg_io_base_mode, 
	T_PORT _arg_io_base_num
)
{	
	Set_base(_arg_io_base_addr,_arg_io_base_mode);
	
	switch (_arg_io_base_mode)
	{
		case EI_IN:
		{
			DDR  = ~_arg_io_base_num;
			PORT =  _arg_io_base_num;
			
			break;
		}
		case EI_OUT:
		{
			DDR  =  _arg_io_base_num;
			PORT = ~_arg_io_base_num;
			
			break;
		}
	}
}

#endif