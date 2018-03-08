/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 11
 * ���ϸ� : CircularQueue.h
 * ���α׷��� ���� �� �⺻ ���
   �� ������ CircularQueue �� ���õ� ����ü�� �Լ��� ������Ÿ���� ������ header �����Դϴ�.
*************************************************************************************************/

#ifndef DataLink_H 
#define DataLink_H 

#include <Windows.h> 
#include <limits.h> 
#include "Packet.h" 
//#include "Circular_Queue.h" 
#include "ConsoleDisplay.h" 
#include "SimParams.h"

typedef struct CircularQueue
{
	CRITICAL_SECTION cs_CQ;
	UINT_32 link_id; // transmitter 
	UINT_32 maxAddr; // used for checking packet correctness 
	int numPacket;
	int max_CQ_size;
	int first_index;
	int last_index;
	Packet **ppPkt; // pointer of packet pointer array 
	struct CirQ_Status*pCirQS;
} CirQ;

typedef struct CirQ_Status
{
	CirQ*pCirQ;
	int pkt_received;
	int pkt_transmitted;
	int current_num_packets;
} CirQ_Status;

void initQueue(CirQ*pCQ, int max_num_packets);
void enQueue(CirQ*pCQ, Packet *pPkt);

Packet *deQueue(CirQ*pCQ);
Packet *peekQueue(CirQ*pCQ);

bool isEmpty(CirQ*pCQ);
bool isFull(CirQ*pCQ);

void printCirQStatusTbl(CirQ_Status CirQStatusTbl[NUM_LINKS]);
void printCirQ(CirQ *pCQ);
//void printCirQStatusTbl(CirQ_Status*pCirQStatusTbl); 

#endif