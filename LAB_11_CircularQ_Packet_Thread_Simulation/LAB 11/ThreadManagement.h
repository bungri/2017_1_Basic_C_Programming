/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : ThreadManagement.h
 * 프로그램의 목적 및 기본 기능
   이 파일은 Thread에 전달할 Parameter와 관련된 구조체, enumeration, 그리고 출력을 위한
   함수의 프로토타입이 포함된 header 파일입니다.
*************************************************************************************************/

#ifndef THREAD_MANAGEMENTS_H
#define THREAD_MANAGEMENTS_H 

#include <stdio.h> 
#include "SimParams.h" 
#include "CircularQueue.h" 

enum ROLE {
	PACKET_GENERATOR,
	LINK_TX
};

enum ThreadExecStatus {
	THREAD_INITIALIZING,
	THREAD_RUNNING,
	THREAD_UNDER_TERMINATING,
	THREAD_TERMINATED
};

extern char*strThrdStatus[];

typedef struct ThreadStatus
{
	int node_id;
	ROLE thread_role;
	ThreadExecStatus thrdStatus;
	int round;
	PacketProcessing pkts_proc;
} ThreadStatus;

typedef struct CriticalSections
{
	CRITICAL_SECTION cs_consoleDisplay;
	CRITICAL_SECTION cs_pktGenStatusUpdate;
	CRITICAL_SECTION cs_linkStatusUpdate;
	CRITICAL_SECTION cs_pkt_tbl;
} CriticalSections;

/* Thread Managements */

typedef struct ThreadParam
{
	FILE *fout; // for log file 
	int id;
	CriticalSections*pCS_main;
	ThreadStatus*pThreadStatus; // status of packet generator and packet forwarder 
	Packet *pPacketStatusTbl;
	CirQ*pCirQ; // pointer array for circular queue 
	ROLE role;
	UINT_32 myAddr;
	int max_Q_capa;
	int num_packets_to_generate;
	int*pThread_Pkt_Gen_Terminate_Flag;
	int*pThread_Link_Terminate_Flag;
	int max_rounds;
	HANDLE consoleHandler;
} ThreadParam;

DWORD WINAPI Thread_PacketGenerator(LPVOID pParam);
DWORD WINAPI Thread_LinkTx(LPVOID pParam);

void printThreadStatus(HANDLE consoleHandler, int loop_count, ThreadStatus*pThreadStatus);
void initializeCriticalSections(CriticalSections*pCS);

#endif