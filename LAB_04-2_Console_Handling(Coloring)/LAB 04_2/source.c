/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 04-2
 * ���ϸ� : source.c
 * ���α׷��� ���� �� �⺻ ���
   �� ���α׷��� �ܼ�â�� 16������ background color�� 16������ foreground color �� �����Ͽ�
   �� 256������ ����-���ڻ��� ȭ�鿡 ǥ���ϴ� ������ �����ϴ� ���α׷��Դϴ�.
*************************************************************************************************/
#include <stdio.h>
#include <Windows.h>

void textColor(unsigned short background, unsigned short foreground);			//�ܼ�â ���ڿ� ��� �� ���� �Լ�

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
	textColor(0, 15);			//���뷡�� ����

	return 0;
}

void textColor(unsigned short background, unsigned short foreground)			//�ܼ�â ���ڿ� ��� �� ���� �Լ�
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground | (background << 4));
}