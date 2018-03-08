/***********************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 1
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 사용자로부터 10개의 성적을 입력받아 합계와 평균, 최대와 최소를 계산하는 프로그램입니다.
************************************************************************************************************/


#include <stdio.h>

#define NUM_STUDENTS 10
#define MAX_NUM 99999    //최대값의 범위
#define MIN_NUM -99999   //최소값의 범위

void main()
{
	printf("My name is 마승현\n");

	int score[NUM_STUDENTS] = { 1,2,3,4,5,6,7,8,9,10 }; //10개의 성적 입력
	int data;      //입력값 저장을 위한 변수
	int sum;       //합계
	int max, min;  //최대,최소
	double avg;    //평균

	sum = 0;
	data = 0;      //변수 초기화

	max = MIN_NUM;
	min = MAX_NUM; //범위설정을 위한 변수 초기화

	printf("성적을 입력해 주세요 : ");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		scanf("%d", &data);  //입력값 저장
		sum += data;         //합계에 입력값 더하기
		score[i] = data;     //성적 배열에 입력값 저장

		if (max < data)
		{
			max = data;      //입력값과 최대값 비교 후 치환
		}
		if (min > data) {
			min = data;      //입력값과 최소값 비교 후 치환
		}
	}
	printf("\n");

	printf("input data is : ");

	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		printf("%3d", score[i]);       //입력값 전체 출력
	}

	avg = sum / (double)NUM_STUDENTS;  //평균 계산
	printf("\n");
	printf("sum of %d students' score is %d\n", NUM_STUDENTS, sum);
	printf("average is %7.2f\n", avg);
	printf("minimum score is %d, maximum score is %d.\n", min, max);
}