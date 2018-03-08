/* PriorityQueue.h */
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include "Event.h"

#define POS_ROOT 1

typedef struct CompleteBinaryTreeNode
{
	int priority;
	Event *pEvent;
} CompBinTreeNode_Event;

typedef struct PriorityQueue
{
	CRITICAL_SECTION cs_priQ;
	int priQ_capacity;
	int num_Events;
	int pos_last;
	CompBinTreeNode_Event *pCBT_Event;
} PriQ_Event;

PriQ_Event *initPriQ_Event(PriQ_Event *pPriQ_Event, int capacity);
int insertPriQ_Event(PriQ_Event *pPriQ_Event, Event *pEvent);
Event *removeMinPriQ_Event(PriQ_Event *pPriQ_Event);
void printPriQ_Event(PriQ_Event *pPriQ_Event);

#endif