/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 11
 * ���ϸ� : ThreadManagement.cpp
 * ���α׷��� ���� �� �⺻ ���
   �� ������ Thread���� ����� CriticalSection�� Initialize�ϴ� �Լ��� Thread�� status��
   ��Ȳ�ǿ� ����ϴ� �Լ��� ���Ե� .cpp �����Դϴ�.
*************************************************************************************************/

#include <stdio.h> 
#include "ThreadManagement.h" 
#include "SimParams.h" 
#include "ConsoleDisplay.h" 
#include "CircularQueue.h"

char*strThrdStatus[] = {
	"INITIALIZING",
	"RUNNING",
	"TERMINATING"
};

void initializeCriticalSections(CriticalSections*pCS)
{
	InitializeCriticalSection(&pCS->cs_consoleDisplay);
	InitializeCriticalSection(&pCS->cs_linkStatusUpdate);
	InitializeCriticalSection(&pCS->cs_pktGenStatusUpdate);
	InitializeCriticalSection(&pCS->cs_pkt_tbl);
}

void printThreadStatus(HANDLE consoleHandler, int main_thread_round, ThreadStatus*pThreadStatus)
{
	int pos_x = 0;
	int pos_y = 1;
	int total_rx, total_generated, total_forwarded;
	char strThreadStatus[50];
	if (pThreadStatus->thread_role == PACKET_GENERATOR)
	{
		system("cls");
		pos_x = 0;
		pos_y = 0;
		gotoxy(consoleHandler, pos_x, pos_y);
		printf("Packet Generator Threads Status (at main_threadround %3d)\n", main_thread_round);
		printf("|-----------------------------------|\n");
		printf("| Node | status |   round | PktGen  |\n");
		printf("|------+--------+---------+---------|\n");

		for (int node = 0; node < 1; node++)
		{
			printf("| %4d |", node);
			printf("  %5d |", pThreadStatus->thrdStatus);
			printf("  %5d  |", pThreadStatus->round);
			printf("  %5d  |\n", pThreadStatus->pkts_proc.num_PktGen);
			printf("|------+--------+---------+---------|\n");
		}

		printf("Note) Packet_Genthread status: INITIALIZING (0), RUNNING (1), UNDER_TERMINATING (2), THREAD_TERMINATED (3)\n");
		printf("Total %3d packets are generated\n ", pThreadStatus->pkts_proc.num_PktGen);
	}
	else if (pThreadStatus->thread_role == LINK_TX)
	{
		pos_x = 0;
		pos_y = 6 + 1 * 2;
		gotoxy(consoleHandler, pos_x, pos_y);
		printf("\nLink_TxThreads Status (at main_threadround %3d)\n", main_thread_round); // loof count
		printf("|-----------------------------------|\n");
		printf("| Link | status |   round | PktFwrd |\n");
		printf("|------+-------+---------+----------|\n");

		for (int link = 0; link < 1; link++)
		{
			printf("| %4d |", link);
			printf("  %5d |", pThreadStatus->thrdStatus);
			printf("  %5d  |", pThreadStatus->round);
			printf("  %5d  |\n", pThreadStatus->pkts_proc.num_PktFwrd);
			printf("|------+--------+---------+---------|\n");
		}

		printf("Note) Link thread status: INITIALIZING (0), RUNNING (1), UNDER_TERMINATING (2), THREAD_TERMINATED (3)\n");
		printf("Total %3d packets are forwarded\n ", pThreadStatus->pkts_proc.num_PktFwrd);

	}

}