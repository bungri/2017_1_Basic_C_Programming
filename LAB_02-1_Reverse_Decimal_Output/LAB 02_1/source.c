/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 2-1
 * ���ϸ� : source.c
 * ���α׷��� ���� �� �⺻ ���
   �� ���α׷��� ����ڷκ��� �ִ� 10�ڸ��� �̳��� 10������ �Է¹ް�, �� 10���� ���ڸ� �������� ����ϴ� ���α׷��Դϴ�.
*************************************************************************************************/
#include <stdio.h>
#define DATA_SIZE 10 //10�ڸ��� ������ �Է¹ޱ� ���Ͽ� �������� DATA_SIZE ����

int power(int x, int y);    //�ŵ������Լ�
int getDigitNum(int x);       //�ڸ��� ã�� �Լ�

int main(void) {
	int inputdata = 0;                  //�Է°��� �����ϱ����� ������ ����� ���ÿ� �ʱ�ȭ
	int outputdata[DATA_SIZE] = { 0, }; //��°��� �����ϱ� ���� intArray�� ����� �ʱ�ȭ
	int DigitNum = 0;                     //�ڸ����� �����ϱ� ���� ������ ����� �ʱ�ȭ
	int temp = 0;                       //�ڸ��� ���� �� ��� �� ������ ���� �ӽú��� ����� �ʱ�ȭ

	printf("Input positive decimal number (upto 10 Digits) : ");
	scanf("%d", &inputdata);
	DigitNum = getDigitNum(inputdata); //�Է¹��� ������ �ڸ����� ���ϴ� �Լ�
	temp = DigitNum;                 //�Է¹��� ���ڸ� intArray�� �����ϱ� ���� �ӽú����� �ڸ����� ����

	for (int i = DATA_SIZE - 1; i >= 0; i--) //�Է¹��� ���ڸ� �迭�� �ϳ��ϳ� �����ϴ� �ݺ���
	{
		if (i <= temp)
		{
			outputdata[i] = inputdata / power(10, temp);    //�迭�� �ش� �ڸ��� ����
			inputdata -= outputdata[i] * power(10, temp);   //���� ����� ���� inputdata�� ����
			temp--;
		}
	}

	printf("Digits in reverse order : ");
	for (int i = 0; i < DATA_SIZE; i++) //�Է¹��� ���ڸ� ������ �迭 ���
	{
		if (i < DigitNum)                 //�ݺ��� ���� i�� �ڸ��������� ���ų� �������� ����Ͽ� 0�� �迭�� ����
		{
			printf("%2d", outputdata[i]);
		}
	}
	printf("\n");
	return 0;
}

int power(int x, int y) //�ŵ������Լ�
{
	int result = x;
	if (y == 0)            //� ������ 0�ŵ������� 1�̴�.
	{
		result = 1;
	}
	else if (y == 1)       //� ������ 1�ŵ������� �� ���� �״���̴�.
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

int getDigitNum(int x)                      //�ڸ��� ã�� �Լ�
{
	int result = 10;
	int temp = power(10, DATA_SIZE - 1);  //�ִ� �ڸ����� 10�ڸ����� ���� �ڸ����� ���ϱ� ���� 10�ڸ��� ���� ������
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