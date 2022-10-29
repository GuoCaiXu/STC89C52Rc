# ifndef _smg_H
# define _smg_H

# include "public.h"

//38译码器引脚
sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

//显示数码管
void smg_ShowLed();

//计算数码管的显示内容和显示有效位
void smg_CopLed(ulong num);

# endif