/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 2-2
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 사용자로부터 2개의 정수(0~255 범위)를 입력받아 10진수,8진수,16진수,2진수 형태로 출력하고
   입력받은 값의 Bit-wise AND, Bit-wise OR 계산을 수행하여 결과값을 이진수로 출력하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>

void binaryOutput(int x); //2진수 출력을 위한 void함수 선언

int main(void) {
	int FirstData = 0; //입력값 저장을 위한 변수 선언
	int SecondData = 0;

	printf("Input first Hexa-decimal Integer(decimal : 0~255, hexa-decimal : FF) : ");
	scanf("%x", &FirstData);
	printf("First input data (decmial) %d = (Octal) %o = (Hexa-decimal) %#x = ", FirstData, FirstData, FirstData); //10진수, 8진수, 16진수를 순서대로 출력
	binaryOutput(FirstData); //첫번째 입력 데이터를 2진수로 출력
	printf("\n");

	printf("Input second Hexa-decimal Integer(decimal : 0~255, hexa-decimal : FF) : ");
	scanf("%x", &SecondData);
	printf("First input data (decmial) %d = (Octal) %o = (Hexa-decimal) %#x = ", SecondData, SecondData, SecondData);
	binaryOutput(SecondData);
	printf("\n");

	printf("Bit-wise AND of two input data (%d & %d) => ", FirstData, SecondData);
	binaryOutput(FirstData & SecondData); //FirstData와 SecondData의 Bit-wise AND 계산 결과값 2진수로 출력
	printf("\n");

	printf("Bit-wise OR of two input data (%d | %d) => ", FirstData, SecondData);
	binaryOutput(FirstData | SecondData); //FirstData와 SecondData의 Bit-wise OR 계산 결과값 2진수로 출력
	printf("\n");

	return 0;
}

void binaryOutput(int x) //2진수 출력을 위한 void 함수
{
	for (int i = 7; i >= 0; i--) //2진수 출력
	{
		printf("%d", (x >> i) & 0x01);
	}
}

