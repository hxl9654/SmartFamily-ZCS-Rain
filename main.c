#include<stc15.h>
#include<init.h>
#include<uart.h>
#include<string.h>
bit WaterFlag;
void Delay100ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void UART_Action(unsigned char *dat, unsigned char len)
{	
//UART_SendString(dat, len);
	if(len <= 1)
		return;

	if(len >= 5 && strncmp(dat, "W:Inf", 5) == 0)
	{
		UART_SendString("M:W.Inf:", 8);
		if(WaterFlag)
			UART_SendString("Y\n", 2);
		else UART_SendString("N\n", 2);
	}
	else if(len >= 2 && strncmp(dat, "W:", 2) == 0)
	{
		//UART_SendString(dat, len);
		UART_SendString("N:W.SERR\n", 9);
	}
}
void main()
{
	UART_T1_Init();
	P3M0 = 0x00; P3M1 = 0x00;
	Timer2Init();
	Interrput_Init();
	WaterFlag = ~P33;
	P34 = P33;
	WDT_CONTR = 0x37;
	while(1)
	{
		WDT_CONTR |= 0x10;
		Delay100ms();
		UART_Driver();
	}
}
void Interrupt_Timer2() interrupt 12
{
	UART_RxMonitor(1);
}
void Interrupt_X1() interrupt 2
{
	if(P33 == 0)
	{
		WaterFlag = 1;
		P34 = 0;
	}
	else
	{
		WaterFlag = 0;
		P34 = 1;
	}
}