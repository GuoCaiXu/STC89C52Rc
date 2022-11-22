# ifndef _lcd1602_H
# define _lcd1602_H

# include "public.h"

sbit lcd1602_E = P2^7;
sbit lcd1602_RS = P2^6;
sbit lcd1602_RW = P2^5;
# define LCD1602_DATAPORT   P0

//显示初始化
void lcd1602_init();

//显示字符
void lcd1602_show_string(u8 x, u8 y, u8 *str);

//清空屏幕指令
void lcd1602_clear();

# endif