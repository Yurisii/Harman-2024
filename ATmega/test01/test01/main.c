/*
 * test01.c
 *
 * Created: 2024-03-20 오전 11:42:12
 * Author : SYSTEM-00
 */ 
#define F_CPU 16000000L				// Board에 대한 CLK정보(16MHz)

#include <avr/io.h>
#include <avr/delay.h>

const int _delay_t = 500;
int k = 0;
int j = 0;
									// PORT를 선언할 변수가 없다. 상수처럼 사용한다.
void TogglePinA(int n, int dl)		// n : n번째 비트, dl : delay in mili-second
{
	char b = 1 << n;				//n의 값에 따라 n번째 비트에 1을 넣는다.	
	PORTA |= b;						//PortA의 0번째 비트를 HIGH로 출력
	_delay_ms(500);
	PORTA &= ~b;					//PortA의 0번째 비트를 LOW로 출력
	_delay_ms(500);
}

int main(void) // 여기로 시작되어 들어감
{
    /* Replace with your application code */
				  // |= OR EQUAL 원래 가지고 있던 값과 상관없이 원하는 비트의 값을 1로 만들어 준다.
				  
	DDRA |= (1<<0 | 1<<1 | 1<<2); // A port의 0, 1 ,2번째 비트를 출력용으로 사용, 나머지는 입력 = 0은 출력, 1은 입력
	DDRB &= ~(1<<0);// B port의 0번째 비트를 입력용으로 사용

	
	int mode = 0;
    while (1)		// Embedded Program은 무한루프가 기본이다.
    {
		//if(PINB & 0x01 == 1)				// 스위치가 눌렸을 때 0, 안눌리면 1
		/*
		if(!(PINB & 0x01 == 1))				// 스위치가 눌렸을 때 1, 안눌리면 0
		{
			TogglePinA(0, _delay_t);		// O번째 비트 점멸
		}
		if(!(PINB & 0x01 == 1))				// 스위치가 눌렸을 때 1, 안눌리면 0
		{
			TogglePinA(1, _delay_t);		// 1번째 비트 점멸
		}
		if(!(PINB & 0x01 == 1))				// 스위치가 눌렸을 때 1, 안눌리면 0
		{
			TogglePinA(2, _delay_t);		// 2번째 비트 점멸

		}
		*/
		
		//교수님 코드▼
		/*
		if(!(PINB & 0x01 == 1))
		{
			mode++;
			if(mode >= 3) mode = 0;
		}
		switch (mode)
		{
			case 0: TogglePinA(0, _delay_t); break;
			
			case 1: TogglePinA(1, _delay_t); break;
			
			case 2: TogglePinA(2, _delay_t); break;
			
			default: mode = 0;
		}
		*/
		
		if(!(PINB & 0x01 == 1))
		{
			k++;
			j = k % 3;
			
			while(1)
			if(PINB & 0x01 == 1)
			{
			break;
			}
		}
		
		switch (j)
		{		
		case 1: TogglePinA(0, _delay_t); break;
		
		case 2: TogglePinA(1, _delay_t); break;
		
		default: TogglePinA(2, _delay_t); break;
		}
    }
}

