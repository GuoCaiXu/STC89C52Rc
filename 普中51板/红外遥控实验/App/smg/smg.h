# ifndef _smg_H
# define _smg_H

# include "public.h"

//30 译码器
sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

extern u8 code LedChar[];
extern u8 LedBuff[];

//显示数码管
void smg_ShowLed();

# endif