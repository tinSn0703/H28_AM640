
/*
1ピン用

 H28 06 13 ver0.0.0
*/

#pragma once

class C_IO_OUT_pin : protected C_IO_OUT
{
	private:
	E_IO_NUM _mem_io_out_pin_bit;
	
	protected:
	void Set(E_IO_PORT_ADDR ,E_IO_NUM );
	
	public:
	C_IO_OUT_pin()	{}
	C_IO_OUT_pin(E_IO_PORT_ADDR ,E_IO_NUM );
	
	void Out(BOOL );
	
	void Out_on();
	void Out_off();
	
	E_IO_NUM Ret_bit()	{	return _mem_io_out_pin_bit;	}
};

//protected
inline void 
C_IO_OUT_pin::
Set
(
	E_IO_PORT_ADDR _arg_io_out_pin_addr, 
	E_IO_NUM _arg_io_out_pin_bit
)
{
	C_IO_base::Set_base(_arg_io_out_pin_addr,EI_OUT);
	
	_mem_io_out_pin_bit = _arg_io_out_pin_bit;
	
	DDR  &= ~(1 << _arg_io_out_pin_bit);
	PORT |=  (1 << _arg_io_out_pin_bit);
}

//public
C_IO_OUT_pin::
C_IO_OUT_pin
(
	E_IO_PORT_ADDR _arg_io_in_pin_addr, 
	E_IO_NUM _arg_io_in_pin_bit
)
{
	Set(_arg_io_in_pin_addr, _arg_io_in_pin_bit);
}

inline void 
C_IO_OUT_pin::
Out (BOOL _arg_io_out_pin_nf)
{
	switch (_arg_io_out_pin_nf)
	{
		case TRUE:	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);	break;
		case FALES:	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);	break;
	}
}

inline void 
C_IO_OUT_pin::
Out_on ()
{
	C_IO_OUT::Out_num_on(_mem_io_out_pin_bit);
}

inline void 
C_IO_OUT_pin::
Out_off ()
{
	C_IO_OUT::Out_num_off(_mem_io_out_pin_bit);
}
