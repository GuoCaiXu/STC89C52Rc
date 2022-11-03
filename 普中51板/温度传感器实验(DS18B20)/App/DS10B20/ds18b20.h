# ifndef _ds18b20_H
# define _ds18b20_H

# include "public.h"
# include "intrins.h"  //_nop_() 函数的头文件

sbit DS18B20_IO = P3^7;

//复位
void ds18b20_reset();

//检测DS18B20 是否存在
uchar ds18b20_check();

//初始化时序
uchar ds18b20_init();

//写字节函数
void ds18b20_write_byte(uchar dat);

//读字节函数
uchar ds18b20_read_bit();

//读字节数据
uchar ds18b20_read_byte();

//温度转化函数
void ds18b20_start();

//返回温度
float ds18b20_read_temperture();


# endif