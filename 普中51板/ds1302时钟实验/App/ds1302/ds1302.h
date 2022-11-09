# ifndef _ds1302_H
# define _ds1302_H

# include "public.h"

sbit ds1302_IO = P3^4;
sbit CE = P3^5;
sbit SCLK = P3^6;

//写字节函数
void ds1302_write_byte();

//读字节函数
u8 ds1302_read_byte();

//ds1302 初始化
void ds1302_init();

//读时间
void ds1302_read_time();

//返回时间
u8 ds1302_turn();


# endif