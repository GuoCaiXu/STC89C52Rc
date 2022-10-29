# include "at24c02.h"

//写字节
void at24c02_write_one_byte(uchar addr, ulong dat){
    iic_start();
    iic_write_byte(0xA0); 
    iic_wait_ack();
    //写入从机地址
    iic_write_byte(addr);
    //判断应答信号
    iic_wait_ack();
    //写入数据
    iic_write_byte(dat);
    iic_wait_ack();
    iic_stop();
}

//读字节
ulong at24c02_read_byte(ulong addr){
    ulong temp = 0;

    iic_start();
    //给主机发送发送数据信号 0
    iic_write_byte(0xA0);
    iic_wait_ack();
    //寻机地址
    iic_write_byte(addr); 
    //应答
    iic_wait_ack();
    //起始信号
    iic_start();
    //给主机发送读字节信号 1
    iic_write_byte(0xA1);
    //应答信号
    iic_wait_ack();
    temp = iic_read_byte(1);
    //停止信号
    iic_stop();

    return temp;
}