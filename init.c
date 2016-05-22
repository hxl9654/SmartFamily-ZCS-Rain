#include<stc15.h>
void Interrput_Init()
{	
	IT1 = 0;                    //设置INT1的中断类型 (1:仅下降沿 0:上升沿和下降沿)
    EX1 = 1;                    //使能INT1中断
	EA = 1;
}
void Timer2Init(void)		//1毫秒@11.0592MHz
{
	AUXR &= 0xFB;		//定时器时钟12T模式
	T2L = 0x66;		//设置定时初值
	T2H = 0xFC;		//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
	IE2 |= 0x04;
	EA = 1;
}

