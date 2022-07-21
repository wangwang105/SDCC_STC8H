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

#ifndef __UART_H
#define __UART_H

#include "config.h"

#define UART1 1

#ifdef UART1
#define COM_TX1_Lenth 30
#define COM_RX1_Lenth 30
#endif

#define UART_ShiftRight 0		//同步移位输出
#define UART_8bit_BRTx (1 << 6) // 8位数据,可变波特率
#define UART_9bit (2 << 6)		// 9位数据,固定波特率
#define UART_9bit_BRTx (3 << 6) // 9位数据,可变波特率

#define UART1_SW_P30_P31 0
#define UART1_SW_P36_P37 (1 << 6)
#define UART1_SW_P16_P17 (2 << 6)
#define UART1_SW_P43_P44 (3 << 6)
#define UART2_SW_P10_P11 0
#define UART2_SW_P46_P47 1
#define UART3_SW_P00_P01 0
#define UART3_SW_P50_P51 2
#define UART4_SW_P02_P03 0
#define UART4_SW_P52_P53 4

#define TimeOutSet1 5
#define TimeOutSet2 5
#define TimeOutSet3 5
#define TimeOutSet4 5

#define BRT_Timer1 1
#define BRT_Timer2 2
#define BRT_Timer3 3
#define BRT_Timer4 4

typedef struct
{
	u8 id; //串口号

	u8 TX_read;	  //发送读指针
	u8 TX_write;  //发送写指针
	u8 B_TX_busy; //忙标志

	u8 RX_Cnt;	   //接收字节计数
	u8 RX_TimeOut; //接收超时
	u8 B_RX_OK;	   //接收块完成
} COMx_Define;

extern COMx_Define COM1;
extern u8 __xdata TX1_Buffer[COM_TX1_Lenth]; //发送缓冲
extern u8 __xdata RX1_Buffer[COM_RX1_Lenth]; //接收缓冲

// In sdcc，interrupt function is needed a declaration
void UART1_int(void) __interrupt(UART1_VECTOR);
void TX1_write2buff(u8 dat); //写入发送缓冲，指针+1
void PrintString1(u8 *puts);

#endif
