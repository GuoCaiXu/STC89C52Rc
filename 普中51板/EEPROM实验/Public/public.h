# ifndef _public_H
# define _public_H

# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int
# define ulong unsigned long

# include "key.h"
# include "smg.h"

//延时函数
void delay(uchar us);

//定时器0 初始化
void T0_init();

# endif