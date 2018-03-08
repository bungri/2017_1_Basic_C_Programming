/* Thread_EventGen.cpp (1) */
#include <Windows.h>
#include <time.h>

#include "Thread.h"
#include "PriorityQueue.h"
#include "Event.h"

DWORD WINAPI Thread_EventGenerator(LPVOID pParam)
{
	ThreadParam_Event *pThrdParam;
	PriQ_Event *pPriQ_Event;

	int myRole;

	THREAD_FLAG *pFlagThreadTerminate;

	int maxRound;

	Event *pEvent;
	int Event_id = 0;
	int Event_pri = 0;
	int Event_gen_count = 0;
	int targetEventGen;
	int myAddr = -1;
	int Event_dstAddr;

	ThreadStatusMonitor *pThrdMon;

	pThrdParam = (ThreadParam_Event *)pParam;
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen;

	srand(time(NULL));
	for (int round = 0; round < maxRound; round++)
	{
		if (Event_gen_count >= targetEventGen)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)
				break;
			else {
				Sleep(500);
				continue;
			}
		}

		pEvent = (Event *)malloc(sizeof(Event));
		//pEvent->srcAddr = myAddr;
		//pEvent->dstAddr = Event_dstAddr = rand() % NUM_ROUTERS;
		//pEvent->Event_id = Event_gen_count;
		//pEvent->Event_priority = Event_pri = rand() % NUM_PRIORITY;
		//pEvent->Event_priority = Event_pri = targetEventGen - Event_gen_count - 1;
		//pEvent->seqNo = Event_gen_count;
		pEvent->event_gen_addr = myAddr;
		pEvent->event_handler_addr = rand() % 20;
		pEvent->event_no = round;
		pEvent->event_pri = rand() % 20;
		pEvent->eventStatus = GENERATED;

		while (insertPriQ_Event(pPriQ_Event, pEvent) == -1)
		{
			Sleep(500);
		}

		EnterCriticalSection(pThrdParam->pCS_thrd_mon);
		pThrdMon->numEventGenerated[myAddr]++;
		pThrdMon->totalEventGenerated++;
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon);

		Event_gen_count++;
		//Sleep(100 + rand() % 300);
		Sleep(10);
	}
	return 0;
}