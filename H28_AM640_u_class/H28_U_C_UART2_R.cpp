
/*
最初から２線通信を想定したUART系のクラス
 H28 05 16 ver0.0.0
 H28 05 18 ver0.1.0 通信を二線通信のみにした。
 H28 05 23 ver1.0.0 C_UART_baseの派生クラスにした。それにともなって色々変えた。
 H28 05 24 ver1.1.0 Set_base_addrを多用するのはやめた。マクロ追加した。
*/

#ifndef _H28_U_C_UART2_R_CPP_
#define _H28_U_C_UART2_R_CPP_ 1

class C_UART_R2 : protected C_UART_base , public C_TIMER_inside
{
	private:
	E_UART_ADDR _mem_arr_uart_r2_addr[2];	//レジスタ用のアドレス
	E_UART_FLAG _mem_uart_r2_in_flag :2;
	T_NUM _mem_uart_r2_num :1;
	
	protected:
	void Set_uart2_addr(T_NUM ,E_UART_ADDR );
	
	E_UART_ADDR Ret_uart2_addr(T_NUM _arg_uart_r2_num)	{	return _mem_arr_uart_r2_addr[_arg_uart_r2_num];	}
		
	#define UCSRA_0 _SFR_MEM8(Ret_uart2_addr(0) + 0)
	#define UCSRB_0 _SFR_MEM8(Ret_uart2_addr(0) + 1)
	#define UCSRC_0 _SFR_MEM8(Ret_uart2_addr(0) + 2)
	#define UBRRL_0 _SFR_MEM8(Ret_uart2_addr(0) + 4)
	#define UBRRH_0 _SFR_MEM8(Ret_uart2_addr(0) + 5)
	#define UDR_0   _SFR_MEM8(Ret_uart2_addr(0) + 6)
		
	#define UCSRA_1 _SFR_MEM8(Ret_uart2_addr(1) + 0)
	#define UCSRB_1 _SFR_MEM8(Ret_uart2_addr(1) + 1)
	#define UCSRC_1 _SFR_MEM8(Ret_uart2_addr(1) + 2)
	#define UBRRL_1 _SFR_MEM8(Ret_uart2_addr(1) + 4)
	#define UBRRH_1 _SFR_MEM8(Ret_uart2_addr(1) + 5)
	#define UDR_1	_SFR_MEM8(Ret_uart2_addr(1) + 6)
	
	void Set(E_UART_ADDR ,E_UART_ADDR ,E_LOGIC ,E_LOGIC );
	
	public:
	C_UART_R2()	{}
	C_UART_R2(E_UART_ADDR ,E_UART_ADDR ,E_LOGIC ,E_LOGIC );
	
	void Set_isr_0(E_LOGIC );
	void Set_isr_1(E_LOGIC );
	
	void Set_bit9_0(E_LOGIC );
	void Set_bit9_1(E_LOGIC );
	
	void Check();
	
	T_DATA In();
	
	E_UART_FLAG Ret_flag()	{	return _mem_uart_r2_in_flag;	}
};

//protected
inline void C_UART_R2::Set_uart2_addr(T_NUM _arg_uart_r2_num, E_UART_ADDR _arg_uart_r2_addr)
{
	_mem_arr_uart_r2_addr[_arg_uart_r2_num] = _arg_uart_r2_addr;
}

inline void C_UART_R2::Set(E_UART_ADDR _arg_uart_r2_addr_0, E_UART_ADDR _arg_uart_r2_addr_1, E_LOGIC _arg_uart_r2_nf_isr_0 = FALES, E_LOGIC _arg_uart_r2_nf_isr_1 = FALES)
{
	Set_uart2_addr(0,_arg_uart_r2_addr_0);
	Set_uart2_addr(1,_arg_uart_r2_addr_1);
	
	C_UART_base::Set_base(_arg_uart_r2_addr_0,EU_REC);
	C_UART_base::Set_base(_arg_uart_r2_addr_1,EU_REC);
	
	Set_isr_0(_arg_uart_r2_nf_isr_0);
	Set_isr_1(_arg_uart_r2_nf_isr_1);
	
	C_TIMER_inside::Set(80);
	
	_mem_uart_r2_in_flag = EU_NONE;
}

//public
inline C_UART_R2::C_UART_R2(E_UART_ADDR _arg_uart_r2_addr_0,E_UART_ADDR _arg_uart_r2_addr_1,E_LOGIC _arg_uart_r2_nf_isr_0 = FALES,E_LOGIC _arg_uart_r2_nf_isr_1 = FALES)
{
	Set(_arg_uart_r2_addr_0,_arg_uart_r2_addr_1,_arg_uart_r2_nf_isr_0,_arg_uart_r2_nf_isr_1);
}

inline void C_UART_R2::Set_isr_0(E_LOGIC _arg_uart_r2_nf_isr_0)
{
	switch (_arg_uart_r2_nf_isr_0)
	{
		case TRUE:	UCSRB_0 |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB_0 &= ~(1 << RXCIE);	break; //Off
	}
}

inline void C_UART_R2::Set_isr_1(E_LOGIC _arg_uart_r2_nf_isr_1)
{
	switch (_arg_uart_r2_nf_isr_1)
	{
		case TRUE:	UCSRB_1 |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB_1 &= ~(1 << RXCIE);	break; //Off
	}
}

inline void C_UART_R2::Set_bit9_0(E_LOGIC _arg_uart2_r_nf_bit9_0)
{	
	switch (_arg_uart2_r_nf_bit9_0)
	{
		case TRUE:	UCSRB_0 |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB_0 &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void C_UART_R2::Set_bit9_1(E_LOGIC _arg_uart_r2_nf_bit9_1)
{
	switch (_arg_uart_r2_nf_bit9_1)
	{
		case TRUE:	UCSRB_1 |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB_1 &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void C_UART_R2::Check()
//受信しなかった方を受信禁止にしたらうまくいった。
{
	UCSRB_0 |= (1 << RXEN);
	UCSRB_1 |= (1 << RXEN);
	
	C_TIMER_inside::Start();
	
	while (1)
	{
		if (CHECK_BIT_TF(UCSRA_0,RXC) & C_TIMER_inside::Ret_flag())	//UART0受信完了
		{
			C_TIMER_inside::End();
			
			UCSRB_1 &= ~(1 << RXEN);
			
			_mem_uart_r2_in_flag = EU_SUCCE;
			
			_mem_uart_r2_num = 0;
		
			break;
		}
		
		if (CHECK_BIT_TF(UCSRA_1,RXC) & C_TIMER_inside::Ret_flag())	//UART1受信完了
		{
			C_TIMER_inside::End();
			
			UCSRB_0 &= ~(1 << RXEN);
			
			_mem_uart_r2_in_flag = EU_SUCCE;
			
			_mem_uart_r2_num = 1;
			
			break;
		}
		
		if (C_TIMER_inside::Check())	//カウント完了(タイムアウト)
		{
			_mem_uart_r2_in_flag = EU_ERROR;
			
			break;
		}
	}
}

T_DATA C_UART_R2::In()
{
	Check();
	
	if (_mem_uart_r2_in_flag == EU_ERROR)	return IN_ERROR;
	
	T_DATA _ret_in_data = 0;
	
	C_UART_base::Set_uart_base_addr(Ret_uart2_addr(_mem_uart_r2_num));	//受信成功したポートにする
	
	if (UCSRB & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_in_data |= (1 << 8);	//9bit通信時
	}
	
	_ret_in_data |= UDR;
	
	_mem_uart_r2_in_flag = EU_NONE;
	
	return _ret_in_data;
}

#endif