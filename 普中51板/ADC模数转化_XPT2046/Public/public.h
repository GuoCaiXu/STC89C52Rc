# ifndef _public_H
# define _public_H

# include <reg52.h>
# include <intrins.h>

# define u8 unsigned char
# define u16 unsigned int

# include "xpt2046.h"
# include "smg.h"

//定时器T0 中断初始化
void T0_init();

# endif