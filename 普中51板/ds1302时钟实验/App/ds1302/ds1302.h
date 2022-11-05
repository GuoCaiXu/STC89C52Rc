# ifndef _ds1302_H
# define _ds1302_H

# include "public.h"

sbit ds1302_IO = P3^4;
sbit CE = P3^5;
sbit SCLK = P3^6;

//写字节函数
void ds1302_write_byte();

//读字节函数
void ds1302_read_byte();

# endif