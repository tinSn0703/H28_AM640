
/*
最初から２線通信を想定したUART系のクラス
 H28 05 16 ver0.0.0
 H28 05 18 ver0.1.0 通信を二線通信のみにした。
 H28 05 23 ver1.0.0 C_UART_baseの派生クラスにした。それにともなって色々変えた。
 H28 05 24 ver1.1.0 Set_base_addrを多用するのはやめた。マクロ追加した。
*/

#pragma once

class C_UART_R2 : protected C_UART_base , public C_TIMER_inside
{
	protected:
	E_UART_ADDR _mem_arr_uart_r2_addr[2];	//レジスタ用のアドレス
	E_UART_FLAG _mem_uart_r2_flag :2;
	T_NUM _mem_uart_r2_num :1;
		
	#define UCSRA_0 _SFR_MEM8(_mem_arr_uart_r2_addr[0] + 0)
	#define UCSRB_0 _SFR_MEM8(_mem_arr_uart_r2_addr[0] + 1)
	#define UCSRC_0 _SFR_MEM8(_mem_arr_uart_r2_addr[0] + 2)
	#define UBRRL_0 _SFR_MEM8(_mem_arr_uart_r2_addr[0] + 4)
	#define UBRRH_0 _SFR_MEM8(_mem_arr_uart_r2_addr[0] + 5)
	#define UDR_0   _SFR_MEM8(_mem_arr_uart_r2_addr[0] + 6)
		
	#define UCSRA_1 _SFR_MEM8(_mem_arr_uart_r2_addr[1] + 0)
	#define UCSRB_1 _SFR_MEM8(_mem_arr_uart_r2_addr[1] + 1)
	#define UCSRC_1 _SFR_MEM8(_mem_arr_uart_r2_addr[1] + 2)
	#define UBRRL_1 _SFR_MEM8(_mem_arr_uart_r2_addr[1] + 4)
	#define UBRRH_1 _SFR_MEM8(_mem_arr_uart_r2_addr[1] + 5)
	#define UDR_1	_SFR_MEM8(_mem_arr_uart_r2_addr[1] + 6)
	
	void Set(E_UART_ADDR ,E_UART_ADDR ,BOOL ,BOOL );
	
	public:
	C_UART_R2()	{}
	C_UART_R2(E_UART_ADDR ,E_UART_ADDR ,BOOL ,BOOL );
	
	void Set_isr_0(BOOL );
	void Set_isr_1(BOOL );
	
	void Set_bit9_0(BOOL );
	void Set_bit9_1(BOOL );
	
	void Check();
	
	T_DATA In();
	
	E_UART_FLAG Ret_flag()	{	return _mem_uart_r2_flag;	}
		
	friend void operator >> (C_UART_R2 &,T_DATA &);
	friend void operator >> (C_UART_R2 &,T_DATA_8 &);
	
	friend bool operator == (C_UART_R2 &,E_UART_FLAG );
	friend bool operator != (C_UART_R2 &,E_UART_FLAG );
};

//protected

inline void 
C_UART_R2::
Set
(
	E_UART_ADDR _arg_uart_r2_addr_0, 
	E_UART_ADDR _arg_uart_r2_addr_1, 
	BOOL _arg_uart_r2_nf_isr_0 = FALES, 
	BOOL _arg_uart_r2_nf_isr_1 = FALES
)
{
	_mem_arr_uart_r2_addr[0] = _arg_uart_r2_addr_0;
	_mem_arr_uart_r2_addr[1] = _arg_uart_r2_addr_1;
	
	C_UART_base::Set_base(_arg_uart_r2_addr_0);
	C_UART_base::Set_base(_arg_uart_r2_addr_1);
	
	Set_isr_0(_arg_uart_r2_nf_isr_0);
	Set_isr_1(_arg_uart_r2_nf_isr_1);
	
	C_TIMER_inside::Set(80);
	
	_mem_uart_r2_flag = EU_NONE;
}

//public
inline 
C_UART_R2::
C_UART_R2
(
	E_UART_ADDR _arg_uart_r2_addr_0,
	E_UART_ADDR _arg_uart_r2_addr_1,
	BOOL _arg_uart_r2_nf_isr_0 = FALES,
	BOOL _arg_uart_r2_nf_isr_1 = FALES
)
{
	Set(_arg_uart_r2_addr_0,_arg_uart_r2_addr_1,_arg_uart_r2_nf_isr_0,_arg_uart_r2_nf_isr_1);
}

inline void 
C_UART_R2::
Set_isr_0 (BOOL _arg_uart_r2_nf_isr_0)
{
	switch (_arg_uart_r2_nf_isr_0)
	{
		case TRUE:	UCSRB_0 |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB_0 &= ~(1 << RXCIE);	break; //Off
	}
}

inline void 
C_UART_R2::
Set_isr_1 (BOOL _arg_uart_r2_nf_isr_1)
{
	switch (_arg_uart_r2_nf_isr_1)
	{
		case TRUE:	UCSRB_1 |=  (1 << RXCIE);	break; //On
		case FALES:	UCSRB_1 &= ~(1 << RXCIE);	break; //Off
	}
}

inline void 
C_UART_R2::
Set_bit9_0 (BOOL _arg_uart2_r_nf_bit9_0)
{	
	switch (_arg_uart2_r_nf_bit9_0)
	{
		case TRUE:	UCSRB_0 |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB_0 &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void 
C_UART_R2::
Set_bit9_1 (BOOL _arg_uart_r2_nf_bit9_1)
{
	switch (_arg_uart_r2_nf_bit9_1)
	{
		case TRUE:	UCSRB_1 |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB_1 &= ~(1 << UCSZ2);	break; //Off
	}
}

inline void 
C_UART_R2::
Check ()
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
			
			_mem_uart_r2_flag = EU_SUCCE;
			
			_mem_uart_r2_num = 0;
		
			break;
		}
		
		if (CHECK_BIT_TF(UCSRA_1,RXC) & C_TIMER_inside::Ret_flag())	//UART1受信完了
		{
			C_TIMER_inside::End();
			
			UCSRB_0 &= ~(1 << RXEN);
			
			_mem_uart_r2_flag = EU_SUCCE;
			
			_mem_uart_r2_num = 1;
			
			break;
		}
		
		if (C_TIMER_inside::Check())	//カウント完了(タイムアウト)
		{
			_mem_uart_r2_flag = EU_ERROR;
			
			break;
		}
	}
}

T_DATA 
C_UART_R2::
In ()
{
	Check();
	
	if (_mem_uart_r2_flag == EU_ERROR)	return IN_ERROR;
	
	T_DATA _ret_in_data = 0;
	
	_mem_uart_base_addr = _mem_arr_uart_r2_addr[_mem_uart_r2_num];	//受信成功したポートにする
	
	if (UCSRB & ((1<<UCSZ2) | (1<<RXB8)))
	{
		_ret_in_data |= (1 << 8);	//9bit通信時
	}
	
	_ret_in_data |= UDR;
	
	_mem_uart_r2_flag = EU_NONE;
	
	return _ret_in_data;
}

void 
operator >> 
(
	C_UART_R2 &_arg_uart_r2,
	T_DATA &_arg_uart_r2_data_in
)
{
	_arg_uart_r2_data_in = _arg_uart_r2.In();
}

void 
operator >> 
(
	C_UART_R2 &_arg_uart_r2,
	T_DATA_8 &_arg_uart_r2_data_in
)
{
	_arg_uart_r2_data_in = (T_DATA_8)_arg_uart_r2.In();
}

bool 
operator == 
(
	C_UART_R2 &_arg_uart_r2,
	E_UART_FLAG _arg_uart_r2_flag
)
{
	if (_arg_uart_r2._mem_uart_r2_flag == _arg_uart_r2_flag)	return true;
	
	return false;
}

bool 
operator != 
(
	C_UART_R2 &_arg_uart_r2,
	E_UART_FLAG _arg_uart_r2_flag
)
{
	if (_arg_uart_r2._mem_uart_r2_flag != _arg_uart_r2_flag)	return true;
	
	return false;
}