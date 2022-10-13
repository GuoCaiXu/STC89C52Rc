#include <reg52.h>
# define uint unsigned int
# define uchar unsigned char

//普中蜂鸣器需要一定的频率， 一直高频和低频切换

sbit BEEP = P2^5;  //定义P2^5 管脚的名字为BEEP

//延迟函数
void delay(uint z){
    while(z--);
}

void main()
{	
    uint i = 2000;
	
	while(1)
	{

        //第一种方法：
        //BEEP = !BEEP;  或 BEEP = 0; BEEP = 1;
        
        //第二种方法
        while(i--){
            BEEP = !BEEP;
            //也可以
            //BEEP = 0; BEEP = 1;
            delay(100);
        }
	}		
}

//两种方式三种不同声音