#include "LinkedList_Queue.h"


void initLL_PktQ(LL_PacketQ *pLL_PacketQ, int priority)
{
	InitializeCriticalSection(&pLL_PacketQ->cs_LLQ);
	pLL_PacketQ->pri = priority;
	pLL_PacketQ->front = pLL_PacketQ->end = NULL;
	pLL_PacketQ->num_Pkt = 0;
}

int enLL_PktQ(LL_PacketQ *pLL_PacketQ, Packet *pM)
{
	ListNode_Pkt *pLN_Pkt;
	if (pM == NULL)
	{
		printf("Error in enLL_PktQ :: pM is NULL !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return -1;
	}
	pLN_Pkt = (ListNode_Pkt *)malloc(sizeof(ListNode_Pkt));
	if (pLN_Pkt == NULL)
	{
		printf("Error in enLL_PktQ :: memory allocation for new ListNode failed !!\n");
		printf("Press any key to continue ...\n");
		getc(stdin);
		return -1;
	}
	pLN_Pkt->pPkt = pM;
	EnterCriticalSection(&pLL_PacketQ->cs_LLQ);
	if (pLL_PacketQ->num_Pkt == 0) // currently empty
	{
		pLL_PacketQ->front = pLL_PacketQ->end = pLN_Pkt;
		pLN_Pkt->prev = pLN_Pkt->next = NULL;
		pLL_PacketQ->num_Pkt = 1;
	}
	else
	{
		pLN_Pkt->prev = pLL_PacketQ->end;
		pLL_PacketQ->end->next = pLN_Pkt;
		pLL_PacketQ->end = pLN_Pkt;
		pLN_Pkt->next = NULL;
		pLL_PacketQ->num_Pkt++;
	}
	LeaveCriticalSection(&pLL_PacketQ->cs_LLQ);
	return 1;
}

Packet *deLL_PktQ(LL_PacketQ *pLL_PacketQ)
{
	Packet *pM;
	ListNode_Pkt *pLN_Pkt_OldFront;
	if (pLL_PacketQ->num_Pkt <= 0)
	{
		return NULL; // LL_PktQ is Empty
	}
	else
	{
		EnterCriticalSection(&pLL_PacketQ->cs_LLQ);
		pLN_Pkt_OldFront = pLL_PacketQ->front;
		pM = pLL_PacketQ->front->pPkt;
		pLL_PacketQ->front = pLL_PacketQ->front->next;
		if (pLL_PacketQ->front != NULL)
			pLL_PacketQ->front->prev = NULL;
		pLL_PacketQ->num_Pkt--;
		free(pLN_Pkt_OldFront); // release memory for the current front ListNode
		LeaveCriticalSection(&pLL_PacketQ->cs_LLQ);
		return pM;
	}
}

void printLL_PktQ(LL_PacketQ *pLL_PacketQ)
{
	int index = 0;
	Packet *pM;
	ListNode_Pkt *pLN_Pkt;
	if (pLL_PacketQ == NULL)
	{
		printf("Error in printLL_PktQ :: pLL_PacketQ is NULL !!");
		printf("Press any key to continue ...\n");
		getc(stdin);
	}
	printf("LL_PktQ(num_Pkt: %2d): ", pLL_PacketQ->num_Pkt);
	if (pLL_PacketQ->num_Pkt <= 0)
		return;
	pLN_Pkt = pLL_PacketQ->front;
	while (pLN_Pkt != NULL)
	{
		pM = pLN_Pkt->pPkt;
		if (pM == NULL)
			break;
		printPacket(pM);
		pLN_Pkt = pLN_Pkt->next;
	}
}