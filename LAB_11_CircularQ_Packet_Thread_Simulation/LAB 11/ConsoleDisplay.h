/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : CircularQueue.h
 * 프로그램의 목적 및 기본 기능
   이 파일은 Thread Monitoring을 위한 Console Display에 관련된
   구조체와 함수의 프로토타입을 정의한 header 파일입니다.
*************************************************************************************************/

#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();
void closeConsoleHandler(HANDLE hndlr);

int gotoxy(HANDLE consoleHandler, int x, int y); // move cursor to (x, y) coordinate 
//int coord_x(HANDLE consoleHandler); // returns the x-axis cursor 
//int coord_y(HANDLE consoleHandler); // returns the y-axis cursor 
void printErrorMessage(char *str);

#endif