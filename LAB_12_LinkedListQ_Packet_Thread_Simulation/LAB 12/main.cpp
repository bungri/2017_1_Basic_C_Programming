/* main_PacketGen_LL_PacketQ_PacketProc.cpp */
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Thread.h"
#include "LinkedList_Queue.h"
#include "Packet.h"
#include "ConsoleDisplay.h"

#define NUM_PKT_GEN 20
#define MAX_ROUND 1000

void main()
{
	LL_PacketQ highPri_LL_PktQ, lowPri_LL_PktQ;
	ThreadParam thrdParam_PktGen, thrdParam_LinkTx;

	HANDLE hThrd_PktGen, hThrd_LinkTx;

	CRITICAL_SECTION cs_main;
	CRITICAL_SECTION cs_thrd_mon;

	ThreadStatusMonitor thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG msgThreadFlag = RUN;

	int count, numPktProcessed;

	Packet *pPkt, pktProcessed[NUM_PKT_GEN];

	InitializeCriticalSection(&cs_main);
	InitializeCriticalSection(&cs_thrd_mon);

	initLL_PktQ(&highPri_LL_PktQ, 0); // high priority
	initLL_PktQ(&lowPri_LL_PktQ, 1); // low priority

	consHndlr = initConsoleHandler();

	thrdMon.numPktGens = 0;
	thrdMon.numPktProcs = 0;
	thrdMon.numPktProcs_priH = 0;
	thrdMon.numPktProcs_priL = 0;
	thrdMon.pFlagThreadTerminate = &msgThreadFlag;
	thrdMon.pPktProc = pktProcessed;

	for (int m = 0; m < NUM_PKT_GEN; m++)
	{
		pktProcessed[m].pkt_id = -1;
		pktProcessed[m].pkt_priority = -1;
	}

	/* Create and Activate Thread_PacketProc */
	thrdParam_LinkTx.role = LINK_TX;
	thrdParam_LinkTx.myAddr = 0; // link address
	thrdParam_LinkTx.pCS_main = &cs_main;
	thrdParam_LinkTx.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_LinkTx.pPriH_LLQ = &highPri_LL_PktQ;
	thrdParam_LinkTx.pPriL_LLQ = &lowPri_LL_PktQ;
	thrdParam_LinkTx.maxRound = MAX_ROUND;
	thrdParam_LinkTx.pThrdMon = &thrdMon;
	hThrd_LinkTx = CreateThread(NULL, 0, Thread_LinkTx, &thrdParam_LinkTx, 0, NULL);

	EnterCriticalSection(&cs_main);
	printf("Thread_PacketGen is created and activated ...\n");
	LeaveCriticalSection(&cs_main);

	/* Create and Activate Thread_PacketGen */
	thrdParam_PktGen.role = PKT_GEN;
	thrdParam_PktGen.myAddr = 0; // my Address
	thrdParam_PktGen.pCS_main = &cs_main;
	thrdParam_PktGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_PktGen.pPriH_LLQ = &highPri_LL_PktQ;
	thrdParam_PktGen.pPriL_LLQ = &lowPri_LL_PktQ;
	thrdParam_PktGen.targetPktGen = NUM_PKT_GEN;
	thrdParam_PktGen.maxRound = MAX_ROUND;
	thrdParam_PktGen.pThrdMon = &thrdMon;
	hThrd_PktGen = CreateThread(NULL, 0, Thread_PktGen, &thrdParam_PktGen, 0, NULL);

	EnterCriticalSection(&cs_main);
	printf("Thread_PacketGen is created and activated ...\n");
	LeaveCriticalSection(&cs_main);

	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main);
		system("cls");

		gotoxy(consHndlr, 0, 0);
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current pkt_gen (%2d), pkt_proc(%2d), pkt_high_pri(%2d), pkt_low_pri(% 2d)\n", round, thrdMon.numPktGens, thrdMon.numPktProcs,	thrdMon.numPktProcs_priH, thrdMon.numPktProcs_priL);
		printf(" PriH_LL_PacketQ::"); printLL_PktQ(&highPri_LL_PktQ); printf("\n");
		printf(" PriL_LL_PacketQ::"); printLL_PktQ(&lowPri_LL_PktQ); printf("\n");
		printf(" Packets processed: \n");

		count = 0;

		numPktProcessed = thrdMon.numPktProcs;
		for (int m = 0; m < numPktProcessed; m++)
		{
			//pPkt = thrdMon.ppPktsg[m];
			pPkt = &pktProcessed[m];
			if (pPkt != NULL)
			{
				printPacket(pPkt);
				if (m < numPktProcessed - 1)
					printf(", ");
				if (((m + 1) % 5) == 0)
					printf("\n");
			}
		}

		printf("\n");
		if (thrdMon.numPktProcs >= NUM_PKT_GEN)
		{
			msgThreadFlag = TERMINATE; // set 1 to terminate threads
			break;
		}
		LeaveCriticalSection(&cs_main);
		Sleep(100);
	}

	DWORD nExitCode = NULL;

	WaitForSingleObject(hThrd_PktGen, INFINITE);
	EnterCriticalSection(&cs_main);
	printf("Thread_PacketGen is terminated !!\n");
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hThrd_PktGen, &nExitCode);
	TerminateThread(hThrd_PktGen, nExitCode);
	CloseHandle(hThrd_PktGen);

	WaitForSingleObject(hThrd_LinkTx, INFINITE);
	EnterCriticalSection(&cs_main);
	printf("Thread_LinkTx is terminated !!\n");
	LeaveCriticalSection(&cs_main);
	GetExitCodeThread(hThrd_LinkTx, &nExitCode);
	TerminateThread(hThrd_LinkTx, nExitCode);
	CloseHandle(hThrd_LinkTx);

	//printf("For debugging only :: press any key to terminate ..\n");
	//getc(stdin);
}