#define _CRT_SECURE_NO_WARNINGS			//�ҽ����Ͽ��� �������� ����(unsafe) scanf, strcpy, fopen ���� ����� �� �ְ� �Ѵ�.


#include <stdio.h>
#include <conio.h>
#include <string.h>

#if 0
int main()
{

	printf("���� Ű�� �Է��ϼ���. �ش��ϴ� ���ܾ �˷��帮�ڽ��ϴ�.\n");
	while (1)
	{
		printf(">");
		char n = getch(); // no echo (���� ���� Ű ���� ȭ��� ������ ���� �ǵ����ش�.)
		// getchar(); �� ���Ͱ� �ʿ��ϴ�.

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
	printf("���ڸ� �Է��ϼ���. �ش��ϴ� ���ܾ �˷��帮�ڽ��ϴ�.\n");
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
	printf("���ڸ� �Է��ϼ���.\n");
	printf("���α׷��� �����÷��� 'Q'�� ��������.\n\n");
	while (1)
	{
		printf("<");
		char n = getch();
		int m = n - 0x30; // ASCII���� num ������ ����.
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





//--------------�Լ� ����------------------//
// Prototype : void Copy(char* p1, char* p2)
// �Լ��� : Copy
// ���   : p2 ���ڿ��� �μ��� �޾Ƽ� p1 ���ڿ��� ����.
// �μ�   : Ÿ�ٹ��ڿ�, �ҽ����ڿ� - char* p1, char *p2;
// ���ϰ� : void
void Copy(char* p1, char* p2)
{
	while (*p2)							// ���ѷ��� (p2�� ��) p2�� ���� \0�� �ƴ϶�� ��Ӽ���
	{
		*p1++ = *p2++;					// p1�� �����ٰ� p2�� ���� ����.
		*p1 = 0;
	}
}
void Dump(char*p, int len)				// �޸� ���� ��¿� ���� �Լ�
{
	for (int i = 0; i < len; i++)
	{
		if (i % 16 == 0)				// 16�� ������� (�� �ٲ��� �Ͼ� ���� ����) ���� ��´�.
		{
			printf("\n%08x", (unsigned int)p);		// p = �ּҰ�
		}
	printf("%02x", (unsigned char)*p);	// *p = ���ڰ�
		if (i % 8 == 0)
		{
			printf("  ");
		}
	}
}
//--------------�Լ� ����------------------//
// int Length(char* str)
// �Լ��� : Length
// ���   : ���ڿ��� �μ��� �޾Ƽ� ���ڿ��� ���̸� ��ȯ.
// �μ�   : ���ڿ� - char* str
// ���ϰ� : ���ڿ��� ���� - int len
int Length(char* str)
{
	char buf[100];
	str = buf;
	printf("�Է� >");
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
	printf("�Է��� [%s]�� ���̴� [%d]�Դϴ�.\n", buf, len);
	return len;
}


//--------------�Լ� ����------------------//
// int Compare(char* str1, char* str2)
// �Լ��� : Compare
// ���   : �� ���ڿ��� ���� ��ġ�� ���ڸ� ���� �Ŀ� ������� ����ϴ� �Լ�
// �μ�   : ���ڿ� - char* str1, char* str2
// ���ϰ� : 1, 0, -1
// ����   : �� ���ڿ��� ���̴� �ٸ�����, ��� ������ ex) hell & hello
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

void test01()				//  ����Ű�� ���� ���ڿ� ���
{
	char* name[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	printf("���ڸ� �Է��ϼ���.\n");
	printf("���α׷��� �����÷��� 'Q'�� ��������.\n\n");
	while (1)
	{
		printf("<");
		char n = _getch();
		int m = n - 0x30; // ASCII���� num ������ ����.
		if (m >= 0 && m <= 9)
			printf("%c : %s\n", n, name[m]);
		else if (n == 'q' || n == 'Q')
			break;
	}

}
void test02()								// ���ڿ��� ���ڹ迭
{
	char ca[] = "Hello";						// ca[0] : H ���� ~ ca[5] : \0
	// int i <- ���� ǥ��, �ۿ��� ���� ���� �߾���� �Ѵ�.
	for (int i = 0; i < 10; i++)					// 0�������� 5����
	{
		printf("ca[%d]:%c (%02x)\n", i, ca[i], ca[i]);
	}
	ca[2] -= 1;
	ca[3] -= 1;

	for (int i = 0; i < 10; i++)					// 0�������� 5����
	{
		printf("ca[%d]:%c (%02x)\n", i, ca[i], ca[i]);
	}
}
void test03()						// �ǵ� : kBuf�� �̿��ؼ� ���� ���ڿ��� �޸𸮰����� ��� �� �ִ��� Ȯ���Ѵ�.(�������� ��ġ ����)
{
	char buf[100];						// ���� �޸� ���� Ȯ��
	char* pBuf;							// ���� �޸� ���� ���� ��� ��ġ
	unsigned int addr;					// ��� ��ġ ������ ���� �Է� ����(�ּ�)
	char kBuf[100];						// ��� ���ڿ� �Է� ���� Ȯ��


	printf("���� ������ �ּҴ� %d[%08x] �Դϴ�.\n", (unsigned)buf, (unsigned int)buf);
	printf("�Է��� ������ �ּҸ� �Է��ϼ��� : ");
	scanf("%d", &addr);					// �������� �ּ� ����
	pBuf = buf + addr;					// ����� ��ġ ����			
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf("%s", kBuf);
	Copy(pBuf, kBuf);					// ���ڿ� ����
	Dump(buf, 100);
}
void test04()			// �����͸� �̿��� ���ڿ� ����� �Լ�
{
	char* arr[10] = {"aaaaa","bbbb","ccc","dd", "e"};
	char buf[100];

	printf("[6] : "); scanf("%s", buf);
	arr[6] = buf;
	printf("[7] : "); scanf("%s", &buf[50]);
	arr[7] = &buf[50];
	for (int i = 0; i < 10; i++)
	{
		// arr[i]�� �� �ּ� ������ ��ȯ�� %x�� %s�� �ٸ��� ������ �ּҰ��� ���ڿ��� ������.
		printf("arr[%d] : 0x%08x %s\n", i, (unsigned int)arr[i], arr[i]);
	}
}
void test05()
{
	struct stTest
	{
		int i;
		float a;
		char * name;					// �ּҴ� ������ 8����Ʈ 64byte����! 
	} s1 = { 1, 3.14 };
	s1.name = "��õ���� �����";	// const �ּҷ� �� �� �ּҰ� name�� ���´�.

	typedef struct stTest st_test;

	struct stTest s2 = s1;
	//printf("%d\n", sizeof(s1.name));
	printf("sizeof(struct stTest) : %d\n", (int)sizeof(st_test)); // �ɹ� ������� �� ����Ʈ ���� �ǵ����ִ� �Լ�(��ũ��)�� sizeof �̴�.

	printf("struct stTset s1 : %d %f %s\n", s1.i, s1.a, s1.name);
	printf("struct stTset s2 : %d %f %s\n", s2.i, s2.a, s2.name);
}
void test06()
{
	//char* s1 = "Good";
	//char* s2 = "Afternoon";
	char buf[100];									// ��������(buf)�� �� Ȱ���ؾ� �Ѵ�.
	char* s1;										// ���� �ϸ� ��� ����Ű���� �𸣰� �������� ���� ����(Heap)�� ����Ų��.
	char* s2;
	//scanf("%s", s1`);								// Ȯ���� �ȵǾ� �ִ� �����̱� ������

	s1 = buf;
	s2 = buf + 50;
	scanf("%s", s1);
	scanf("%s", s2);
	/*
	scanf("%s", s1 = buf);							// buf�� �ּҰ� �Ѿ��.
	scanf("%s", s2 = buf + 50);						// buf�� 50�� ° �ּҿ� s2�� �ִ´�.
	*/
	// strcat Test
	printf("s1 : %s\n", s1);
	printf("s2 : %s\n", s2);
	/*
	printf("strcat(s1, s2) : %s\n", strcat(s1, s2));							// s1�� const ����(�������)�̶� ���� �Ұ��̴�.
	*/							
	// ����� 1) s1 , s2�� �ִ� ���� ���� �������� ������ �ͼ� ������ �� �Ŀ� ����� �Ѵ�.
	//		  2) printf���� �⺻ printf�� �ְ� fprintf(���Ϸ� ���)�� �ִ�.
	//		  3) sprintf(string printf) �� �ִ� sprintf�� buffer�� ����� �Ŵ� �Լ��̴�. 

	// strlen�� return�ϴ� ���� ���� \0(null) ��������.(= null�� ī��Ʈ���� �ʴ´�.)
	printf("s1 : %s(%d) \n", s1, strlen(s1));									
	printf("s2 : %s(%d) \n", s2, strlen(s2));
	strcpy(buf, s1);
	printf("strcat(s1, s2) : %s\n", strcat(buf, s2));

	// buf�� �ִ� ���� �޸� ������ ����� ��������. fprintf�� buf�� �ƴ� FILE* stream���� �����ϸ� ���� ������ �����Ѵ�.
	// sprintf(buf, "strcat(s1, s2) : %s%s\n", s1, s2);							// strcat(s1, s2);�� ����ϸ� �������ڿ��� ����Ű�� �ִ� s1�� const�� �����ϴ� ���� �Ұ����ؼ� ������ ���´�
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
	printf("������� 1, 0, -1�� ��µ˴ϴ�.\n���� ��Ȳ �� ���� ������ ��µ˴ϴ�.\n");
	printf("1�� ���ڿ��� �Է��ϼ���:");
	scanf("%s", buf1);
	printf("2�� ���ڿ��� �Է��ϼ���:");
	scanf("%s", buf2);

	asr = Compare(buf1, buf2);
	
	if (asr == 999999)
	{
		printf("<����>�� ���� �ڸ����� ���� �ʽ��ϴ�.�ڸ����� ���� �� �ٽ� �õ��Ͽ��ֽʽÿ�.\n\n");
	}
	else	printf("����� [%d]�Դϴ�.\n\n", asr);
}




int main(void)
{
	int n;
	void* p_arr[] = { test01, test02, test03, test04, test05, test06, Length, test08};			// Ÿ���� �������� ���� ������
	void (*p_func)();			// ���ϰ��� ���� ���ڰ� ������������ �Լ� ������ ����
	while (1)
	{
		printf("1. ����Ű�� ���� ���ڿ� ��� �̼�\n");
		printf("2. ���ڿ��� ���ڹ迭\n");
		printf("3. �������� ��ġ ����\n");
		printf("4. �����͸� �̿��� ���ڿ� ����� �Լ�\n");
		printf("5. ����ü �׽�Ʈ\n");
		printf("6. ǥ�� �Լ� �׽�Ʈ\n");
		printf("7. ���ڿ� ���� �׽�Ʈ\n");
		printf("8. ���ڿ� �� �׽�Ʈ\n");

		printf("0. ����\n");
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
			printf("����\n");
		}
		else if (c >= 0x41 && c <= 0x5a)
		{
			printf("�빮��\n");
		}
		else if (c >= 0x61 && c <= 0x7a)
		{
			printf("�ҹ���\n");
		}
		else if (c == 0x1b)
		{
			break;
		}
		else
		{
			printf("Ư������\n");
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