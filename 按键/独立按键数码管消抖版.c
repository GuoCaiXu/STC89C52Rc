# include <reg52.h>
# define uint unsigned int
# define uchar unsigned char

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

//k4按键
sbit KEY4 = P2^7;

//数字显示数组
uchar code LedChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
};

uchar Keystc = 1;

void main(){

bit backup = 1;
ulong cnt = 0;
	
  //打开数码管0
	ADDR0 = 0;
	ADDR1 = 0;
	ADDR2 = 0;
	ADDR3 = 1;
	ENLED = 0;
	
  //打开总中断使能开关
	EA = 1;
  //工作模式1
	TMOD = 0x01;
	
  //F8CD表示0.002s， 也就是2毫秒
	TH0 = 0xf8;
	TL0 = 0xcd;
	
  //打开定时器T0 中断开关
	ET0 = 1;
//打开定时器T0 开关
	TR0 = 1;
  
  //给KEYout4
  P2 = 0xf7;
  //如果一直没按下按键就一直显示数字0
	P0 = LedChar[cnt];

  while(1){

    //一开始backup 是弹起状态 keystc一开始也是弹起状态
    if (Keystc != backup){

      //判断backup 是否是按下状态
        if (backup == 0){

          cnt++;

          if (cnt >= 10){
            cnt = 0; 
          }
          P0 = LedChar[cnt];
        }
      backup = Keystc;
    }
  }
}

void InteruptTime0() interrupt 1{

//一开始判断KeyBuf 是弹起状态
  static uint KeyBuf = 0xff;

//0.002s中断一次
	TH0 = 0xf8;
	TL0 = 0xcd;

//判断KeyBuf是否进入按下状态， 0.002s进行一次判断， 
  KeyBuf = (KeyBuf << 1) | KEY4;

  //如果都是按下状态0就判断是按下状态
  if (KeyBuf == 0x00){

    Keystc = 0;
  }
  //如果是弹起状态都是1就判断是弹起状态
  else if (KeyBuf == 0xff){

    Keystc = 1;
  }
  else{

  }
}