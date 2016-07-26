
/*
AD変換を行うクラス。ポテンジョンメータの値を読むことができる。
 H28 05 10 ver0.0.0
 H28 05 21 ver0.0.1   IOポートの設定を前の逆にした
 H28 05 21 ver0.0.2   メンバ変数の名前の変更
 H28 05 21 ver1.0.0   ADMUXのリセットがうまくいっておらず、複数個用いる場合のAD変換の値が共有されてしまうバグを解消した。
					あと割り込み処理を設定できないようにした。
 H28 05 22 ver2.0.0   メンバ変数をカプセル化した。
*/

#pragma once

class C_AD
{	
	protected:
	union U_AD_MUX
	{
		struct S_AD_MUX
		{
			BOOL _mux0 :1;
			BOOL _mux1 :1;
			BOOL _mux2 :1;
			BOOL _mux3 :1;
			BOOL _mux4 :1;
			BOOL _mux5 :1;
		};
		
		S_AD_MUX _mux_bit;
		usint _mux_admux :5;
		E_AD_NUM _ad_num :6;
	};
	
	U_AD_MUX _mem_ad;
	
	void Set_num(E_AD_NUM );
	
	void Set_first();
	void Set(E_AD_NUM ,BOOL );
	
	public:
	C_AD()	{}
	C_AD(E_AD_NUM ,BOOL );

	usint Do();
};

//protected
inline void 
C_AD::
Set_num (E_AD_NUM _arg_ad_num)
{
	_mem_ad._ad_num = _arg_ad_num;
}

inline void 
C_AD::
Set_first ()
{
	static BOOL _sta_ad_first = FALES;
	
	if (_sta_ad_first == FALES)
	{
		ADMUX  = (1<<REFS0);
		ADCSRA = ((1 << ADEN) | (1 << ADPS1) | (1 << ADPS0));
		ADCSRB = 0;
		DIDR0  = 0;
		DIDR2  = 0;
		
		_sta_ad_first = TRUE;
	}
}

inline void 
C_AD::
Set
(
	E_AD_NUM _arg_ad_num, 
	BOOL _arg_ad_io_turn = TRUE
)
{
	Set_first();
	
	Set_num(_arg_ad_num);
	
	switch (_arg_ad_io_turn)
	{
		case TRUE:
		{
			DDRF  &= ~(TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._mux_admux);
			PORTF |=  (TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._mux_admux);
			
			DDRK  &= ~(_mem_ad._mux_bit._mux5 << _mem_ad._mux_admux);
			PORTK |=  (_mem_ad._mux_bit._mux5 << _mem_ad._mux_admux);
			
			break;
		}
		case FALES:
		{
			DDRF  |=  (TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._mux_admux);
			PORTF &= ~(TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._mux_admux);
			
			DDRK  |=  (_mem_ad._mux_bit._mux5 << _mem_ad._mux_admux);
			PORTK &= ~(_mem_ad._mux_bit._mux5 << _mem_ad._mux_admux);
			
			break;
		}
	}

	DIDR0 |= (TURN_TF(_mem_ad._mux_bit._mux5) << _mem_ad._mux_admux);
	DIDR2 |= (_mem_ad._mux_bit._mux5 << _mem_ad._mux_admux);
}

//public
inline 
C_AD::
C_AD
(
	E_AD_NUM _arg_ad_num, 
	BOOL _arg_ad_io_turn = TRUE
)
{	
	Set(_arg_ad_num, _arg_ad_io_turn);
}

inline usint 
C_AD::
Do ()
{	
	ADMUX += _mem_ad._mux_admux;
	
	ADCSRB = (_mem_ad._mux_bit._mux5 << MUX5);
	
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1<<ADSC));
	
	usint _ret_data_in = ADCL;
	_ret_data_in |= (ADCH << 8);
	
	ADMUX  = (1<<REFS0);
	ADCSRB = 0;
	
	return _ret_data_in;
}