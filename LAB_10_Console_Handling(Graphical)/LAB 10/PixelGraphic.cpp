/*************************************************************************************************
 * 작성자 : 21411947 마승현
 * LAB 10
 * 파일명 : PixelGraphic.cpp
 * 프로그램의 목적 및 기본 기능
   이 파일은 pixelDrawing을 하기 위한 함수 몸체들이 포함되어 있습니다.
*************************************************************************************************/
#include "PixelDrawing.h"

COLORREF color_array[NUM_COLOR] = {
	RGB(255,255,255), //White
	RGB(0,0,0),	//Black
	RGB(255,0,0), //Red
	RGB(0,255,0), //Green
	RGB(0,0,255), //Blue
	RGB(255,255,0)	//Yellow
};

HDC get_dev_context()
{
	HWND console;
	HDC device_context;

	console = GetConsoleWindow();
	device_context = GetDC(console);
	return device_context;
}

void release_dev_context(HDC hdc)
{
	HWND console;
	console = GetConsoleWindow();
	ReleaseDC(console, hdc);
}

unsigned char getHexValue(unsigned char hexChar)
{
	unsigned char hexVal;
	if ((hexChar >= '0') && (hexChar <= '9'))
	{
		hexVal = hexChar - '0';
	}
	else if ((hexChar >= 'A') && (hexChar <= 'F'))
	{
		hexVal = hexChar - 'A' + 10;
	}
	else if ((hexChar >= 'a') && (hexChar <= 'f'))
	{
		hexVal = hexChar - 'a' + 10;
	}
	else
	{
		printf("Error in getHexColorCode :: colorHexCode(%x) is not hex code character !!\n", hexChar);
	}

	return hexVal;
}

unsigned char getHexColorCode(char colorHexCode[])
{
	unsigned char uc, colorCode;

	uc = colorHexCode[0];
	colorCode = getHexValue(uc);

	colorCode *= 16;
	uc = colorHexCode[1];
	colorCode += getHexValue(uc);

	return colorCode;
}

void getRGBHexCode(char *RGBHexCodeStr, RGBHexCode *rgbHexCode)
{
	char colorHexCode[2];
	unsigned char colorCode;

	if (rgbHexCode == NULL)
	{
		printf("Error in getRGBHexCode :: rgbHexCode is null\n");
		exit(-1);
	}
	if (strlen(RGBHexCodeStr) < 6)
	{
		printf("Errorin getRGBHexCode :: RGBHexCode is short (less then 6)\n");
		exit(-1);
	}

	colorHexCode[0] = RGBHexCodeStr[0];
	colorHexCode[1] = RGBHexCodeStr[1];
	colorCode = getHexColorCode(colorHexCode);
	rgbHexCode->redCode = colorCode;

	colorHexCode[0] = RGBHexCodeStr[2];
	colorHexCode[1] = RGBHexCodeStr[3];
	colorCode = getHexColorCode(colorHexCode);
	rgbHexCode->greenCode = colorCode;

	colorHexCode[0] = RGBHexCodeStr[4];
	colorHexCode[1] = RGBHexCodeStr[5];
	colorCode = getHexColorCode(colorHexCode);
	rgbHexCode->blueCode = colorCode;

}

void drawLine(HDC hdc, POINT p1, POINT p2, int pen_thickness, int line_color)
{
	HPEN new_pen, old_pen;
	new_pen = CreatePen(PS_SOLID, pen_thickness, color_array[line_color]);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	MoveToEx(hdc, p1.x, p1.y, NULL);
	LineTo(hdc, p2.x, p2.y);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
}

void drawGrid(HDC hdc, Position pos_org, GridAttr gridAttr,	int line_thickness, Color line_color)
{
	TCHAR str_org[16] = "0";
	TCHAR str[16];
	int Y_CHAR_HEIGHT_OFFSET = -10;
	//SetBkColor(hdc, color_array[WHITE]);
	POINT PTN_1, PTN_2;
	PTN_1.x = pos_org.x + gridAttr.grid_x_low;
	PTN_1.y = pos_org.y;
	PTN_2.x = pos_org.x + gridAttr.grid_x_high;
	PTN_2.y = pos_org.y;

	drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);

	PTN_1.x = pos_org.x;
	PTN_1.y = pos_org.y - gridAttr.grid_y_low;
	PTN_2.x = pos_org.x;
	PTN_2.y = pos_org.y - gridAttr.grid_y_high;
	drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);

	SetTextColor(hdc, color_array[BLACK]);
	TextOut(hdc, pos_org.x + 2, pos_org.y + 2, str_org, strlen(str_org));
	for (int x = -gridAttr.grid_step; x >= gridAttr.grid_x_low; x -= gridAttr.grid_step)
	{
		PTN_1.x = pos_org.x + x;
		PTN_1.y = pos_org.y - 5;
		PTN_2.x = pos_org.x + x;
		PTN_2.y = pos_org.y + 5;
		drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);
		sprintf(str, "%d", x);
		TextOut(hdc, pos_org.x + x + 2, pos_org.y + 2, str, strlen(str));
	} for (
		int x
		=
		0; x
		<= gridAttr.grid_x_high; x
		+= gridAttr.grid_step)
		for (int x = 0; x <= gridAttr.grid_x_high; x += gridAttr.grid_step)
		{
			PTN_1.x = pos_org.x + x;
			PTN_1.y = pos_org.y - 5;
			PTN_2.x = pos_org.x + x;
			PTN_2.y = pos_org.y + 5;
			drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);
			sprintf(str, "%d", x);
			TextOut(hdc, pos_org.x + x + 2, pos_org.y + 2, str, strlen(str));
		}
	if (gridAttr.dimension == 3)
	{
		sprintf(str, "x (Red)");
		TextOut(hdc, pos_org.x + gridAttr.grid_x_high + 2, pos_org.y + 2 * Y_CHAR_HEIGHT_OFFSET, str, strlen(str));
	} for (
		int y
		=
		gridAttr.grid_step; y
		<= -
		gridAttr.grid_y_low; y
		+= gridAttr.grid_step)
	{
		PTN_1.x = pos_org.x - 5;
		PTN_1.y = pos_org.y + y;
		PTN_2.x = pos_org.x + 5;
		PTN_2.y = pos_org.y + y;
		drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);
		sprintf(str, "-%4d", y);
		if (y != 0)
			TextOut(hdc, pos_org.x - 40, pos_org.y + y + Y_CHAR_HEIGHT_OFFSET, str, strlen(str));
	} for (
		int y
		=
		0; y
		<= gridAttr.grid_y_high; y
		+= gridAttr.grid_step)
	{
		PTN_1.x = pos_org.x - 5;
		PTN_1.y = pos_org.y - y;
		PTN_2.x = pos_org.x + 5;
		PTN_2.y = pos_org.y - y;
		drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);
		sprintf(str, "%4d", y);
		if (y != 0)
			TextOut(hdc, pos_org.x - 40, pos_org.y - y + Y_CHAR_HEIGHT_OFFSET, str, strlen(str));
	}

	if (gridAttr.dimension == 3)
	{
		sprintf(str, "y (Green)");
		TextOut(hdc, pos_org.x, pos_org.y - gridAttr.grid_y_high - 15, str, strlen(str));
	}

	if (gridAttr.dimension == 3)
	{
		int z_x, z_y, z_high;
		double zaxis_x_cos, zaxis_y_sin;
		z_high = gridAttr.grid_z_high;
		zaxis_x_cos = cos(gridAttr.zaxis_dir*PI / 180);
		zaxis_y_sin = sin(gridAttr.zaxis_dir*PI / 180);
		z_x = pos_org.x + z_high*zaxis_x_cos;
		z_y = pos_org.y - z_high*zaxis_y_sin;
		PTN_1.x = pos_org.x - 5;
		PTN_1.y = pos_org.y;
		PTN_2.x = z_x;
		PTN_2.y = z_y;

		drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);

		for (int z = gridAttr.grid_step; z < gridAttr.grid_z_high; z += gridAttr.grid_step)
		{
			z_x = pos_org.x + z*zaxis_x_cos;
			z_y = pos_org.y - z*zaxis_y_sin;

			PTN_1.x = z_x - 5;
			PTN_1.y = z_y;
			PTN_2.x = z_x + 5;
			PTN_2.y = z_y;
			drawLine(hdc, PTN_1, PTN_2, line_thickness, line_color);
			sprintf(str, "%4d", z);
			TextOut(hdc, z_x - 40, z_y + Y_CHAR_HEIGHT_OFFSET, str, strlen(str));
		}

		sprintf(str, "z (Blue)");

		TextOut(hdc, pos_org.x + z_high*zaxis_x_cos,
			pos_org.y - z_high*zaxis_y_sin, str, strlen(str));
	}
}

void drawRectangle(HDC hdc, Position pos_org, int width, int length,
	int pen_thickness, COLORREF line_color, COLORREF brush_color)
{
	POINT p[4];
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	p[0].x = pos_org.x;
	p[0].y = pos_org.y;
	p[1].x = pos_org.x + width;
	p[1].y = pos_org.y;
	p[2].x = pos_org.x + width;
	p[2].y = pos_org.y + length;
	p[3].x = pos_org.x;
	p[3].y = pos_org.y + length;
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	SelectObject(hdc, new_brush);
	Polygon(hdc, p, 4);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void drawCircle(HDC hdc, Position pos_org, int radius, int pen_thickness, Color line_color, Color brush_color)
{
	double radian;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	new_pen = CreatePen(PS_SOLID, pen_thickness, color_array[line_color]);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush =	CreateSolidBrush(color_array[brush_color]);
	old_brush =	(HBRUSH)SelectObject(hdc, new_brush);
	SelectObject(hdc, new_brush);
	Ellipse(hdc, pos_org.x - radius, pos_org.y - radius, pos_org.x + radius, pos_org.y + radius);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void drawTriangle(HDC hdc, Position pos_org, int base, int height, Color color)
{
	int x1, x2, x3;
	int y1, y2, y3;
	POINT p[3];
	p[1].x = pos_org.x - base / 2;
	p[1].y = pos_org.y + height * 1.0 / 3.0;
	p[2].x = pos_org.x + base / 2;
	p[2].y = pos_org.y + height * 1.0 / 3.0;
	p[3].x = pos_org.x;
	p[3].y = pos_org.y - height * 2.0 / 3.0;
	Polygon(hdc, p, 3);
}

void drawPolygon(HDC hdc, Position pos_org, int radius, int num_poly, int pen_thickness, Color line_color, Color brush_color)
{
	POINT *points = (POINT *)malloc(num_poly * sizeof(POINT));
	double rad_angle, delta_angle; // angle in radian
	int x, y;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	delta_angle = 2.0*PI / num_poly;
	rad_angle = PI / 2.0;
	for (int i = 0; i < num_poly; i++, rad_angle += delta_angle)
	{
		x = pos_org.x + radius * cos(rad_angle);
		y = pos_org.y - radius * sin(rad_angle);
		points[i].x = x;
		points[i].y = y;
	}
	new_pen = CreatePen(PS_SOLID, pen_thickness, color_array[line_color]);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(color_array[brush_color]);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	SelectObject(hdc, new_brush);
	Polygon(hdc, points, num_poly);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void putPixelsOnPlane(HDC hdc, Position pos_org, GridAttr gridAttr, PLANENUM planeno, int base_color)
{
	int x, y, z, z_x, z_y;
	int red, grn, blu;
	int x_low, x_high;
	int y_low, y_high;
	int z_low, z_high, z_max;
	int pixel_pos_x, pixel_pos_y;
	double zaxis_x_cos, zaxis_y_sin;

	x_low = gridAttr.grid_x_low;
	x_high = gridAttr.grid_x_high - 50;
	y_low = gridAttr.grid_y_low;
	y_high = gridAttr.grid_y_high - 50;
	z_low = gridAttr.grid_z_low;
	z_high = gridAttr.grid_z_high - 50;

	COLORREF color;
#define X_MAX 256
#define Y_MAX 256
#define Z_MAX 256
	switch (planeno)
	{
	case PLANE_RED_GREEN:
		z_low = base_color;
		z_high = base_color;
		break;
	case PLANE_RED_BLUE:
		y_low = base_color;
		y_high = base_color;
		break;
	case PLANE_GREEN_BLUE:
		x_low = base_color;
		x_high = base_color;
		break;
	}
	z_max = gridAttr.grid_z_high;
	zaxis_x_cos = cos(gridAttr.zaxis_dir*PI / 180);
	zaxis_y_sin = sin(gridAttr.zaxis_dir*PI / 180);
	for (z = z_low; z <= z_high; z++)// blue
		for (y = y_low; y <= y_high; y++) // green
			for (x = x_low; x <= x_high; x++) // red
			{
				red = x * 256.0 / X_MAX;
				grn = y * 256.0 / Y_MAX;
				blu = z * 256.0 / Z_MAX;
				color = RGB(red, grn, blu);
				z_x = z*zaxis_x_cos;
				z_y = z*zaxis_y_sin;
				pixel_pos_x = pos_org.x + (x + z_x);
				pixel_pos_y = pos_org.y - (y + z_y);
				SetPixel(hdc, pixel_pos_x,
					pixel_pos_y, color);
			}
}