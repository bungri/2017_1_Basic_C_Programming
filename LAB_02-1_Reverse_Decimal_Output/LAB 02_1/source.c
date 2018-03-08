/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 2-1
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 사용자로부터 최대 10자리수 이내의 10진수를 입력받고, 그 10진수 숫자를 역순으로 출력하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>
#define DATA_SIZE 10 //10자리의 정수를 입력받기 위하여 전역번수 DATA_SIZE 선언

int power(int x, int y);    //거듭제곱함수
int getDigitNum(int x);       //자릿수 찾는 함수

int main(void) {
	int inputdata = 0;                  //입력값을 저장하기위한 변수를 선언과 동시에 초기화
	int outputdata[DATA_SIZE] = { 0, }; //출력값을 저장하기 위한 intArray를 선언과 초기화
	int DigitNum = 0;                     //자릿수를 저장하기 위한 변수를 선언과 초기화
	int temp = 0;                       //자릿수 연산 및 출력 시 참조를 위한 임시변수 선언과 초기화

	printf("Input positive decimal number (upto 10 Digits) : ");
	scanf("%d", &inputdata);
	DigitNum = getDigitNum(inputdata); //입력받은 숫자의 자릿수를 구하는 함수
	temp = DigitNum;                 //입력받은 숫자를 intArray에 저장하기 위해 임시변수에 자릿수값 대입

	for (int i = DATA_SIZE - 1; i >= 0; i--) //입력받은 숫자를 배열에 하나하나 저장하는 반복문
	{
		if (i <= temp)
		{
			outputdata[i] = inputdata / power(10, temp);    //배열에 해당 자릿수 저장
			inputdata -= outputdata[i] * power(10, temp);   //다음 계산을 위해 inputdata값 차감
			temp--;
		}
	}

	printf("Digits in reverse order : ");
	for (int i = 0; i < DATA_SIZE; i++) //입력받은 숫자를 저장한 배열 출력
	{
		if (i < DigitNum)                 //반복문 변수 i가 자릿수값보다 같거나 작을때만 출력하여 0인 배열값 무시
		{
			printf("%2d", outputdata[i]);
		}
	}
	printf("\n");
	return 0;
}

int power(int x, int y) //거듭제곱함수
{
	int result = x;
	if (y == 0)            //어떤 숫자의 0거듭제곱은 1이다.
	{
		result = 1;
	}
	else if (y == 1)       //어떤 숫자의 1거듭제곱은 그 숫자 그대로이다.
	{
		result = x;
	}
	else
	{
		for (int i = 2; i <= y; i++)
		{
			result = result * x;
		}
	}
	return result;
}

int getDigitNum(int x)                      //자릿수 찾는 함수
{
	int result = 10;
	int temp = power(10, DATA_SIZE - 1);  //최대 자릿수가 10자리수인 수의 자릿수를 구하기 위해 10자리의 수로 나누기
	for (int i = 0; i < DATA_SIZE; i++)
	{
		if (x / temp != 0)
		{
			break;
		}
		temp = temp / 10;
		result--;
	}
	return result;
}