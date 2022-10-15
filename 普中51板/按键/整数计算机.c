#include <reg52.h>
# define uint unsigned int
# define uchar unsigned char
# define ulong unsigned long

sbit KeyIn4 = P1^0;
sbit KeyIn3 = P1^1;
sbit KeyIn2 = P1^2;
sbit KeyIn1 = P1^3;
sbit KeyOut4 = P1^4;
sbit KeyOut3 = P1^5;
sbit KeyOut2 = P1^6;
sbit KeyOut1 = P1^7;

sbit ADDR0 = P2^2;
sbit ADDR1 = P2^3;
sbit ADDR2 = P2^4;

uchar code LedChar[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};  //数字0~9
uchar code KeyCodeMap[4][4] = {  //矩阵按键编号与ascll表对应
  {0x31, 0x32, 0x33, 0x2b},  //数字键1， 数字键2， 数字键3， 加法
  {0x34, 0x35, 0x36, 0x2d},  //数字键4， 数字键5， 数字键6， 减法
  {0x37, 0x38, 0x39, 0x2a},  //数字键7， 数字键8， 数字键9， 乘法
  {0x30, 0x1b, 0x0d, 0x2f}   //数字键0， 清空， 回车(等于)， 除法
};

//数码管缓冲区
uchar LedBuff[8] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

uchar KeySta[4][4] = {  //全部按键的当前状态
  {1,1,1,1},{1,1,1,1},
  {1,1,1,1},{1,1,1,1}
};

void KeyDirver();

void main(){

  EA = 1;  //使能总中断开关 1开启
  TMOD = 0x01;  //工作模式1
  
  //fc66是0.001s, 也就是1毫秒
  TH0 = 0xfc;
  TL0 = 0x66;

  ET0 = 1;  //定时器T0中断开关 1开启
  TR0 = 1;  //定时器T0开关 1开启
LedBuff[0] = LedChar[0];

  while(1){
    KeyDirver();
  }
}

void ShowNumber(ulong num){

  signed char i;
  uchar arr[8];
  for (i = 0; i < 8; i++){
    arr[i] = num % 10;
    num /= 10;
  }
  for (i = 7; i >= 1; i--){
    if (arr[i] == 0){
      LedBuff[i] = 0x00;
    }else{
      break;
    }
  }
  for (;i >= 0; i--){
    LedBuff[i] = LedChar[arr[i]];
  }
}

void KeyAction(uchar Keycode){

  static ulong result = 0;
  static ulong addend = 0;
  static char choose = 0;

//输入数字
  if (Keycode >= 0x30 && Keycode <= 0x39){
    addend = (addend*10) + (Keycode - 0x30);
    ShowNumber(addend);
  }
  //加法
  else if (Keycode == 0x2b || Keycode == 0x2d || Keycode == 0x2a || Keycode == 0x2f){
    result += addend;
    addend = 0;
    if (Keycode == 0x2b) choose = 1;  //加法
    else if (Keycode == 0x2d) choose = 2;  //减法
    else if (Keycode == 0x2a) choose = 3;  //乘法
    else if (Keycode == 0x2f) choose = 4;  //除法

    ShowNumber(result);
  }
  //运算结果
  else if (Keycode == 0x0d){
    switch(choose){
      case 1: result += addend; addend = 0; choose = 0; break;
      case 2: result -= addend; addend = 0; choose = 0; break;
      case 3: result *= addend; addend = 0; choose = 0; break;
      case 4: result /= addend; addend = 0; choose = 0; break;

    }
    ShowNumber(result);
  }
  else if(Keycode == 0x1b){
    result = 0;
    addend = 0;
    ShowNumber(addend);
  }
}

//驱动函数， 检测按键动作
void KeyDirver(){

  static uchar KeyBac[4][4] = {
    {1,1,1,1},{1,1,1,1},
    {1,1,1,1},{1,1,1,1}
  };

  uchar i, j;

  for (i = 0; i < 4; i++){
    for (j = 0; j < 4; j++){

      if (KeyBac[i][j] != KeySta[i][j]){
        if (KeyBac[i][j] != 0){
          KeyAction(KeyCodeMap[i][j]);
        }
        KeyBac[i][j] = KeySta[i][j];
      }
    }
  }
}

//判断按键是否按下
void KeyScan(){

  uchar i;
  static uchar KeyOut = 0;
  static uchar KeyBuf[4][4] = {
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1},
    {1,1,1,1}
  };

  KeyBuf[KeyOut][0] =  KeyIn1;
  KeyBuf[KeyOut][1] =  KeyIn2;
  KeyBuf[KeyOut][2] =  KeyIn3;
  KeyBuf[KeyOut][3] =  KeyIn4;

  for (i = 0; i < 4; i++){
    if (KeyBuf[KeyOut][i] == 0){
      KeySta[KeyOut][i] = 0;
    }
    else if (KeyBuf[KeyOut][i] == 1){
      KeySta[KeyOut][i] = 1;
    }
  }

  KeyOut++;
  KeyOut &= 0x03;

  switch(KeyOut){
    case 0: KeyOut1 = 0; KeyOut4 = 1; break;
    case 1: KeyOut2 = 0; KeyOut1 = 1; break;
    case 2: KeyOut3 = 0; KeyOut2 = 1; break;
    case 3: KeyOut4 = 0; KeyOut3 = 1; break;
  }
}

//显示数码管
void LedScan(){

  static uchar i = 0;

  P0 = 0x00;
  switch(i){
    case 0: ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; i++; P0 = LedBuff[0]; break;
    case 1: ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; i++; P0 = LedBuff[1]; break;
    case 2: ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; i++; P0 = LedBuff[2]; break;
    case 3: ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; i++; P0 = LedBuff[3]; break;
    case 4: ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; i++; P0 = LedBuff[4]; break;
    case 5: ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; i++; P0 = LedBuff[5]; break;
    case 6: ADDR0 = 0; ADDR1 = 1; ADDR2 = 1; i++; P0 = LedBuff[6]; break;
    case 7: ADDR0 = 1; ADDR1 = 1; ADDR2 = 1; i=0; P0 = LedBuff[7]; break;
    default: break;
  }
}

//中断函数
void InterruptTime0() interrupt 1{

  TH0 = 0xfc;
  TL0 = 0x66;
  LedScan();
  KeyScan();
}