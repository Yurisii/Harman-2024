/*
 * test04-Timer.c
 *
 * Created: 2024-03-28 오전 10:57:13
 * Author : SYSTEM-00
 */ 
#include "myHeader.h"		//""는 
#define OPTMAX 3
#define STATEMAX 3
#define RESETMAX 3

#include <avr/io.h>			//<>는 System header, 제공하는 header 약속되어 있는 곳에 있다.
#include <avr/delay.h>
#include <avr/interrupt.h>

#define __delay_t 500

volatile int opt = 0, state = 0, reset = 0;
unsigned long cnt = 0, tcnt = 0;


int main(void)
{
    /* Replace with your application code */
	PortSet(&PORTC, &PORTD);
	PORTE = 0x07;
	DDRA = 0x01;
	DDRC = 0x0F;
	DDRD = 0xFF;
	DDRE = 0x00;
	
// 	TIMSK |= 0x01;		// TOIE(TNCT Overflow Interrupt Enable) >> 0번 = 0 , 2번 = 6  or 
// 						// OCIE(OCR Compare Interrupt Enable) >> 0번 = 1, 2번 = 7
// 						// 0000 0001b - Timer 0 TCNT overflow interrupt
// 	TCCR0 = 0x04;		// 분주비(Pre-scaler) 64
	
// 	TIMSK |= 0x40;		// 0100 0001b - Timer 2 TCNT overflow interrupt
// 	TCCR2 = 0x04;
	EIMSK = 0x70;		// 0111 0000	//INT 4~INT 6 활성화
	EICRB = 0x2a;		//4개의 B그룹(INT4~INT7)의 인터럽트 발생 시점 결정(00 10 10 10, 각 7 6 5 4에서의 INT발생 시점을 rising edge로 결정)

	TIMSK |= 0x04;		// 16bit - 0000 0100b - Timer 2 TCNT overflow interrupt
	TCCR1B = 0x04;		// 분주비(Pre-scaler) 64

	SREG |= 0x80;		//status Register - 인터럽트 허용 상태 레지스터
	sei();
    while (1) 
    {
	if(cnt > 0x10000) cnt = 0;
	SegDisp(cnt);
	
	if(state != 0)
	{
		switch(state)
		{
			case 1: _delay_ms(100);
			case 2: _delay_ms(100);
			case 3: _delay_ms(100);
			case 4: _delay_ms(100);
			default : state = 0; break;
		}
	}
	else if(opt != 0)
	{
		switch(opt)
		{
			case 1: PORTD = 0x40
			case 2: 
			case 3:
			case 4:
			default : opt = 0; break;
		}
	}
	else if(reset == 1)
	{
		
	}
    }
}

ISR(TIMER1_OVF_vect)
{
	cnt++;
}

// ISR(TIMER0_OVF_vect)
// {
// 	tcnt++;
// 	if(tcnt >= 10)
// 	{
// 		cnt++; tcnt = 0;
// 	}
// }
// 
// ISR(TIMER2_OVF_vect)
// {
// 	tcnt++;
// 	if(tcnt >= 10)
// 	{
// 		cnt++; tcnt = 0;
// 	}
// }
ISR(INT4_vect)
{	//INT4 인터럽트 처리 루틴: sw1
	opt++;  cnt--; 
	if (opt >= OPTMAX)opt = 0;
}

ISR(INT5_vect)
{	//INT5 인터럽트 처리 루틴: sw2
	state++;
	if (state >= STATEMAX) state = 0;
}

ISR(INT6_vect)
{	//INT6 인터럽트 처리 루틴: sw3
	reset++;
	if (reset >= RESETMAX) reset = 0;
}
