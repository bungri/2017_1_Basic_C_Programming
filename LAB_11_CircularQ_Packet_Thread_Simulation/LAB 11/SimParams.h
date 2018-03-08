/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 11
 * ���ϸ� : Packet.h
 * ���α׷��� ���� �� �⺻ ���
   �� ������ Packet Networking Simulation�� �ʿ��� Parameter���� ������ header �����Դϴ�.
*************************************************************************************************/

#ifndef SIMULATION_PARAMETERS_H 
#define SIMULATION_PARAMETERS_H

#define NUM_PKT_GEN_PROCS 1 
#define NUM_LINKS 3 
#define TEST_TOPOLOGY 1 
#define NUM_PACKET_GENS_PER_PROC 20
#define NUM_ROUTERS 6
#define MAX_QUEUE_CAPACITY 10 
#define MAX_Q_SIZE 10
#define PLUS_INF INT_MAX 
#define SINGLE_HOP 100 
#define MAX_ROUNDS 10000 
#define TOTAL_NUM_PKT_GEN (NUM_PACKET_GENS_PER_PROC * NUM_PKT_GEN_PROCS) 
#define MAX_ROUTER_ADDR (NUM_ROUTERS -1)  //valid address range : 0 .. (NUM_ROUTERS -1)

typedef struct PacketProcessing
{
	int num_PktGen;
	int num_PktRcvd;
	int num_PktFwrd;
	int pkts_Gen[NUM_PACKET_GENS_PER_PROC];
	int pkts_Rcvd[TOTAL_NUM_PKT_GEN];
	int pkts_Fwrd[TOTAL_NUM_PKT_GEN];
} PacketProcessing;

#endif