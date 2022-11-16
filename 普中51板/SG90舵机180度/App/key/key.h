# ifndef _key_H
# define _key_H

# include "public.h"

sbit KEY1 = P3^1;
sbit KEY2 = P3^0;

//判断按键是否按下
u8 key_Judgement();

void key_pick();

# endif