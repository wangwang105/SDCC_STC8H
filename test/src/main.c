#include "config.h"

void Delaynms(u32 ms);
void Delay1ms(); //软件延时
void ClockConfig();

void main(void)
{
    //	float temp[10] = 0.0f;
    //	u8 i;
    P0M1 =0;
    P0M0 =0;
    ClockConfig();
    // UART1Config();
    EA = 1; //打开总中断
    while (1)
    {
        P02 = 1;
        Delaynms(1);
        P02 = 0;
        Delaynms(1);
        /* code */
    }
}

/**
 * @Author: 王荣文
 * @description: 时钟设置（内部IRC，外部晶振，内部RTC）
 * @return {*}
 */
void ClockConfig(void)
{
    P_SW2 = 0x80; //特殊功能寄存器为扩展SFR，逻辑地址位于XDATA区域，访问前需要将P_SW2（BAH）寄存器的最高位（EAXFR）置1
    CKSEL = 0x00; //选择内部高精度IRC ( 默认 )
    P_SW2 = 0x00;

    // P_SW2 = 0x80;
    // XOSCCR = 0xc0; //启动外部晶振
    // NOP3();
    // while (!(XOSCCR & 1))
    // 	;		   //等待时钟稳定
    // CLKDIV = 0x00; //时钟不分频
    // CKSEL = 0x01;  //选择外部晶振
    // P_SW2 = 0x00;

    //	P_SW2 = 0x80;
    //	IRC32KCR = 0x80;                            //启动内部32K IRC（误差较大）
    //	while (!(IRC32KCR & 1));                    //等待时钟稳定
    //	CKDIV = 0x00;                               //时钟不分频
    //	CKSEL = 0x03;                               //选择内部32K
    //	P_SW2 = 0x00;
}

/**
 * @Author: 王荣文
 * @description: nms的软件延时
 * @param {u32} ms
 * @return {*}
 */
void Delaynms(u32 ms)
{
    while (ms)
    {
        ms--;
        Delay1ms();
    }
}
/**
 * @Author: 王荣文
 * @description: 1ms软件延时
 * @return {*}
 */
void Delay1ms() //@24.000MHz
{
    unsigned char i, j;

    _nop_();
    i = 32;
    j = 40;
    do
    {
        while (--j)
            ;
    } while (--i);
}
