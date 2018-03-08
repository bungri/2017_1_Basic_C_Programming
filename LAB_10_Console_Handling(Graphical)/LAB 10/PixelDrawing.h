/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 10
 * 파일명 : PixelDrawing.h
 * 프로그램의 목적 및 기본 기능
   이 파일은 pixelDrawing을 하기 위한 구조체와 함수 프로토타입이 포함되어 있는 헤더 파일입니다.
*************************************************************************************************/

#ifndef PIXEL_GRAPHIC_H
#define PIXEL_GRAPHIC_H

#include <Windows.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


#define PI 3.141592
#define MAX_X 1000
#define MAX_Y 900
#define X_MARGIN 50
#define Y_MARGIN 50
#define MAX_COLOR_NAME_LEN 32

enum Color
{
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	NUM_COLOR
};

enum PLANENUM
{
	PLANE_RED_GREEN,
	PLANE_RED_BLUE,
	PLANE_GREEN_BLUE
};

extern COLORREF color_array[];

/*
PEN_TYPE

#define PS_SLOID 0
#define PS_DASH 1	// -------
#define PS_DOT 2	// .......
#define PS_DASHDOT 3	//_._._._.
#define PA_DASHDOTDOT 4	//_.._.._..
#define PS_NULL 5
#define PS_INSIDEFRAME 6
#define PS_USERSTYLE 7
#define PS_ALTERNATE 8
*/

typedef struct Position
{
	int x; //position x
	int y; //position y
} Position;

typedef struct TrigonoAttr
{
	double amplitude;
	double wavelength;
	double frequency;
	double phase_offset;
	double step_size;
}TrigonoAttr;

typedef struct GridAttr
{
	int dimension;
	int grid_x_low;
	int grid_x_high;
	int grid_y_low;
	int grid_y_high;
	int grid_z_low;
	int grid_z_high;
	int zaxis_dir;
	int grid_step;
	
}GridAttr;

typedef struct RGBHexCode
{
	unsigned char redCode;
	unsigned char greenCode;
	unsigned char blueCode;
}RGBHexCode;

typedef struct ColorNameCode
{
	char name[MAX_COLOR_NAME_LEN];
	RGBHexCode rgbhexCode;
}ColorNameCode;

void drawGrid(HDC hdc, Position pos_org, GridAttr gridAttr, int line_thickness, Color line_color);
//void drawLine(HDC hdc, int x1, int y1, int x2, int y2, int line_thickness, int line_color);
//void drawLine(HDC hdc, Position p1, Position p2, int line_thickness, int color);
void drawLine(HDC hdc, POINT p1, POINT p2, int pen_thickness, int line_color);

//void drawArray(HDC hdc, int *array, int left, int right, int color);
HDC get_dev_context();
void release_dev_context(HDC hdc);
void drawRectangle(HDC hdc, Position pos_org, int width, int length, int pen_thickness, COLORREF line_color, COLORREF bruch_color);

//void drawXYaxis(HDC hdc, int pos_x, int pos_y, int x_minus, int x_plus, int y_minus, int y_plus, int grid_step, int line_thickness, Color color);

void drawTriangle(HDC hdc, Position pos_org, int base, int height, Color color);
void drawPolygon(HDC hdc, Position pos_org, int radius, int num_poly, int pen_thickness,Color line_color, Color brush_color);
void drawCircle(HDC hdc, Position pos_org, int radius, int pen_thickness, Color line_color, Color brush_color);

void drawSineGraph(HDC hdc, Position pos_org, TrigonoAttr trigonoAttr, int pen_thickness, Color color);
void drawSumOfWeightedHarmonicsGraph(HDC hdc, Position pos_org, TrigonoAttr trigonoAttr, int num_harmonics, int pen_thickness, Color color);
double sumOfWeightedHarmonics(double amp, double freq, int n, int time);

void putPixelsOnPlane(HDC hdc, Position pos_org, GridAttr gridAttr, PLANENUM planeno, int base_color);

void getRGBHexCode(char *RGBhexCodeStr, RGBHexCode *rgbHexCode);
#endif