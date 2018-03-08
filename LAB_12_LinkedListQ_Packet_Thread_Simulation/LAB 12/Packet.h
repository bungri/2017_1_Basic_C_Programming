#ifndef PACKET_H
#define PACKET_H

#include <stdio.h>
#include "ConsoleDisplay.h"
#include "SimParams.h"

typedef unsigned int UINT_32;
typedef unsigned short UINT_16;
typedef unsigned char UINT_8;
#define NUM_PRIORITY 2
#define MAX_HOP_COUNT 16

enum PacketStatus {
	GENERATED,
	ENQUEUED,
	TRANSMITTED,
	UNDER_FORWARDING,
	ARRIVED_AT_DESTINATION,
	UNDEFINED
};
extern char *strPktStatus[];

typedef struct Packet
{
	int pkt_id;
	UINT_32 srcAddr;
	UINT_32 dstAddr;
	UINT_32 seqNo;
	UINT_8 pkt_priority;
	PacketStatus pktStatus;
} Packet;

typedef struct PacketProcessing
{
	int num_PktGen;
	int num_PktRcvd;
	int num_PktFwrd;
	int pkts_Gen[NUM_PACKET_GENS_PER_PROC];
	int pkts_Rcvd[TOTAL_NUM_PKT_GEN];
	int pkts_Fwrd[TOTAL_NUM_PKT_GEN];
} PacketProcessing;

void initPacket(Packet *pPkt, UINT_32 srcAddr, UINT_32 dstAddr, UINT_32 sN, UINT_8 pri);
void printPacket(Packet* pPkt);
void initPacketStatusTbl(Packet packetStatusTbl[], int num_packet);
void printPacketStatusTbl(Packet packetStatusTbl[], int num_packet);

#endif