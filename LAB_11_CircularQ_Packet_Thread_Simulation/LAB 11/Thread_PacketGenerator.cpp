/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : Thread_PacketGenerator.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 Packet을 생성하여 Circular Queue에 enque 시키는 PacketGenerator Thread를 정의하는
   .cpp 파일입니다.
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

#define DEBUG_PACKET_GENERATION 
#define DEBUG_PACKET_RECEPTION

DWORD WINAPI Thread_PacketGenerator(LPVOID pParam)
{
	HANDLE consoleHandler;
	ThreadParam*pThrParam;
	CriticalSections*pCS_main;
	ThreadStatus*pMyThreadStatus;
	Packet *pPacketStatusTbl, *pPktTbl;
	int id, link_id;
	CirQ*pCirQ;
	UINT_32 myAddr = -1;
	Packet *pPkt;
	UINT_32 src, dst, nextHop;
	int pktID, seqNo = 0;
	int packet_gen_count = 0;
	int round = 0;
	FILE *fout;

	pThrParam = (ThreadParam*)pParam;
	dst = 0;
	pktID = 0;
	src = 0;
	nextHop = 1;
	id = 0;

	consoleHandler = pThrParam->consoleHandler;
	pCS_main = pThrParam->pCS_main;
	myAddr = pThrParam->id;
	fout = pThrParam->fout;
	pPacketStatusTbl = pThrParam->pPacketStatusTbl;
	pCirQ = pThrParam->pCirQ;

	pMyThreadStatus = pThrParam->pThreadStatus;
	pMyThreadStatus->thrdStatus = THREAD_INITIALIZING;
	pMyThreadStatus->round = 0;
	pMyThreadStatus->node_id = myAddr;
	pMyThreadStatus->pkts_proc.num_PktGen = 0;
	pMyThreadStatus->pkts_proc.num_PktRcvd = 0;
	pMyThreadStatus->pkts_proc.num_PktFwrd = 0;

	srand(time(0) + myAddr);
	pMyThreadStatus->thrdStatus = THREAD_RUNNING;
	seqNo = 1000 * myAddr; // initial sequence number of each node 

	for (int round = 1; round < pThrParam->max_rounds; round++)
	{
		EnterCriticalSection(&pCS_main->cs_pktGenStatusUpdate);
		pMyThreadStatus->round = round;
		LeaveCriticalSection(&pCS_main->cs_pktGenStatusUpdate);
		if (packet_gen_count >= pThrParam->num_packets_to_generate)
		{
			if (*pThrParam->pThread_Pkt_Gen_Terminate_Flag == 1)
			{
				break;
			}
			else
			{
				/* Since packet generator dynamically create a packet, the generator should stay alive
				until that packet is arrived at forwarding/destination !!
				Otherwise, there will be memory fault in the packet forwarding/destination !!*/
				Sleep(1000);
				continue;
			}
		}//end-if

		/**************************** [ H E R E ] ****************************/
		pPkt = (Packet*)malloc(sizeof(Packet));

		pPkt->srcAddr = myAddr;
		pPkt->pktID = ++pktID;
		pPkt->dstAddr = (dst += 1) % 10;
		pPkt->seqNo = seqNo++;
		pPkt->pktStatus = GENERATED;
		pPkt->hop_count = 1;

		pPktTbl = &pPacketStatusTbl[pktID - 1];

		pPktTbl->srcAddr = pPkt->srcAddr;
		pPktTbl->pktID = pPkt->pktID;
		pPktTbl->dstAddr = pPkt->dstAddr;
		pPktTbl->seqNo = pPkt->seqNo;
		pPktTbl->pktStatus = pPkt->pktStatus;
		pPktTbl->hop_count = pPkt->hop_count;

		while (isFull(pCirQ))
		{
			Sleep(100);  // wait ultil the Circular Queue is not full 
		}
		enQueue(pCirQ, pPkt);
		/**************************** [ H E R E ] ****************************/

		//printf("   Router (%d) :: return from enQueue()₩n", myAddr); 
		EnterCriticalSection(&pCS_main->cs_pktGenStatusUpdate);
		pPkt->pktStatus = ENQUED;
		pMyThreadStatus->pkts_proc.num_PktGen++;
		packet_gen_count++; LeaveCriticalSection(&pCS_main->cs_pktGenStatusUpdate);
		Sleep(100); // for context switching
	}


	EnterCriticalSection(&pCS_main->cs_consoleDisplay);
	printf("### Thread_Packet_Gen(%2d) is outside of while loop !!\n", myAddr);
	LeaveCriticalSection(&pCS_main->cs_consoleDisplay);

	EnterCriticalSection(&pCS_main->cs_pktGenStatusUpdate);
	pMyThreadStatus->thrdStatus = THREAD_UNDER_TERMINATING;
	LeaveCriticalSection(&pCS_main->cs_pktGenStatusUpdate);

	return 0;
}
