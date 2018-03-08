/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : CircularQueue.h
 * 프로그램의 목적 및 기본 기능
   이 파일은 CircularQueue 에 관련된 구조체와 함수의 프로토타입을 정의한 header 파일입니다.
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