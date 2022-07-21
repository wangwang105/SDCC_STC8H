/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include "UART.h"

#ifdef UART1
COMx_Define COM1;
u8 __xdata TX1_Buffer[COM_TX1_Lenth]; //发送缓冲
u8 __xdata RX1_Buffer[COM_RX1_Lenth]; //接收缓冲
#endif

/*********************************************************/

/********************* UART1 函数 ************************/
#ifdef UART1
void TX1_write2buff(u8 dat) //写入发送缓冲，指针+1
{
	TX1_Buffer[COM1.TX_write] = dat; //装发送缓冲
	if (++COM1.TX_write >= COM_TX1_Lenth)
		COM1.TX_write = 0;

	if (COM1.B_TX_busy == 0) //空闲
	{
		COM1.B_TX_busy = 1; //标志忙
		TI = 1;				//触发发送中断
	}
}

void PrintString1(u8 *puts)
{
	for (; *puts != 0; puts++)
		TX1_write2buff(*puts); //遇到停止符0结束
}

void UART1_int(void) __interrupt(UART1_VECTOR)
{
	if (RI)
	{
		RI = 0;
		if (COM1.B_RX_OK == 0)
		{
			if (COM1.RX_Cnt >= COM_RX1_Lenth)
				COM1.RX_Cnt = 0;
			RX1_Buffer[COM1.RX_Cnt++] = SBUF;
			COM1.RX_TimeOut = TimeOutSet1;
		}
	}

	if (TI)
	{
		TI = 0;
		if (COM1.TX_read != COM1.TX_write)
		{
			SBUF = TX1_Buffer[COM1.TX_read];
			
			if (++COM1.TX_read >= COM_TX1_Lenth)
				COM1.TX_read = 0;
		}
		else
			COM1.B_TX_busy = 0;
	}
}
#endif

/**
 * @Author: 王荣文
 * @description: printf重定向
 * @param {char} c
 * @return {*}
 */
// int putchar(int c)
// {
//     TX1_write2buff((i8)c);
//     return c;
// }
int putchar(int c)
{
    TX1_write2buff(c);
    return c;

    //可以输出
    // ES=0;
    // SBUF = c;
    // while(TI==0);
    // TI=0;
    // ES=1;
    // return 0;
}