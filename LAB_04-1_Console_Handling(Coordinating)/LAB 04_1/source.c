/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 04-1
 * ���ϸ� : source.c
 * ���α׷��� ���� �� �⺻ ���
   �� ���α׷��� gotoxy()�Լ��� ����Ͽ� ��ǥ ������ ��Ÿ���� ���簢���� �׸���
   x������ 20ĭ, y������ 10ĭ �������� ��ǥ(x,y)���� ����ϴ� ���α׷��Դϴ�.
*************************************************************************************************/
#include <stdio.h>
#include <Windows.h>

void gotoxy(int x, int y);				//gotoxy()�Լ��� ���� ����

int main(void)
{
	for (int width = 5; width <= 185; width++)
	{
		for (int height = 5; height <= 55; height++)
		{
			if (((width == 5) || (width == 185)) && ((height == 5) || (height == 55)))	//�簢���� �𼭸��� ���� ��� ���� ���ǽ�
			{
				gotoxy(width, height);
				printf("*");
			}
			if (((width > 5) && (width < 185)) && ((height == 5) || (height == 55)))	//�簢���� ���κ��� ǥ���ϱ� ���� ���ǽ�
			{
				gotoxy(width, height);
				printf("-");
			}
			if (((height > 5) && (height < 55)) && ((width == 5) || (width == 185)))	//�簢���� ���κ��� ǥ���ϱ� ���� ���ǽ�
			{
				gotoxy(width, height);
				printf("|");
			}
			if (((height - 5) % 10 == 0) && ((width - 5) % 20 == 0))					//��ǥ�� ǥ���ϱ� ���� ���ǽ�
			{
				gotoxy(width + 1, height + 1);
				printf("(%3d,%3d)", width, height);
			}

		}
	}
	printf("\n");
	return 0;
}

void gotoxy(int x, int y)				//gotoxy() �Լ�
{
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coords = { (short)x, (short)y };
	SetConsoleCursorPosition(consoleHandler, coords);
}
