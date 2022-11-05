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

    while((!DS18B20_IO) && time_temp < 20){
        time_temp ++;
        public_us_delay(1);
    }
    if (time_temp >= 20) return 1;
    return 0;
}

//读位函数
uchar ds18b20_read_bit(){

    uchar dat = 0;
    DS18B20_IO = 0;
    _nop_(); _nop_();  //2 us
    DS18B20_IO = 1;
    if (DS18B20_IO) dat = 1;
    else dat = 0;
    public_us_delay(5);
    return dat;
}

//读字节数据
uchar ds18b20_read_byte(){
    uchar i;
    uchar temp = 0;
    uchar dat  = 0;
    for (i = 0; i < 8; i++){
        temp = ds18b20_read_bit();
        dat = (temp << 7) | (dat >> 1);
    }
    return dat;
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
            public_us_delay(6);
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


//温度转化函数
void ds18b20_start(){

    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0x44);
}

//初始化时序
uchar ds18b20_init(){
    ds18b20_reset();
    return ds18b20_check();
}

//返回温度
float ds18b20_read_temperture(){

    float temp;
    uchar dath = 0;
    uchar datl = 0;
    uint value = 0;

    ds18b20_start();
    ds18b20_reset();
    ds18b20_check();
    ds18b20_write_byte(0xcc);
    ds18b20_write_byte(0xbe);

    datl = ds18b20_read_byte();
    dath = ds18b20_read_byte();
    value = (dath << 8) + datl;

    //判断温度是-还是+
    if ((value & 0xf800) == 0xf800){

        value = (~value) + 1;
        temp = value * (-0.0625);
    }
    else {
        temp = value * 0.0625;
    }

    return temp;
}