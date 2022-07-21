#include "config.h"


void ClockConfig(void);
void UART1Config(void);


void main(void)
{
    // P0M1 = 0;
    // P0M0 = 0;
    // P1M1 = 0;
    // P1M0 = 0;
    // P2M1 = 0;
    // P2M0 = 0;
    // P3M1 = 0;
    // P3M0 = 0;
    // P4M1 = 0;
    // P4M0 = 0;
    // P5M1 = 0;
    // P5M0 = 0;
    P0n_push_pull(Pin2);

    ClockConfig();
    UART1Config();

    EA = 1; //打开总中断

    while (1)
    {
        P02 = 1;
        Delaynms(100);
        P02 = 0;
        Delaynms(100);
        printf_small("hello world\r\n");
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
 * @description: 串口1设置（使用定时器2）// use timer 2
 * @return {*}
 */
void UART1Config(void) // 24MHz 9600 Baud rate
{
    // UART1_Priority(3);
    SCON = 0x50;  // 8位数据,可变波特率
    AUXR |= 0x01; //串口1选择定时器2为波特率发生器
    AUXR |= 0x04; //定时器时钟1T模式
    T2L = 0x8F;   //设置定时初始值
    T2H = 0xFD;   //设置定时初始值
    AUXR |= 0x10; //定时器2开始计时

    // TI = 1; //使用printf函数时，在初始化里TI置1.

    ES = 1; //使能串口中断
    EA = 1;
    return;
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

    NOP1();
    i = 32;
    j = 40;
    do
    {
        while (--j)
            ;
    } while (--i);
}
