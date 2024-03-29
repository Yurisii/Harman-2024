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
uint8_t dec[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};

char arr[5];		//segment image 정보를 담을 안전영역
char *PC = &PORTC, *PD = &PORTD;
extern int state;			//전역변수로 state를 가져옴
extern long cnt, tcnt;		//   ``		cnt와 tcnt도 가져옴
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

void seg_state(int pos, uint8_t c)
{
	if((state - 1) != pos)			//state 에 맞는 자리를 
	{
		*PC |= 0x0F;
		*PC &= ~(1 << (3 - pos));

		*PD = c;
		_delay_ms(2);
	}
}


void FND_x(char* inf) // segment Image 배열
{
	for(int i = 0; i < 4; i++)
	{
		seg(i, *(inf + i));
	}
}

void FND_state(char* inf) // segment Image 배열
{
	for(int i = 0; i < 4; i++)
	{
		seg_state(i, *(inf + i));
	}
}

char* SegDisp(unsigned long num)		// 16 진수 함수
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

char* DecDisp(unsigned long num)		// 기본 시간 함수
{	//10진 정수를 입력받아 16진수 문자열로 변환 ex)65535 ==> 0xffff, 56506=>0xBCDA
	int n1 = num % 10;			//A(10): 문자가 아닌 숫자
	int n2 = (num / 10) % 6;	//B(11)
	int n3 = (num / 60) % 10;	//C(12)
	int n4 = (num / 100) % 6;		//D(13)
	
	arr[0] = dec[n1]; arr[1] = dec[n2]; arr[2] = dec[n3]; arr[3] = dec[n4];
	
	if ( num<10 ){
		arr[3] = 0; arr[1] = 0; arr[2] = 0;
	}
	else if ( num<60 ){
		arr[2] = 0; arr[3] = 0;
	}
	else if ( num<600 ){
		arr[3] = 0;
	}
	k = (num > 600) ? 4 : (num > 60) ? 3 : (num > 10) ? 2 : 1;
	FND_4(arr);
	return arr;
}

char* AllDisp(unsigned long num)		// 0인 자리까지 다 보여주는 함수
{	//10진 정수를 입력받아 16진수 문자열로 변환 ex)65535 ==> 0xffff, 56506=>0xBCDA
	int n1 = num % 10;			//A(10): 문자가 아닌 숫자
	int n2 = (num / 10) % 6;	//B(11)
	int n3 = (num / 60) % 10;	//C(12)
	int n4 = (num / 600) % 6;		//D(13)
	
	arr[0] = dec[n1]; arr[1] = dec[n2]; arr[2] = dec[n3]; arr[3] = dec[n4];
	FND_x(arr);
	return arr;
}

char* AllDisp_state(unsigned long num)	// state 번호 제외 하고 다 보여주는 함수 > 교차로 사용해서 깜빡임
{	//10진 정수를 입력받아 16진수 문자열로 변환 ex)65535 ==> 0xffff, 56506=>0xBCDA
	int n1 = num % 10;			//A(10): 문자가 아닌 숫자
	int n2 = (num / 10) % 6;	//B(11)
	int n3 = (num / 60) % 10;	//C(12)
	int n4 = (num / 600) % 6;		//D(13)
	
	arr[0] = dec[n1]; arr[1] = dec[n2]; arr[2] = dec[n3]; arr[3] = dec[n4];
	FND_state(arr);
	return arr;
}

void Toggle(char m)
{
	for(int n = 0; n < 3; n++)
	{
		char m = 1 << n;
		PORTA |= m;
		_delay_ms(50);
		PORTA &= ~m;
		_delay_ms(50);
		for(int i = 0; i < 10; i++)
		AllDisp(tcnt);
		for(int i = 0; i < 10; i++)
		AllDisp_state(tcnt);
	}
}
