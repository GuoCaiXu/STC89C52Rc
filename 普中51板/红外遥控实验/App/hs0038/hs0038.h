# ifndef _hs0038_H
# define _hs0038_H

# include "public.h"

sbit IRED = P3^2;

extern u8 gired[4];

//红外遥控初始化
void hs0038_ired_init();

# endif