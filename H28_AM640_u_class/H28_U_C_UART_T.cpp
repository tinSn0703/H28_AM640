
/*
送信を行うUART系のクラス
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 C_UART_baseの改造に合わせた
*/

#pragma once

#include "H28_U_C_UART_base.cpp"

class C_UART_T : public virtual C_UART_base
{
	protected:	
	void Set(E_UART_ADDR ,E_LOGIC );
	
	public:
	C_UART_T() {}
	C_UART_T(E_UART_ADDR ,E_LOGIC );
	
	void Set_isr(E_LOGIC );
	void Out(T_DATA );
	
	friend void operator<<(C_UART_T &,T_DATA );
};

//protected
inline void 
C_UART_T::
Set
(
	E_UART_ADDR _arg_uart_t_addr, 
	E_LOGIC _arg_uart_t_nf_isr = FALES
)
{
	C_UART_base::Set_base(_arg_uart_t_addr);
	Set_isr(_arg_uart_t_nf_isr);
}

//public
inline 
C_UART_T::
C_UART_T
(
	E_UART_ADDR _arg_uart_t_addr, 
	E_LOGIC _arg_uart_t_nf_isr = FALES
)
{	
	Set(_arg_uart_t_addr, _arg_uart_t_nf_isr);
}

inline void 
C_UART_T::
Set_isr (E_LOGIC _arg_uart_t_nf_isr)
{
	switch (_arg_uart_t_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << UDRIE);	break; //On
		case FALES:	UCSRB &= ~(1 << UDRIE);	break; //Off
	}
}

void 
C_UART_T::
Out (T_DATA _arg_uart_t_out_data)
{	
	UCSRB |= (1 << TXEN); //送信許可する。
	
	while (!(UCSRA & (1 << UDRE))); //送信が可能になるまで待機
	
	if ((C_UART_base::Ret_bit9() & CHECK_BIT_TF(_arg_uart_t_out_data,8)) == TRUE)
	{
		UCSRB |= (1 << TXB8);
	}

	UDR = (_arg_uart_t_out_data & 0xff);
	
	while (!(UCSRA & (1 << TXC))); //送信完了まで待機
	
	UCSRA |= (1 << TXC);
}

void 
operator << 
(
	C_UART_T &_arg_uart_t,
	T_DATA _arg_uart_t_data_out
)
{
	_arg_uart_t.Out(_arg_uart_t_data_out);
}