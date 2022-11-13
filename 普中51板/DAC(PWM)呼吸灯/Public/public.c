# include "public.h"

//1ms 延迟函数
void delay_ms(u8 z){

    u8 i = 0;
    while(z --){
        for (i = 0; i <= 120; i++);
    }
}