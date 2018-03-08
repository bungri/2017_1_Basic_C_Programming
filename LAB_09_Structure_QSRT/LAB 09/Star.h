/*************************************************************************************************
* 작성자 : 21411947 마승현
* LAB 09
* 파일명 : main.cpp
* 프로그램의 목적 및 기본 기능
이 프로그램은 은하계(Galaxy)를 위한 구조체(Struct Star)배열입니다.
*************************************************************************************************/

struct Star
{
	char name[16];
	int id;
	unsigned int size : 3;
	unsigned int color : 3;
	unsigned int grade : 2;
	double distance;
	double luminosity;
	double mass;
	double radius;
	int age;
};