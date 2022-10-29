# ifndef _smg_H
# define _smg_H

# include "public.h"

sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;


//计算数码管显示的有效位
void smg_Calculate(uchar num);

//显示数码管函数
void ShowLed();

# endif