# include "at24c02.h"

//写字节
void at24c02_write_byte(uchar addr, ulong dat){

    //起始信号
    iic_start();
    //设置位发送数据
    iic_write_byte(0xa0);
    //应答信号
    iic_wait_ack();
    //写入从机地址
    iic_write_byte(addr);
    //应答信号
    iic_wait_ack();
    //发送数据
    iic_write_byte(dat);
    //判断应答信号
    iic_wait_ack();
    //停止信号
    iic_stop();
}

//读字节
ulong at24c02_read_byte(uchar addr){

    ulong temp = 0;
    //起始信号
    iic_start();
    //设置发送数据
    iic_write_byte(0xa0);
    //应答信号
    iic_wait_ack();
    //写入从机地址
    iic_write_byte(addr);
    //应答信号
    iic_wait_ack();
    //起始信号
    iic_start();
    //设置接收数据
    iic_write_byte(0xa1);
    //应答信号
    iic_wait_ack();
    temp = iic_read_byte(1);
    iic_stop();

    return temp;
}