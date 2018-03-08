#include <stdio.h>
#include <stdlib.h>
#include "Packet.h"

char *strPktStatus[] = {
	"GENERATED",
	"ENQUED",
	"TRANSMITTED",
	"UNDER_FORWARDING",
	"ARRIVED_AT_DESTINATION",
	"UNDEFINED"
};

void initPacket(Packet *pPkt, UINT_32 srcAddr, UINT_32 dstAddr, UINT_32 sN, UINT_8 pri)
{
	pPkt->srcAddr = srcAddr;
	pPkt->dstAddr = dstAddr;
	pPkt->seqNo = sN;
	pPkt->pkt_priority = pri;
}

void printPacket(Packet* pPkt)
{
	char str_pri[6];
	(pPkt->pkt_priority == 0) ? strcpy(str_pri, "H_pri") : strcpy(str_pri, "L_pri");
	printf("Packet(%2d, %2d, %6s, %2d)", pPkt->srcAddr, pPkt->dstAddr, str_pri, pPkt->pkt_id);
}

void initPacketStatusTbl(Packet packetStatusTbl[], int num_packet)
{
	for (int p = 0; p < num_packet; p++)
	{
		packetStatusTbl[p].pkt_id = -1; // not yet created
		packetStatusTbl[p].srcAddr = -1;
		packetStatusTbl[p].dstAddr = -1;
		packetStatusTbl[p].pktStatus = UNDEFINED;
		packetStatusTbl[p].seqNo = -1;
		packetStatusTbl[p].pkt_priority = -1;
	}
}

void printPacketStatusTbl(Packet packetStatusTbl[], int num_packet)
{
	printf("\n<Packet processing status>\n");
	for (int p = 0; p < num_packet; p++)
	{
		printf("Packet (%3d) :: ", p);
		printf(" src(%2d), dst(%2d), seq_no(%5d) ", packetStatusTbl[p].srcAddr,
			packetStatusTbl[p].dstAddr, packetStatusTbl[p].seqNo);
		printf(" status (%23s), ", strPktStatus[packetStatusTbl[p].pktStatus]);
		printf("\n");
	}
	printf("\n");
}