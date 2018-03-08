/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 06-2
 * 파일명 : main.c
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 입력파일로부터 행렬을 받아와 가우스-조단 소거법으로 연산을 수행하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5 // size of linear system
#define EPSILON 0.000001

void diagonalize(double **mtrxAug, int size_N, int size_M, int *solExist);
void pivoting(double **augMtrx, int size_N, int size_M, int p, int *piv_found);
void printDblArray(double **mA, int size_n, int size_m);

int main(void)
{
	FILE *fin;
	int size_N;
	double *x;
	double **augMtrx;
	int i, j, solExist = 1, error = 0;
	double d;

	fin = fopen("augMtrx.txt", "r");

	if (fin == NULL)
	{
		printf("Error in opening input.txt file !!\n");
		exit(-1);
	}
	fscanf(fin, "%d", &size_N);

	augMtrx = (double **)calloc(size_N, sizeof(double *));				//이중 동적배열 선언
	for (int n = 0; n < size_N; n++)
	{
		augMtrx[n] = (double *)calloc((size_N + 1), sizeof(double));
	}

	x = (double *)calloc(size_N, sizeof(double));			//해를 입력하기 위한 동적배열 선언
	printf("Augmented Matrix size_N : %d\n", size_N);

	for (int n = 0; n < size_N; n++)
		for (int m = 0; m < size_N + 1; m++)
		{
			fscanf(fin, "%lf", &d);
			//printf("augMtrx[%d][%d] = %5.1f, ", n, m, d);
			augMtrx[n][m] = d;
		}

	printf("Augmented Matrix : \n");
	printDblArray(augMtrx, size_N, size_N + 1);

	diagonalize((double **)augMtrx, N, N + 1, &solExist);

	if (solExist) {
		printf("The solution of the given linear system:\n");
		for (i = 0; i < N; i++) {
			x[i] = augMtrx[i][N];
			printf(" x[%d] : %4f\n", i, augMtrx[i][N]);
		}
	}
	else {
		printf("No unique solution\n");

	}

	fclose(fin);
	return 0;
}

void diagonalize(double **mtrxAug, int size_N, int size_M, int *solExist)
{
	int piv_found = 0;

	double pivot_scale, w;

	for (int p = 0; (*solExist) && (p < size_N); p++)
	{
		pivoting(mtrxAug, size_N, size_M, p, solExist);		//피보팅을 수행


		if (mtrxAug[p][p] != 1.0)
		{
			pivot_scale = mtrxAug[p][p];
			mtrxAug[p][p] = 1.0;

			for (int k = p + 1; k < size_M; k++)
			{
				mtrxAug[p][k] /= pivot_scale;		//대각선 행렬요소의 값을 1로 맞춰주고 나머지 열을 pivot_scale 로 나눠줌
			}

		}
		else {
			break;
		}

		for (int j = 0; j < size_N; j++)
		{
			if ((j != p) && (mtrxAug[j][p] != 0.0))
			{
				w = mtrxAug[j][p];
				mtrxAug[j][p] = 0.0;

				for (int k = p + 1; k <= size_N; k++)
				{
					mtrxAug[j][k] -= w * mtrxAug[p][k];
				}
			}
		}

	}

}

void pivoting(double **augMtrx, int size_N, int size_M, int p, int *piv_found)
{
	double xTemp;
	int max_row;

	double xmax = fabs(augMtrx[p][p]);	
	max_row = p;

	for (int j = p + 1; j < size_N; j++)
	{
		if (fabs(augMtrx[j][p]) > xmax)
		{
			xmax = fabs(augMtrx[j][p]);
			max_row = j;
		}

	}

	if (fabs(xmax) < EPSILON) {
		*piv_found = 0;
	}

	else
	{
		*piv_found = 1;
		if (max_row != p)
		{
			for (int k = p; k < size_M; k++)
			{
				xTemp = augMtrx[p][k];
				augMtrx[p][k] = augMtrx[max_row][k];
				augMtrx[max_row][k] = xTemp;
			}
		}
	}
}

void printDblArray(double **mA, int size_n, int size_m)
{
	for (int i = 0; i < size_n; i++)
	{
		for (int j = 0; j < size_m; j++)
		{
			if ((i == 0) && (j == 0))	//왼쪽 맨 위
			{
				printf("%c%c %7.2f", 0xa6, 0xa3, mA[i][j]);
			}
			else if ((i == (size_n - 1)) && (j == 0))	//왼쪽 맨 밑
			{
				printf("%c%c %7.2f", 0xa6, 0xa6, mA[i][j]);
			}
			else if ((i == 0) && (j == (size_m - 1)))	//오른쪽 맨 위
			{
				printf("%7.2f %c%c", mA[i][j], 0xa6, 0xa4);
			}
			else if ((i == (size_n - 1)) && (j == (size_m - 1))) //오른쪽 맨 밑
			{
				printf("%7.2f %c%c", mA[i][j], 0xa6, 0xa5);
			}
			else if (j == 0)			//왼쪽줄
			{
				printf("%c%c %7.2f", 0xa6, 0xa2, mA[i][j]);
			}
			else if (j == (size_m - 1))	//오른쪽줄
			{
				printf("%7.2f %c%c", mA[i][j], 0xa6, 0xa2);
			}
			else
			{
				printf("%7.2f", mA[i][j]);
			}
		}
		printf("\n");
	}


}
