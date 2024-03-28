/*
 * CFile1.c
 *
 * Created: 2024-03-28 오후 1:56:47
 *  Author: SYSTEM-00
 */ 
#include "myHeader.h"

#include <avr/io.h>
#include <avr/delay.h>


uint8_t digit[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
char arr[5];		//segment image 정보를 담을 안전영역
char *PC = &PORTC, *PD = &PORTD;

void PortSet(char *p1, char *p2)
{
	PC = p1; PD = p2;
}
void seg(int pos, uint8_t c)
{
	*PC |= 0x0F;
	*PC &= ~(1 << (3 - pos));

	*PD = c;
	_delay_ms(2);
}
int k = 4;

void FND_4(char* inf) // segment Image 배열
{
	for(int i = 0; i < k; i++)
	{
		seg(i, *(inf + i));
		//seg(i, inf[i]);
	}
}


char* SegDisp(unsigned long num)
{	//10진 정수를 입력받아 16진수 문자열로 변환 ex)65535 ==> 0xffff, 56506=>0xBCDA
	int n1 = num % 16;			//A(10): 문자가 아닌 숫자
	int n2 = (num / 16) % 16;	//B(11)
	int n3 = (num / 256) % 16;	//C(12)
	int n4 = num / 4096;		//D(13)
	
	arr[0] = digit[n1]; arr[1] = digit[n2]; arr[2] = digit[n3]; arr[3] = digit[n4];
	
	if ( num<16 ){
		arr[3] = 0; arr[1] = 0; arr[2] = 0;
	}
	else if ( num<256 ){
		arr[2] = 0; arr[3] = 0;
	}
	else if ( num<4096 ){
		arr[3] = 0;
	}
	k = (num > 4095) ? 4 : (num > 256) ? 3 : (num > 16) ? 2 : 1;
	FND_4(arr);
	return arr;
}