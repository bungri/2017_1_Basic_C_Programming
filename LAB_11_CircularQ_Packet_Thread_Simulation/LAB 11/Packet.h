/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 11
 * ���ϸ� : Packet.h
 * ���α׷��� ���� �� �⺻ ���
   �� ������ Packet�� ���ǿ� ���� ����ü�� �� ��Ŷ�� �ʱ�ȭ�ϰ� ����ϴ� �� �ʿ���
   �Լ��� ������Ÿ���� ���ǵ� header �����Դϴ�.
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
