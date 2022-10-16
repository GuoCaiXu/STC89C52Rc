//外部中断0
# include <reg52.h>

sbit KEY3 = P3^2;
sbit OUT1 = P1^0;

void main(){

    EA = 1;  //打开总中断开关
    EX0 = 1;  //开外部中断0
    IT0 = 1; //打开外部中断
    OUT1 = 0;

    while(1){

    }
}

void init0() interrupt 0{

    if (KEY3 == 0){
        OUT1 = !OUT1;
    }
}