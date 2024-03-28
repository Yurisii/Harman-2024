/*
 * test02.c
 *
 * Created: 2024-03-21 오후 3:33:35
 * Author : SYSTEM-00
 */ 

#define F_CPU 16000000L				// Board에 대한 CLK정보(16MHz)

#include <avr/io.h>
#include <avr/delay.h>

uint8_t ox[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67};
uint8_t hex[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x27, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
char arr[5];		//segment image 정보를 담을 안전영역
char* port_num = {0x07, 0x03, 0x01, 0x00};

void seg(int pos, uint8_t c)
{
	PORTC |= 0x0F;
	PORTC &= ~(1 << (3 - pos));

	PORTD = c;
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

char* Trans4(int num)	//10진 정수를 입력받아서 16진수 문자열로 변환 : 56506 => 0xDCBA
{
	int n1 = num % 10;			// A(10) : 문자가 아닌 숫자
	int n2 = (num / 10) % 10;	// B(11)
	int n3 = (num / 100) % 10;  // C(12)
	int n4 = (num / 1000);		// D(13)
	arr[0] = hex[n1];
	arr[1] = hex[n2];
	arr[2] = hex[n3];
	arr[3] = hex[n4];
	
	if(num < 10) k = 1;
	else if(num < 100) k = 2;
	else if(num < 1000) k = 3;
	else if(num < 10000) k = 4;
	

	return arr;
}



void out2(int x)
{
	while(1)
	{
		PORTC = 0x0b;//~(1 << 3);
		PORTD = ox[x];
		x++;
		_delay_ms(5000);
		if(x == 10) x = 0;
	}
}


int main(void)
{
    /* Replace with your application code */
	DDRB &= ~(1<<0);
	DDRC |= 0x0F;
	DDRD |= 0xFF;
	
	int i = 0, j = 0;  
	  
	while (1) 
    {
	
    }
}

