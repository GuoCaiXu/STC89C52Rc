# ifndef _public_H
# define _public_H

# include <reg52.h>

# define u8 unsigned char
# define u16 unsigned int

# include "smg.h"
# include "hs0038.h"

//T0中断初始化
void T0_init();

//延迟函数 us
void delay_us(u8 z);

# endif