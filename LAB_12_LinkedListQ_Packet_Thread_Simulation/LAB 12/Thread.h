#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include "LinkedList_Queue.h"

enum ROLE {
	LINK_TX,
	PKT_GEN
};
enum THREAD_FLAG {
	RUN,
	TERMINATE
};

typedef struct ThreadStatusMonitor
{
	int numPktGens;
	int numPktProcs;
	int numPktProcs_priH;
	int numPktProcs_priL;
	THREAD_FLAG *pFlagThreadTerminate;
	Packet *pPktProc;
}ThreadStatusMonitor;

typedef struct ThreadParam
{
	CRITICAL_SECTION *pCS_main;
	CRITICAL_SECTION *pCS_thrd_mon;
	LL_PacketQ *pPriH_LLQ;
	LL_PacketQ *pPriL_LLQ;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetPktGen;
	ThreadStatusMonitor *pThrdMon;
} ThreadParam_Pkt;

DWORD WINAPI Thread_LinkTx(LPVOID pParam);
DWORD WINAPI Thread_PktGen(LPVOID pParam);

#endif