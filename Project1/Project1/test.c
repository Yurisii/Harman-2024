#define _CRT_SECURE_NO_WARNINGS			//소스파일에서 안전하지 않은(unsafe) scanf, strcpy, fopen 등을 사용할 수 있게 한다.


#include <stdio.h>
#include <conio.h>
#include <string.h>

#if 0
int main()
{

	printf("숫자 키를 입력하세요. 해당하는 영단어를 알려드리겠습니다.\n");
	while (1)
	{
		printf(">");
		char n = getch(); // no echo (내가 누른 키 값이 화면상에 찍히기 전에 되돌려준다.)
		// getchar(); 는 엔터가 필요하다.

		if (n == '1') printf("%c : ONE\n", n);
		else if (n == '2') printf("%c : TWO\n", n);
		else if (n == '3') printf("%c : THREE\n", n);
		else if (n == '4') printf("%c : FOUR\n", n);
		else if (n == '5') printf("%c : FIVE\n", n);
		else if (n == '6') printf("%c : SIX\n", n);
		else if (n == '7') printf("%c : SEVEN\n", n);
		else if (n == '8') printf("%c : EIGHT\n", n);
		else if (n == '9') printf("%c : NINE\n", n);
		else if (n == '0') printf("%c : ZERO\n", n);
		else if (n == 'q' || n == 'Q') break;
		else printf("wrong key\n");
	}
}
#endif


#if 0
int main()
{
	printf("숫자를 입력하세요. 해당하는 영단어를 알려드리겠습니다.\n");
	int k = 1;
	while (k)
	{
		printf("<");
		char n = getch();

		switch (n)
		{
		case '1': printf("%c : ONE\n", n); break;
		case '2': printf("%c : TWO\n", n); break;
		case '3': printf("%c : THREE\n", n); break;
		case '4': printf("%c : FOUR\n", n); break;
		case '5': printf("%c : FIVE\n", n); break;
		case '6': printf("%c : SIX\n", n); break;
		case '7': printf("%c : SEVEN\n", n); break;
		case '8': printf("%c : EIGHT\n", n); break;
		case '9': printf("%c : NINE\n", n); break;
		case '0': printf("%c : ZERO\n", n); break;

		case 'q':
		case 'Q': k = 0; break;
		}

	}
}
#endif


#if 0
int main()
{
	char* name[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	printf("숫자를 입력하세요.\n");
	printf("프로그램을 끝내시려면 'Q'를 누르세요.\n\n");
	while (1)
	{
		printf("<");
		char n = getch();
		int m = n - 0x30; // ASCII값을 num 값으로 변경.
		if (m >= 0 && m <= 9)
			printf("%c : %s\n", n, name[m]);
		else if (n == 'q' || n == 'Q')
			break;
	}

}
#endif

#if 1
void test01();
void test02();
void test03();
void test04();
void test05();
void test06();
void test07();
void test08();

void Dump(char* p, int len);
void Copy(char* p1, char* p2);
int Length(char* str);
int Compare(char* str1, char* str2);





//--------------함수 설계------------------//
// Prototype : void Copy(char* p1, char* p2)
// 함수명 : Copy
// 기능   : p2 문자열을 인수로 받아서 p1 문자열로 복사.
// 인수   : 타겟문자열, 소스문자열 - char* p1, char *p2;
// 리턴값 : void
void Copy(char* p1, char* p2)
{
	while (*p2)							// 무한루프 (p2의 값) p2의 값이 \0이 아니라면 계속수행
	{
		*p1++ = *p2++;					// p1의 값에다가 p2의 값을 대입.
		*p1 = 0;
	}
}
void Dump(char*p, int len)				// 메모리 공간 출력용 범용 함수
{
	for (int i = 0; i < len; i++)
	{
		if (i % 16 == 0)				// 16의 배수마다 (줄 바꿈이 일어 날때 마다) 값을 찍는다.
		{
			printf("\n%08x", (unsigned int)p);		// p = 주소값
		}
	printf("%02x", (unsigned char)*p);	// *p = 문자값
		if (i % 8 == 0)
		{
			printf("  ");
		}
	}
}
//--------------함수 설계------------------//
// int Length(char* str)
// 함수명 : Length
// 기능   : 문자열을 인수로 받아서 문자열의 길이를 반환.
// 인수   : 문자열 - char* str
// 리턴값 : 문자열의 길이 - int len
int Length(char* str)
{
	char buf[100];
	str = buf;
	printf("입력 >");
	scanf("%s", str);
	int len = 0;
	while (*str)							
	{
		str++;
		len++;
	}
	/*
	while (1)
	{
		if (*(str + len) == 0)
		len++;
	}
	*/
	printf("입력한 [%s]의 길이는 [%d]입니다.\n", buf, len);
	return len;
}


//--------------함수 설계------------------//
// int Compare(char* str1, char* str2)
// 함수명 : Compare
// 기능   : 두 문자열의 같은 배치의 문자를 비교한 후에 결과값을 출력하는 함수
// 인수   : 문자열 - char* str1, char* str2
// 리턴값 : 1, 0, -1
// 예외   : 두 문자열의 길이는 다르지만, 모두 같을때 ex) hell & hello
int Compare(char* str1, char* str2)
{
	int asr;

	while (1)
	{
		if (*str1 == *str2)	asr = 0;
		else if (*str1 > *str2)	asr = 1;
		else if (*str1 < *str2)	asr = -1;

		str1++;	str2++;

		if (asr == 0 && (*str1 ^ *str2) == '\0') return asr = 999999;
		else if (asr != 0 || (*str1 || *str2) == '\0')		break;
		
	}
	return asr;
}

void test01()				//  숫자키에 대한 문자열 출력
{
	char* name[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	printf("숫자를 입력하세요.\n");
	printf("프로그램을 끝내시려면 'Q'를 누르세요.\n\n");
	while (1)
	{
		printf("<");
		char n = _getch();
		int m = n - 0x30; // ASCII값을 num 값으로 변경.
		if (m >= 0 && m <= 9)
			printf("%c : %s\n", n, name[m]);
		else if (n == 'q' || n == 'Q')
			break;
	}

}
void test02()								// 문자열과 문자배열
{
	char ca[] = "Hello";						// ca[0] : H 부터 ~ ca[5] : \0
	// int i <- 예전 표준, 밖에서 변수 선언 했었어야 한다.
	for (int i = 0; i < 10; i++)					// 0에서부터 5까지
	{
		printf("ca[%d]:%c (%02x)\n", i, ca[i], ca[i]);
	}
	ca[2] -= 1;
	ca[3] -= 1;

	for (int i = 0; i < 10; i++)					// 0에서부터 5까지
	{
		printf("ca[%d]:%c (%02x)\n", i, ca[i], ca[i]);
	}
}
void test03()						// 의도 : kBuf를 이용해서 찍은 문자열이 메모리공간에 어디에 들어가 있는지 확인한다.(포인터의 위치 지정)
{
	char buf[100];						// 안전 메모리 공간 확보
	char* pBuf;							// 안전 메모리 공간 중의 출력 위치
	unsigned int addr;					// 출력 위치 지정을 위한 입력 변수(주소)
	char kBuf[100];						// 출력 문자열 입력 공간 확보


	printf("안전 공간의 주소는 %d[%08x] 입니다.\n", (unsigned)buf, (unsigned int)buf);
	printf("입력을 시작할 주소를 입력하세요 : ");
	scanf("%d", &addr);					// 안전공간 주소 참고
	pBuf = buf + addr;					// 상수값 위치 지정			
	printf("문자열을 입력하세요 : ");
	scanf("%s", kBuf);
	Copy(pBuf, kBuf);					// 문자열 복사
	Dump(buf, 100);
}
void test04()			// 포인터를 이용한 문자열 입출력 함수
{
	char* arr[10] = {"aaaaa","bbbb","ccc","dd", "e"};
	char buf[100];

	printf("[6] : "); scanf("%s", buf);
	arr[6] = buf;
	printf("[7] : "); scanf("%s", &buf[50]);
	arr[7] = &buf[50];
	for (int i = 0; i < 10; i++)
	{
		// arr[i]둘 다 주소 하지만 변환자 %x와 %s가 다르기 때문에 주소값과 문자열을 보낸다.
		printf("arr[%d] : 0x%08x %s\n", i, (unsigned int)arr[i], arr[i]);
	}
}
void test05()
{
	struct stTest
	{
		int i;
		float a;
		char * name;					// 주소는 무조건 8바이트 64byte에서! 
	} s1 = { 1, 3.14 };
	s1.name = "삼천갑자 동방삭";	// const 주소로 들어가 그 주소가 name에 들어온다.

	typedef struct stTest st_test;

	struct stTest s2 = s1;
	//printf("%d\n", sizeof(s1.name));
	printf("sizeof(struct stTest) : %d\n", (int)sizeof(st_test)); // 맴버 편수들의 총 바이트 수를 되돌려주는 함수(매크로)가 sizeof 이다.

	printf("struct stTset s1 : %d %f %s\n", s1.i, s1.a, s1.name);
	printf("struct stTset s2 : %d %f %s\n", s2.i, s2.a, s2.name);
}
void test06()
{
	//char* s1 = "Good";
	//char* s2 = "Afternoon";
	char buf[100];									// 안전지대(buf)를 잘 활용해야 한다.
	char* s1;										// 선언만 하면 어딜 가르키는지 모르고 안전하지 않은 공간(Heap)을 가르킨다.
	char* s2;
	//scanf("%s", s1`);								// 확보가 안되어 있는 공간이기 때문에

	s1 = buf;
	s2 = buf + 50;
	scanf("%s", s1);
	scanf("%s", s2);
	/*
	scanf("%s", s1 = buf);							// buf의 주소가 넘어간다.
	scanf("%s", s2 = buf + 50);						// buf의 50번 째 주소에 s2에 넣는다.
	*/
	// strcat Test
	printf("s1 : %s\n", s1);
	printf("s2 : %s\n", s2);
	/*
	printf("strcat(s1, s2) : %s\n", strcat(s1, s2));							// s1은 const 영역(상수영역)이라 수정 불가이다.
	*/							
	// 방법은 1) s1 , s2에 있는 값을 로컬 영역으로 가지고 와서 수정을 한 후에 출력을 한다.
	//		  2) printf에는 기본 printf가 있고 fprintf(파일로 출력)이 있다.
	//		  3) sprintf(string printf) 가 있다 sprintf는 buffer에 출력을 거는 함수이다. 

	// strlen이 return하는 길이 값은 \0(null) 전까지다.(= null은 카운트하지 않는다.)
	printf("s1 : %s(%d) \n", s1, strlen(s1));									
	printf("s2 : %s(%d) \n", s2, strlen(s2));
	strcpy(buf, s1);
	printf("strcat(s1, s2) : %s\n", strcat(buf, s2));

	// buf에 있는 안전 메모리 공간에 출력을 내보낸다. fprintf도 buf가 아닌 FILE* stream으로 지정하면 같은 원리로 동작한다.
	// sprintf(buf, "strcat(s1, s2) : %s%s\n", s1, s2);							// strcat(s1, s2);를 사용하면 고정문자열을 가리키고 있는 s1을 const로 지정하는 것이 불가능해서 오류가 나온다
	// printf("%s", buf);
}
void test07()
{

}
void test08()
{
	char buf1[100];
	char buf2[100];
	int asr;
	printf("결과값은 1, 0, -1로 출력됩니다.\n예외 상황 시 오류 문구가 출력됩니다.\n");
	printf("1번 문자열을 입력하세요:");
	scanf("%s", buf1);
	printf("2번 문자열을 입력하세요:");
	scanf("%s", buf2);

	asr = Compare(buf1, buf2);
	
	if (asr == 999999)
	{
		printf("<오류>두 값의 자릿수가 맞지 않습니다.자릿수를 맞춘 후 다시 시도하여주십시오.\n\n");
	}
	else	printf("결과는 [%d]입니다.\n\n", asr);
}




int main(void)
{
	int n;
	void* p_arr[] = { test01, test02, test03, test04, test05, test06, Length, test08};			// 타입이 정해지지 않은 포인터
	void (*p_func)();			// 리턴값이 없고 인자가 정해지지않은 함수 포인터 선언
	while (1)
	{
		printf("1. 숫자키에 대한 문자열 출력 미션\n");
		printf("2. 문자열과 문자배열\n");
		printf("3. 포인터의 위치 지정\n");
		printf("4. 포인터를 이용한 문자열 입출력 함수\n");
		printf("5. 구조체 테스트\n");
		printf("6. 표준 함수 테스트\n");
		printf("7. 문자열 길이 테스트\n");
		printf("8. 문자열 비교 테스트\n");

		printf("0. 종료\n");
		printf("====================================\n");

		scanf("%d", &n);
		p_func = p_arr[n - 1];
		p_func();
	}
	if (n == 1) p_func = test01;
	//test01(1);
	//test02(1);
	//test03(1);
	//test04(1);
}
#endif

#if 0
int main(void)
{
	while (1)
	{
		printf("<");
		char c = _getch();

		if (c >= 0x30 && c <= 0x39)
		{
			printf("숫자\n");
		}
		else if (c >= 0x41 && c <= 0x5a)
		{
			printf("대문자\n");
		}
		else if (c >= 0x61 && c <= 0x7a)
		{
			printf("소문자\n");
		}
		else if (c == 0x1b)
		{
			break;
		}
		else
		{
			printf("특수문자\n");
		}

	}
}
#endif

#if 0
int main(void)
{
	printf("Hello");
}
#endif