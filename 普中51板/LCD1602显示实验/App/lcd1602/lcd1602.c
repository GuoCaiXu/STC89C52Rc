# include "lcd1602.h"

//lcd1602写命令
void lcd1602_write_cmd(u8 cmd){

    //RS 为0 是写命令 如果为1 是写数据
    LCD1602_RS = 0;

    //选择写为0 选择读为1
    LCD1602_RW = 0;

    LCD1602_E = 0;

    //写入数据
    LCD1602_DATAPORT = cmd;
    //延时1ms
    delay_ms(1);

    //上升延
    LCD1602_E = 1;
    //延迟1ms
    LCD1602_E = 0;
}

//写数据
void lcd1602_write_data(u8 dat){
    //RS 为0 是写命令 如果为1 是写数据
    LCD1602_RS = 1;

    //选择写为0 选择读为1
    LCD1602_RW = 0;

    LCD1602_E = 0;

    //写入数据
    LCD1602_DATAPORT = dat;
    //延时1ms
    delay_ms(1);

    //上升延
    LCD1602_E = 1;
    //延迟1ms
    LCD1602_E = 0;
}

//lcd1602初始化
void lcd1602_init(){

    //功能设定指令
    lcd1602_write_cmd(0x38);
    //开关控制 开启
    lcd1602_write_cmd(0x0c);
    //模式设置指令 光标向右移动
    lcd1602_write_cmd(0x06);
    //清屏指令
    lcd1602_write_cmd(0x01);
}

//显示字符串
void lcd1602_show_string(u8 x, u8 y, u8 *str){

    u8 i = 0;

    if (y > 1 || x > 15) return;

    if (y < 1){ //第1 行
        while (*str != '\0'){
            if (i < 16 - x) 
                lcd1602_write_cmd(0x80 + x + i); //第1 行
            else 
                lcd1602_write_cmd(0x80 + 0x40 + x + i - 16); //第2 行
                //写入显示内容
            lcd1602_write_data(*str);
            str++;
            i++;
        }
    }
    else { //第2 行开始

    while(*str != '\0'){
        if (i < 16 - x)
            lcd1602_write_cmd(0x80 + 0x40 + x + i);
        else 
            lcd1602_write_cmd(0x80 + x + i - 16);
            lcd1602_write_data(*str);
        str++;
        i++;
         }
    }
}

//清屏幕
void lcd1602_clear(){
    lcd1602_write_cmd(0x01);
}