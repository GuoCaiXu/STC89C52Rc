# ifndef _key_H
# define _key_H

# include "public.h"

//按键引脚
sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

//判断按键是否按下
uchar key_JudKey();

//按键消抖
void key_Vanish();

# endif