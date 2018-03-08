/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 04-2
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 콘솔창에 16가지의 background color와 16가지의 foreground color 를 지정하여
   총 256가지의 배경색-문자색을 화면에 표시하는 동작을 수행하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>
#include <Windows.h>

void textColor(unsigned short background, unsigned short foreground);			//콘솔창 문자열 출력 색 변경 함수

int main(void)
{
	char *colors[16] = { "0:Black", "1:Blue", "2:Green", "3:Aqua", "4:Red", "5:Purple", "6:Yellow", "7:White",
						 "8:Gray", "9:Light Blue", "10:Light Green", "11:LightAqua", "12:Light Red",
						 "13:Light Purple", "14:Light Yellow", "15: Birght White"};

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			textColor(i, j);
			printf("Text color testing [(bg_color : %02X, fg_color : %02X) ==> color[%02X]\n", i, j, i | (j << 4));
		}
	}
	textColor(0, 15);			//원대래로 변경

	return 0;
}

void textColor(unsigned short background, unsigned short foreground)			//콘솔창 문자열 출력 색 변경 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground | (background << 4));
}