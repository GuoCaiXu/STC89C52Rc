# include "iic.h"

//起始信号
void iic_start(){

    iic_SDA = 1;
    iic_SCL = 1;
    delay(1);
    iic_SDA = 0;
    delay(1);
    iic_SCL = 0;
    delay(1);
}

//终止信号
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
void iic_nack(){

    iic_SCL = 0;
    iic_SDA = 1;
    delay(1);
    iic_SCL = 1;
    delay(1);
    iic_SCL = 0;
    delay(1);
}

//判断应答信号
uchar iic_wait_ack(){
    uchar ack_temp = 0;

    iic_SCL = 1;
    delay(1);
    while(iic_SDA){
        ack_temp++;

        if (ack_temp >= 100){
            iic_stop();
            return 1;
        }
    }
    iic_SCL = 0;
    return 0;
    //应答 0， 非应答 1
}

//写字节函数
void iic_write_byte(ulong dat){

    uchar i;

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

//读字节
ulong iic_read_byte(uchar ack){
    uchar i;
    ulong temp = 0;

    for (i = 0; i < 8; i++){
        iic_SCL = 0;
        delay(1);
        iic_SCL = 1;
        delay(1);
        temp <<= 1;
        if (iic_SDA){
            temp++;
        }
    }
    if (ack) iic_nack();
    else iic_ack();

    return temp;
}