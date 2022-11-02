# include "ds18b20.h"

//复位
void ds18b20_reset(){
    DS18B20_IO = 0;
    public_us_delay(75);
    DS18B20_IO = 1;
    public_us_delay(2);
}

//检测DS18B20 是否存在
uchar ds18b20_check(){

    uchar time_temp = 0;
    while(DS18B20_IO && time_temp < 20){
        time_temp ++;
        public_us_delay(1);
    }
    if (time_temp >= 20) return 1;
    else time_temp = 0;
    //0 检测到ds18b20 响应， 1 为响应超时和非响应

    while(!DS18B20_IO && time_temp < 20){
        time_temp ++;
        public_us_delay(1);
    }
    if (time_temp >= 20) return 1;
    return 0;
}

//初始化时序
uchar ds18b20_init(){
    ds18b20_reset();
    return ds18b20_check();
}

//写函数
void ds18b20_write_byte(uchar dat){
    uchar i;
    uchar temp = 0;
    for (i = 0; i < 8; i++){
        temp = dat & 0x01;
        dat >>= 1;
        if (temp) {
            DS18B20_IO = 0;
            //一个_nop_() 函数代表一个um (微秒)
            _nop_();
            _nop_();
            DS18B20_IO = 1;
            public_um_delay(6);
        }
        else {
            DS18B20_IO = 0;
            public_us_delay(6);
            DS18B20_IO = 1;
            _nop_();
            _nop_();
        }
    }
}

//读位函数
uchar ds18b20_read_bit(){

    uchar dat = 0;
    uchar i;
    DS18B20_IO = 0;
    _nop_(); _nop_();  //2 us
    if (DS18B20_IO) dat = 1;
    else dat = 0;
    public_um_delay(5);
    return dat;
}

//读字节数据
uchar ds18b20_read_byte(){
    uchar i;
    uchar temp = 0;
    uchar dat  = 0;
    for (i = 0; i < 8; i++){
        temp = ds18b20_read_bit();
        dat >>= 1; 
        dat |= temp<<7;
    }

    return dat;
}