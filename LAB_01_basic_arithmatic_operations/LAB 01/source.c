/***********************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 1
 * ���ϸ� : source.c
 * ���α׷��� ���� �� �⺻ ���
   �� ���α׷��� ����ڷκ��� 10���� ������ �Է¹޾� �հ�� ���, �ִ�� �ּҸ� ����ϴ� ���α׷��Դϴ�.
************************************************************************************************************/


#include <stdio.h>

#define NUM_STUDENTS 10
#define MAX_NUM 99999    //�ִ밪�� ����
#define MIN_NUM -99999   //�ּҰ��� ����

void main()
{
	printf("My name is ������\n");

	int score[NUM_STUDENTS] = { 1,2,3,4,5,6,7,8,9,10 }; //10���� ���� �Է�
	int data;      //�Է°� ������ ���� ����
	int sum;       //�հ�
	int max, min;  //�ִ�,�ּ�
	double avg;    //���

	sum = 0;
	data = 0;      //���� �ʱ�ȭ

	max = MIN_NUM;
	min = MAX_NUM; //���������� ���� ���� �ʱ�ȭ

	printf("������ �Է��� �ּ��� : ");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		scanf("%d", &data);  //�Է°� ����
		sum += data;         //�հ迡 �Է°� ���ϱ�
		score[i] = data;     //���� �迭�� �Է°� ����

		if (max < data)
		{
			max = data;      //�Է°��� �ִ밪 �� �� ġȯ
		}
		if (min > data) {
			min = data;      //�Է°��� �ּҰ� �� �� ġȯ
		}
	}
	printf("\n");

	printf("input data is : ");

	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		printf("%3d", score[i]);       //�Է°� ��ü ���
	}

	avg = sum / (double)NUM_STUDENTS;  //��� ���
	printf("\n");
	printf("sum of %d students' score is %d\n", NUM_STUDENTS, sum);
	printf("average is %7.2f\n", avg);
	printf("minimum score is %d, maximum score is %d.\n", min, max);
}