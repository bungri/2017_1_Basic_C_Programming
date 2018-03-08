#include <Windows.h>
#include <time.h>
#include "Thread.h"
#include "PriorityQueue.h"
#include "Event.h"
DWORD WINAPI Thread_EventHandler(LPVOID pParam)
{
	ThreadParam_Event *pThrdParam;
	PriQ_Event *pPriQ_Event;

	int myRole;

	THREAD_FLAG *pFlagThreadTerminate;

	int maxRound;

	Event *pEvent, *pEventProc;

	int Event_id = 0;
	int Event_pri = 0;
	int Event_gen_count = 0;
	int num_Event_processed = 0;
	int myAddr = -1;

	int targetEventGen;

	ThreadStatusMonitor *pThrdMon;

	pThrdParam = (ThreadParam_Event *)pParam;

	myRole = pThrdParam->role;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	myAddr = pThrdParam->myAddr;

	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	pEventProc = pThrdParam->pThrdMon->eventProcessed;
	targetEventGen = pThrdParam->targetEventGen;
	srand(time(NULL));

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
			break;
		if ((pEvent = removeMinPriQ_Event(pPriQ_Event)) != NULL)
		{
			//printf("Thread_LinkTx::removeMinPriQ_Event() : ");
			//printEvent(pEvent);
			//printf("₩n");
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);
			//pThrdMon->ppEventsg[pThrdMon->numEventProcs] = pEvent;
			pEventProc[pThrdMon->totalEventProcessed] = *pEvent;
			pThrdMon->numEventProcessed[myAddr]++;
			pThrdMon->totalEventProcessed++;
			free(pEvent);
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);
		}
		Sleep(300 + rand() % 500);
	}
	return 0;
}