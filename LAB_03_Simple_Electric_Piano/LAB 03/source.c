/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 03
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 사용자로부터 키를 입력받아서 해당 키에 매핑되어있는 beep음을 재생하여
   전자 피아노를 연주할 수 있게 동작하는 프로그램입니다.
*************************************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#define DURATION 100			//음 연주 시 연주시간

int key_to_freq(char key);		//입력된 char형 자료를 매핑된 freqency로 변환해 주는 함수

void main(void)
{
	char ch;
	printf("\nSimple Electric Piano!!");
	printf("'A'~'J' : are mapped into C, D, E, F, G, A, B code in octave 8\n");
	printf("'Z'~'M' : are mapped into C, D, E, F, G, A, B code in octave 7\n");
	printf("'q'~'u' : are mapped into C, D, E, F, G, A, B code in octave 6\n");
	printf("'a'~'j' : are mapped into C, D, E, F, G, A, B code in octave 5\n");
	printf("'z'~'m' : are mapped into C, D, E, F, G, A, B code in octave 4\n");
	printf("input next key : \n");

	while ((ch = _getch()) != 27)				//키 입력 (ESC 감지 시 반복문 탈출)
	{
		if (key_to_freq(ch) != -1)				//key_to_freq 함수가 -1값을 리턴하는지를 판단하는 조건문
		{
			printf("input key (%c) : freq (%3d)\n", ch, key_to_freq(ch));
			Beep(key_to_freq(ch), DURATION);	//beep
		}
		else {
			printf("input key (%c) is wrong key input.....\n", ch);
		}
	}
}

int key_to_freq(char key)			//입력된 char형 자료를 매핑된 freqency로 변환해 주는 함수
{
	int freqTable[2][26] =			//MappingTable
	{ { 4186, 3136, 2637, 5274,   -1, 5588, 6272, 7040,   -1, 7902,   -1,   -1, 3951, 3520,   -1,   -1,   -1,   -1, 4699,   -1,   -1, 2794,   -1, 2349,   -1, 2093 },
		//   A,   B ,   C ,   D ,   E ,    F ,   G ,   H ,  I ,   J ,   K ,   L ,   M ,   N ,   O ,   P ,   Q ,   R  ,   S ,   T ,   U ,   V ,   W ,   X ,   Y ,   Z
	{ 523,  391,  330,  659, 1319,  698,  783,  880,   -1,  987,   -1,   -1,  494,  440,   -1,   -1, 1047, 1396,  587, 1568, 1976,  349, 1175,  294, 1760,  262 } };
	//   a,   b ,   c ,   d ,   e ,    f ,   g ,   h ,  i ,   j ,   k ,   l ,   m ,   n ,   o ,   p ,   q ,   r  ,   s ,   t ,   u ,   v ,   w ,   x ,   y ,   z

	if ((key >= 'a') && (key <= 'z'))				//a <= key <= z
	{
		return freqTable[key / 'a'][key - 'a'];
	}
	else if ((key >= 'A') && (key <= 'Z'))			//A <= key <= Z
	{
		return freqTable[key / 'a'][key - 'A'];
	}
	else {											//예외처리
		return -1;
	}
}