
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
			E_LOGIC _mux0 :1;
			E_LOGIC _mux1 :1;
			E_LOGIC _mux2 :1;
			E_LOGIC _mux3 :1;
			E_LOGIC _mux4 :1;
#ifdef _AVR_IOM640_H_
			E_LOGIC _mux5 :1;
#endif
		};
		
		S_AD_MUX _mux_bit;		
#if defined(_AVR_IOM640_H_)
		usint _mux_admux :5;
		E_AD_NUM _ad_num :6;
#elif defined(_AVR_IOM164_H_)
		E_AD_NUM _mux_admux :5;
#endif
	};
	
	U_AD_MUX _mem_ad;
	
	void Set_num(E_AD_NUM );
	
	void Set_first();
	void Set(E_AD_NUM ,E_LOGIC );
	
	public:
	C_AD()	{}
	C_AD(E_AD_NUM ,E_LOGIC );

	usint Do();
};

//protected
inline void 
C_AD::
Set_num (E_AD_NUM _arg_ad_num)
{
#if defined(_AVR_IOM640_H_)
	_mem_ad._ad_num = _arg_ad_num;
#elif defined(_AVR_IOM164_H_)
	_mem_ad._mux_admux = _arg_ad_num;
#endif
}

inline void 
C_AD::
Set_first ()
{
	static E_LOGIC _sta_ad_first = FALES;
	
	if (_sta_ad_first == FALES)
	{
		ADMUX  = (1<<REFS0);
		ADCSRA = ((1 << ADEN) | (1 << ADPS1) | (1 << ADPS0));
		ADCSRB = 0;
		DIDR0  = 0;
#ifdef _AVR_IOM640_H_
		DIDR2  = 0;
#endif
		
		_sta_ad_first = TRUE;
	}
}

inline void 
C_AD::
Set
(
	E_AD_NUM _arg_ad_num, 
	E_LOGIC _arg_ad_io_turn = TRUE
)
{
	Set_first();
	
	Set_num(_arg_ad_num);
	
#if defined(_AVR_IOM640_H_)
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
#elif defined(_AVR_IOM164_H_)
	switch (_arg_ad_io_turn)
	{
		case TRUE:
		{
			DDRA  &= ~(1 << _mem_ad._mux_admux);
			PORTA |=  (1 << _mem_ad._mux_admux);
			
			break;
		}
		case FALES:
		{
			DDRA  |=  (1 << _mem_ad._mux_admux);
			PORTA &= ~(1 << _mem_ad._mux_admux);
			
			break;
		}
	}

	DIDR0 |= (1 << _mem_ad._mux_admux);
#endif
}

//public
inline 
C_AD::
C_AD
(
	E_AD_NUM _arg_ad_num, 
	E_LOGIC _arg_ad_io_turn = TRUE
)
{	
	Set(_arg_ad_num, _arg_ad_io_turn);
}

inline usint 
C_AD::
Do ()
{	
	ADMUX += _mem_ad._mux_admux;
#ifdef _AVR_IOM640_H_
	ADCSRB = (_mem_ad._mux_bit._mux5 << MUX5);
#endif	
	
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1<<ADSC));
	
	usint _ret_data_in = ADCL;
	_ret_data_in |= (ADCH << 8);
	
	ADMUX  = (1<<REFS0);
	ADCSRB = 0;
	
	return _ret_data_in;
}