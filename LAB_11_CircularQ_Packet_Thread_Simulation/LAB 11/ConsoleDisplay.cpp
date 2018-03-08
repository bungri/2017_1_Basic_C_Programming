/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : ConsoleDisplay.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 Thread Monitoring에 필요한 상황판을 출력하는데에 필요한 함수의 몸체를 정의한
   .cpp 파일입니다.
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