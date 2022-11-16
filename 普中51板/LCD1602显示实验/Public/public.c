# include "public.h"

//延时函数 ms
void delay_ms(u16 z){
    u16 i;
    while(z --){
        for (i = 110; i > 0; i --);
    }
}