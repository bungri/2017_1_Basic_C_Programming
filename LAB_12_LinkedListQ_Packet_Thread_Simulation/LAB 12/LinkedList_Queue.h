#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <Windows.h>
#include <stdio.h>
#include "Packet.h"

typedef struct ListNode
{
	ListNode *next;
	ListNode *prev;
	Packet *pPkt;
} ListNode_Pkt;

typedef struct LinkedList_Queue
{
	CRITICAL_SECTION cs_LLQ;
	int pri;
	ListNode_Pkt *front;
	ListNode_Pkt *end;
	int num_Pkt;
} LL_PacketQ;

void initLL_PktQ(LL_PacketQ *pLL_PacketQ, int priority);
int enLL_PktQ(LL_PacketQ *pLL_PacketQ, Packet *pM);
Packet *deLL_PktQ(LL_PacketQ *pLL_PacketQ);
void printLL_PktQ(LL_PacketQ *pLL_PacketQ);

#endif