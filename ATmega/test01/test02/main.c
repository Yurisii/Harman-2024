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

void FND_4(char* inf) // segment Image 배열
{
	for(int i = 0; i < 4; i++)
	{
		seg(i, *(inf + i));
		//seg(i, inf[i]);
	}
}

char* Trans1(int num)	//10진 정수를 입력받아서 16진수 문자열로 변환 : 56506 => 0xDCBA
{
	int n1 = num % 10;			// A(10) : 문자가 아닌 숫자
	int n2 = (num / 10) % 10;	// B(11)
	int n3 = (num / 100) % 10;  // C(12)
	int n4 = (num / 1000);		// D(13)
	arr[0] = hex[n1];
	arr[1] = 0;
	arr[2] = 0;
	arr[3] = 0;

	return arr;
}

char* Trans2(int num)	//10진 정수를 입력받아서 16진수 문자열로 변환 : 56506 => 0xDCBA
{
	int n1 = num % 10;			// A(10) : 문자가 아닌 숫자
	int n2 = (num / 10) % 10;	// B(11)
	int n3 = (num / 100) % 10;  // C(12)
	int n4 = (num / 1000);		// D(13)
	arr[0] = hex[n1];
	arr[1] = hex[n2];
	arr[2] = 0;
	arr[3] = 0;
	
	return arr;
}

char* Trans3(int num)	//10진 정수를 입력받아서 16진수 문자열로 변환 : 56506 => 0xDCBA
{
	int n1 = num % 10;			// A(10) : 문자가 아닌 숫자
	int n2 = (num / 10) % 10;	// B(11)
	int n3 = (num / 100) % 10;  // C(12)
	int n4 = (num / 1000);		// D(13)
	arr[0] = hex[n1];
	arr[1] = hex[n2];
	arr[2] = hex[n3];
	arr[3] = 0;
	
	return arr;
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
	
	if ( num<10 )
	{
		arr[3] = 0; arr[1] = 0; arr[2] = 0;
	}
	else if ( num<100 )
	{
		arr[2] = 0; arr[3] = 0;
	}
	else if ( num<1000 )
	{
		arr[3] = 0;
	}
	return arr;
}
/*
// void output(int pos, int a)
// {
// 	int b, c, d = 0;
// 	pos = 1;
// 	switch (pos)
// 	{
// 		case 1: digit(4, a);
// 		case 2: digit(4, a); digit(3, b);
// 		case 3: digit(4, a); digit(3, b); digit(2, c); 
// 		case 4: digit(4, a); digit(3, b); digit(2, c); digit(1, d);
// 		default : PORTD = none;
// 	}
// 	a++;
// 	if(a == 9)	pos++;
// 	if(a % 10 == 0)	b++; a = 0; 
// 	if(b == 9)	pos++;
// 	if(b % 10 == 0) c++; b = 0; 
// 	if(c == 9)	pos++;
// 	if(c % 10 == 0)	pos++; d++; c = 0; 
// 	_delay_ms(1000);
// }
*/


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
		PORTD = 0x40;	
		if(!(PINB & 0x01 == 1))
		{
			i++;
			while(1)
			if(PINB & 0x01 == 1) break;
		}
		switch (i)
		{
			case 1:
			{
				while(i == 1)
				{
					if(j < 10)	PORTC = 0x07; FND_4(Trans1(j++));					_delay_ms(10);
					if(j >= 10 && j < 100); PORTC = 0x03; FND_4(Trans2(j++));		_delay_ms(10);
					if(j >= 100 && j < 1000); PORTC = 0x01; FND_4(Trans3(j++));		_delay_ms(10);
					if(j >= 1000 && j < 10000); PORTC = 0x00;FND_4(Trans4(j++));	_delay_ms(10);
					
					if(!(PINB & 0x01 == 1))
					{
						i++;
						while(1)
						if(PINB & 0x01 == 1) break;
					}				
				}				
				break;
			};
			case 2:
			{
				if(j < 10)	FND_4(Trans1(j));					
				if(j >= 10 && j < 100); FND_4(Trans2(j));		
				if(j >= 100 && j < 1000); FND_4(Trans3(j));
				if(j >= 1000 && j < 10000); FND_4(Trans4(j));
				break;
			}
			default:
			{
				PORTD = 0x40;
				i = 0;
				j = 0;
				break;
			}
		}

		/*switch (y)
		{
			case 1: PORTC =(PORTC & (0x0f<<0))|(0x01<<0); PORTD = ox[x];	break;
			case 2: PORTC = 0x03; PORTD = ox[x]; break;			
			
		}*/
		
		/*
		for(x = 0; x < 4; x++)
		{
			PORTC |= 0x0F;
			PORTC &= ~(1 << x);
			
			for(y = 0; y < 16; y++)
			{
				PORTD = hex[y];
				_delay_ms(100);
			}
		}
		*/
    }
}

