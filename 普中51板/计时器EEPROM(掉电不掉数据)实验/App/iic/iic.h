# ifndef _iic_H
# define _iic_H

# include "public.h"

sbit iic_SCL = P2^1;  //时钟信号线
sbit iic_SDA = P2^0;  //数据信号线

//起始信号
void iic_start();

//终止信号
void iic_stop();

//应答信号
void iic_ack();

//非应答信号
void iic_nack();

//判断应答信号
uchar iic_wait_ack();

//写字节
void iic_write_byte(ulong dat);

//读字节
ulong iic_read_byte(uchar ack);

# endif