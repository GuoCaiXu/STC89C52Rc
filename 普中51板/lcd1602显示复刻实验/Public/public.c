# include "public.h"

//延时函数 ms
void delay_ms(u8 z){
    u8 i;
    while(z --){
        for (i = 0; i < 120; i++);
    }
}