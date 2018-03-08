/*************************************************************************************************
* 작성자 : 21411947 마승현
* LAB 05
* 파일명 : source.c
* 프로그램의 목적 및 기본 기능
  이 프로그램은 텍스트파일 Message.txt를 읽어와 출력파일인 Output.txt로 옮기는 파일입니다.
*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int fsize(FILE *fp);						//파일의 크기를 구하기 위한 함수 원형
void FileToStr(FILE *FP);						//파일의 내용을 출력하기 위한 함수 원형

int main(void)
{
	FILE *fp_msg, *fp_out = NULL;					//File 포인터 *fp를 생성하고 NULL로 초기화

/*****************************************************파일 입력부*****************************************************/

	fp_msg = fopen("Message.txt", "r");		//Message.txt를 읽기모드로 열고, 그 주소를 fp에 저장
	int file_size = fsize(fp_msg);

	if (fp_msg == NULL)
	{
		printf("# 파일 열기 실패!\n");
		exit(1);
	}
	else {
		printf("# 파일 열기 성공!\n");
	}

	//동적배열 할당부
	char *inputdata = (char*)calloc(sizeof(char), fsize(fp_msg));		//문자열 저장을 위한 동적배열 할당
	if (inputdata == NULL)
	{
		printf("# 동적배열 할당 실패!");
		exit(1);
	}

	FileToStr(fp_msg, inputdata);

	printf("-----입력파일의 내용은 아래와 같습니다.-----\n");
	printf("%s\n", inputdata);
	printf("--------------------------------------------\n\n");
	fclose(fp_msg);			//입력파일 닫기

/*****************************************************파일 출력부*****************************************************/

	fp_out = fopen("Output.txt", "w+");			//Output.txt를 읽기, 열기 모드로 엶. 파일이 없으면 만들고 있어도 덮어씌움.

	if (fp_out == NULL)
	{
		printf("# 파일 열기 실패!\n");
		exit(1);
	}
	else {
		printf("# 파일 열기 성공!\n");
	}

	fputs(inputdata, fp_out);					//동적배열에 저장되어있는 문자열을 Output.txt에 삽입

	printf("-----출력파일의 내용은 아래와 같습니다.-----\n%s\n", inputdata);
	fprintf(fp_out, inputdata);
	printf("--------------------------------------------\n\n");


	fclose(fp_out);			//출력파일 닫기
	free(inputdata);		//동적할당 메모리 반납
	return 0;
}

int fsize(FILE *fp)				//파일의 크기를 구하는 함수
{
	if (fgetc(fp) != EOF)
	{
		int result = 0;
		fseek(fp, 0, SEEK_END);	//포인터의 위치를 끝으로 옮긴다.
		result = ftell(fp);
		fseek(fp, 0, SEEK_SET);	//포인터의 위치를 다시 처음으로 옮긴다.
		return result;
	}
}

void FileToStr(FILE *fp, char* strArray)			//파일의 내용을 출력하는 함수
{
	char *temp = (char*)calloc(sizeof(char), fsize(fp));		//문자열 저장을 위한 동적배열 할당
	int file_size = fsize(fp);

	if (temp == NULL)
	{
		printf("# 동적배열 할당 실패!");
		exit(1);
	}

	while (fgets(temp, file_size + 1, fp) != NULL) {	//파일의 문자열을 읽어와서 동적배열에 저장
														//fsize(fp_msg+1)을 해주는 이유는 마지막에 들어갈 null 문자(/0)를 고려한 것임.
		strcat(strArray, temp);		// 읽어온 temp string의 내용을 stringArray로 추가

	}

	free(temp);
}