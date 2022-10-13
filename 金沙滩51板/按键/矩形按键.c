# include <reg52.h>
# define uint unsigned int
# define uchar unsigned char

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;  //选择数码管DS1进行显示

//按键
sbit KeyOut4 = P2^0;
sbit KeyOut3 = P2^1;
sbit KeyOut2 = P2^2;
sbit KeyOut1 = P2^3;
sbit KeyIn1 = P2^4;
sbit KeyIn2 = P2^5;
sbit KeyIn3 = P2^6;
sbit KeyIn4 = P2^7;

uchar code LedChar[] = {  //数码管显示字符转换表
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,0x80, 0x90
};

uchar KeyStc[4][4] = {
  {1, 1, 1, 1 }, {1, 1, 1, 1},
  {1, 1, 1, 1 }, {1, 1, 1, 1}
};

void main(){
	
	uchar i, j;
	uchar KeyBac[4][4] = {
  {1, 1, 1, 1}, {1, 1, 1, 1},
  {1, 1, 1, 1}, {1, 1, 1, 1}
};

	
	EA = 1;
	TMOD = 0x01;
	
  ADDR0 = 0;
  ADDR1 = 0;
  ADDR2 = 0;
  ADDR3 = 1;
  ENLED = 0;

  TH0 = 0xfc;  //设置T0赋初值fc67 也就是0.001s 1毫秒
  TL0 = 0x67;

  ET0 = 1;  //T0使能中断开启
  TR0 = 1;  //定时器T0开启
	P0 = LedChar[0];  //数码一开始默认输出0

  while(1){
		
    for (i = 0; i < 4; i++){
      for (j = 0; j < 4; j++){

        if (KeyBac[i][j] != KeyStc[i][j]){

          if (KeyBac[i][j] != 0){

            P0 = LedChar[i*4+j];
          }
          KeyBac[i][j] = KeyStc[i][j];
        }
      }
    }
    
 }
}

void InterruptTime0() interrupt 1{

  uint i;
  static uchar KeyOut = 0;
  static uchar KeyBuf[4][4] = {
    {0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff}
  };


  TH0 = 0xfc;
  TL0 = 0x67;

  //消除按键抖动
  KeyBuf[KeyOut][0] = (KeyBuf[KeyOut][0] << 1) | KeyIn1;
  KeyBuf[KeyOut][1] = (KeyBuf[KeyOut][1] << 1) | KeyIn2;
  KeyBuf[KeyOut][2] = (KeyBuf[KeyOut][2] << 1) | KeyIn3;
  KeyBuf[KeyOut][3] = (KeyBuf[KeyOut][3] << 1) | KeyIn4;

  //更新按键状态
  for (i = 0; i < 4; i++){
    if ((KeyBuf[KeyOut][i] & 0x0f) == 0x00){
      KeyStc[KeyOut][i] = 0;
    } 
    else if ((KeyBuf[KeyOut][i] & 0x0f) == 0x0f){
      KeyStc[KeyOut][i] = 1;
    }
  }

  //执行下一次的扫描输出
  KeyOut++;  //输出索引递增1
  KeyOut &= 0x03;  //索引值到4归零

  switch(KeyOut){
    case 0 : KeyOut1 = 0; KeyOut4 = 1; break;
    case 1 : KeyOut2 = 0; KeyOut1 = 1; break;
    case 2 : KeyOut3 = 0; KeyOut2 = 1; break;
    case 3 : KeyOut4 = 0; KeyOut3 = 1; break;
    default: break;
  }

}