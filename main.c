# include <reg52.h>
# define uint unsigned int
# define uchar unsigned char

sbit ADDR0 = P1 ^ 0;
sbit ADDR1 = P1 ^ 1;
sbit ADDR2 = P1 ^ 2;
sbit ADDR3 = P1 ^ 3;
sbit ENLED = P1 ^ 4;

unsigned char code LedChar[] = {
	0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
};

unsigned char LedBuff[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

uchar flagls = 0;
uint cnt = 0;
uchar i = 0;

void main() {

	unsigned long sec = 0;

	EA = 1;
	ENLED = 0;
	ADDR3 = 1;

	TMOD = 0x01;
	TH0 = 0xfc;
	TL0 = 0x00;

	ET0 = 1;
	TR0 = 1;

	while (1) {

		if (flagls == 1) {

			flagls = 0;
			sec++;

			LedBuff[0] = LedChar[sec%10];
			LedBuff[1] = LedChar[sec/10%10];
			LedBuff[2] = LedChar[sec/100%10];
			LedBuff[3] = LedChar[sec/1000%10];
			LedBuff[4] = LedChar[sec/10000%10];
			LedBuff[5] = LedChar[sec/100000%10];
		}

	}
}

void InterruptTimer0() interrupt 1{

	TH0 = 0xfc;
	TL0 = 0x00;
	cnt++;

	if (cnt >= 1000) {

		cnt = 0;
		flagls = 1;
	}

	P0 = 0xff;
	switch (i) {

	case 0:                           ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; P0 = LedBuff[0];  i++; break;
	case 1: if (LedBuff[1] != 0xC0) { ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; P0 = LedBuff[1]; } i++; break;
	case 2: if (LedBuff[2] != 0xC0) { ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; P0 = LedBuff[2]; } i++; break;
	case 3: if (LedBuff[3] != 0xC0) { ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; P0 = LedBuff[3]; } i++; break;
	case 4: if (LedBuff[4] != 0xC0) { ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; P0 = LedBuff[4]; } i++; break;
	case 5: if (LedBuff[5] != 0xC0) { ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; P0 = LedBuff[5]; } i = 0; break;
	default: break;
	}
}