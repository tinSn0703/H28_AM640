
/*
UART系の基底となるクラス。こいつは宣言しないでね
 H28 05 18 ver0.0.0
 H28 05 23 ver0.1.0 コンストラクタ消しといた。
*/

#ifndef _H28_U_C_UART_BASE_CPP_
#define _H28_U_C_UART_BASE_CPP_ 1

class C_UART_base
{
	private:
	E_UART_ADDR _mem_uart_base_addr :9;	//レジスタ用のアドレス
	E_UART_MODE _mem_uart_base_mode :1;	//モードの記録
	
	protected:
	
	void Set_uart_base_addr(E_UART_ADDR );
	void Set_uart_base_mode(E_UART_MODE );
	
	E_UART_ADDR Ret_uart_base_addr()		{	return _mem_uart_base_addr;	}
	E_UART_MODE Ret_uart_base_mode()	{	return _mem_uart_base_mode;	}

	#define UCSRA _SFR_MEM8(Ret_uart_base_addr() + 0)
	#define UCSRB _SFR_MEM8(Ret_uart_base_addr() + 1)
	#define UCSRC _SFR_MEM8(Ret_uart_base_addr() + 2)
	#define UBRRL _SFR_MEM8(Ret_uart_base_addr() + 4)
	#define UBRRH _SFR_MEM8(Ret_uart_base_addr() + 5)
	#define UDR	  _SFR_MEM8(Ret_uart_base_addr() + 6)
	
	/*bit UCSRA*/
	#define RXC  7
	#define TXC	 6
	#define UDRE 5
	#define FE	 4
	#define DOR  3
	#define UPE  2
	#define U2X  1
	#define MPCM 0
	
	/*bit UCSRB*/
	#define RXCIE 7
	#define TXCIE 6
	#define UDRIE 5
	#define RXEN  4
	#define TXEN  3
	#define UCSZ2 2
	#define RXB8  1
	#define TXB8  0

	/*bit UCSRC*/
	#define UMSEL1 7
	#define UMSEL0 6
	#define UPM1   5
	#define UPM0   4
	#define USBS   3
	#define UCSZ1  2
	#define UCSZ0  1
	#define UCPOL  0

	void Set_base(E_UART_ADDR ,E_UART_MODE );

	public:
	void Set_bit9(E_LOGIC );
	E_LOGIC Ret_bit9()	{	return CHECK_BIT_TF(UCSRB,UCSZ2);	}
};

//protected
inline void C_UART_base::Set_uart_base_addr(E_UART_ADDR _arg_uart_base_addr)
{
	_mem_uart_base_addr = _arg_uart_base_addr;
}

inline void C_UART_base::Set_uart_base_mode(E_UART_MODE _arg_uart_base_mode)
{
	_mem_uart_base_mode = _arg_uart_base_mode;
}

inline void C_UART_base::Set_base(E_UART_ADDR _arg_uart_base_addr, E_UART_MODE _arg_uart_base_mode)
{
	Set_uart_base_addr(_arg_uart_base_addr);
	Set_uart_base_mode(_arg_uart_base_mode);
	
	UBRRH = 0x00;
	UBRRL = 0x04;
	//F_CPU=10MHz 250kbps
	
	UCSRA = (1<<U2X);
	//Double teransmission spead
	
	UCSRB &= ~((1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE));
	//割り込み許可以外は全部OFF。おあとに設定してね
	
	UCSRC = ((1<<UPM1) | (1<<UPM0) | (1<<UCSZ1) | (1<<UCSZ0));
	//Odd parity mode_i
}

//public
inline void C_UART_base::Set_bit9(E_LOGIC _arg_uart_base_nf_bit9)
{
	switch (_arg_uart_base_nf_bit9)
	{
		case TRUE:	UCSRB |=  (1 << UCSZ2);	break; //On
		case FALES:	UCSRB &= ~(1 << UCSZ2);	break; //Off
	}
}

#endif