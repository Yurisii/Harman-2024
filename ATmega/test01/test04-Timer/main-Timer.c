/*
 * test04-Timer.c
 *
 * Created: 2024-03-28 오전 10:57:13
 * Author : SYSTEM-00
 */ 
#include "myHeader.h"		//""는 
#define OPTMAX 10
#define STATEMAX 5
#define RESETMAX 2

#include <avr/io.h>			//<>는 System header, 제공하는 header 약속되어 있는 곳에 있다.
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define __delay_t 500

volatile int opt = 0, state = 0, reset = 0;
unsigned long cnt = 0, tcnt = 0;



int main(void)
{
    /* Replace with your application code */
	PortSet(&PORTC, &PORTD);
	PORTE = 0x07;
	DDRA = 0x0F;
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
	PORTD = 0x3F;

	if((cnt == tcnt) && (cnt != 0))
	{
		while(reset == 0)
		{
			char m;
			Toggle(m);
		}
		
	}
	if(state != 0)
	{
		while(0 < state && state < 5)
		{
			for(int i = 0; i < 50; i++)
			AllDisp(tcnt);
			for(int i = 0; i < 50; i++)
			AllDisp_state(tcnt); continue;
		}
// 		switch(state)
// 		{
// 			case 1: 
// 			{
// 				for(int i = 0; i < 50; i++)
// 				AllDisp(tcnt);
// 				for(int i = 0; i < 50; i++)
// 				AllDisp_state(tcnt); continue;
// 			}
// 			case 2: 			
// 			{
// 				for(int i = 0; i < 50; i++)
// 				AllDisp(tcnt);
// 				for(int i = 0; i < 50; i++)
// 				AllDisp_state(tcnt); continue;
// 			}
// 			case 3: 
// 			{
// 				for(int i = 0; i < 50; i++)
// 				AllDisp(tcnt);
// 				for(int i = 0; i < 50; i++)
// 				AllDisp_state(tcnt); continue;
// 			}
// 			case 4: 
// 			{
// 				for(int i = 0; i < 50; i++)
// 				AllDisp(tcnt);
// 				for(int i = 0; i < 50; i++)
// 				AllDisp_state(tcnt); continue;
// 			}
// 			default : 
// 			{
// 				for(int i = 0; i < 50; i++)
// 				AllDisp(tcnt); state = 0; break; 
// 			}
// 		}
	}
	else if(opt != 0)
	{
// 		if(opt < 3)	for(int i = 0; i < 50; i++)	 {DecDisp(cnt);}		//기본 시작
// 		else if (opt >= 3) wdt_enable(WDTO_15MS);
		switch(opt)
		{
			case 1: 
			for(int i = 0; i < 50; i++)	 DecDisp(cnt); continue;		//기본 시작
			case 2: 
			for(int i = 0; i < 50; i++)	 DecDisp(cnt); continue;
			case 3:	wdt_enable(WDTO_15MS);
			default : opt = 0; break;
		}
	}

	else if(reset != 0)
	{
		switch(reset)
		{
			case 1: cnt = 0, tcnt = 0; continue;
			default: reset = 0; cnt = 0, tcnt = 0; break;
		}
	}
    }
}

ISR(TIMER1_OVF_vect)
{
	if((opt == 1) && (state == 0))	cnt++;
}

ISR(INT4_vect)
{		
	if(state == 1)	
	{
		tcnt++;
		if((tcnt % 10) == 0) tcnt-=10;
	}	// 설정에 들어가면 1의 자리 ++
	else if(state == 2) 
	{
		(tcnt += 10);
		if(((tcnt / 10) % 6) == 0) tcnt-=60;
	}		// 다음 10의 자리 ++
	else if(state == 3) 
	{
		(tcnt += 60);\
		if(((cnt / 60) % 10) == 0) tcnt-=600;
	}		// 다음 100의 자리 ++
	else if(state == 4) 
	{
		(tcnt += 600);	
		if(((tcnt / 600) % 10) == 0) tcnt-=6000;
	}	// 다음 1000의 자리 ++
	else if((state == 0) && (opt > 4))	opt = 0;
	else
	{
		opt++;
		if (opt >= OPTMAX) opt = 0;
	}
}

ISR(INT5_vect)
{	//INT5 인터럽트 처리 루틴: sw2
	state++;
	if (state >= STATEMAX) state = 0;
}

ISR(INT6_vect)
{	//INT6 인터럽트 처리 루틴: sw3
	reset++;
	state = 0;
	opt = 0;
	wdt_enable(WDTO_15MS);
	wdt_reset();
	if (reset >= RESETMAX) 
	{
		reset = 0;
		cnt = 0, tcnt = 0;
	}
}
