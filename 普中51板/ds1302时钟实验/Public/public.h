# ifndef _public_H
# define _public_H

# include <reg52.h>
# include "intrins.h"  //_nop_() 等于 1us
# define u8 unsigned char
# define u16 unsigned int

//延时函数 us
void delay_us(u8 z);

//延时函数 ms
void delay_ms(u8 z);

//中断函数初始化
void T0_init();

# endif