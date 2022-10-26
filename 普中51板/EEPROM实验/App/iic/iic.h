# ifndef _iic_H
# define _iic_H

# include "public.h"

sbit iic_SDA = P2^0;
sbit iic_SCL = P2^1;

//iic的起始信号
void iic_start();

//iic的停止信号
void iic_stop();

//应答信号
void iic_ack();

//非应答信号
void iic_nock();

//判断应答信号
uchar iic_wait_ack();

//写入数据
void iic_write_byte();

//读数据
uchar iic_read_byte(uchar ack);

# endif