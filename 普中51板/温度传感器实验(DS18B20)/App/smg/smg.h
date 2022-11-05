# ifndef _smg_H
# define _smg_H

# include "public.h"

//38译码器引脚
sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

//显示数码管
void smg_ShowLed();

//数码管显示有效位
void smg_ShowNumber(uint num, uchar pick);

# endif