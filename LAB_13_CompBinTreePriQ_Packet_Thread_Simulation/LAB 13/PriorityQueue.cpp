/* PriorityQueue.cpp (1) */
#include "PriorityQueue.h"
#include "Event.h"

bool hasLeftChild(int pos, PriQ_Event *pPriQ_Event)
{
	if (pos * 2 <= pPriQ_Event->num_Events)
		return TRUE;
	else
		return FALSE;
}

bool hasRightChild(int pos, PriQ_Event *pPriQ_Event)
{
	if (pos * 2 + 1 <= pPriQ_Event->num_Events)
		return TRUE;
	else
		return FALSE;
}

PriQ_Event *initPriQ_Event(PriQ_Event *pPriQ_Event, int capacity)
{
	InitializeCriticalSection(&pPriQ_Event->cs_priQ);

	pPriQ_Event->priQ_capacity = capacity;
	pPriQ_Event->pCBT_Event = (CompBinTreeNode_Event *)malloc(sizeof(CompBinTreeNode_Event) * (capacity + 1));
	pPriQ_Event->num_Events = 0;
	pPriQ_Event->pos_last = 0;

	return pPriQ_Event;
}

void deletePriQ_Event(PriQ_Event *pPriQ_Event)
{
	if (pPriQ_Event->pCBT_Event != NULL)
		free(pPriQ_Event->pCBT_Event);
}

int insertPriQ_Event(PriQ_Event *pPriQ_Event, Event *pEvent)
{
	int pos, pos_parent;
	CompBinTreeNode_Event CBT_Event_tmp;

	if (pPriQ_Event->num_Events >= pPriQ_Event->priQ_capacity)
	{
		PriQ_Event pPriQ_Temp;
		pPriQ_Temp.pCBT_Event = (CompBinTreeNode_Event *)malloc(sizeof(CompBinTreeNode_Event) * (pPriQ_Event->priQ_capacity + 1));
		pPriQ_Temp.pCBT_Event = pPriQ_Event->pCBT_Event;

		pPriQ_Event->pCBT_Event = (CompBinTreeNode_Event*)realloc(pPriQ_Event->pCBT_Event, sizeof(CompBinTreeNode_Event) * (pPriQ_Event->priQ_capacity * 2));
		pPriQ_Event->pCBT_Event = pPriQ_Temp.pCBT_Event;
		//free(pPriQ_Temp);
		return -1;
	}


	EnterCriticalSection(&pPriQ_Event->cs_priQ);
	pos = ++pPriQ_Event->num_Events;

	//pPriQ_Event->pCBT_Event[pos].priority = pEvent->Event_priority;
	pPriQ_Event->pCBT_Event[pos].pEvent = pEvent;

	/* up-heap bubbling*/
	while (pos != POS_ROOT)
	{
		pos_parent = pos / 2;
		if (pPriQ_Event->pCBT_Event[pos].pEvent->event_pri >= pPriQ_Event->pCBT_Event[pos_parent].pEvent->event_pri)
		{
			break; // if the priority of the new Event is lower than its parent's priority, just stop up-heap bubbling
		}
		else
		{
			CBT_Event_tmp = pPriQ_Event->pCBT_Event[pos_parent];
			pPriQ_Event->pCBT_Event[pos_parent] = pPriQ_Event->pCBT_Event[pos];
			pPriQ_Event->pCBT_Event[pos] = CBT_Event_tmp;
			pos = pos_parent;
		}
	}
	LeaveCriticalSection(&pPriQ_Event->cs_priQ);
}

Event *removeMinPriQ_Event(PriQ_Event *pPriQ_Event)
{
	Event *pEvent;
	CompBinTreeNode_Event CBT_Event_tmp;
	int pos, pos_root = 1, pos_last, pos_child;

	if (pPriQ_Event->num_Events <= 0)
		return NULL; // Priority queue is empty

	EnterCriticalSection(&pPriQ_Event->cs_priQ);

	pEvent = pPriQ_Event->pCBT_Event[1].pEvent; // get the Event address of current top
	pos_last = pPriQ_Event->num_Events;
	pPriQ_Event->num_Events--;

	if (pPriQ_Event->num_Events > 0)
	{
		/* put the last node into the top position */
		pPriQ_Event->pCBT_Event[pos_root] = pPriQ_Event->pCBT_Event[pos_last];

		/* down heap bubbling */
		pos = pos_root;
		while (hasLeftChild(pos, pPriQ_Event))
		{
			pos_child = pos * 2;
			if (hasRightChild(pos, pPriQ_Event))
			{
				if (pPriQ_Event->pCBT_Event[pos_child].pEvent->event_pri > pPriQ_Event->pCBT_Event[pos_child + 1].pEvent->event_pri)
					pos_child = pos * 2 + 1;
				// if right child has higher priority, then select it
			}
			/* if the Event in pos_child has higher priority than Event
			in pos, swap them */
			if (pPriQ_Event->pCBT_Event[pos_child].pEvent->event_pri < pPriQ_Event->pCBT_Event[pos].pEvent->event_pri)
			{
				CBT_Event_tmp = pPriQ_Event->pCBT_Event[pos];
				pPriQ_Event->pCBT_Event[pos] = pPriQ_Event->pCBT_Event[pos_child];
				pPriQ_Event->pCBT_Event[pos_child] = CBT_Event_tmp;
			}
			else
			{
				break;
			}
			pos = pos_child;
		} // end while
	} // end if
	LeaveCriticalSection(&pPriQ_Event->cs_priQ);
	return pEvent;
}

void printPriQ_Event(PriQ_Event *pPriQ_Event)
{
	int pos, count;
	int Event_pri;
	int level = 0, level_count = 1;
	Event *pEvent;
	if (pPriQ_Event->num_Events == 0)
	{
		printf("PriorityQueue_Event is empty !!");
		return;
	}
	pos = 1; count = 1; level = 0;
	level_count = 1; // level_count = 2^^level
	while (count <= pPriQ_Event->num_Events)
	{
		printf("CompBinTree(level%2d): ", level);
		for (int i = 0; i < level_count; i++)
		{
			pEvent = pPriQ_Event->pCBT_Event[pos].pEvent;
			Event_pri = pPriQ_Event->pCBT_Event[pos].pEvent->event_pri;
			//printf("Event(pri:%2d, id:%2d) ", Event_pri, pEvent->event_no);
			printEvent(pEvent);
			pos++;
			count++;
			if (count > pPriQ_Event->num_Events)
				break;
		}
		printf("\n");

		level++;
		level_count *= 2;

	} // end while
	printf("\n");
}