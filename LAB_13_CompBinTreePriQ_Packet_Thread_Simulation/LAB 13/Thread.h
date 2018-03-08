/* Thread.h (1) */
#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>
#include "Event.h"
#include "PriorityQueue.h"

enum ROLE {
	EVENT_GENERATOR,
	EVENT_HANDLER
};

enum THREAD_FLAG {
	INITIALIZE,
	RUN,
	TERMINATE
};

typedef struct ThreadStatusMonitor
{
	int numEventGenerated[NUM_EVENT_GENERATORS];
	int numEventProcessed[NUM_EVENT_HANDLERS];
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventProcessed[TOTAL_NUM_EVENTS]; // used for monitoring only
	THREAD_FLAG *pFlagThreadTerminate;
}ThreadStatusMonitor;

typedef struct ThreadParam
{
	CRITICAL_SECTION *pCS_main;
	CRITICAL_SECTION *pCS_thrd_mon;
	PriQ_Event *pPriQ_Event;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	ThreadStatusMonitor *pThrdMon;
} ThreadParam_Event;

DWORD WINAPI Thread_EventHandler(LPVOID pParam);
DWORD WINAPI Thread_EventGenerator(LPVOID pParam);

#endif