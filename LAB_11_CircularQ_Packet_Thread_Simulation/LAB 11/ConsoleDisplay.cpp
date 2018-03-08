/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 11
 * ���ϸ� : ConsoleDisplay.cpp
 * ���α׷��� ���� �� �⺻ ���
   �� ������ Thread Monitoring�� �ʿ��� ��Ȳ���� ����ϴµ��� �ʿ��� �Լ��� ��ü�� ������
   .cpp �����Դϴ�.
*************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
//#include "ConsoleDisplay.h"

HANDLE consoleHandler; // use as a global variable
HANDLE initConsoleHandler()
{
	HANDLE stdCnslHndlr;
	stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
	consoleHandler = stdCnslHndlr;
	return stdCnslHndlr;
}

void closeConsoleHandler(HANDLE hndlr)
{
	CloseHandle(hndlr);
}

int gotoxy(HANDLE consoleHandler, int x, int y)
{
	if (consoleHandler == INVALID_HANDLE_VALUE)
		return 0;
	COORD coords = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(consoleHandler, coords);
	return 1;
}

void printErrorMessage(char *str)
{
	printf("%s is Error\n", str);
}