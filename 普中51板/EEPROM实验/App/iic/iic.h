# ifndef _iic_H
# define _iic_H

# include "public.h"

sbit iic_SDA = P2^0;  //SDA数据线
sbit iic_SCL = P2^1;  //SCL时钟线

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
void iic_write_byte(ulong dat);

//读数据
ulong iic_read_byte(ulong ack);

# endif