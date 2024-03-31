/*
 * test04-Timer.c
 *
 * Created: 2024-03-28 오전 10:57:13
 * Author : SYSTEM-00
 */ 
#include "myHeader.h"		//""는 동일 디렉토리 안에서 호출 시
#define OPTMAX 10
#define STATEMAX 5
#define RESETMAX 2

#include <avr/io.h>			//<>는 System header, 제공하는 header 약속되어 있는 곳에 있다.
#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#define __delay_t 500

volatile int opt = 0, state = 0, reset = 0;
unsigned long cnt = 0, tcnt = 0;			// cnt는 실제 카운트 tcnt는 설정 카운트



int main(void)
{
	PortSet(&PORTC, &PORTD);
	PORTE = 0x07;
	DDRA = 0x0F;
	DDRC = 0x0F;
	DDRD = 0xFF;
	DDRE = 0x00;

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
			Toggle(m);	// 시간에 도달하면 LED와 Segment가 함께 깜박이는 역할
		}
	}
	if(state != 0)		// state(가운데 = 숫자 변경용) 이 동작하면
	{
		while(0 < state && state < 5)	// 1 ~ 4동안 변경할 자릿 수 점등
		{
			for(int i = 0; i < 50; i++)	// delay를 주고 설정카운트 전체 점등
			AllDisp(tcnt);
			for(int i = 0; i < 50; i++)	// delay를 주고 설정 카운트 중 설정할 값 제외하고 점등
			AllDisp_state(tcnt); continue;
		}
	}
	else if(opt != 0)	// opt(첫번 째 = 시작/정지 버튼) 이 동작하면
	{
		switch(opt)
		{
			case 1:	
			for(int i = 0; i < 50; i++)	 DecDisp(cnt); continue;		// 1번 누르면 시작
			case 2: 
			for(int i = 0; i < 50; i++)	 DecDisp(cnt); continue;		// 2번 누르면 멈춤
			case 3: continue;											// 3번 누르면 0
			case 4:	wdt_enable(WDTO_15MS);								// 4번 누르면 reset
			default : opt = 0; break;
		}
	}

	else if(reset != 0)	//reset이 동작하면.
	{
		switch(reset)
		{
			case 1: cnt = 0, tcnt = 0; continue;						// 카운트된 값 초기화
			default: reset = 0; cnt = 0, tcnt = 0; break;				// 카운트된 값 초기화(안전용)
		}
	}
    }
}
ISR(TIMER1_OVF_vect)
{
	if((opt == 1) && (state == 0))	cnt++;			// opt만 1번 동작하고 state는 동작하지 않으면 cnt 올라간다.
}
ISR(INT4_vect)										// 왼쪽(적색) 스위치
{		
	if(state == 1)									// state 1이면 1의 자리 증가
	{
		tcnt++;
		if((tcnt % 10) == 0) tcnt-=10;				// 9에서 10으로 넘어가면 -10
	}	
	else if(state == 2)								// state 2이면 10의 자리 증가
	{
		(tcnt += 10);
		if(((tcnt / 10) % 6) == 0) tcnt-=60;		// 5에서 6으로 넘어가면 -60
	}		
	else if(state == 3)								// state 3이면 세번째 자리 증가
	{
		(tcnt += 60);\
		if(((tcnt / 60) % 10) == 0) tcnt-=600;		// 9에서 10으로 넘어가면 -600
	}		
	else if(state == 4)								// state 4이면 네 번째 자리 증가
	{
		(tcnt += 600);	
		if(((tcnt / 600) % 10) == 0) tcnt-=6000;	// 5에서 6으로 넘어가면 -6000
	}	
	else if((state == 0) && (opt > 4))	opt = 0;
	else
	{
		opt++;
		if (opt >= OPTMAX) opt = 0;
	}
}
ISR(INT5_vect)										// 가운데(주황색) 스위치
{	
	state++;
	if (state >= STATEMAX) state = 0;
}
ISR(INT6_vect)										// 오른쪽(노란색) 스위치
{	
	reset++;
	state = 0;
	opt = 0;
	wdt_enable(WDTO_15MS);							//Reset
	wdt_reset();
	if (reset >= RESETMAX) 
	{
		reset = 0;
		cnt = 0, tcnt = 0;
	}
}
