# ifndef _lcd1602_H
# define _lcd1602_H

# include "public.h"

sbit LCD1602_E = P2^7;
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;

//数据端宏定义
# define LCD1602_DATAPORT   P0

//lcd1602初始化
void lcd1602_init();

//显示字符串
void lcd1602_show_string(u8 x, u8 y, u8 *str);

//清屏幕
void lcd1602_clear();

# endif