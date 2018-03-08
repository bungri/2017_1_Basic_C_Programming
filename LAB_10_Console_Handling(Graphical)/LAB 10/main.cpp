/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 10
 * 파일명 : main.cpp
 * 프로그램의 목적 및 기본 기능
   이 프로그램은 원과 원에 내접하는 다각형, 고조파의 합을 나타내는 그래프, 색상 코드표,
   3차원 색상 그래프를 출력하는 역할을 수행하는 프로그램입니다.
*************************************************************************************************/
#include <stdio.h>
#include <math.h>
#include "PixelDrawing.h"

#define TEST_CIRCLE_AND_POLYGON				//원과 원에 내접하는 다각형
//#define TEST_SUM_OF_WEIGHTED_HARMONICS		//고조파의 합을 나타내는 그래프
//#define TEST_STANDARD_COLOR_CODES				//색상 코드표
//#define TEST_3D_COLORING_ANIMATION			//3차원 색상 그래프


#define MAX_NUM_COLOR_CODES 200

void main()
{
	HDC hdc;
	int base, height;
	int thickness;
	hdc = get_dev_context();

#ifdef TEST_CIRCLE_AND_POLYGON
	int POS_X = 500, POS_Y = 500;
	Position pos_org = { POS_X, POS_Y };
	int pen_thickness;
	int RADIUS = 300;
	int X_AXIS_LOW = -(RADIUS + 30);
	int X_AXIS_HIGH = (RADIUS + 30);
	int Y_AXIS_LOW = (RADIUS + 30);
	int Y_AXIS_HIGH = -(RADIUS + 30);

	GridAttr gridAttr =
	{
		2, // dimension
		-RADIUS, // grid_x_low
		RADIUS, //grid_x_high
		-RADIUS, // grid_y_low
		RADIUS, // grid_y_high
		0, // grid_z_low
		0, //grid_z_high
		0, // zaxis_dir, direction of z-axis from x-axis in degree
		50, //grid_step
	};

	TCHAR str_X_axis[16] = "X axis";
	TCHAR str_Y_axis[16] = "Y axis";
	drawCircle(hdc, pos_org, RADIUS, 4, BLUE, GREEN);
	drawPolygon(hdc, pos_org, RADIUS, 6, 4, RED, YELLOW);
	drawPolygon(hdc, pos_org, RADIUS * 2 / 3, 5, 4, BLACK, RED);
	drawCircle(hdc, pos_org, RADIUS / 4, 4, BLUE, GREEN);
	pen_thickness = 2;
	drawGrid(hdc, pos_org, gridAttr, pen_thickness, BLACK);
	SetBkColor(hdc, color_array[WHITE]);
	SetTextColor(hdc, color_array[RED]);
	TextOut(hdc, POS_X + X_AXIS_HIGH, POS_Y, str_X_axis, strlen(str_X_axis));
	TextOut(hdc, POS_X, POS_Y + Y_AXIS_HIGH, str_Y_axis, strlen(str_Y_axis));
#endif

#ifdef TEST_STANDARD_COLOR_CODES
	FILE *fin, *fout;
	//char colorNameCode0[] = "inputData.txt";
	char colorNameCode0[] = "StandardColorNameHexCode_inColorGroup.txt";
	char colorNameCode[] = "StandardColorNameHexCode_ColorGrouping.txt";
	ColorNameCode colors[MAX_NUM_COLOR_CODES];
	char colorName[MAX_COLOR_NAME_LEN] = { '\0' };
	char RGBhexCodeStr[7] = { '\0' };
	RGBHexCode rgbHexCode;

	fin = fopen(colorNameCode0, "r");
	if (fin == NULL)
	{
		printf("Error in file open (%s) !!\n", colorNameCode0);
		exit(-1);
	}
	fout = fopen(colorNameCode, "w");
	if (fout == NULL)
	{
		printf("Error in file open (%s) !!\n", colorNameCode);
		exit(-1);
	}

	int color_count = 0;
	while (fscanf(fin, "%s %s", colorName, RGBhexCodeStr) != EOF)
	{
		strcpy(colors[color_count].name, colorName);
		for (int i = strlen(colorName); i < MAX_COLOR_NAME_LEN; i++)
		{
			colors[color_count].name[i] = '\0';
		}
		getRGBHexCode(RGBhexCodeStr, &rgbHexCode);
		colors[color_count].rgbhexCode = rgbHexCode;
		if (color_count >= MAX_NUM_COLOR_CODES)
		{
			break;
		}
		fprintf(fout, "%20s %10s\n", colors[color_count].name, RGBhexCodeStr);
		color_count++;
	}
	fclose(fout);
	fclose(fin);

	int width = 140, length = 25;
	int x_step = 150, y_step = 50;
	int pen_thickness = 1;
	Position pos_org = { 50, 50 };
	Position pos;
	int x, y;
	COLORREF color, line_color, brush_color;
	TCHAR str[64] = { '\0' };
	x = 0; y = 0;

	for (int i = 0; i < color_count; i++)
	{
		pos.x = pos_org.x + x;
		pos.y = pos_org.y + y;
		TextOut(hdc, pos.x, pos.y - 20, colors[i].name, strlen(colors[i].name));
		line_color = brush_color = RGB(colors[i].rgbhexCode.redCode, colors[i].rgbhexCode.greenCode, colors[i].rgbhexCode.blueCode);
		drawRectangle(hdc, pos, width, length, pen_thickness, line_color, brush_color);
		x = (x + x_step) % (x_step * 10);
		if (x == 0)
		{
			y = (y + y_step) % (y_step * 30);
		}
	}
#endif

#ifdef TEST_3D_COLORING_ANIMATION
		Position pos_org =
		{
			500, //pos_org.x
			400 //pos_org.y
		};
		GridAttr gridAttr =
		{
			3, // dimension
			0, // grid_x_low
			305, //grid_x_high
			0, // grid_y_low
			305, // grid_y_high
			0, // grid_z_low
			305, //grid_z_high
			225, // zaxis_dir, direction of z-axis from x-axis in degree
			50, //grid_step
		};
		int pen_thickness;
		COLORREF color;
		int red, grn, blu;
		int x, y, z, z_x, z_y, z_high;
		double zaxis_x_cos, zaxis_y_sin;
		TCHAR str[128];
		char ch;
		PLANENUM planeno;
		int base_color;
		PLANENUM planeArray[3] = { PLANE_RED_GREEN, PLANE_RED_BLUE, PLANE_GREEN_BLUE };
		char* base_color_name[3] = { "Blue", "Green", "Red" };

		pen_thickness = 2;
		drawGrid(hdc, pos_org, gridAttr, pen_thickness, BLACK);
		printf("Press any key to continue to next ...\n");
		flushall();
		getch();
		zaxis_x_cos = cos(gridAttr.zaxis_dir*PI / 180);
		zaxis_y_sin = sin(gridAttr.zaxis_dir*PI / 180);
		for (int i = 0; i < 3; i++)
		{
			//printf("Put pixels on Plane %s ...\n", planes[i]);
			planeno = planeArray[i];
			base_color = 0;
			putPixelsOnPlane(hdc, pos_org, gridAttr, planeno, base_color);
			printf("Press any key to continue to next ...\n");
			flushall();
			getch();
		}
		drawGrid(hdc, pos_org, gridAttr, pen_thickness, BLACK);
		printf("Press any key to continue to next step (animation of coloring) ...\n");
		flushall();
		getch();
		for (int i = 0; i < 3; i++)
		{
			system("cls");
			printf("Pixel coloring with %s = 0 .. 255\n", base_color_name[i]);
			drawGrid(hdc, pos_org, gridAttr, pen_thickness, BLACK);
			planeno = planeArray[i];
			for (int base_color = 0; base_color < 256; base_color++)
			{
				putPixelsOnPlane(hdc, pos_org, gridAttr, planeno, base_color);
			}
			printf("Press any key to continue to next ...\n");
			flushall();
			getch();
		} // end for
#endif

#ifdef TEST_SUM_OF_WEIGHTED_HARMONICS
		Position pos_org = { X_MARGIN, Y_MARGIN+MAX_Y/2 };
		GridAttr gridAttr =
		{
			2, // dimension
			-10, // grid_x_low
			1000, //grid_x_high
			-400, // grid_y_low
			400, // grid_y_high
			0, // grid_z_low
			0, //grid_z_high
			0, // zaxis_dir, direction of z-axis from x-axis in degree
			50, //grid_step
		};
		TrigonoAttr trigonoAttr =
		{
			300.0, // trigonoAttr.amplitude = 300.0;
			500.0, // trigonoAttr.wavelength = 1000.0;
			1.0, //trigonoAttr.frequency = 2.0;
			0.0, //trigonoAttr.phase_offset = 0.0; // in degree
			1.0 //trigonoAttr.step_size = 1.0;
		};
		int num_harmonics;
		int pen_thickness = 2;
		int color_no = 0;
		Color pen_color;
		Color colors[NUM_COLOR] = { WHITE,BLACK,RED,GREEN,BLUE,YELLOW };

		drawGrid(hdc, pos_org, gridAttr, pen_thickness, BLACK);
		int count = 1;
		do {
			printf("Input the upper limit of harmonics N (odd number, -1 to terminate)");
				scanf("%d", &num_harmonics);
			if (num_harmonics == -1)
				break;
			if (count >= NUM_COLOR)
			{
				count = 0;
			}
			pen_color = colors[count];
			drawSumOfWeightedHarmonicsGraph(hdc, pos_org, trigonoAttr, num_harmonics, pen_thickness, pen_color);
			count++;
		} while (1);
#endif
		release_dev_context(hdc);
}