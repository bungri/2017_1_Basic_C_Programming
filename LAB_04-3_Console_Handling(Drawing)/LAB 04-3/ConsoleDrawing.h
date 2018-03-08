/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 04-3
 * 파일명 : ConsoleDrawing.h
 * 프로그램의 목적 및 기본 기능
   이 header 파일  콘솔창에 drawing pane를 그리는 역할을 수행하며,
   saw-tooth, sine, cosine, tangent 그래프를 그리는 함수를 포함하고 있습니다.
*************************************************************************************************/
#include <stdio.h>
#include <Windows.h>
#include <math.h>


#define DP_WIDTH 180
#define DP_HEIGHT 50
#define DP_X_MARGIN 5
#define DP_Y_MARGIN 5
#define X_BASE DP_X_MARGIN
#define Y_BASE (DP_HEIGHT/2 + DP_Y_MARGIN)
#define MAX_Y (DP_HEIGHT + DP_Y_MARGIN)
#define MAX_X (X_BASE + DP_WIDTH)

#define PI 3.141592653589

void gotoxy(int x, int y)
{
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD coords = { (short)x, (short)y };
	COORD coords = { (short)x, (short)y };
	SetConsoleCursorPosition(consoleHandler, coords);
}

void textColor(unsigned short background, unsigned short foreground)			//콘솔창 문자열 출력 색 변경 함수
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground | (background << 4));
}

void drawing_pane(void)
{
	textColor(0, 11);

	for (int width = DP_X_MARGIN; width <= MAX_X; width++)
	{
		for (int height = DP_Y_MARGIN; height <= MAX_Y; height++)
		{
			if (((width == DP_X_MARGIN) || (width == MAX_X)) && ((height == DP_Y_MARGIN) || (height == MAX_Y)))	//사각형의 모서리에 점을 찍기 위한 조건식
			{
				gotoxy(width, height);
				printf("*");
			}

			if (((width > DP_X_MARGIN) && (width < MAX_X)) && ((height == DP_Y_MARGIN) || (height == MAX_Y)))	//사각형의 가로변을 표시하기 위한 조건식
			{
				gotoxy(width, height);
				if ((width + DP_X_MARGIN) % 10 == 0)
				{
					printf("|");
				}
				else {
					printf("-");
				}
			}

			if (((height > DP_Y_MARGIN) && (height < MAX_Y)) && ((width == DP_X_MARGIN) || (width == MAX_X)))	//사각형의 세로변을 표시하기 위한 조건식
			{
				gotoxy(width, height);
				printf("|");
			}

			if ((width == DP_X_MARGIN) && (height % 5 == 0))
			{
				gotoxy(width, height);
				printf("*");
				gotoxy(width - 3, height);
				printf("%3d", Y_BASE - height);
			}

			if (height == Y_BASE)
			{
				if ((width == DP_X_MARGIN) || (width == MAX_X))
				{
					gotoxy(width, height);
					printf("*");
					gotoxy(width + 1, height + 1);
					printf("%d", width - X_BASE);
				}
				else {
					if ((width + DP_X_MARGIN) % 10 == 0)
					{
						gotoxy(width, height);
						printf("|");
						gotoxy(width + 1, height + 1);
						printf("%d", width - X_BASE);
					}
					else {
						gotoxy(width, height);
						printf("-");
					}
				}
			}
		}
	}
	printf("\n\n");
}

double deg_to_rad(int degree)
{
	double radian = 0;
	radian = degree * (PI / 180);
	return radian;
}

void saw_tooth(int amp, int freq)
{
	textColor(0, 12);

	double Gradient = amp / (DP_WIDTH / (freq * 4));
	int decent = 0;
	int cycle = 0;

	for (int num = 0, cycle = 0; num <= freq; num++, cycle += (DP_WIDTH / freq))
	{
		for (int x = X_BASE, y = Y_BASE; x <= MAX_X; x++)
		{
			if ((x >= X_BASE + cycle) && (x < (X_BASE + (DP_WIDTH / (freq * 4)) + cycle)))
			{
				y -= Gradient;
				gotoxy(x, y);
				printf("*");

			}
			else if ((x > (X_BASE + (DP_WIDTH / (freq * 4))) + cycle) && (x < (X_BASE + ((3 * DP_WIDTH) / (freq * 4)) + cycle)))
			{
				y += Gradient;
				gotoxy(x, y);
				printf("*");

			}
			else if ((x > (X_BASE + ((3 * DP_WIDTH) / (freq * 4))) + cycle) && (x < (X_BASE + (DP_WIDTH / freq) + cycle)))
			{
				y -= Gradient;
				gotoxy(x, y);
				printf("*");
			}
		}

	}


	textColor(0, 15);
	gotoxy(0, MAX_Y + 1);

}

void sin_gr(int amp, int freq)
{
	textColor(0, 12);
	double deg = 0;
	for (int x = X_BASE, y = 0; x <= MAX_X; x++)
	{
		y = Y_BASE - amp*sin(deg_to_rad(deg));
		gotoxy(x, y);
		printf("*");

		deg += (360 * freq) / DP_WIDTH;
	}

	textColor(0, 15);
	gotoxy(0, MAX_Y + 1);
}

void cos_gr(int amp, int freq)
{
	textColor(0, 12);
	double deg = 0;
	for (int x = X_BASE, y = 0; x <= MAX_X; x++)
	{
		y = Y_BASE - amp*cos(deg_to_rad(deg));
		gotoxy(x, y);
		printf("*");

		deg += (360 * freq) / DP_WIDTH;
	}

	textColor(0, 15);
	gotoxy(0, MAX_Y + 1);
}

void tan_gr(int amp, int freq)
{
	textColor(0, 12);
	double deg = 0;
	for (int x = X_BASE, y = 0; x <= MAX_X; x++)
	{
		y = Y_BASE - amp*tan(deg_to_rad(deg));
		gotoxy(x, y);
		printf("*");

		deg += (360 * freq) / DP_WIDTH;
	}

	textColor(0, 15);
	gotoxy(0, MAX_Y + 1);
}

