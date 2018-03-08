/*************************************************************************************************
* 작성자 : 21411947 마승현
* LAB 06-1
* 파일명 : main.c
* 프로그램의 목적 및 기본 기능
이 프로그램은 입력 데이터가 포함된 파일에서 행렬을 읽어와 행렬의 덧셈,뺄셈,곱셈을 수행하는
프로그램입니다.
*************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

void printMtrx(int **mA, int size_n);
void fprintMtrx(FILE* fout, int **mA, int size_n);
int initMtrx(FILE *fp, int **m, int size);
void addMtrx(int **mA, int **mB, int **mX, int size);
void subtractMtrx(int **mA, int **mB, int **mX, int size);
void multiplyMtrx(int **mA, int **mB, int **mX, int size);

int main(void)
{
	FILE *fin = NULL;
	int data;


	int **mA;
	int **mB;
	int **mC;
	int **mD;
	int **mE;

	mA = (int**)calloc(SIZE, sizeof(int*));
	mB = (int**)calloc(SIZE, sizeof(int*));
	mC = (int**)calloc(SIZE, sizeof(int*));
	mD = (int**)calloc(SIZE, sizeof(int*));
	mE = (int**)calloc(SIZE, sizeof(int*));

	for (int n = 0; n < SIZE; n++)
	{
		mA[n] = (int*)calloc(SIZE, sizeof(int));
		mB[n] = (int*)calloc(SIZE, sizeof(int));
		mC[n] = (int*)calloc(SIZE, sizeof(int));
		mD[n] = (int*)calloc(SIZE, sizeof(int));
		mE[n] = (int*)calloc(SIZE, sizeof(int));
	}

	/*
	int mA[SIZE][SIZE];
	int mB[SIZE][SIZE];
	int mC[SIZE][SIZE];
	int mD[SIZE][SIZE];
	int mE[SIZE][SIZE];
	*/

	fin = fopen("mtrx_input.txt", "r");
	if (fin == NULL)
	{
		printf("Error in input data file open!!\n");
		return 0;
	}

	if ((initMtrx(fin, mA, SIZE) == -1))
	{
		printf("Error in matrix initialization with input file");
	}
	if ((initMtrx(fin, mB, SIZE) == -1))
	{
		printf("Error in matrix initialization with input file");
	}


	printf("\n Matrix mA : \n");
	printMtrx(mA, SIZE);

	printf("\n Matrix mb : \n");
	printMtrx(mB, SIZE);

	addMtrx(mA, mB, mC, SIZE);
	printf("\n Matrix mC = mA + mB : \n");
	printMtrx(mC, SIZE);

	subtractMtrx(mA, mB, mD, SIZE);
	printf("\n Matrix mD = mA - mB : \n");
	printMtrx(mD, SIZE);

	multiplyMtrx(mA, mB, mE, SIZE);
	printf("\n Matrix mE = mA * mB : \n");
	printMtrx(mE, SIZE);

	printf("\n");

	fclose(fin);
	return 0;
}

void printMtrx(int **mA, int size_n)
{
	for (int i = 0; i < size_n; i++)
	{
		for (int j = 0; j < size_n; j++)
		{
			if ((i == 0) && (j == 0))	//왼쪽 맨 위
			{
				printf("%c%c %5d", 0xa6, 0xa3, mA[i][j]);
			}
			else if ((i == (size_n - 1)) && (j == (size_n - 1))) //오른쪽 맨 밑
			{
				printf("%5d %c%c", mA[i][j], 0xa6, 0xa5);
			}
			else if ((i == (size_n - 1)) && (j == 0))	//왼쪽 맨 밑
			{
				printf("%c%c %5d", 0xa6, 0xa6, mA[i][j]);
			}
			else if ((i == 0) && (j == (size_n - 1)))	//오른쪽 맨 위
			{
				printf("%5d %c%c", mA[i][j], 0xa6, 0xa4);
			}
			else if (j == 0)			//왼쪽줄
			{
				printf("%c%c %5d", 0xa6, 0xa2, mA[i][j]);
			}
			else if (j == (size_n - 1))	//오른쪽줄
			{
				printf("%5d %c%c", mA[i][j], 0xa6, 0xa2);
			}
			else
			{
				printf("%5d", mA[i][j]);
			}
		}
		printf("\n");
	}

}

void fprintMtrx(FILE* fout, int **mA, int size_n)
{
	for (int i = 0; i < size_n; i++)
	{
		for (int j = 0; j < size_n; j++)
		{
			if ((i == 0) && (j == 0))	//왼쪽 맨 위
			{
				fprintf(fout, "%c%c %5d", 0xa6, 0xa3, mA[i][j]);
			}
			else if ((i == (size_n - 1)) && (j == (size_n - 1))) //오른쪽 맨 밑
			{
				fprintf(fout, "%5d %c%c", mA[i][j], 0xa6, 0xa5);
			}
			else if ((i == (size_n - 1)) && (j == 0))	//왼쪽 맨 밑
			{
				fprintf(fout, "%c%c %5d", 0xa6, 0xa6, mA[i][j]);
			}
			else if ((i == 0) && (j == (size_n - 1)))	//오른쪽 맨 위
			{
				fprintf(fout, "%5d %c%c", mA[i][j], 0xa6, 0xa4);
			}
			else if (j == 0)			//왼쪽줄
			{
				fprintf(fout, "%c%c %5d", 0xa6, 0xa2, mA[i][j]);
			}
			else if (j == (size_n - 1))	//오른쪽줄
			{
				fprintf(fout, "%5d %c%c", mA[i][j], 0xa6, 0xa2);
			}
			else
			{
				fprintf(fout, "%5d", mA[i][j]);
			}
		}
		printf("\n");
	}

}

int initMtrx(FILE *fp, int **m, int size)
{
	if (m == NULL)
	{
		return -1;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				fscanf(fp, "%d", &m[i][j]);
			}
		}
		return 0;
	}
}

void addMtrx(int **mA, int **mB, int **mX, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mX[i][j] = mA[i][j] + mB[i][j];
		}
	}
}

void subtractMtrx(int **mA, int **mB, int **mX, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			mX[i][j] = mA[i][j] - mB[i][j];
		}
	}
}

void multiplyMtrx(int **mA, int **mB, int **mX, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				mX[i][j] = mX[i][j] + (mA[i][k] * mB[k][j]);
			}
		}
	}
}

