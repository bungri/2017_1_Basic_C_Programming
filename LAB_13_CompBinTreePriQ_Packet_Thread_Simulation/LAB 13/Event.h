/* Event.h */
#ifndef EVENT_H
#define EVENT_H
#include <stdio.h>
#include "ConsoleDisplay.h"
#include "SimParams.h"

typedef unsigned int UINT_32;
typedef unsigned short UINT_16;
typedef unsigned char UINT_8;

#define NUM_PRIORITY 100
#define EVENT_PER_LINE 5

enum EventStatus {
	GENERATED,
	ENQUEUED,
	PROCESSED,
	UNDEFINED
};

extern char *strEventStatus[];

typedef struct Event
{
	int event_no;
	UINT_32 event_gen_addr;
	UINT_32 event_handler_addr;
	UINT_8 event_pri; // event_priority
	EventStatus eventStatus;
} Event;

void printEvent(Event* pEvt);

#endif