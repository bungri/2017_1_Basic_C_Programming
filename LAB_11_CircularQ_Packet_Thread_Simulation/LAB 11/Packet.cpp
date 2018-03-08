/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 11
 * 파일명 : Packet.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 Packet을 생성하고 그 Packet을 확인하기 위해 출력하는 함수의 몸체를 정의한
   .cpp 파일입니다.
*************************************************************************************************/

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
	pPkt->priority = pri;
}

void printPacket(Packet* pPkt)
{
	printf("Packet: srcAddr(%u)", pPkt->srcAddr);
	printf(", seqNo(%u)", pPkt->seqNo);
	printf(", dstAddr(%u)", pPkt->dstAddr);
	printf("\n");
}

FILE * fprintPacket(FILE *fout, Packet* pPkt)
{
	fprintf(fout, "Packet: srcAddr(%u)", pPkt->srcAddr);
	fprintf(fout, ", seqNo(%u)", pPkt->seqNo);
	fprintf(fout, ", dstAddr (%u)", pPkt->dstAddr);
	fprintf(fout, "\n");
	return fout;
}

void initPacketStatusTbl(Packet packetStatusTbl[], int num_packet)
{
	for (int p = 0; p < num_packet; p++)
	{
		packetStatusTbl[p].pktID = -1; // not yet created 
		packetStatusTbl[p].srcAddr = -1;
		packetStatusTbl[p].dstAddr = -1;
		packetStatusTbl[p].pktStatus = UNDEFINED;
		packetStatusTbl[p].seqNo = -1;
		packetStatusTbl[p].priority = -1;
		packetStatusTbl[p].hop_count = 0;
		for (int h = 0; h < MAX_HOP_COUNT; h++)
		{
			packetStatusTbl[p].route_nodes[h] = -1;
		}
	}
}

void printPacketStatusTbl(Packet packetStatusTbl[], int num_packet)
{
	printf("\n<Packet processing status>\n");
	for (int p = 0; p < num_packet; p++)
	{
		printf("Packet (%3d) :: ", p);
		printf(" src(%2d), dst(%2d), seq_no(%5d) ", packetStatusTbl[p].srcAddr, packetStatusTbl[p].dstAddr, packetStatusTbl[p].seqNo);
		printf(" status (%23s), ", strPktStatus[packetStatusTbl[p].pktStatus]);
		//packetStatusTbl[p].priority = -1; 
		printf(" hop_count(%2d) ", packetStatusTbl[p].hop_count - 1); // remove the starting node from the route in counting hop_count 
																	  /*
																	  printf(" packet route: ");
																	  for (int h = 0; h < packetStatusTbl[p].hop_count; h++)
																	  {
																	  printf(" %2d ", packetStatusTbl[p].route_nodes[h]);
																	  if (h != (packetStatusTbl[p].hop_count-1))
																	  printf("->");
																	  } */
		printf("\n");
	}
	printf("\n");
}