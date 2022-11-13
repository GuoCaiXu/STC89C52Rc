# include "xpt2046.h"

//写数据函数
void xpt2046_write_data(u8 dat){

    u8 i = 0;

    //DCLK 拉低
    DCLK = 0;
    _nop_();

    for (i = 0; i < 8; i ++){

        DIN = dat >> 7;
        dat <<= 1;

        //拉低
        DCLK = 0;
        _nop_();

        //上升延
        DCLK = 1;
        _nop_();
    }   
}

//读函数
u16 xpt2046_read_data(){

    u8 i = 0;
    u16 dat = 0;

    //DCLK 拉高
    DCLK = 1;
    _nop_();

    for (i = 0; i < 12; i++){

        dat <<= 1;
        //下降延
        DCLK = 0;
        _nop_();
        dat |= DOUT;
    }

    return dat;
}

//读adc数据
u16 xpt2046_read_adc_value(u8 cmd){
    u16 adc_value = 0;

    CS = 0;
    //写通道
    xpt2046_write_data(cmd);
    
    //把盲信号给清除掉
    DCLK = 0;
    _nop_();
    DCLK = 1;
    _nop_();

    //读数据
    adc_value = xpt2046_read_data();
    CS = 1;

    return adc_value;
}