
/*
受信、送信両方を行えるUART系のクラス
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_baseの改造に合わせた
*/

#ifndef _H28_U_C_UART_CPP_
#define _H28_U_C_UART_CPP_ 1

#include "H28_U_C_UART_R.cpp"
#include "H28_U_C_UART_T.cpp"

class C_UART : public C_UART_R , public C_UART_T
{
	void Set(E_UART_ADDR ,E_LOGIC );
	
	public:
	C_UART() {}
	C_UART(E_UART_ADDR ,E_UART_MODE ,E_LOGIC);
	
	void Chan_mode(E_UART_MODE );
	void Set_isr(E_LOGIC );
};

C_UART::C_UART(E_UART_ADDR _arg_uart_addr, E_UART_MODE _arg_uart_mode, E_LOGIC _arg_uart_nf_isr = FALES)
{
	Set_base(_arg_uart_addr,_arg_uart_mode);
	Set_isr(_arg_uart_nf_isr);
}

inline void C_UART::Chan_mode(E_UART_MODE _arg_uart_mode_chan)
{
	Set_uart_base_mode(_arg_uart_mode_chan);
}

inline void C_UART::Set_isr(E_LOGIC _arg_uart_nf_isr)
{
	switch(Ret_uart_base_mode())
	{
		case EU_REC:	C_UART_R::Set_isr(_arg_uart_nf_isr);	break;
		case EU_TRA:	C_UART_T::Set_isr(_arg_uart_nf_isr);	break;
	}
}

#endif