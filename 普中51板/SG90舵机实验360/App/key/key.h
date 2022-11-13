# ifndef _key_H
# define _key_H

# include "public.h"

sbit KEY1 = P3^1;
sbit KEY2 = P3^0;
sbit KEY3 = P3^2;

extern u8 sta[3];
extern u8 bac[3];

//判断函数是否按下
void key_Judgement();

//按键功能
void key_fun(u8 key);

# endif