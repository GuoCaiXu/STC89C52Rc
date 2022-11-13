# include "ds1302.h"

//秒寄存器
u8 ds1302_write_CK[] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};
u8 ds1302_read_CK[] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};

u8 ds1302_Time[7] = {0x00, 0x37, 0x13, 0x06, 0x11, 0x07, 0x22}; //秒 分 时 日 月 星期 年

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
u8 ds1302_read_byte(u8 addr){
    u8 i = 0;
    u8 value = 0;
    u8 temp = 0;
    
    //CE 拉高
    CE = 0;
    //延时
    _nop_();

    //SCLK 拉高
    SCLK = 0;

    //延时
    _nop_();

    //CE 再拉高
    CE = 1;

    //延时
    _nop_();

    //先发送地址
    for (i = 0; i < 8; i++){

        //从低位开始读取， 一位一位开始读取
        ds1302_IO = addr & 0x01;
        addr >>= 1;
        
        //SCLK 拉高
        SCLK = 1;
        _nop_();

        //SCLK 拉低
        SCLK = 0;
        _nop_();
    }

    //读数据
    for (i = 0; i < 8; i++){

        temp = ds1302_IO;
        value = (value >> 1) | (temp << 7);

        //SCLK 拉高
        SCLK = 1;
        _nop_();

        //SCLK 拉低
        SCLK = 0;
        _nop_();
    }

    //CE 拉低
    CE = 0;
    ds1302_IO = 0;
    SCLK = 0;

    return value;
}

//ds1302 初始化
void ds1302_init(){

    u8 i = 0;

    //初始化时钟 先把写保护寄存器给关了
    ds1302_write_byte(0x8e, 0x00);

    for (i = 0; i < 7; i++){
        ds1302_write_byte(ds1302_write_CK[i], ds1302_Time[i]);
    }
    //初始化完时间再把写保护给开启
    ds1302_write_byte(0x8e, 0x8e);
}

//读时间
void ds1302_read_time(){
    u8 i = 0;

    for (i = 0; i < 7; i++){
        ds1302_Time[i] = ds1302_read_byte(ds1302_read_CK[i]);
    }
}