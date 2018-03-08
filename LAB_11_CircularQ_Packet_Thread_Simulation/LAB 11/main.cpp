/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : main.cpp
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 두개의 쓰레드(Thread_PacketGenerator, Thread_LinkTx)를 추가로 실행하여,
   Thread_PacketGenerator에서 Packet를 Circular Queue에 enqueue 시키고,
   Thread_LinkTx에서 enqueue 된 Packet를 dequeue 시켜서 srcAddr과 destAddr의 주소를 비교하여
   해당 Packet의 status를 변경하여
   main Thread에서 ThreadManagement 함수를 사용하여 만든 상황판에 출력하여
   패킷 네트워킹을 시뮬레이션 하는 프로그램입니다.
*************************************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#include <Windows.h> 
#include <time.h> 
#include "ConsoleDisplay.h" 
#include "CircularQueue.h" 
#include "Packet.h" 
#include "ThreadManagement.h" 
#include "SimParams.h" 

void main()
{
	HANDLE consoleHandler;
	int total_packets_to_be_forwarded = TOTAL_NUM_PKT_GEN;
	int total_packets_to_be_generated = TOTAL_NUM_PKT_GEN;
	int numNodes, numDataLinks;
	CirQ cirQ, *pCQ;
	ThreadParam *pThrdPktGenParam;
	ThreadParam *pThrdLinkParam;
	CriticalSections cs_main;
	HANDLE hThreadPktGenProc;
	HANDLE hThreadLink;
	ThreadStatus pktGenStatus;
	ThreadStatus linkStatus;
	Packet packetStatusTbl[TOTAL_NUM_PKT_GEN];
	CirQ_Status cirQ_Status;
	int Thread_Pkt_Gen_Terminate_Flag = 0;
	int Thread_Link_Terminate_Flag = 0;
	int main_total_pkt_generated = 0;
	int main_total_pkt_processed = 0;

	consoleHandler = initConsoleHandler();
	int pos_x = 0, pos_y = 0;
	initializeCriticalSections(&cs_main);
	initQueue(&cirQ, MAX_Q_SIZE);
	cirQ_Status.pCirQ = &cirQ;
	cirQ.pCirQS = &cirQ_Status;

	linkStatus.thread_role = LINK_TX;
	linkStatus.round = 0;
	linkStatus.thrdStatus = THREAD_INITIALIZING;
	pktGenStatus.thread_role = PACKET_GENERATOR;
	pktGenStatus.round = 0;
	pktGenStatus.thrdStatus = THREAD_INITIALIZING;

	initPacketStatusTbl(packetStatusTbl, TOTAL_NUM_PKT_GEN);

	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printf("Generating packet forwarders (link) ...\n");
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);

	pThrdLinkParam = (ThreadParam *)malloc(sizeof(ThreadParam));
	pThrdLinkParam->fout = stdout; //fout; stdout; 
	pThrdLinkParam->consoleHandler = consoleHandler;
	pThrdLinkParam->id = 0;
	pThrdLinkParam->pCS_main = &cs_main;
	pThrdLinkParam->pThreadStatus = &linkStatus;
	pThrdLinkParam->pPacketStatusTbl = packetStatusTbl;
	pThrdLinkParam->pCirQ = &cirQ;
	pThrdLinkParam->role = LINK_TX;
	pThrdLinkParam->max_Q_capa = MAX_QUEUE_CAPACITY;
	pThrdLinkParam->pThread_Link_Terminate_Flag = &Thread_Link_Terminate_Flag;
	pThrdLinkParam->max_rounds = MAX_ROUNDS;

	hThreadLink = CreateThread(NULL, 0, Thread_LinkTx, pThrdLinkParam, 0, NULL);

	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printf("Link thread is created now. \n");
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);

	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printf("Generating %d packet generater processes ...\n", NUM_PKT_GEN_PROCS);
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);
	pThrdPktGenParam = (ThreadParam *)malloc(sizeof(ThreadParam));
	pThrdPktGenParam->fout = stdout; //fout; stdout;  
	pThrdPktGenParam->consoleHandler = consoleHandler;
	pThrdPktGenParam->id = 0;
	pThrdPktGenParam->pCS_main = &cs_main;
	pThrdPktGenParam->pThreadStatus = &pktGenStatus;
	pThrdPktGenParam->pPacketStatusTbl = packetStatusTbl;
	pThrdPktGenParam->pCirQ = &cirQ;
	pThrdPktGenParam->role = PACKET_GENERATOR;
	pThrdPktGenParam->max_Q_capa = MAX_QUEUE_CAPACITY;
	pThrdPktGenParam->num_packets_to_generate = TOTAL_NUM_PKT_GEN;
	pThrdPktGenParam->pThread_Pkt_Gen_Terminate_Flag = &Thread_Pkt_Gen_Terminate_Flag;
	pThrdPktGenParam->max_rounds = MAX_ROUNDS;

	hThreadPktGenProc = CreateThread(NULL, 0, Thread_PacketGenerator, pThrdPktGenParam, 0, NULL);

	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printf("Packet generator thread is created now. \n");
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);

	/* Thread monitoring */
	int thread_pkt_gen_terminating = 0;
	int thread_link_terminating = 0;
	int loop_count = 1;

	do {
		EnterCriticalSection(&cs_main.cs_consoleDisplay);
		printThreadStatus(consoleHandler, loop_count, &pktGenStatus);
		printThreadStatus(consoleHandler, loop_count, &linkStatus);
		printCirQ(&cirQ);
		printPacketStatusTbl(packetStatusTbl, TOTAL_NUM_PKT_GEN);
		LeaveCriticalSection(&cs_main.cs_consoleDisplay);

		EnterCriticalSection(&cs_main.cs_linkStatusUpdate);
		if (linkStatus.pkts_proc.num_PktFwrd >= total_packets_to_be_forwarded)   // 만족시 break
		{
			Thread_Link_Terminate_Flag = 1;
			Thread_Pkt_Gen_Terminate_Flag = 1;
		}
		LeaveCriticalSection(&cs_main.cs_linkStatusUpdate);
		if ((pktGenStatus.thrdStatus == THREAD_UNDER_TERMINATING) && (linkStatus.thrdStatus == THREAD_UNDER_TERMINATING))
		{
			EnterCriticalSection(&cs_main.cs_consoleDisplay);
			printf("\n . . . . Both (Packet-Gen and Link) threads are in status of  THREAD_UNDER_TERMINATING !!\n");
			LeaveCriticalSection(&cs_main.cs_consoleDisplay);
			break;
		}
		Sleep(100);
		loop_count++;

	} while ((Thread_Pkt_Gen_Terminate_Flag != 1) && (Thread_Link_Terminate_Flag != 1));

	DWORD nExitCode = NULL;

	WaitForSingleObject(hThreadPktGenProc, INFINITE); // flag 만족시까지 무한대로 
	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printf("Terminating packet generator thread\n");
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);
	GetExitCodeThread(hThreadPktGenProc, &nExitCode);
	TerminateThread(hThreadPktGenProc, nExitCode);
	CloseHandle(hThreadPktGenProc);
	pktGenStatus.thrdStatus = THREAD_TERMINATED;

	WaitForSingleObject(hThreadLink, INFINITE);
	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printf("Terminating link thread ...\n");
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);
	GetExitCodeThread(hThreadLink, &nExitCode);
	TerminateThread(hThreadLink, nExitCode);
	CloseHandle(hThreadLink);
	linkStatus.thrdStatus = THREAD_TERMINATED;

	/* Print out the final status of simulation */
	EnterCriticalSection(&cs_main.cs_consoleDisplay);
	printThreadStatus(consoleHandler, loop_count, &pktGenStatus);
	printThreadStatus(consoleHandler, loop_count, &linkStatus);
	printPacketStatusTbl(packetStatusTbl, TOTAL_NUM_PKT_GEN);
	LeaveCriticalSection(&cs_main.cs_consoleDisplay);

	//printf("(For debugging purpose only) Press any key to continue: ");  
	//getch();  
	closeConsoleHandler(consoleHandler);

}