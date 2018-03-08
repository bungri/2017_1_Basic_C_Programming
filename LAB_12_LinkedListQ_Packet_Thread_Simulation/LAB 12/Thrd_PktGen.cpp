#include <Windows.h>
#include <time.h>

#include "Thread.h"
#include "LinkedList_Queue.h"
#include "Packet.h"

DWORD WINAPI Thread_PktGen(LPVOID pParam)
{
	ThreadParam_Pkt *pThrdParam;
	LL_PacketQ *pPriH_LLQ, *pPriL_LLQ, *pLL_PktQ;
	int myRole;
	THREAD_FLAG *pFlagThreadTerminate;
	int maxRound;
	Packet *pM;
	int Pkt_id = 0;
	int Pkt_pri = 0;
	int Pkt_gen_count = 0;
	int targetPktGen;
	int myAddr;

	ThreadStatusMonitor *pThrdMon;
	pThrdParam = (ThreadParam_Pkt *)pParam;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriH_LLQ = pThrdParam->pPriH_LLQ;
	pPriL_LLQ = pThrdParam->pPriL_LLQ;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetPktGen = pThrdParam->targetPktGen;

	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)
	{
		if (Pkt_gen_count >= targetPktGen)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				Sleep(500);
				continue;
			}
		}
		Pkt_pri = rand() % NUM_PRIORITY;
		pM = (Packet *)malloc(sizeof(Packet));
		pM->pkt_id = Pkt_gen_count;

		pM->srcAddr = myAddr;
		pM->dstAddr = round % 10;

		pM->pkt_priority = Pkt_pri;
		pLL_PktQ = (Pkt_pri == 0) ? pPriH_LLQ : pPriL_LLQ;
		while (enLL_PktQ(pLL_PktQ, pM) == -1)
		{
			Sleep(100);
		}
		EnterCriticalSection(pThrdParam->pCS_thrd_mon);
		pThrdMon->numPktGens++;
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		Pkt_gen_count++;
		Sleep(100 + rand() % 300);
	}
	return 0;
}