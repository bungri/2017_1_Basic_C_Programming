/*************************************************************************************************
* �ۼ��� : 21411947 ������
* LAB 09
* ���ϸ� : main.cpp
* ���α׷��� ���� �� �⺻ ���
�� ���α׷��� ���ϰ�(Galaxy)�� ���� ����ü(Struct Star)�迭�Դϴ�.
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