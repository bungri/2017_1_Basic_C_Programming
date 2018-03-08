/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : Thread_PacketGenerator.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 Circular Queue에서 하나의 Packet를 dequeue 한 후 srcAddr과 destAddr을 비교하여
   Packet의 status를 변경하는 LinkTx Thread를 정의하는 .cpp 파일입니다.
*************************************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <Windows.h> 
#include <time.h> 
#include "ConsoleDisplay.h" 
#include "CircularQueue.h" 
#include "Packet.h" 
#include "ThreadManagement.h" 
#include "SimParams.h" 
//#include "NetworkTopology.h"

DWORD WINAPI Thread_LinkTx(LPVOID pParam)
{
	HANDLE consoleHandler;
	char errMsg[256];
	ThreadParam*pThrParam;
	CriticalSections*pCS_main;
	ThreadStatus*pMyThreadStatus, *pThreadStatus;
	Packet *pPacketStatusTbl, *pPktTbl;
	char logFileName[50];
	int id;
	CirQ*pCQ;
	UINT_32 myAddr = -1;
	int max_queue_capacity;
	int total_rx = 0, total_gen = 0, total_under_forwarding = 0;
	int num_packets_received = 0;
	// number of packets received at this node 
	Packet *pPkt;
	UINT_32 src, dst, nextHop;
	int pktID;
	int round = 0;
	unsigned char pri = 0;
	int pending_packet_exits = 0;

	pThrParam = (ThreadParam*)pParam;
	consoleHandler = pThrParam->consoleHandler;
	pCS_main = pThrParam->pCS_main;
	myAddr = pThrParam->id;
	pPacketStatusTbl = pThrParam->pPacketStatusTbl;
	pMyThreadStatus = pThrParam->pThreadStatus;
	pMyThreadStatus->thrdStatus = THREAD_INITIALIZING;
	pMyThreadStatus->round = 0;
	pMyThreadStatus->node_id = myAddr;
	pMyThreadStatus->pkts_proc.num_PktGen = 0;
	pMyThreadStatus->pkts_proc.num_PktRcvd = 0;
	pMyThreadStatus->pkts_proc.num_PktFwrd = 0;
	pCQ = pThrParam->pCirQ;
	srand(time(0) + myAddr);
	pMyThreadStatus->thrdStatus = THREAD_RUNNING;

	for (int round = 0; round < pThrParam->max_rounds; round++)
	{
		EnterCriticalSection(&pCS_main->cs_linkStatusUpdate);
		pMyThreadStatus->round = round;
		LeaveCriticalSection(&pCS_main->cs_linkStatusUpdate);

		if (isEmpty(pCQ))
		{
			if (*pThrParam->pThread_Link_Terminate_Flag == 1)
			{
				EnterCriticalSection(&pCS_main->cs_consoleDisplay);
				printf("### Thread_Link(%2d) :: Terminate_Flagis ON by main() thread !!\n", myAddr);
				LeaveCriticalSection(&pCS_main->cs_consoleDisplay);
				break;
			}
			else
			{
				Sleep(rand() % 500 + 300); // for context switching 
				continue;
			}
		}

		pPkt = deQueue(pCQ);

		/**************************** [ H E R E ] ****************************/
		if (pPkt != NULL)
		{
			pPkt->hop_count++;
			if (myAddr == pPkt->dstAddr)
			{
				pPkt->pktStatus = ARRIVED_AT_DESTINATION;
			}
			else
			{
				pPkt->pktStatus = UNDER_FORWARDING;
			}

			pPktTbl = &pPacketStatusTbl[pPkt->pktID - 1];

			pPktTbl->srcAddr = pPkt->srcAddr;
			pPktTbl->pktID = pPkt->pktID;
			pPktTbl->dstAddr = pPkt->dstAddr;
			pPktTbl->seqNo = pPkt->seqNo;
			pPktTbl->pktStatus = pPkt->pktStatus;
			pPktTbl->hop_count = pPkt->hop_count;


			EnterCriticalSection(&pCS_main->cs_linkStatusUpdate);
			pMyThreadStatus->pkts_proc.num_PktFwrd++;
			LeaveCriticalSection(&pCS_main->cs_linkStatusUpdate);
		}
		/**************************** [ H E R E ] ****************************/


	}// end for

	EnterCriticalSection(&pCS_main->cs_consoleDisplay);
	printf("### Thread_Link(%2d) is outside of loop !!\n", myAddr);
	LeaveCriticalSection(&pCS_main->cs_consoleDisplay);

	EnterCriticalSection(&pCS_main->cs_linkStatusUpdate);
	pMyThreadStatus->thrdStatus = THREAD_UNDER_TERMINATING;
	LeaveCriticalSection(&pCS_main->cs_linkStatusUpdate);

	return 0;
}