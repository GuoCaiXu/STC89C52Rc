# include "ds1302.h"

//写字节函数
void ds1302_write_byte(u8 addr, u8 dat){

    u8 i = 0;

    CE = 0;
    //延时 1us
    _nop_();
    SCLK = 0;
    //延时1 us
    _nop_();
    CE = 1;
    _nop_();

    //先发送地址
    for (i = 0; i < 8; i++){
        ds1302_IO = addr & 0x01;
        addr >>= 1;
        //SCLK 拉高
        SCLK = 1;
        //延时
        _nop_();
        //SCLK 拉低
        SCLK = 0;
        //延时
        _nop_();
    }

    //写入数据
    for (i = 0; i < 8; i++){
        ds1302_IO = dat & 0x01;
        dat >>= 1;
        //SCLK 拉高
        SCLK = 1;
        //延时
        _nop_();
        //SCLK 拉低
        SCLK = 0;
        //延时
        _nop_();
    }

    CE = 0;
}

//读字节函数
void ds1302_read_byte(){
    
}