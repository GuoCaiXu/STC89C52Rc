 # ifndef _key_H
# define _key_H

# include "public.h"

//独立按键
sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;
sbit KEY4 = P3^3;

//判断按键是否按下函数
uchar JudKey();

//消抖按键函数
void ShakeKey();

# endif