# include <reg52.h>
# define uchar unsigned char
# define uint unsigned int

sbit OUT1 = P1^0;
sbit KEY1 = P3^1;

uchar KeySta = 1;
void main(){
    uchar KeyBac = 1;
    uchar cnt = 0;
   EA = 1;
   TMOD = 0x01;
   TH0 = 0xfc;
   TL0 = 0x66;
   ET0 = 1;
   TR0 = 1;

   OUT1 = 0;
   while(1){

    if (KeyBac != KeySta){
        if (KeyBac == 0){
            OUT1 = 1;
            cnt++;
            if (cnt == 2){
                cnt = 0;
                OUT1 = 0;
            }
        }
        KeyBac = KeySta;
    }
   }
}

void InterruptTime0() interrupt 1{
    TH0 = 0xfc;
    TL0 = 0x66;

    if (KEY1 == 0){
        KeySta = 0;
    }
    else if (KEY1 == 1){
        KeySta = 1;
    }

}