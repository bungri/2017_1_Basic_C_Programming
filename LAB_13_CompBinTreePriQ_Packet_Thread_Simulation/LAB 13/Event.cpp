#include <stdio.h>
#include <stdlib.h>

#include "Event.h"

char *strEventStatus[] = {
	"GENERATED",
	"ENQUED",
	"PROCESSED",
	"UNDEFINED"
};

void printEvent(Event* pEvent)
{
	char str_pri[6];
	printf("Ev(pri:%2d, src:%2d, id:%3d) ", pEvent->event_pri, pEvent->event_gen_addr, pEvent->event_no);
}