# include <reg52.h>
# define uint unsigned int

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code LEDChar[] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90  //����0~9
};

unsigned char LEDBuff[6] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF  //6�������
};

void main(){
	
	uint cnt = 0;  //0.1s�Ĵ���
	uint i = 0;  //���������
	uint sec = 0; //����
	
	ADDR3 = 1;
	ENLED = 0;
	
	TMOD = 0x01;  //ģʽ1
	TH0 = 0xfc;  //0.01s
	TL0 = 0x67;  //Ҳ����Ϊ0x00 �޲��
	
	TR0 = 1; //��ʱ������
	
	while(1){
		
		if(TF0 == 1){  //�����TF0ֵ0
			
			TF0 = 0;
			TH0 = 0xfc;
			TL0 = 0x67;
			cnt++;
		}
		
		if (cnt >= 1000){ //����һ��
			
			cnt = 0; //cnt��0
			sec++; //����һ��
			
			LEDBuff[0] = LEDChar[sec%10];  //0�ܸ�ֵ
			LEDBuff[1] = LEDChar[sec/10%10]; //1�ܸ�ֵ
			LEDBuff[2] = LEDChar[sec/100%10];  //2�ܸ�ֵ
			LEDBuff[3] = LEDChar[sec/1000%10];  //3�ܸ�ֵ
			LEDBuff[4] = LEDChar[sec/10000%10];  //4�ܸ�ֵ
			LEDBuff[5] = LEDChar[sec/100000%10];  //5�ܸ�ֵ
		}
		
		//������������� 0.01s���
		if (i = 0) {ADDR0 = 0; ADDR1 = 0; ADDR2 = 0; i++; P0 = LEDBuff[0];}
		else if (i == 1) {ADDR0 = 1; ADDR1 = 0; ADDR2 = 0; i++; P0 = LEDBuff[1];}
		else if (i == 2) {ADDR0 = 0; ADDR1 = 1; ADDR2 = 0; i++; P0 = LEDBuff[2];}
		else if (i == 3) {ADDR0 = 1; ADDR1 = 1; ADDR2 = 0; i++; P0 = LEDBuff[3];}
		else if (i == 4) {ADDR0 = 0; ADDR1 = 0; ADDR2 = 1; i++; P0 = LEDBuff[4];}
		else if (i == 5) {ADDR0 = 1; ADDR1 = 0; ADDR2 = 1; i = 0; P0 = LEDBuff[5];}
	}
}