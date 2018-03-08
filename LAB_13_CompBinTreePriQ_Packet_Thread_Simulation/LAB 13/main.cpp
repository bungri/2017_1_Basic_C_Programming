#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#include "Thread.h"
#include "PriorityQueue.h"
#include "Event.h"
#include "ConsoleDisplay.h"

//#define TEST_PRIORITY_QUEUE
#define TEST_EVENT_GEN_PRIQ_HANDLER

void main()
{
	PriQ_Event priQ_Pkt;
	Event *pEvent;
	int myAddr = 0;
	int pkt_event_handler_addr, eventPriority;
	initPriQ_Event(&priQ_Pkt, PRI_QUEUE_CAPACITY);

#ifdef TEST_PRIORITY_QUEUE
	for (int i = 0; i<PRIQ_PKT_SIZE; i++)
	{
		pEvent = (Event *)malloc(sizeof(Event));
		pEvent->event_gen_addr = myAddr;
		pEvent->event_no = i;
		pEvent->event_pri = eventPriority = rand() % NUM_PRIORITY;
		if (insertPriQ_Event(&priQ_Pkt, pEvent) == -1)
		{
			printf("Error in insertPriQ_Event() !!\n");
		}
	}
	printf("Priority Queue after %d insertPriQ_Event_Pkt(): \n", PRIQ_PKT_SIZE);
	printPriQ_Event(&priQ_Pkt);
	for (int i = 0; i < PRIQ_PKT_SIZE; i++)
	{
		pEvent = removeMinPriQ_Event(&priQ_Pkt);
		pEvent->event_handler_addr = i % NUM_EVENT_HANDLERS;
		printf("Result of removePriQ_Event():: "); printEvent(pEvent); printf("\n");
		printf("Priority Queue after removePriQ_Event(): \n");
		printPriQ_Event(&priQ_Pkt);
	}
#endif

#ifdef TEST_EVENT_GEN_PRIQ_HANDLER
	ThreadParam_Event thrdParam_EventGen[NUM_EVENT_GENERATORS], thrdParam_EventHndlr[NUM_EVENT_HANDLERS];
	HANDLE hThrd_EventGenerator[NUM_EVENT_GENERATORS], hThrd_EventHandler[NUM_EVENT_HANDLERS];
	CRITICAL_SECTION cs_main;
	CRITICAL_SECTION cs_thrd_mon;
	ThreadStatusMonitor thrdMon;
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int count, numEventProcessed;
	Event eventProcessed[TOTAL_NUM_EVENTS];

	InitializeCriticalSection(&cs_main);
	InitializeCriticalSection(&cs_thrd_mon);

	consHndlr = initConsoleHandler();

	thrdMon.pFlagThreadTerminate = &eventThreadFlag;

	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;

	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].event_no = -1; // mark as not-processed
		thrdMon.eventProcessed[ev].event_pri = -1;
	}
	/* Create and Activate Thread_EventHandlers */
	for (int evntHndlr = 0; evntHndlr < NUM_EVENT_HANDLERS; evntHndlr++)
	{
		thrdMon.numEventProcessed[evntHndlr] = 0;

		thrdParam_EventHndlr[evntHndlr].role = EVENT_HANDLER;
		thrdParam_EventHndlr[evntHndlr].myAddr = evntHndlr; // link address
		thrdParam_EventHndlr[evntHndlr].pCS_main = &cs_main;
		thrdParam_EventHndlr[evntHndlr].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventHndlr[evntHndlr].pPriQ_Event = &priQ_Pkt;
		thrdParam_EventHndlr[evntHndlr].maxRound = MAX_ROUND;
		thrdParam_EventHndlr[evntHndlr].pThrdMon = &thrdMon;

		hThrd_EventHandler[evntHndlr] = CreateThread(NULL, 0, Thread_EventHandler, &thrdParam_EventHndlr[evntHndlr], 0, NULL);

		EnterCriticalSection(&cs_main);
		printf("Thread_EventGen is created and activated ...\n");
		LeaveCriticalSection(&cs_main);
	}
	/* Create and Activate Thread_EventGen */
	for (int evntGen = 0; evntGen < NUM_EVENT_GENERATORS; evntGen++)
	{
		thrdMon.numEventGenerated[evntGen] = 0;

		thrdParam_EventGen[evntGen].role = EVENT_GENERATOR;
		thrdParam_EventGen[evntGen].myAddr = evntGen; // my Address
		thrdParam_EventGen[evntGen].pCS_main = &cs_main;
		thrdParam_EventGen[evntGen].pCS_thrd_mon = &cs_thrd_mon;
		thrdParam_EventGen[evntGen].pPriQ_Event = &priQ_Pkt;
		thrdParam_EventGen[evntGen].targetEventGen = NUM_EVENTS_PER_GEN;
		thrdParam_EventGen[evntGen].maxRound = MAX_ROUND;
		thrdParam_EventGen[evntGen].pThrdMon = &thrdMon;

		hThrd_EventGenerator[evntGen] = CreateThread(NULL, 0, Thread_EventGenerator, &thrdParam_EventGen[evntGen], 0, NULL);

		EnterCriticalSection(&cs_main);
		printf("Thread_EventGen (%d) is created and activated ...\n", evntGen);
		LeaveCriticalSection(&cs_main);
	}
	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main);
		system("cls");
		gotoxy(consHndlr, 0, 0);

		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n");

		for (int evntGen = 0; evntGen < NUM_EVENT_GENERATORS; evntGen++)
		{
			printf("Event_Gen(%2d) generated %2d events\n", evntGen, thrdMon.numEventGenerated[evntGen]);
		}
		for (int evntHndlr = 0; evntHndlr < NUM_EVENT_HANDLERS; evntHndlr++)
		{
			printf("Event_Handler(%2d) processed %2d events\n", evntHndlr, thrdMon.numEventProcessed[evntHndlr]);
		}
		printf("\n");

		printf("Priority_Queue_Event::"); printPriQ_Event(&priQ_Pkt);
		printf("\n");
		printf("Events processed: \n ");

		count = 0;

		numEventProcessed = thrdMon.totalEventProcessed;

		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];
			if (pEvent != NULL)
			{
				printEvent(pEvent);
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");

		if (numEventProcessed >= TOTAL_NUM_EVENTS)
		{
			eventThreadFlag = TERMINATE; // set 1 to terminate threads
			break;
		}
		LeaveCriticalSection(&cs_main);
		Sleep(100);

	}

	DWORD nExitCode = NULL;

	for (int evntGen = 0; evntGen < NUM_EVENT_HANDLERS; evntGen++)
	{
		WaitForSingleObject(hThrd_EventGenerator[evntGen], INFINITE);

		EnterCriticalSection(&cs_main);
		printf("Thread_EventGenerator (%d) is terminated !!\n", evntGen);
		LeaveCriticalSection(&cs_main);

		GetExitCodeThread(hThrd_EventGenerator[evntGen], &nExitCode);
		TerminateThread(hThrd_EventGenerator[evntGen], nExitCode);
		CloseHandle(hThrd_EventGenerator[evntGen]);
	}
	for (int evntHndlr = 0; evntHndlr < NUM_EVENT_HANDLERS; evntHndlr++)
	{
		WaitForSingleObject(hThrd_EventHandler[evntHndlr], INFINITE);

		EnterCriticalSection(&cs_main);
		printf("Thread_EventHandler (%d) is terminated !!\n", evntHndlr);
		LeaveCriticalSection(&cs_main);

		GetExitCodeThread(hThrd_EventHandler[evntHndlr], &nExitCode);
		TerminateThread(hThrd_EventHandler[evntHndlr], nExitCode);
		CloseHandle(hThrd_EventHandler[evntHndlr]);
	}
#endif
}