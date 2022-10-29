# include "iic.h"

//iic的起始信号
void iic_start(){

    iic_SDA = 1;
    iic_SCL = 1;
    delay(1);
    iic_SDA = 0;
    delay(1);
    iic_SCL = 0;
}

//iic的停止信号
void iic_stop(){

    iic_SDA = 0;
    iic_SCL = 1;
    delay(1);
    iic_SDA = 1;
    delay(1);
}

//应答信号
void iic_ack(){
    iic_SCL = 0;
    iic_SDA = 0;
    delay(1);
    iic_SCL = 1;
    delay(1);
    iic_SCL = 0;
    delay(1);
}

//非应答信号
void iic_nock(){
     iic_SCL = 0;
     iic_SDA = 1;
     delay(1);
     iic_SCL = 1;
     delay(1);
     iic_SCL = 0;
}

//判断应答信号
uchar iic_wait_ack(){

    uchar time_temp = 0;
    iic_SCL = 1;
    delay(1);
    while(iic_SDA){
        time_temp++;
        if (time_temp > 100){
            iic_stop();
            return 1;
        }
    }
    iic_SCL = 0;
    return 0;
    //0 是应答， 1非应答
}

//写入数据
void iic_write_byte(ulong dat){
    uchar i = 0;

    iic_SCL = 0;
    for (i = 0; i < 8; i++){
        if ((dat & 0x80) > 0){
            iic_SDA = 1;
        }
        else {
            iic_SDA = 0;
        }
        dat <<= 1;
        iic_SCL = 1;
        delay(1);
        iic_SCL = 0;
        delay(1);
    }
}

//读数据
ulong iic_read_byte(ulong ack){

    uchar i = 0;
    ulong receive = 0;
    for (i = 0; i < 8; i++){
        iic_SCL = 0;
        delay(1);
        iic_SCL = 1;
        delay(1);
        receive <<= 1;
        if (iic_SDA){
            receive++; 
        }
    }
if (ack) iic_nock();
else iic_ack(); 

    return receive;
}