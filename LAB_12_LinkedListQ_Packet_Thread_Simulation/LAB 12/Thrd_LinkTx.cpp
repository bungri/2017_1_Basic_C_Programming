#include <Windows.h>
#include <time.h>

#include "Thread.h"
#include "LinkedList_Queue.h"
#include "Packet.h"

DWORD WINAPI Thread_LinkTx(LPVOID pParam)
{
	ThreadParam_Pkt *pThrdParam;
	LL_PacketQ *pPriH_LLQ, *pPriL_LLQ, *pLL_PktQ;
	int myRole;
	THREAD_FLAG *pFlagThreadTerminate;
	int maxRound;
	Packet *pM, *pPktProc;
	int Pkt_id = 0, Pkt_pri = 0, Pkt_gen_count = 0, num_Pkt_processed = 0;
	int targetPktGen;

	ThreadStatusMonitor *pThrdMon;
	pThrdParam = (ThreadParam_Pkt *)pParam;
	myRole = pThrdParam->role;
	pPriH_LLQ = pThrdParam->pPriH_LLQ;
	pPriL_LLQ = pThrdParam->pPriL_LLQ;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	pPktProc = pThrdParam->pThrdMon->pPktProc;
	targetPktGen = pThrdParam->targetPktGen;

	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		while ((pM = deLL_PktQ(pPriH_LLQ)) != NULL)
		{
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);
			pPktProc[pThrdMon->numPktProcs] = *pM;
			pThrdMon->numPktProcs++;
			pThrdMon->numPktProcs_priH++;
			free(pM);
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
			Sleep(300 + rand() % 500);
		} // end while
		if ((pM = deLL_PktQ(pPriL_LLQ)) != NULL)
		{
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);
			pPktProc[pThrdMon->numPktProcs] = *pM;
			pThrdMon->numPktProcs++;
			pThrdMon->numPktProcs_priL++;
			free(pM);
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		}
		Sleep(300 + rand() % 500);
	}
	return 0;
}