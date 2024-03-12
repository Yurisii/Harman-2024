#include <stdio.h>
#include <conio.h>


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
int test01();
void test02(int a);
void test03(int a);
void Dump(char* p, int len);
void Copy(char* p1, char* p2);



int test01()
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
void test02(int a)								// 문자열과 문자배열
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
void test03(int a)							// 의도 : kBuf를 이용해서 찍은 문자열이 메모리공간에 어디에 들어가 있는지 확인한다.
{
	char buf[100];						// 안전 메모리 공간 확보
	char* pBuf;							// 안전 메모리 공간 중의 출력 위치
	unsigned int addr;							// 출력 위치 지정을 위한 입력 변수(주소)
	char kBuf[100];						// 출력 문자열 입력 공간 확보


	printf("안전 공간의 주소는 %d[%08x] 입니다.\n", (unsigned)buf, (unsigned int)buf);
	printf("입력을 시작할 주소를 입력하세요 : ");
	scanf("%d", &addr);					// 안전공간 주소 참고
	pBuf = buf + addr;					
	printf("문자열을 입력하세요 : ");
	scanf("%s", kBuf);
	Copy(pBuf, kBuf);					// 문자열 복사
	Dump(buf, 100);
}

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
int main(void)
{
	//test01(1);
	//test02(1);
	test03(1);
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