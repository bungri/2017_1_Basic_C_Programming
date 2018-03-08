/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 11
 * ���ϸ� : CircularQueue.h
 * ���α׷��� ���� �� �⺻ ���
   �� ������ Thread Monitoring�� ���� Console Display�� ���õ�
   ����ü�� �Լ��� ������Ÿ���� ������ header �����Դϴ�.
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