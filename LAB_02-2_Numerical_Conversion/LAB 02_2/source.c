/*************************************************************************************************
 * �ۼ��� : 21411947 ������
 * LAB 2-2
 * ���ϸ� : source.c
 * ���α׷��� ���� �� �⺻ ���
   �� ���α׷��� ����ڷκ��� 2���� ����(0~255 ����)�� �Է¹޾� 10����,8����,16����,2���� ���·� ����ϰ�
   �Է¹��� ���� Bit-wise AND, Bit-wise OR ����� �����Ͽ� ������� �������� ����ϴ� ���α׷��Դϴ�.
*************************************************************************************************/
#include <stdio.h>

void binaryOutput(int x); //2���� ����� ���� void�Լ� ����

int main(void) {
	int FirstData = 0; //�Է°� ������ ���� ���� ����
	int SecondData = 0;

	printf("Input first Hexa-decimal Integer(decimal : 0~255, hexa-decimal : FF) : ");
	scanf("%x", &FirstData);
	printf("First input data (decmial) %d = (Octal) %o = (Hexa-decimal) %#x = ", FirstData, FirstData, FirstData); //10����, 8����, 16������ ������� ���
	binaryOutput(FirstData); //ù��° �Է� �����͸� 2������ ���
	printf("\n");

	printf("Input second Hexa-decimal Integer(decimal : 0~255, hexa-decimal : FF) : ");
	scanf("%x", &SecondData);
	printf("First input data (decmial) %d = (Octal) %o = (Hexa-decimal) %#x = ", SecondData, SecondData, SecondData);
	binaryOutput(SecondData);
	printf("\n");

	printf("Bit-wise AND of two input data (%d & %d) => ", FirstData, SecondData);
	binaryOutput(FirstData & SecondData); //FirstData�� SecondData�� Bit-wise AND ��� ����� 2������ ���
	printf("\n");

	printf("Bit-wise OR of two input data (%d | %d) => ", FirstData, SecondData);
	binaryOutput(FirstData | SecondData); //FirstData�� SecondData�� Bit-wise OR ��� ����� 2������ ���
	printf("\n");

	return 0;
}

void binaryOutput(int x) //2���� ����� ���� void �Լ�
{
	for (int i = 7; i >= 0; i--) //2���� ���
	{
		printf("%d", (x >> i) & 0x01);
	}
}

