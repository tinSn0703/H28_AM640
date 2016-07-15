
/*
受信のみ可能なUART系列のクラス
 H28 05 13 ver 0.0.0
 H28 05 16 ver 0.1.0 継承でC_TIMER_insideをとっつけて,class内部のカウントをこいつで行うようにした。
 H28 05 23 ver 0.2.0 C_UART_baseの改造に合わせた
*/

#ifndef _H28_U_C_UART_R_CPP_
#define _H28_U_C_UART_R_CPP_ 1

#include "H28_U_C_UART_base.cpp"

class C_UART_R : public virtual C_UART_base , public C_TIMER_inside
{
	protected:
	E_UART_FLAG _mem_uart_r_flag :2; //最後の受信状態の記録
	
	void Set(E_UART_ADDR ,E_LOGIC );
	
	public:
	C_UART_R() {}
	C_UART_R(E_UART_ADDR ,E_LOGIC );
	
	void Set_isr(E_LOGIC );
	void Check();
	
	T_DATA In();

	E_UART_FLAG Ret_flag()	{	return _mem_uart_r_flag;	}
	
	friend void operator >> (C_UART_R &, T_DATA &);
	friend void operator >> (C_UART_R &, T_DATA_8 &);
	
	friend bool operator == (C_UART_R &,E_UART_FLAG );
	friend bool operator != (C_UART_R &,E_UART_FLAG );
};

//protevted
inline void C_UART_R::Set(E_UART_ADDR _arg_uart_r_addr, E_LOGIC _arg_uart_r_nf_isr)
{
	Set_base(_arg_uart_r_addr);
	
	Set_isr(_arg_uart_r_nf_isr);
	
	C_TIMER_inside::Set(80);
	
	_mem_uart_r_flag = EU_NONE;
}

//public
inline C_UART_R::C_UART_R(E_UART_ADDR _arg_uart_r_addr, E_LOGIC _arg_uart_r_nf_isr = FALES)
{	
	Set(_arg_uart_r_addr,_arg_uart_r_nf_isr);
}

inline void C_UART_R::Set_isr(E_LOGIC _arg_uart_r_nf_isr)
{
	switch (_arg_uart_r_nf_isr)
	{
		case TRUE:	UCSRB |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB &= ~(1 << RXCIE);	break; //Off
	}
}

void C_UART_R::Check()
{	
	UCSRB |= (1 << RXEN); //受信許可
	
	C_TIMER_inside::Start();
	
	while (1)
	{
		if ((C_TIMER_inside::Ret_flag() & CHECK_BIT_TF(UCSRA,RXC)) == TRUE)	//受信完了
		{
			C_TIMER_inside::End();
			
			_mem_uart_r_flag = EU_SUCCE;
			break;
		}
		
		if (C_TIMER_inside::Check() == TRUE)	//カウント完了(タイムアウト)
		{
			_mem_uart_r_flag = EU_ERROR;
			break;
		}
	}
}

T_DATA C_UART_R::In()
{
	Check(); //受信チェック
	
	if (_mem_uart_r_flag == EU_ERROR)	return IN_ERROR;	//受信失敗
	
	T_DATA _ret_in_data = 0;
		
	if (UCSRB & ((1<<UCSZ2) | (1<<RXB8)))	_ret_in_data = (1 << 8);	//9bit通信時
	
	_ret_in_data |= UDR;
	
	_mem_uart_r_flag = EU_NONE;
	
	return _ret_in_data;
}

void operator >> (C_UART_R &_arg_uart_r,T_DATA &_arg_uart_r_data_in)
{
	_arg_uart_r_data_in = _arg_uart_r.In();
}

void operator >> (C_UART_R &_arg_uart_r,T_DATA_8 &_arg_uart_r_data_in)
{
	_arg_uart_r_data_in = (T_DATA_8 )_arg_uart_r.In();
}

bool operator == (C_UART_R &_arg_uart_r,E_UART_FLAG _arg_uart_r_flag)
{	
	if (_arg_uart_r._mem_uart_r_flag == _arg_uart_r_flag)	return true;
	
	return false;
}

bool operator != (C_UART_R &_arg_uart_r,E_UART_FLAG _arg_uart_r_flag)
{
	if (_arg_uart_r._mem_uart_r_flag != _arg_uart_r_flag)	return true;
	
	return false;
}

#endif