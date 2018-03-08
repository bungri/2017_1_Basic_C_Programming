/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 05
 * 파일명 : source.cpp
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 텍스트파일 Message.txt를 읽어와 출력파일인 Output.txt로 옮기는 파일입니다.
*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 256
#define TRUE 1
#define FALSE 0
#define CIPHER_CODE 0x00 // 0000 0000, used in XOR for each character
//#define CIPHER_CODE 0x69 //0110 1001, used in XOR for each character

int fsize(FILE *fp);						//파일의 크기를 구하기 위한 함수 원형
void cipherChar(unsigned char ch, unsigned char &cc_u, unsigned char &cc_l);
void cipherText(FILE *fp_msg, FILE *fp_tx, unsigned char cipher_code);
unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l);
void deCipherText(FILE *fp_tx, FILE *fp_out, unsigned char cipher_code);

int main(void)
{
	FILE *fp_msg, *fp_tx, *fp_out = NULL;					//File 포인터 *fp를 생성하고 NULL로 초기화
	fp_msg = fopen("Message.txt", "r");		//Message.txt를 읽기모드로 열고, 그 주소를 fp에 저장
	fp_tx = fopen("Ciphered.txt", "w+");		//Message.txt를 읽기모드로 열고, 그 주소를 fp에 저장
	fp_out = fopen("DeCiphered.txt", "w+");		//Message.txt를 읽기모드로 열고, 그 주소를 fp에 저장


	if ((fp_msg == NULL) || (fp_tx == NULL) || (fp_out == NULL))
	{
		printf("# 파일 열기 실패!\n");
		exit(1);
	}
	else {
		printf("# 파일 열기 성공!\n");
	}

	cipherText(fp_msg, fp_tx, CIPHER_CODE);
	deCipherText(fp_tx, fp_out, CIPHER_CODE);


	unsigned char ch1 = 'A';
	unsigned char ch11 = 'A';
	unsigned char cch1 = '0', cch2 = '0';
	unsigned char ch2 = '0';
	unsigned char dch1 = '6', dch2 = 'f';
	cipherChar(ch1, cch1, cch2);
	printf("First, '%c', %x, %x, %x\n", ch1, ch1, cch1, cch2);
	ch11 = deCipherChar(cch1, cch2);
	printf("second, '%c', %x\n", ch11, ch11);
	deCipherChar(dch1, dch2);
	printf("thrid, '%c', %x, %x, %x\n", ch2, ch2, dch1, dch2);

	return 0;
}

int fsize(FILE *fp)				//파일의 크기를 구하는 함수
{
	int result = 0;
	if (fgetc(fp) != EOF)
	{
		fseek(fp, 0, SEEK_END);	//포인터의 위치를 끝으로 옮긴다.
		result = ftell(fp);
		fseek(fp, 0, SEEK_SET);	//포인터의 위치를 다시 처음으로 옮긴다.
	}
	return result;
}



void cipherChar(unsigned char ch, unsigned char &cc_u, unsigned char &cc_l)
{
	cc_u = ((ch&(0x0f << 4)) >> 4) ^ CIPHER_CODE;
	cc_l = (ch & 0x0f) ^ CIPHER_CODE;
}

void cipherText(FILE *fp_msg, FILE *fp_tx, unsigned char cipher_code)
{
	int file_size = fsize(fp_msg);

	char *inputdata = (char*)calloc(sizeof(char), file_size);		//문자열 저장을 위한 동적배열 할당
	char *temp = (char*)calloc(sizeof(char), file_size);		//문자열 저장을 위한 동적배열 할당

	if ((inputdata == NULL) || (temp == NULL))
	{
		printf("# 동적배열 할당 실패!");
		exit(1);
	}

	while (fgets(temp, file_size + 1, fp_msg) != NULL) {	//파일의 문자열을 읽어와서 동적배열에 저장
															//fsize(fp_msg+1)을 해주는 이유는 마지막에 들어갈 null 문자(/0)를 고려한 것임.
		strcat(inputdata, temp);							// 읽어온 temp string의 내용을 stringArray로 추가
	}

	free(temp);

	for (int i = 0; i <= file_size; i++)
	{
		unsigned char cipher_temp[2] = { 0,0 };

		if (inputdata[i] == EOF)
		{
			break;
		}
		else if (inputdata[i] != '\n')
		{
			cipherChar(inputdata[i], cipher_temp[0], cipher_temp[1]);
			fprintf(fp_tx, "%1X%1X", cipher_temp[0], cipher_temp[1]);
		}
		else if (inputdata[i] == '\n')
		{
			cipherChar(inputdata[i], cipher_temp[0], cipher_temp[1]);
			fprintf(fp_tx, "%1X%1X", cipher_temp[0], cipher_temp[1]);
			fprintf(fp_tx, "\n");
		}

	}
	free(inputdata);
}

unsigned char deCipherChar(unsigned char rc_u, unsigned char rc_l)
{
	unsigned char result;
	int i_u = 0, i_l = 0;

	if ((rc_u>='0') && (rc_u<='9'))
	{
		i_u = rc_u - '0';
	}
	else if ((rc_u>='A')&&(rc_u<='F'))
	{
		i_u = rc_u - 'A' + 10;
	}
	if ((rc_l >= '0') && (rc_l <= '9'))
	{
		i_l = rc_l - '0';
	}
	else if ((rc_l >= 'A') && (rc_l <= 'F'))
	{
		i_l = rc_l - 'A' + 10;
	}
	
	result = (((i_u^CIPHER_CODE) & 0x0f) << 4) | (i_l^CIPHER_CODE);

	return result;
}

void deCipherText(FILE *fp_tx, FILE *fp_out, unsigned char cipher_code)
{
	int file_size = fsize(fp_tx);

	char *inputdata = (char*)calloc(sizeof(char), file_size);		//문자열 저장을 위한 동적배열 할당
	char *temp = (char*)calloc(sizeof(char), file_size);		//문자열 저장을 위한 동적배열 할당

	if ((inputdata == NULL) || (temp == NULL))
	{
		printf("# 동적배열 할당 실패!");
		exit(1);
	}

	while (fgets(temp, file_size + 1, fp_tx) != NULL) {	//파일의 문자열을 읽어와서 동적배열에 저장
															//fsize(fp_msg+1)을 해주는 이유는 마지막에 들어갈 null 문자(/0)를 고려한 것임.
		strcat(inputdata, temp);		// 읽어온 temp string의 내용을 stringArray로 추가
	}

	for (int i = 0; i <= file_size; i ++)
	{
		unsigned char decipher_temp[2] = { 0,0 };
		if (inputdata[i] == 0x00)
		{
			break;
		}
		else if (inputdata[i] != '\n')
		{
			for (int j = 0; j < 2; j++)
			{
				decipher_temp[j] = inputdata[i+j];
			}
			fprintf(fp_out, "%c", deCipherChar(decipher_temp[0], decipher_temp[1]));
			i++;
		}
		else if (inputdata[i] == '\n')
		{
			continue;
		}
	}
	free(inputdata);

}