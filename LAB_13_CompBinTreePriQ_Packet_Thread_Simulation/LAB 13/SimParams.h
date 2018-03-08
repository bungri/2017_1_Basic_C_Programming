/*************************************************************************************************
* 작성자 : 21411947 마승현
* LAB 11
* 파일명 : Packet.h
* 프로그램의 목적 및 기본 기능
이 파일은 Packet Networking Simulation에 필요한 Parameter들을 정의한 header 파일입니다.
*************************************************************************************************/

#ifndef SIMULATION_PARAMETERS_H 
#define SIMULATION_PARAMETERS_H

#define NUM_EVENT_GENERATORS 3 
#define NUM_EVENT_HANDLERS 2

#define NUM_EVENTS_PER_GEN 20
#define TOTAL_NUM_EVENTS (NUM_EVENTS_PER_GEN * NUM_EVENT_GENERATORS) 

#define MAX_ROUND 1000

#define PRIQ_PKT_SIZE 10
#define PRI_QUEUE_CAPACITY 60


#endif