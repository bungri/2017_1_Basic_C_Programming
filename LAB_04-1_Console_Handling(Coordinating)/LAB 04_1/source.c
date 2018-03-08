/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 04-1
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 gotoxy()함수를 사용하여 좌표 범위를 나타내는 직사각형을 그리고
   x축으로 20칸, y축으로 10칸 간격으로 좌표(x,y)값을 출력하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y);				//gotoxy()함수의 원형 선언

int main(void)
{
	for (int width = 5; width <= 185; width++)
	{
		for (int height = 5; height <= 55; height++)
		{
			if (((width == 5) || (width == 185)) && ((height == 5) || (height == 55)))	//사각형의 모서리에 점을 찍기 위한 조건식
			{
				gotoxy(width, height);
				printf("*");
			}
			if (((width > 5) && (width < 185)) && ((height == 5) || (height == 55)))	//사각형의 가로변을 표시하기 위한 조건식
			{
				gotoxy(width, height);
				printf("-");
			}
			if (((height > 5) && (height < 55)) && ((width == 5) || (width == 185)))	//사각형의 세로변을 표시하기 위한 조건식
			{
				gotoxy(width, height);
				printf("|");
			}
			if (((height - 5) % 10 == 0) && ((width - 5) % 20 == 0))					//좌표를 표시하기 위한 조건식
			{
				gotoxy(width + 1, height + 1);
				printf("(%3d,%3d)", width, height);
			}

		}
	}
	printf("\n");
	return 0;
}

void gotoxy(int x, int y)				//gotoxy() 함수
{
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coords = { (short)x, (short)y };
	SetConsoleCursorPosition(consoleHandler, coords);
}
