# include "lcd1602.h"

//写命令
void lcd1602_write_cmd(u8 cmd){
    //通过RS 设置写命令功能 0
    lcd1602_RS = 0;

    //写功能
    lcd1602_RW = 0;

    //开始写入命令
    lcd1602_E = 0;
    delay_ms(1);

    LCD1602_DATAPORT = cmd;

    lcd1602_E = 1;

    lcd1602_E = 0;
}

//写数据
void lcd1602_write_data(u8 dat){
    //通过RS 设置写数据功能 1
    lcd1602_RS = 1;

    //写功能
    lcd1602_RW = 0;

    //开始写入数据
    lcd1602_E = 0;
    delay_ms(1);

    LCD1602_DATAPORT = dat;

    lcd1602_E = 1;

    lcd1602_E = 0;
}

//显示初始化
void lcd1602_init(){
    //先写命令
    //功能指示命令
    lcd1602_write_cmd(0x38);

    //显示开关控制指令
    lcd1602_write_cmd(0x0c);

    //模式设置指令
    lcd1602_write_cmd(0x06);

    //清屏指令
    lcd1602_write_cmd(0x01);
}

//显示字符
void lcd1602_show_string(u8 x, u8 y, u8 *str){
    u8 i = 0;
    
    if (y > 1 || x > 15) return;

    if (y < 1){
        while(*str != '\0'){
            if (i < 16 - x)
            lcd1602_write_cmd(0x80 + x + i);
            else
            lcd1602_write_cmd(0x80 + 0x40 + x + i - 16);

            //写入显示内容
            lcd1602_write_data(*str);
            str ++;
            i ++;
        }
    }
    else {
        while(*str != '\0'){
            if (i < 16 - x)
            lcd1602_write_cmd(0x80 + 0x40 + x + i);
            else 
            lcd1602_write_cmd(0x80 + x + i - 16);

            //写入显示内容
            lcd1602_write_data(*str);
            str ++;
            i ++;
        }
    }
}

//清空屏幕指令
void lcd1602_clear(){
    lcd1602_write_cmd(0x01);
}