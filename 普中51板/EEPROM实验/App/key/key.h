# ifndef _key_H
# define _key_H

# include "public.h"

//独立按键
sbit Key1 = P3^1;
sbit Key2 = P3^0;
sbit Key3 = P3^2;
sbit Key4 = P3^3;

static uchar KeySta = 1;
static uchar KeyBac = 1;

//判断按键是否按下函数
void JudKey();

# endif