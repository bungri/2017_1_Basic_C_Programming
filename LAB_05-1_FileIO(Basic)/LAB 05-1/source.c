/*************************************************************************************************
* �ۼ��� : 21411947 ������
* LAB 05
* ���ϸ� : source.c
* ���α׷��� ���� �� �⺻ ���
  �� ���α׷��� �ؽ�Ʈ���� Message.txt�� �о�� ��������� Output.txt�� �ű�� �����Դϴ�.
*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int fsize(FILE *fp);						//������ ũ�⸦ ���ϱ� ���� �Լ� ����
void FileToStr(FILE *FP);						//������ ������ ����ϱ� ���� �Լ� ����

int main(void)
{
	FILE *fp_msg, *fp_out = NULL;					//File ������ *fp�� �����ϰ� NULL�� �ʱ�ȭ

/*****************************************************���� �Էº�*****************************************************/

	fp_msg = fopen("Message.txt", "r");		//Message.txt�� �б���� ����, �� �ּҸ� fp�� ����
	int file_size = fsize(fp_msg);

	if (fp_msg == NULL)
	{
		printf("# ���� ���� ����!\n");
		exit(1);
	}
	else {
		printf("# ���� ���� ����!\n");
	}

	//�����迭 �Ҵ��
	char *inputdata = (char*)calloc(sizeof(char), fsize(fp_msg));		//���ڿ� ������ ���� �����迭 �Ҵ�
	if (inputdata == NULL)
	{
		printf("# �����迭 �Ҵ� ����!");
		exit(1);
	}

	FileToStr(fp_msg, inputdata);

	printf("-----�Է������� ������ �Ʒ��� �����ϴ�.-----\n");
	printf("%s\n", inputdata);
	printf("--------------------------------------------\n\n");
	fclose(fp_msg);			//�Է����� �ݱ�

/*****************************************************���� ��º�*****************************************************/

	fp_out = fopen("Output.txt", "w+");			//Output.txt�� �б�, ���� ���� ��. ������ ������ ����� �־ �����.

	if (fp_out == NULL)
	{
		printf("# ���� ���� ����!\n");
		exit(1);
	}
	else {
		printf("# ���� ���� ����!\n");
	}

	fputs(inputdata, fp_out);					//�����迭�� ����Ǿ��ִ� ���ڿ��� Output.txt�� ����

	printf("-----��������� ������ �Ʒ��� �����ϴ�.-----\n%s\n", inputdata);
	fprintf(fp_out, inputdata);
	printf("--------------------------------------------\n\n");


	fclose(fp_out);			//������� �ݱ�
	free(inputdata);		//�����Ҵ� �޸� �ݳ�
	return 0;
}

int fsize(FILE *fp)				//������ ũ�⸦ ���ϴ� �Լ�
{
	if (fgetc(fp) != EOF)
	{
		int result = 0;
		fseek(fp, 0, SEEK_END);	//�������� ��ġ�� ������ �ű��.
		result = ftell(fp);
		fseek(fp, 0, SEEK_SET);	//�������� ��ġ�� �ٽ� ó������ �ű��.
		return result;
	}
}

void FileToStr(FILE *fp, char* strArray)			//������ ������ ����ϴ� �Լ�
{
	char *temp = (char*)calloc(sizeof(char), fsize(fp));		//���ڿ� ������ ���� �����迭 �Ҵ�
	int file_size = fsize(fp);

	if (temp == NULL)
	{
		printf("# �����迭 �Ҵ� ����!");
		exit(1);
	}

	while (fgets(temp, file_size + 1, fp) != NULL) {	//������ ���ڿ��� �о�ͼ� �����迭�� ����
														//fsize(fp_msg+1)�� ���ִ� ������ �������� �� null ����(/0)�� ����� ����.
		strcat(strArray, temp);		// �о�� temp string�� ������ stringArray�� �߰�

	}

	free(temp);
}