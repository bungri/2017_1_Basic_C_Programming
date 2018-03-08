/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 09
 * 파일명 : main.cpp
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 은하계(Galaxy)를 위한 구조체(Struct Star)배열입니다.
*************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

//#include <fstream>
//#include <iostream>
//#include <string>

#include "Star.h"

#define NUM_STARS 500000
#define PRINT_SIZE 100

//using namespace std;

void genBigRandArray(int arrID[], int bigRandMax);
void initArrayStars(Star arrStars[], int size, int arrID[]);
void fprintBigArray(FILE *fout, Star *pSA, int size, int printSize);
void quickSortGalaxyById(Star *pSA, int left, int right);
void selectionSortGalaxyByName(Star *pSA, int numStars);

void printBigArray(Star *pSA, int size, int printSize);
int partition(Star *pSA, int left, int right, int pivotIndex);
void starswp(Star *dest, Star *source);

int main(void)
{
	FILE *fout;
	Star *pS;
	Star *glxStars;
	int *starIDs, i, sID;

	LARGE_INTEGER freq, t_1, t_2;
	LONGLONG t_diff;
	double elapsed_time, accumulated_elapsedTime;

	QueryPerformanceFrequency(&freq);

	fout = fopen("output.txt", "w+");
	if (fout == NULL)
	{
		printf("Outputfile (output.txt) open failed !! \n");
	}

	glxStars = (Star*)malloc(sizeof(Star)*NUM_STARS);
	starIDs = (int*)malloc(sizeof(int)*NUM_STARS);
	genBigRandArray(starIDs, NUM_STARS);
	initArrayStars(glxStars, NUM_STARS, starIDs);

	printf("\ninitializedGalaxy (array of stars)\n");
	fprintf(fout, "\ninitializedGalaxy (array of stars)\n");
	fprintBigArray(fout, glxStars, NUM_STARS, PRINT_SIZE);
	printBigArray(glxStars, NUM_STARS, PRINT_SIZE);

	//Quick Sorting

	printf("\nQuick sorting Galaxy...");
	fprintf(fout, "\nQuick sorting Galaxy...");
	QueryPerformanceCounter(&t_1);
	quickSortGalaxyById(glxStars, 0, NUM_STARS - 1);
	QueryPerformanceCounter(&t_2);

	t_diff = t_2.QuadPart - t_1.QuadPart;
	elapsed_time = ((double)t_diff / freq.QuadPart);
	printf("\nTime for quickSorting of array of stars : %f seconds\n", elapsed_time);
	printf("Sorted Galaxy (array of stars) by Star_ID : \n");
	fprintf(fout, "\nTime for quickSorting of array of stars : %f seconds\n", elapsed_time);
	fprintf(fout, "Sorted Galaxy (array of stars) by Star_ID : \n");
	fprintBigArray(fout, glxStars, NUM_STARS, PRINT_SIZE);
	printBigArray(glxStars, NUM_STARS, PRINT_SIZE);

	//Selection Sorting

	printf("\nSelection sorting Galaxy bt name..");
	fprintf(fout, "\nSelection sorting Galaxy bt name..");
	QueryPerformanceCounter(&t_1);
	selectionSortGalaxyByName(glxStars, NUM_STARS);
	QueryPerformanceCounter(&t_2);

	t_diff = t_2.QuadPart - t_1.QuadPart;
	elapsed_time = ((double)t_diff / freq.QuadPart);
	printf("\nTime for selectionSorting of array of stars : %f seconds\n", elapsed_time);
	printf("Sorted Galaxy (array of stars) by Star_ID : \n");
	fprintf(fout, "\nTime for selectionSorting of array of stars : %f seconds\n", elapsed_time);
	fprintf(fout, "Sorted Galaxy (array of stars) by Star_ID : \n");
	fprintBigArray(fout, glxStars, NUM_STARS, PRINT_SIZE);
	printBigArray(glxStars, NUM_STARS, PRINT_SIZE);

	fclose(fout);
	return 0;
}

void genBigRandArray(int arrID[], int bigRandMax)
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
			arrID[count++] = bigRand;
		}
	}

	free(flag);

}

void initArrayStars(Star arrStars[], int size, int arrID[])
{
	srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		/************ arrStars[i].name ************/
		int Length = (rand() % 11) + 5;
		for (int j = 0; j <= Length; j++)
		{
			if (j == 0)
			{
				arrStars[i].name[j] = (char)(rand() % 26 + 'A');
			}
			else if(j==Length)
			{
				arrStars[i].name[j] = '\0';
			}
			else
			{
				arrStars[i].name[j] = (char)(rand() % 26 + 'a');
			}
		}
		/************ arrStars[i].id ************/
		arrStars[i].id = arrID[i];

		/************ arrStars[i].size, color ************/
		arrStars[i].size = rand()%8;
		arrStars[i].color = rand() % 8;

		/************ arrStars[i].grade ************/
		arrStars[i].grade = rand() % 4;

		/************ arrStars[i].distance, luminosity, mass, radius, age ************/
		arrStars[i].distance = (rand() % 9990) + 10.0;
		arrStars[i].luminosity = (rand() % 9990) + 10.0;
		arrStars[i].mass = (rand() % 9990) + 10.0;
		arrStars[i].radius = (rand() % 9990) + 10.0;
		arrStars[i].age = (rand() % 9990) + 10.0;
	}
}

void fprintBigArray(FILE *fout, Star *pSA, int size, int printSize)
{
	for (int i = 0; i < printSize; i++)
	{
		fprintf(fout, "%s(%d)", (pSA+i)->name, (pSA+i)->id);
		if ((i != 0) && (i%10 == 0))
		{
			fprintf(fout, "\n");
		}
	}
}
void printBigArray(Star *pSA, int size, int printSize)
{
	for (int i = 0; i < printSize; i++)
	{
		printf("%s(%d)", (pSA + i)->name, (pSA + i)->id);
		if ((i != 0) && (i % 10 == 0))
		{
			printf("\n");
		}
		else
		{
			printf(" ");
		}
	}
	printf("\n");

}

void quickSortGalaxyById(Star *pSA, int left, int right)
{
	if (left >=right)
		return;
	else if (left < right)
	{
		int pivotIndex = (left + right) / 2;
		int new_pivotIndex = partition(pSA, left, right, pivotIndex);

		if (left < (new_pivotIndex - 1))
		{
			quickSortGalaxyById(pSA, left, new_pivotIndex - 1);
		}
		if ((new_pivotIndex + 1) < right)
		{
			quickSortGalaxyById(pSA, new_pivotIndex + 1, right);
		}
	}
}

int partition(Star *pSA, int left, int right, int pivotIndex)
{
	int pivotValue = (pSA + pivotIndex)->id;
	starswp((pSA + pivotIndex), (pSA + right));
	int si_l = left;
	int si_r = right - 1;
	while (si_l <= si_r)
	{
		while ((si_l <= si_r) && (((pSA + si_l)->id) <= pivotValue))
		{
			si_l++;
		}
		while ((si_r >= si_l) && (pivotValue <= ((pSA + si_r)->id)))
		{
			si_r--;
		}
		if (si_l < si_r)
		{
			starswp((pSA + si_l), (pSA + si_r));
		}
	}
	if (si_l != right)
	{
		starswp((pSA + si_l), (pSA + right));
	}
	return si_l;
}

void selectionSortGalaxyByName(Star *pSA, int numStars)
{
	int temp, least;
	for (int i = 0; i < numStars; i++)
	{
		least = i;

		for (int j = i + 1; j < numStars; j++)
		{
			if (strcmp((pSA+least)->name,(pSA+j)->name)>0)
			{
				least = j;
			}
		}

		if (least != i)
		{
			starswp((pSA + i), (pSA + least));
		}

	}

}

void starswp(Star *dest, Star *source)
{
	Star temp;

	/************ name ************/
	strcpy(temp.name, dest->name);
	strcpy(dest->name, source->name);
	strcpy(source->name, temp.name);

	/************ id ************/
	temp.id = dest->id;
	dest->id = source->id;
	source->id = temp.id;

	/************ size, color ************/
	temp.size = dest->size;
	dest->size = source->size;
	source->size = temp.size;

	temp.color = dest->color;
	dest->color = source->color;
	source->color = temp.color;

	/************ grade ************/
	temp.grade = dest->grade;
	dest->grade = source->grade;
	source->grade = temp.grade;

	/************ distance, luminosity, mass, radius, age ************/
	temp.distance = dest->distance;
	dest->distance = source->distance;
	source->distance = temp.distance;

	temp.luminosity = dest->luminosity;
	dest->luminosity = source->luminosity;
	source->luminosity = temp.luminosity;

	temp.mass = dest->mass;
	dest->mass = source->mass;
	source->mass = temp.mass;

	temp.radius = dest->radius;
	dest->radius = source->radius;
	source->radius = temp.radius;

	temp.age = dest->age;
	dest->age = source->age;
	source->age = temp.age;

}