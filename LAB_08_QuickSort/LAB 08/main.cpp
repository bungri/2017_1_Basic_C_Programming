#include <stdio.h> 
#include <string.h>
#include <stdlib.h> 
#include <time.h> 
#include <Windows.h>
#include <psapi.h>

double power_recursive(double base, double exponent);
double power_iterative(double base, double exponent);

#define MAX_WORD_LENGTH 10 
#define MIN_WORD_LENGTH 5 
#define NUM_WORDS 10000 
#define WORDS_PER_LINE 10 
#define FIRST_LAST_WORDS 20 
void genWords(char **words, int num_words, int max_word_len, int min_word_len);
//void printWord(char **word, int size);
void quickSort(char **word, int left, int right);
int partition(char **word, int left, int right, int pivotindex);
//void printArrayRange(char **words, int num_words, int left, int right, int pivotIndex); 
void printBigWordsArray(char **words, int size, int firstLastWords, int wordsPerLine);

void strswp(char *dest, char *source);

int global_var;
#define ARRAY_SIZE 100 
SIZE_T mem_usage = 0, old_usage = 0;
FILE* fout = NULL;
void recursive_call(int level);
#define MAX_RECURSIVE_DEPTH 1550
#define PRINT_LEVEL 10

SIZE_T GetProcessWorkingSetSize()
{
	PROCESS_MEMORY_COUNTERS pmc;
	if (!GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
		return 0;
	return pmc.PagefileUsage;
}

void main(int argc, char *argv[])
{
	int c;
	char command[128] = { NULL };
	char mode[16] = { NULL };
	double base, exponent, result;

	printf("argc: %d\n", argc);
	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d]: %s\n", i, argv[i]);
	}

	strcpy(command, argv[1]);

	if (strcmp(command, "power") == 0)
	{
		printf("power computation");
		strcpy(mode, argv[2]);
		base = atof(argv[3]);
		exponent = atof(argv[4]);
		if (strcmp(mode, "r") == 0)
		{
			printf("power_recursive (base = %10.5lf, exponent = %7.3lf) \n", base, exponent);
			result = power_recursive(base, exponent);
			printf(" ==> result (%15.5lf)\n", result);
		}
		else if (strcmp(mode, "i") == 0)
		{
			printf("power_iterative (base = %10.5lf, exponent = %7.3lf)> \n", base, exponent);
			result = power_iterative(base, exponent);
			printf(" ==> result (%15.5lf)\n", result);
		}
		else
		{
			printf("mode (%s) is not correct !!\n", mode);
		}
	}
	else if (strcmp(command, "WordsQuickSorting") == 0)
	{
		char **words;
		int num_words = NUM_WORDS;
		words = (char **)malloc(sizeof(char *)* num_words);
		for (int i = 0; i < num_words; i++)
		{
			words[i] = (char *)malloc(sizeof(char)* (MAX_WORD_LENGTH + 1));
		}
		srand(time(0));
		genWords(words, num_words, MAX_WORD_LENGTH, MIN_WORD_LENGTH);
		printf("%d Words before sorting : \n", num_words);
		printBigWordsArray(words, num_words, FIRST_LAST_WORDS, WORDS_PER_LINE);
		printf("\n");
		quickSort(words, 0, num_words - 1);
		printf("%d Words after sorting  : \n", num_words);
		printBigWordsArray(words, num_words, FIRST_LAST_WORDS, WORDS_PER_LINE);
		printf("\n");
		free(words);
	}
	else if (strcmp(command, "CheckMemoryAddr") == 0)
	{
		int local_x;
		static int static_local;

		fout = fopen("output.txt", "w");
		printf("Address of main() function: %p\n", main);
		printf("Address of global var: %p\n", &global_var);
		printf("Address of local var in main(): %p\n", &local_x);
		printf("Address of static local variable: %p\n", &static_local);
		fprintf(fout, "Address of main() function: %p\n", main);
		fprintf(fout, "Address of global var: %p\n", &global_var);
		fprintf(fout, "Address of local var in main(): %p\n", &local_x);
		fprintf(fout, "Address of static local variable: %p\n", &static_local);
		old_usage = mem_usage;

		recursive_call(0);
		fclose(fout);
	}
}
void recursive_call(int level)
{
	int auto_y;
	static int static_y;
	int array[ARRAY_SIZE];
	int *dynamicArray;

	if (level >= MAX_RECURSIVE_DEPTH)
		return;
	dynamicArray = (int *)malloc(sizeof(int)* ARRAY_SIZE);
	if (dynamicArray == NULL)
	{
		printf("Error in dynamic memory allocation at level (%d) \n", level);
	}
	mem_usage = GetProcessWorkingSetSize();
	if ((level % PRINT_LEVEL) == 0)
	{
		fprintf(fout, "Addr of local variables (in recursive level %3d): auto_y: %p,  static_y: %p, dynamicArray: %p, memory usage (%7d), memory increment (%7d)\n", level, &auto_y, &static_y, dynamicArray, mem_usage, mem_usage - old_usage);
		printf("Addr of local variables (in recursive level %3d): auto_y: %p,  static_y: %p, dynamicArray: %p, memory usage (%7d), memory increment (%7d)\n", level, &auto_y, &static_y, dynamicArray, mem_usage, mem_usage - old_usage);
		fflush(stdout);
		old_usage = mem_usage;
	}
	recursive_call(level + 1);
	free(dynamicArray);
}
double power_recursive(double base, double exponent)
{
	if (exponent == 0)
		return 1;
	else if (exponent > 0)
		return base*power_recursive(base, exponent - 1);
	else
		return (1 / base)*power_recursive(base, exponent + 1);

}
double power_iterative(double base, double exponent)
{
	double result = 1;
	if (exponent == 0)
	{
		result = 1;
	}
	else if (exponent > 0)
	{
		for (int i = 0; i<exponent; i++)
			result = result*base;
	}
	else
	{
		for (int i = 0; i>exponent; i--)
			result = result / base;
	}
	return result;
}
void genWords(char **words, int num_words, int max_word_len, int min_word_len)
{
	int i, j;
	char *str;
	int length;
	str = (char*)malloc(sizeof(char)*max_word_len);
	for (j = 0; j < max_word_len; j++)
		str[j] = { NULL };
	for (i = 0; i < NUM_WORDS; i++)   //  NUM_WORDS 개의단어들 생성
	{
		length = rand() % (max_word_len - min_word_len) + min_word_len;
		str[0] = rand() % 26 + 'A';
		for (j = 1; j < length; j++)  // 한 단어생성
		{
			str[j] = rand() % 26 + 'a';
		}//
		str[j] = { NULL };
		strcpy(words[i], str);
		for (j = 0; j < max_word_len; j++)
			str[j] = { NULL };
	}
	free(str);
}
void printBigWordsArray(char **words, int size, int firstLastWords, int wordsPerLine)
{

	for (int i = 0; i < firstLastWords; i++)
	{
		printf("%-15s", words[i]);

		if ((i + 1) % wordsPerLine == 0)
			printf("\n");
	}

	printf("\n\n    . . .\n\n");

	for (int i = 0; i < firstLastWords; i++) {
		printf("%-15s", words[(size - firstLastWords) + i]);
		if ((i + 1) % wordsPerLine == 0)
			printf("\n");
	}
}

int partition(char **words, int left, int right, int pivotIndex)
{
	char *pivotValue = (char*)calloc(sizeof(char), MAX_WORD_LENGTH);
	strcpy(pivotValue, words[pivotIndex]);

	int storeIndex = left;

	strswp(words[right], words[pivotIndex]);

	for (int i = left; i < right; i++)
	{
		if (strcmp(words[i], pivotValue) < 0)
		{
			strswp(words[i], words[storeIndex]);
			storeIndex += 1;
		}
	}
	strswp(words[storeIndex], words[right]);

	return storeIndex;
}

void quickSort(char **word, int left, int right)
{
	if (left >= right) {
		return;
	}
	else if (left < right) {
		int pivotIndex = (left + right) / 2;
		int new_pivotIndex = partition(word, left, right, pivotIndex);

		if (left < (new_pivotIndex - 1))
		{
			quickSort(word, left, (new_pivotIndex - 1));
		}
		if ((new_pivotIndex + 1) < right)
		{
			quickSort(word, (new_pivotIndex + 1), right);
		}

	}
}

void strswp(char *dest, char *source)		//스트링의 스왑
{
	char *tempArray = (char*)calloc(sizeof(char), MAX_WORD_LENGTH + 1);
	strcpy(tempArray, dest);
	strcpy(dest, source);
	strcpy(source, tempArray);
}