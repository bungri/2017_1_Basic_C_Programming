/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : CircularQueue.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 CircularQueue 에 관련된 함수의 몸체를 정의한 .cpp파일입니다.
*************************************************************************************************/

#include "CircularQueue.h" 
#include <Windows.h>

void initQueue(CirQ*pCQ, int max_num_packets)
{
	InitializeCriticalSection(&pCQ->cs_CQ); // initialize critical section for CirQ 
											//EnterCriticalSection(&pCQ->cs_CQ);

	pCQ->link_id = 0;
	pCQ->max_CQ_size = max_num_packets;
	pCQ->ppPkt = (Packet **)malloc(sizeof(Packet *)* max_num_packets);
	pCQ->first_index = pCQ->last_index = 0;
	pCQ->numPacket = 0;
	for (int i = 0; i< pCQ->max_CQ_size; i++)
	{
		pCQ->ppPkt[i] = NULL;
	}

	//LeaveCriticalSection(&pCQ->cs_CQ);
}

void enQueue(CirQ*pCQ, Packet *pPkt)
{
	//EnterCriticalSection(&pCQ->cs_CQ);

	char errMsg[256];
	int index = -1;
	/* check the correctness of packet */
	if ((pPkt->dstAddr<0) || (pPkt->dstAddr> pCQ->maxAddr) || (pPkt->srcAddr<0) || (pPkt->srcAddr> pCQ->maxAddr))
	{
		sprintf(errMsg, "\n Error at CirQ(%d->%d)::enCQ() at handling packet address (source: %d, destination: %d, seq_no: %d, hop_count: %d)\n", pPkt->srcAddr, pPkt->dstAddr, pPkt->seqNo, pPkt->hop_count);
		printErrorMessage(errMsg);
		exit(-1);
	}
	else {
		//printf("   CirQ(%d->%d)::enCQ() for packet (source: %d, destination: %d, 
		//seq_no: %d, hop_count: %d)₩n", 
		//DL_tx, DL_rx, pPkt->srcAddr, pPkt->dstAddr, pPkt->seqNo, pPkt->hop_count); 
	}


	if (pCQ->numPacket >= pCQ->max_CQ_size)
	{
		printf("Queue is Full!!\n");
		exit(-1);
	}
	else
	{
		index = pCQ->last_index;
		pCQ->ppPkt[index] = pPkt;
		pCQ->last_index = (pCQ->last_index + 1) % pCQ->max_CQ_size;
		pCQ->numPacket++;
		pCQ->pCirQS->pkt_received++;
		pCQ->pCirQS->current_num_packets++;
		//printQueue(pCQ); // for debugging
	}
	//LeaveCriticalSection(&pCQ->cs_CQ);

}
Packet *deQueue(CirQ*pCQ)
{
	//EnterCriticalSection(&pCQ->cs_CQ);

	char errMsg[256];
	Packet *pPkt;
	int index = -1;
	if (pCQ->numPacket <= 0)
	{
		//printf("Queue is Empty!!₩n"); 
		return NULL;
	}
	else
	{
		index = pCQ->first_index;
		pPkt = pCQ->ppPkt[index];
		//pCQ->ppPkt[index] = NULL; 
		pCQ->first_index = (pCQ->first_index + 1) % pCQ->max_CQ_size;
		pCQ->numPacket--;
		pCQ->pCirQS->pkt_transmitted++;
		pCQ->pCirQS->current_num_packets--;
		if ((pPkt->dstAddr<0) || (pPkt->dstAddr> pCQ->maxAddr) || (pPkt->srcAddr<0) || (pPkt->srcAddr> pCQ->maxAddr))
		{
			sprintf(errMsg, "CirQfor Link (%2d) ::Error in packet address (source: %d, destination: %d, seq_no: %d, hop_count: %d)\n", pCQ->link_id, pPkt->srcAddr, pPkt->dstAddr, pPkt->seqNo, pPkt->hop_count);
			printErrorMessage(errMsg);
			return NULL;
		}
		else
		{
			//printf("deCQat CirQ(%d->%d) ::packet (source: %d, destination: %d, 
			//    seq_no: %d, hop_count: %d)\n", 
			//DL_tx, DL_rx, pPkt->srcAddr, pPkt->dstAddr, pPkt->seqNo, pPkt->hop_count); 
			//printQueue(pCQ);  // for debugging 
		}
		return pPkt;
	}
	//LeaveCriticalSection(&pCQ->cs_CQ);

}
Packet *peekQueue(CirQ*pCQ)
{
	Packet *pPkt;
	int index = -1;
	char errMsg[256];
	if (isEmpty(pCQ))
	{
		//printf("Queue is Empty!!₩n"); 
		return NULL;
	}
	else
	{
		index = pCQ->first_index;
		pPkt = pCQ->ppPkt[index];
		if ((pPkt->dstAddr < 0) || (pPkt->dstAddr > pCQ->maxAddr) || (pPkt->srcAddr < 0) || (pPkt->srcAddr > pCQ->maxAddr))
		{
			sprintf(errMsg, "peekCQat CirQfor Link (%2d) ::Error in packet address (source: %d, destination: %d, seq_no: %d)\n", pCQ->link_id, pPkt->srcAddr, pPkt->dstAddr, pPkt->seqNo);
			//printErrorMessage(errMsg); 
			sprintf(errMsg, "Current CQ status: first index (%d), last index (%d), num_packets(%d) \n", pCQ->first_index, pCQ->last_index, pCQ->numPacket);
			//printErrorMessage(errMsg); 
			//printQueue(pCQ); 
			return NULL;
		}
		else
		{
			//printf("peekCQat CirQ(%d->%d) ::packet (source: %d, destination: %d, 
			//    seq_no: %d, hop_count: %d)₩n", 
			//DL_tx, DL_rx, pPkt->srcAddr, pPkt->dstAddr, pPkt->seqNo, pPkt->hop_count); 
		}
		return pPkt;
	}
}
bool isEmpty(CirQ*pCQ)
{
	int size;
	EnterCriticalSection(&pCQ->cs_CQ);
	size = pCQ->numPacket;
	LeaveCriticalSection(&pCQ->cs_CQ);
	if (size <= 0)
		return true;
	else
		return false;
}
bool isFull(CirQ*pCQ)
{
	int size;
	EnterCriticalSection(&pCQ->cs_CQ);
	size = pCQ->numPacket;
	LeaveCriticalSection(&pCQ->cs_CQ);
	if (size >= pCQ->max_CQ_size)
		return true;
	else return
		false;
}
void printCirQStatusTbl(CirQ_Status CirQStatusTbl[NUM_LINKS])
{
	CirQ_Status*pCirQS;
	printf("<Current status of data links>\n");
	for (int link = 0; link < NUM_LINKS; link++)
	{
		pCirQS = &CirQStatusTbl[link];
		if (pCirQS != NULL)
		{
			printf("CirQof Link (%2d) :: ", pCirQS->pCirQ->link_id);
			printf("pkt_received(%3d), pkt_transmitted(%3d), current_num_packets(%3d)", pCirQS->pkt_received, pCirQS->pkt_transmitted, pCirQS->current_num_packets);
			printf("\n");
		}
	}
}

void printCirQ(CirQ *pCQ)
{
	printf("Circular Quene (id : %3d) currently has %d packets : ", pCQ->link_id, pCQ->numPacket);
	for (int i = pCQ->first_index; i < pCQ->last_index; i++)
	{
		printf("Pkt(%d, %d, %d)", pCQ->ppPkt[i]->srcAddr, pCQ->ppPkt[i]->dstAddr, pCQ->ppPkt[i]->seqNo);
		if (i != pCQ->last_index - 1)
		{
			printf(", ");
		}
	}
	printf("\n");
}
