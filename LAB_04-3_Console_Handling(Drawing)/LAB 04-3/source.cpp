/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 04-3
 * 파일명 : source.c
 * 프로그램의 목적 및 기본 기능
*************************************************************************************************/
#include <stdio.h>
#include <Windows.h>
#include <math.h>

#include "ConsoleDrawing.h"

int main(void)
{
	int inputC = 0;
	int amplitude, freq = 0;


	printf("input type of graph : sawtooth(0), sine(1), cosine(2), tangent(3) : ");
	scanf("%d", &inputC);
	printf("Amplitude(AMP_MAX=25) : ");
	scanf("%d", &amplitude);
	printf("Frequency : ");
	scanf("%d", &freq);
	switch (inputC)
	{
	case 0: printf("Drawing saw-tooth : amplitude = %d, freq = %d\n",amplitude,freq);
			drawing_pane();
			saw_tooth(amplitude, freq);
		break;
	case 1: printf("Drawing sine graph : amplitude = %d, freq = %d\n", amplitude, freq);
			drawing_pane();
			sin_gr(amplitude, freq);
		break;
	case 2: printf("Drawing cosine graph : amplitude = %d, freq = %d\n", amplitude, freq);
			drawing_pane();
			cos_gr(amplitude, freq);
		break;
	case 3: printf("Drawing tangent graph : amplitude = %d, freq = %d\n", amplitude, freq);
			drawing_pane();
			tan_gr(amplitude, freq);
		break;
	default: printf("Wrong Input!\n");
	}




	return 0;
}

