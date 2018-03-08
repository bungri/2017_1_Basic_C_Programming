/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : Packet.h
 * 프로그램의 목적 및 기본 기능
   이 파일은 Packet의 정의에 대한 구조체와 이 패킷을 초기화하고 출력하는 데 필요한
   함수의 프로토타입이 정의된 header 파일입니다.
*************************************************************************************************/

#ifndef PACKET_H 
#define PACKET_H

#include <stdio.h> 
#include "ConsoleDisplay.h"

typedef unsigned int UINT_32;
typedef unsigned short UINT_16;
typedef unsigned char UINT_8;

#define MAX_HOP_COUNT 16 

enum PacketStatus {
	GENERATED,
	ENQUED,
	TRANSMITTED,
	UNDER_FORWARDING,
	ARRIVED_AT_DESTINATION,
	UNDEFINED
};

extern char *strPktStatus[];

typedef struct Packet
{
	int pktID;
	UINT_32 srcAddr;
	UINT_32 dstAddr;
	UINT_32 seqNo;
	UINT_8 priority;
	PacketStatus pktStatus;
	int hop_count;
	int route_nodes[MAX_HOP_COUNT];
}Packet;

void initPacket(Packet *pPkt, UINT_32 srcAddr, UINT_32 dstAddr, UINT_32 sN, UINT_8 pri);
void printPacket(Packet* pPkt);
FILE* fprintPacket(FILE *fout, Packet* pPkt);
void initPacketStatusTbl(Packet packetStatusTbl[], int num_packet);
void printPacketStatusTbl(Packet packetStatusTbl[], int num_packet);

#endif
