/*************************************************************************************************
* 작성자 : 21411947 마승현
* LAB 07
* 파일명 : main.c
* 프로그램의 목적 및 기본 기능
이 프로그램은 중복되지 않는 500,000개의 big random number array를 생성하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <time.h>

using namespace std;

#define SIZE 1000000 // 100000, 500000, 1000000
#define ITEMS_PER_LINE 10
#define FIRSTLAST_PRINTSIZE 20

void genBigRandArray(int *array, int bigRandMax);
void copyArray(int *dest, int *src, int size);
void printBigArray(int *array, int size, int firstLastPrintSize);
int partition(int *array, int size, int left, int right, int pivotIndex, int level);
void quickSort(int *array, int size, int left, int right, int level);
void selectionSort(int *array, int size);

void main()
{
	int *arr1, *arr2;
	LARGE_INTEGER freq, t1, t2;
	LONGLONG t_diff;
	double elapsed_time;

	arr1 = (int *)calloc(sizeof(int), SIZE);
	arr2 = (int *)calloc(sizeof(int), SIZE);

	srand(time(0));
	genBigRandArray(arr1, SIZE);
	copyArray(arr2, arr1, SIZE);

	printf("\nGenerated int array (before sorting): \n");
	printBigArray(arr1, SIZE, FIRSTLAST_PRINTSIZE);

	QueryPerformanceFrequency(&freq);
	printf("\nSorting array of %d integers with Quick Sorting (org) ...\n", SIZE);
	QueryPerformanceCounter(&t1);
	quickSort(arr1, SIZE, 0, SIZE - 1, 0);
	QueryPerformanceCounter(&t2);
	t_diff = t2.QuadPart - t1.QuadPart;

	elapsed_time = ((double)t_diff / freq.QuadPart) * 1000000; // in micro-second
	printf("QuickSort took %7.2f [milli-second] to sort %d integer array.\n", elapsed_time / 1000.0, SIZE);
	printf("\nSorted Array : \n");
	printBigArray(arr1, SIZE, FIRSTLAST_PRINTSIZE);


	printf("\nSorting array of %d integers with Selection Sorting ...\n", SIZE);
	QueryPerformanceCounter(&t1);
	selectionSort(arr2, SIZE);
	QueryPerformanceCounter(&t2);
	t_diff = t2.QuadPart - t1.QuadPart;

	elapsed_time = ((double)t_diff / freq.QuadPart) * 1000000; // in micro-second
	printf("SelectionSort took %7.2f [milli-second] to sort %d integer array.\n", elapsed_time / 1000.0, SIZE);

	printf("\nSorted Array : \n");

	printBigArray(arr2, SIZE, FIRSTLAST_PRINTSIZE);
	printf("\n");
}

void genBigRandArray(int *array, int bigRandMax)
{
	char *flag = (char*)calloc(sizeof(char), bigRandMax);
	unsigned int uint_32 = 0;
	unsigned int bigRand = 0;
	int count = 0;

	srand(time(NULL));			//현재 시간을 seed로 사용

	if (flag == NULL)
	{
		printf("메모리 할당 오류!\n");
		exit(1);
	}

	while (count < bigRandMax)
	{
		uint_32 = ((long)rand() << 15) | rand();		//15-bit rand short integer를 15만큼 shift한 후 다시 bit-wise or 연산을 수행

		bigRand = uint_32 % bigRandMax;
		if (flag[bigRand] == 1)
		{
			continue;
		}
		else {
			flag[bigRand] = 1;
			array[count++] = bigRand;
		}
	}

	free(flag);
}

void copyArray(int *dest, int *src, int size)
{
	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

void printBigArray(int *array, int size, int firstLastPrintSize)
{
	int count = 0;
	for (int i = 0; i < firstLastPrintSize; i++)
	{

		printf("%8d", array[i]);
		count += 1;
		if (count == ITEMS_PER_LINE)
		{
			count = 0;
			printf("\n");
		}
		else {
			printf(",");
		}
	}
	printf("\n");

	count = 0;
	for (int i = (size - firstLastPrintSize); i < size; i++)
	{
		printf("%8d", array[i]);
		count += 1;
		if (count == ITEMS_PER_LINE)
		{
			count = 0;
			printf("\n");
		}
		else {
			printf(",");
		}
	}
}
int partition(int *array, int size, int left, int right, int pivotIndex, int level)
{
	/************************** PRINT MTRX FOR DEBUGGING **************************
	printf("Quick sort : level[%d], left[%d], right[%d]\n", level, left, right);
	int count = 0;
	for (int i = 0; i < 20; i++)
	{
	if (i == pivotIndex)
	{
	printf("[%8d]", array[i]);
	}
	else if (i == left)
	{
	printf("<%8d", array[i]);
	}
	else if (i == right) {
	printf("%8d>", array[i]);
	}
	else {
	printf("%8d", array[i]);
	}

	count += 1;
	if (count == ITEMS_PER_LINE)
	{
	count = 0;
	printf("\n");
	}
	else {
	printf(",");
	}
	}
	printf("\n");
	*******************************************************************************/

	int pivotValue = array[pivotIndex];
	int storeIndex = left;

	int temp = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = temp;

	for (int i = left; i < right; i++)
	{
		if (array[i] <= pivotValue)
		{
			temp = array[i];
			array[i] = array[storeIndex];
			array[storeIndex] = temp;
			storeIndex += 1;
		}
	}
	temp = array[storeIndex];
	array[storeIndex] = array[right];
	array[right] = temp;



	return storeIndex;
}

void quickSort(int *array, int size, int left, int right, int level)
{
	if (left >= right) {
		return;
	}
	else if (left < right) {
		int pivotIndex = (left + right) / 2;
		int new_pivotIndex = partition(array, size, left, right, pivotIndex, level);

		level += 1;
		if (left < (new_pivotIndex - 1))
		{
			quickSort(array, size, left, (new_pivotIndex - 1), level);
		}
		if ((new_pivotIndex + 1) < right)
		{
			quickSort(array, size, (new_pivotIndex + 1), right, level);
		}

	}
}

void selectionSort(int *array, int size)
{
	int temp, least;
	for (int i = 0; i < size; i++)
	{
		least = i;

		for (int j = i + 1; j < size; j++)
		{
			if (array[j] < array[least])
			{
				least = j;
			}
		}

		if (least != i)
		{
			temp = array[i];
			array[i] = array[least];
			array[least] = temp;
		}

	}

}