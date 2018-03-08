/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 10
 * 파일명 : TrigonoMetricPixelDrawing.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 sum of weighted harmonics graph 를 그리기 위한 함수가 포함되어 있습니다.
*************************************************************************************************/

#include "PixelDrawing.h"

void drawSineGraph(HDC hdc, Position pos_org, TrigonoAttr trigonoAttr, int pen_thickness, Color color)
{

}

double sumOfWeightedHarmonics(double amp, double freq, int n, int time)
{
	double y, swh;
	swh = MAX_Y / 2;
	for (int i = 1; i <= n; i++)
	{
		if (i % 2 == 1)
		{
			y = -(((4.0*amp) / PI) *(sin((2 * freq * i * (time - X_MARGIN)) / MAX_X * PI) / i));
			swh += y;
		}
	}
	return swh;
}

void drawSumOfWeightedHarmonicsGraph(HDC hdc, Position pos_org, TrigonoAttr trigonoAttr, int num_harmonics, int pen_thickness, Color color)
{
	POINT p1, p2;
	p1 = { X_MARGIN,Y_MARGIN + MAX_Y / 2 };
	p2 = { X_MARGIN,Y_MARGIN + MAX_Y / 2 };
	for (p2.x = X_MARGIN; p2.x < (MAX_X + X_MARGIN); p2.x++)
	{
		p2.y = sumOfWeightedHarmonics(trigonoAttr.amplitude, trigonoAttr.frequency, num_harmonics, p2.x) + Y_MARGIN;
		drawLine(hdc, p1, p2, pen_thickness, color);
		p1 = p2;
	}
}