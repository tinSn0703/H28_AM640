
/*
AD変換を行うクラス。ポテンジョンメータの値を読むことができる。
 H28 05 10 ver0.0.0
 H28 05 21 ver0.0.1   IOポートの設定を前の逆にした
 H28 05 21 ver0.0.2   メンバ変数の名前の変更
 H28 05 21 ver1.0.0   ADMUXのリセットがうまくいっておらず、複数個用いる場合のAD変換の値が共有されてしまうバグを解消した。
					あと割り込み処理を設定できないようにした。
 H28 05 22 ver2.0.0   メンバ変数をカプセル化した。
*/

#ifndef _H28_I_C_AD_CPP_
#define _H28_I_C_AD_CPP_ 1

class C_AD
{	
	private:
	union U_AD_MUX
	{
		struct S_AD_MUX
		{
			E_LOGIC mux0 :1;
			E_LOGIC mux1 :1;
			E_LOGIC mux2 :1;
			E_LOGIC mux3 :1;
			E_LOGIC mux4 :1;
			E_LOGIC mux5 :1;
		};
		
		S_AD_MUX mux_bit;
		usint mux_admux :5;
		E_AD_NUM ad_num :6;
	};
	
	U_AD_MUX _mem_ad_num;
	
	protected:	
	E_LOGIC Ret_mux0()	{	return _mem_ad_num.mux_bit.mux0;	}
	E_LOGIC Ret_mux1()	{	return _mem_ad_num.mux_bit.mux1;	}
	E_LOGIC Ret_mux2()	{	return _mem_ad_num.mux_bit.mux2;	}
	E_LOGIC Ret_mux3()	{	return _mem_ad_num.mux_bit.mux3;	}
	E_LOGIC Ret_mux4()	{	return _mem_ad_num.mux_bit.mux4;	}
	E_LOGIC Ret_mux5()	{	return _mem_ad_num.mux_bit.mux5;	}
	usint Ret_admux()	{	return _mem_ad_num.mux_admux;		}
	E_AD_NUM Ret_num()	{	return _mem_ad_num.ad_num;			}
	
	void Set_num(E_AD_NUM );
	
	void Set_first();
	void Set(E_AD_NUM ,E_LOGIC );
	
	public:
	C_AD()	{}
	C_AD(E_AD_NUM ,E_LOGIC );

	usint Do();
};

//protected
inline void C_AD::Set_num(E_AD_NUM _arg_ad_num)
{
	_mem_ad_num.ad_num = _arg_ad_num;
}

inline void C_AD::Set_first()
{
	static E_LOGIC _sta_ad_first = FALES;
	
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

inline void C_AD::Set(E_AD_NUM _arg_ad_num, E_LOGIC _arg_ad_io_turn = TRUE)
{
	Set_first();
	
	Set_num(_arg_ad_num);
	
	switch (_arg_ad_io_turn)
	{
		case TRUE:
		{
			DDRF  &= ~(TURN_TF(Ret_mux5()) << Ret_admux());
			PORTF |=  (TURN_TF(Ret_mux5()) << Ret_admux());
			
			DDRK  &= ~(Ret_mux5() << Ret_admux());
			PORTK |=  (Ret_mux5() << Ret_admux());
			
			break;
		}
		case FALES:
		{
			DDRF  |=  (TURN_TF(Ret_mux5()) << Ret_admux());
			PORTF &= ~(TURN_TF(Ret_mux5()) << Ret_admux());
			
			DDRK  |=  (Ret_mux5() << Ret_admux());
			PORTK &= ~(Ret_mux5() << Ret_admux());
			
			break;
		}
	}

	DIDR0 |= (TURN_TF(Ret_mux5()) << Ret_admux());
	DIDR2 |= (Ret_mux5() << Ret_admux());
}

//public
inline C_AD::C_AD(E_AD_NUM _arg_ad_num, E_LOGIC _arg_ad_io_turn = TRUE)
{	
	Set(_arg_ad_num, _arg_ad_io_turn);
}

inline usint C_AD::Do()
{	
	ADMUX += Ret_admux();
	ADCSRB = (Ret_mux5() << MUX5);
	
	ADCSRA |= (1 << ADSC);
	
	while (ADCSRA & (1<<ADSC));
	
	usint _ret_in_data = ADCL;
	_ret_in_data |= (ADCH << 8);
	
	ADMUX  = (1<<REFS0);
	ADCSRB = 0;
	
	return _ret_in_data;
}

#endif