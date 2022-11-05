# ifndef _public_H
# define _public_H

# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int
# define ulong unsigned long

# include "smg.h"

//中断初始化函数
void public_T0_init();

//延时函数 us
void public_us_delay(uchar z);

# endif