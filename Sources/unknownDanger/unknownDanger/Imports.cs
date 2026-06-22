using System;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace unknownDanger
{
	// Token: 0x02000005 RID: 5
	internal class Imports
	{
		// Token: 0x06000005 RID: 5 RVA: 0x00002314 File Offset: 0x00000514
		public static Bitmap FlipBitmap(Bitmap original, RotateFlipType flipType)
		{
			Bitmap bitmap = new Bitmap(original);
			bitmap.RotateFlip(flipType);
			return bitmap;
		}

		// Token: 0x06000006 RID: 6
		[DllImport("ntdll.dll", SetLastError = true)]
		private static extern int NtSetInformationProcess(IntPtr hProcess, int processInformationClass, ref int processInformation, int processInformationLength);

		// Token: 0x06000007 RID: 7 RVA: 0x00002338 File Offset: 0x00000538
		public static void SetProcessCritical(bool critical)
		{
			int num = critical ? 1 : 0;
			int processInformationLength = 4;
			IntPtr handle = Process.GetCurrentProcess().Handle;
			int num2 = Imports.NtSetInformationProcess(handle, 29, ref num, processInformationLength);
			bool flag = num2 != 0;
			if (flag)
			{
				throw new Exception("Failed to set process critical status.");
			}
		}

		// Token: 0x06000008 RID: 8
		[DllImport("ntdll.dll")]
		public static extern uint RtlAdjustPrivilege(int Privilege, bool bEnablePrivilege, bool IsThreadPrivilege, out bool PreviousValue);

		// Token: 0x06000009 RID: 9
		[DllImport("ntdll.dll")]
		public static extern uint NtSetSystemPowerState(Imports.POWER_ACTION paction, Imports.SYSTEM_POWER_STATE pst, ulong flags);

		// Token: 0x0600000A RID: 10
		[DllImport("ntdll.dll")]
		public static extern uint NtShutdownSystem(Imports.SHUTDOWN_ACTION action);

		// Token: 0x0600000B RID: 11
		[DllImport("ntdll.dll")]
		public static extern uint NtRaiseHardError(uint ErrorStatus, uint NumberOfParameters, uint UnicodeStringParameterMask, IntPtr Parameters, uint ValidResponseOption, out uint Response);

		// Token: 0x0600000C RID: 12
		[DllImport("kernel32.dll", SetLastError = true)]
		private static extern int GetProcessId(IntPtr handle);

		// Token: 0x0600000D RID: 13 RVA: 0x00002380 File Offset: 0x00000580
		public static int GetProcessIdFromHandle(IntPtr handle)
		{
			bool flag = handle == IntPtr.Zero;
			int result;
			if (flag)
			{
				result = 0;
			}
			else
			{
				try
				{
					result = Imports.GetProcessId(handle);
				}
				catch (Exception ex)
				{
					Console.WriteLine("Error getting process id from handle: " + ex.Message);
					result = 0;
				}
			}
			return result;
		}

		// Token: 0x0600000E RID: 14 RVA: 0x000023DC File Offset: 0x000005DC
		public static Process GetProcessFromHandle(IntPtr handle)
		{
			Process result;
			try
			{
				int processIdFromHandle = Imports.GetProcessIdFromHandle(handle);
				bool flag = processIdFromHandle == 0;
				if (flag)
				{
					result = null;
				}
				else
				{
					Process processById = Process.GetProcessById(processIdFromHandle);
					result = processById;
				}
			}
			catch (Exception ex)
			{
				Console.WriteLine("Error getting process from handle: " + ex.Message);
				result = null;
			}
			return result;
		}

		// Token: 0x0600000F RID: 15
		[DllImport("user32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool GetWindowRect(IntPtr hWnd, out Imports.RECT lpRect);

		// Token: 0x06000010 RID: 16
		[DllImport("user32.dll", SetLastError = true)]
		internal static extern bool MoveWindow(IntPtr hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint);

		// Token: 0x06000011 RID: 17
		[DllImport("user32.dll")]
		public static extern IntPtr GetForegroundWindow();

		// Token: 0x06000012 RID: 18
		[DllImport("user32.dll")]
		public static extern bool SetWindowText(IntPtr hWnd, string text);

		// Token: 0x06000013 RID: 19 RVA: 0x00002438 File Offset: 0x00000638
		public static double fmod(double xx, double yy)
		{
			long num = (long)(xx * 10000000.0);
			long num2 = (long)(yy * 10000000.0);
			num %= num2;
			return (double)num / 10000000.0;
		}

		// Token: 0x06000014 RID: 20
		[DllImport("user32.dll")]
		public static extern IntPtr GetDC(IntPtr hWnd);

		// Token: 0x06000015 RID: 21 RVA: 0x00002474 File Offset: 0x00000674
		public static void CopyToDC(IntPtr hdcDest, IntPtr hdcSrc)
		{
			Imports.BitBlt(hdcDest, 0, 0, Imports.x, Imports.y, hdcSrc, 0, 0, Imports.SRCCOPY);
		}

		// Token: 0x06000016 RID: 22 RVA: 0x000024A0 File Offset: 0x000006A0
		public static void CopyBlt(IntPtr hdcDest, IntPtr hdcSrc, long dwRop)
		{
			Imports.BitBlt(hdcDest, 0, 0, Imports.x, Imports.y, hdcSrc, 0, 0, dwRop);
		}

		// Token: 0x06000017 RID: 23 RVA: 0x000024C8 File Offset: 0x000006C8
		public static double sin(double v)
		{
			bool flag = double.IsNaN((double)((float)v)) || double.IsInfinity((double)((float)Math.Abs(v)));
			if (flag)
			{
				throw new NotImplementedException("really?");
			}
			return Math.Sin(v);
		}

		// Token: 0x06000018 RID: 24 RVA: 0x0000250C File Offset: 0x0000070C
		public static double cos(double v)
		{
			bool flag = double.IsNaN((double)((float)v)) || double.IsInfinity((double)((float)Math.Abs(v)));
			if (flag)
			{
				throw new NotImplementedException("really?");
			}
			return Math.Cos(v);
		}

		// Token: 0x06000019 RID: 25 RVA: 0x00002550 File Offset: 0x00000750
		public static int abs(int j)
		{
			return Math.Abs(j);
		}

		// Token: 0x0600001A RID: 26 RVA: 0x00002568 File Offset: 0x00000768
		public static long abs(long j)
		{
			return Math.Abs(j);
		}

		// Token: 0x0600001B RID: 27 RVA: 0x00002580 File Offset: 0x00000780
		public static double abs(double j)
		{
			return Math.Abs(j);
		}

		// Token: 0x0600001C RID: 28 RVA: 0x00002598 File Offset: 0x00000798
		public static float abs(float j)
		{
			return Math.Abs(j);
		}

		// Token: 0x0600001D RID: 29 RVA: 0x000025B0 File Offset: 0x000007B0
		public static double min(double v, double k)
		{
			return Math.Min(v, k);
		}

		// Token: 0x0600001E RID: 30 RVA: 0x000025CC File Offset: 0x000007CC
		public static double max(double v, double k)
		{
			return Math.Max(v, k);
		}

		// Token: 0x0600001F RID: 31 RVA: 0x000025E8 File Offset: 0x000007E8
		public static void CircleBlt(IntPtr hdc, int x, int y, int radius, long dwRop)
		{
			IntPtr intPtr = Imports.CreateEllipticRgn(x - radius, y - radius, x + radius, y + radius);
			Imports.SelectClipRgn(hdc, intPtr);
			Imports.BitBlt(hdc, 0, 0, 879235498, 43673567, hdc, 0, 0, dwRop);
			Imports.DeleteObject(intPtr);
			IntPtr intPtr2 = Imports.CreateRectRgn(0, 0, x, y);
			Imports.SelectClipRgn(hdc, intPtr2);
			Imports.DeleteObject(intPtr2);
		}

		// Token: 0x06000020 RID: 32 RVA: 0x00002648 File Offset: 0x00000848
		public static void BitBltf(IntPtr hdcDest, double xx, double yy, double sx, double sy, IntPtr hdcSrc, double xsr, double ysr, long dwrop)
		{
			Imports.BitBlt(hdcDest, (int)xx, (int)yy, (int)sx, (int)sy, hdcSrc, (int)xsr, (int)ysr, dwrop);
		}

		// Token: 0x06000021 RID: 33 RVA: 0x00002670 File Offset: 0x00000870
		public static void StretchBltf(IntPtr hdcDest, double xx, double yy, double sx, double sy, IntPtr hdcSrc, double xsr, double ysr, double wsr, double hsr, long dwrop)
		{
			Imports.StretchBlt(hdcDest, (int)xx, (int)yy, (int)sx, (int)sy, hdcSrc, (int)xsr, (int)ysr, (int)wsr, (int)hsr, dwrop);
		}

		// Token: 0x06000022 RID: 34
		[DllImport("msimg32.dll")]
		public static extern bool TransparentBlt(IntPtr hdcDest, int xoriginDest, int yoriginDest, int wDest, int hDest, IntPtr hdcSrc, int xoriginSrc, int yoriginSrc, int wSrc, int hSrc, uint crTransparent);

		// Token: 0x06000023 RID: 35
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreatePolygonRgn(Imports.POINT[] lppt, int cPoints, int fnPolyFillMode);

		// Token: 0x06000024 RID: 36
		[DllImport("gdi32.dll")]
		public static extern int SelectClipRgn(IntPtr hdc, IntPtr hrgn);

		// Token: 0x06000025 RID: 37 RVA: 0x000026A0 File Offset: 0x000008A0
		public static void PolyBlt(IntPtr hdc, int sides, int xx, int yy, int radius, long dwRop, int ang, int sexp)
		{
			Imports.POINT[] array = new Imports.POINT[sides];
			for (int i = 0; i < sides; i++)
			{
				array[i] = new Imports.POINT((int)((double)xx + Math.Sin(6.283185307179586 / (double)sides * (double)i * (double)sexp + 0.017453292519943295 * (double)ang) * (double)radius), (int)((double)yy + Math.Cos(6.283185307179586 / (double)sides * (double)sexp * (double)i + 0.017453292519943295 * (double)ang) * (double)radius));
			}
			IntPtr intPtr = Imports.CreatePolygonRgn(array, sides, 2);
			Imports.SelectClipRgn(hdc, intPtr);
			Imports.BitBlt(hdc, xx - radius, yy - radius, 35677356, 36736755, hdc, xx - radius, yy - radius, dwRop);
			Imports.DeleteObject(intPtr);
			IntPtr intPtr2 = Imports.CreateRectRgn(0, 0, Imports.x, Imports.y);
			Imports.SelectClipRgn(hdc, intPtr2);
			Imports.DeleteObject(intPtr2);
		}

		// Token: 0x06000026 RID: 38 RVA: 0x00002790 File Offset: 0x00000990
		public static int rand()
		{
			long num = (long)DateTime.Now.Millisecond;
			int num2 = (int)(num & 2147483647L);
			int num3 = Imports.r.Next(int.MaxValue);
			num3 ^= (num3 >> 7 | (num3 << 1 & int.MaxValue));
			num3 |= (num3 >> 4 ^ num3 >> 3);
			num3 ^= num2;
			Imports.rs ^= (Imports.r.Next(int.MinValue, int.MaxValue) ^ num3);
			return Imports.rs %= int.MaxValue;
		}

		// Token: 0x06000027 RID: 39 RVA: 0x00002820 File Offset: 0x00000A20
		public static int seedXY(int seed)
		{
			Imports.j = seed;
			return seed;
		}

		// Token: 0x06000028 RID: 40 RVA: 0x0000283C File Offset: 0x00000A3C
		public static int XorYeet32()
		{
			long ticks = DateTime.Now.Ticks;
			int num = (int)(ticks & 2147483647L);
			int num2 = num;
			int maxValue = int.MaxValue;
			Imports.seedXY(Imports.rand() % 7358321);
			Imports.j ^= Imports.rand() % 2774265;
			Imports.j |= Imports.rand() % 1697837;
			Imports.j ^= (Imports.j >> 7 | Imports.j << 3);
			Imports.j ^= (num2 & maxValue);
			Imports.j++;
			Imports.j &= maxValue;
			return Imports.j & maxValue;
		}

		// Token: 0x06000029 RID: 41
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateEllipticRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x0600002A RID: 42
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreatePen(Imports.PenStyle fnPenStyle, int nWidth, uint crColor);

		// Token: 0x0600002B RID: 43
		[DllImport("gdi32.dll", SetLastError = true)]
		public static extern IntPtr CreateCompatibleDC(IntPtr hdc);

		// Token: 0x0600002C RID: 44
		[DllImport("gdi32.dll")]
		public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);

		// Token: 0x0600002D RID: 45
		[DllImport("gdi32.dll")]
		public static extern bool MoveToEx(IntPtr hdc, int X, int Y, IntPtr lpPoint);

		// Token: 0x0600002E RID: 46
		[DllImport("gdi32.dll", SetLastError = true)]
		public static extern bool MaskBlt(IntPtr hdcDest, int xDest, int yDest, int width, int height, IntPtr hdcSrc, int xSrc, int ySrc, IntPtr hbmMask, int xMask, int yMask, uint rop);

		// Token: 0x0600002F RID: 47
		[DllImport("gdi32.dll")]
		public static extern bool LineTo(IntPtr hdc, int nXEnd, int nYEnd);

		// Token: 0x06000030 RID: 48
		[DllImport("gdi32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool DeleteObject(IntPtr hObject);

		// Token: 0x06000031 RID: 49
		[DllImport("gdi32.dll", SetLastError = true)]
		[return: MarshalAs(UnmanagedType.Bool)]
		public static extern bool BitBlt(IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight, IntPtr hdcSrc, int nXSrc, int nYSrc, long dwRop);

		// Token: 0x06000032 RID: 50
		[DllImport("gdi32.dll")]
		public static extern bool StretchBlt(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, long dwRop);

		// Token: 0x06000033 RID: 51
		[DllImport("gdi32.dll")]
		public static extern bool PlgBlt(IntPtr hdcDest, Imports.POINT[] lpPoint, IntPtr hdcSrc, int nXSrc, int nYSrc, int nWidth, int nHeight, IntPtr hbmMask, int xMask, int yMask);

		// Token: 0x06000034 RID: 52
		[DllImport("gdi32.dll")]
		public static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft, int nWidth, int nHeight, long dwRop);

		// Token: 0x06000035 RID: 53
		[DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
		public static extern IntPtr Ellipse(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x06000036 RID: 54
		[DllImport("gdi32.dll", EntryPoint = "GdiAlphaBlend")]
		public static extern bool AlphaBlend(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, Imports.BLENDFUNCTION blendFunction);

		// Token: 0x06000037 RID: 55
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateSolidBrush(uint crColor);

		// Token: 0x06000038 RID: 56
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateBitmap(int nWidth, int nHeight, uint cPlanes, uint cBitsPerPel, byte[] lpvBits);

		// Token: 0x06000039 RID: 57
		[DllImport("gdi32.dll", EntryPoint = "CreateBitmap")]
		public static extern IntPtr CreateBitmapI(int nWidth, int nHeight, uint cPlanes, uint cBitsPerPel, int[] lpvBits);

		// Token: 0x0600003A RID: 58
		[DllImport("gdi32.dll")]
		public static extern bool DeleteDC(IntPtr hdc);

		// Token: 0x0600003B RID: 59
		[DllImport("gdi32.dll")]
		public static extern bool FloodFill(IntPtr hdc, int nXStart, int nYStart, uint crFill);

		// Token: 0x0600003C RID: 60
		[DllImport("gdi32.dll", EntryPoint = "GdiGradientFill", ExactSpelling = true)]
		public unsafe static extern bool GradientFill(IntPtr hdc, Imports.TRIVERTEX[] pVertex, uint dwNumVertex, Imports.GRADIENT_TRIANGLE* pMesh, uint dwNumMesh, Imports.GRADIENT_FILL dwMode);

		// Token: 0x0600003D RID: 61
		[DllImport("user32.dll")]
		public static extern IntPtr GetDesktopWindow();

		// Token: 0x0600003E RID: 62
		[DllImport("user32.dll")]
		public static extern IntPtr GetWindowDC(IntPtr hwnd);

		// Token: 0x0600003F RID: 63
		[DllImport("user32.dll")]
		public static extern bool InvalidateRect(IntPtr hWnd, IntPtr lpRect, bool bErase);

		// Token: 0x06000040 RID: 64
		[DllImport("User32.dll")]
		public static extern int ReleaseDC(IntPtr hwnd, IntPtr dc);

		// Token: 0x06000041 RID: 65
		[DllImport("gdi32.dll")]
		public static extern bool FillRgn(IntPtr hdc, IntPtr hrgn, IntPtr hbr);

		// Token: 0x06000042 RID: 66
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateRectRgn(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x06000043 RID: 67
		[DllImport("gdi32.dll")]
		public static extern bool Pie(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nXRadial1, int nYRadial1, int nXRadial2, int nYRadial2);

		// Token: 0x06000044 RID: 68
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int nWidth, int nHeight);

		// Token: 0x06000045 RID: 69
		[DllImport("gdi32.dll")]
		public static extern bool Rectangle(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect);

		// Token: 0x06000046 RID: 70
		[DllImport("gdi32.dll")]
		public static extern uint SetPixel(IntPtr hdc, int X, int Y, int crColor);

		// Token: 0x06000047 RID: 71
		[DllImport("gdi32.dll")]
		public static extern IntPtr GetPixel(IntPtr hdc, int nXPos, int nYPos);

		// Token: 0x06000048 RID: 72
		[DllImport("gdi32.dll")]
		public static extern bool AngleArc(IntPtr hdc, int X, int Y, uint dwRadius, float eStartAngle, float eSweepAngle);

		// Token: 0x06000049 RID: 73
		[DllImport("gdi32.dll")]
		public static extern bool RoundRect(IntPtr hdc, int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, int nWidth, int nHeight);

		// Token: 0x0600004A RID: 74
		[DllImport("gdi32.dll")]
		public static extern bool DeleteMetaFile(IntPtr hmf);

		// Token: 0x0600004B RID: 75
		[DllImport("gdi32.dll")]
		public static extern bool CancelDC(IntPtr hdc);

		// Token: 0x0600004C RID: 76
		[DllImport("gdi32.dll")]
		public static extern bool Polygon(IntPtr hdc, Imports.POINT[] lpPoints, int nCount);

		// Token: 0x0600004D RID: 77
		[DllImport("gdi32.dll")]
		public static extern int SetBitmapBits(IntPtr hbmp, int cBytes, Imports.RGBQUAD[] lpBits);

		// Token: 0x0600004E RID: 78
		[DllImport("kernel32.dll", SetLastError = true)]
		public static extern bool Beep(uint dwFreq, uint dwDuration);

		// Token: 0x0600004F RID: 79
		[DllImport("user32.dll")]
		public static extern bool BlockInput(bool block);

		// Token: 0x06000050 RID: 80
		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		public static extern IntPtr LoadImage(IntPtr hinst, string lpszName, uint uType, int cxDesired, int cyDesired, uint fuLoad);

		// Token: 0x06000051 RID: 81
		[DllImport("user32.dll", SetLastError = true)]
		public static extern int DestroyIcon(IntPtr hIcon);

		// Token: 0x06000052 RID: 82
		[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		public static extern IntPtr LoadLibraryEx(IntPtr lpFileName, IntPtr hFile, Imports.LoadLibraryFlags dwFlags);

		// Token: 0x06000053 RID: 83
		[DllImport("user32.dll")]
		public static extern IntPtr LoadBitmap(IntPtr hInstance, string lpBitmapName);

		// Token: 0x06000054 RID: 84
		[DllImport("user32.dll")]
		public static extern IntPtr BeginPaint(IntPtr hwnd, out Imports.PAINTSTRUCT lpPaint);

		// Token: 0x06000055 RID: 85
		[DllImport("user32.dll")]
		public static extern bool EndPaint(IntPtr hWnd, out Imports.PAINTSTRUCT lpPaint);

		// Token: 0x06000056 RID: 86
		[DllImport("gdi32.dll")]
		public static extern int SetStretchBltMode(IntPtr hdc, Imports.StretchBltMode iStretchMode);

		// Token: 0x06000057 RID: 87
		[DllImport("gdi32.dll")]
		public static extern int StretchDIBits(IntPtr hdc, int XDest, int YDest, int nDestWidth, int nDestHeight, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight, Imports.RGBQUAD rgbq, [In] ref Imports.BITMAPINFO lpBitsInfo, Imports.DIB_Color_Mode dib_mode, Imports.TernaryRasterOperations dwRop);

		// Token: 0x06000058 RID: 88
		[DllImport("gdi32.dll")]
		public static extern int GetDIBits([In] IntPtr hdc, in IntPtr hbmp, uint uStartScan, uint cScanLines, [Out] int[] lpvBits, ref Imports.BITMAPINFO lpbi, Imports.DIB_Color_Mode uUsage);

		// Token: 0x06000059 RID: 89
		[DllImport("gdi32.dll")]
		public static extern bool SetDeviceGammaRamp(IntPtr hDC, ref Imports.RAMP lpRamp);

		// Token: 0x0600005A RID: 90
		[DllImport("Gdi32")]
		public static extern long GetBitmapBits([In] IntPtr hbmp, [In] int cbBuffer, Imports.RGBQUAD[] lpvBits);

		// Token: 0x0600005B RID: 91
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateHatchBrush(int iHatch, uint Color);

		// Token: 0x0600005C RID: 92
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreatePatternBrush(IntPtr hbmp);

		// Token: 0x0600005D RID: 93
		[DllImport("gdi32.dll")]
		public static extern IntPtr CreateDIBitmap(IntPtr hdc, [In] ref Imports.BITMAPINFOHEADER lpbmih, uint fdwInit, byte[] lpbInit, [In] ref Imports.BITMAPINFO lpbmi, uint fuUsage);

		// Token: 0x0600005E RID: 94
		[DllImport("gdi32.dll")]
		public static extern int SetDIBitsToDevice(IntPtr hdc, int XDest, int YDest, uint dwWidth, uint dwHeight, int XSrc, int YSrc, uint uStartScan, uint cScanLines, byte[] lpvBits, [In] ref Imports.BITMAPINFO lpbmi, uint fuColorUse);

		// Token: 0x0600005F RID: 95
		[DllImport("gdi32.dll")]
		public static extern IntPtr SetDIBits(IntPtr hdc, IntPtr hbm, uint start, uint line, int[] lpBits, [In] ref Imports.BITMAPINFO lpbmi, Imports.DIB_Color_Mode ColorUse);

		// Token: 0x06000060 RID: 96 RVA: 0x000028F8 File Offset: 0x00000AF8
		public static Color RGB(int r, int g, int b)
		{
			return Color.FromArgb(r & 255, g & 255, b & 255);
		}

		// Token: 0x06000061 RID: 97 RVA: 0x00002924 File Offset: 0x00000B24
		public static uint _RGB(byte r, byte g, byte b)
		{
			return (uint)((int)r | (int)g << 8 | (int)b << 16);
		}

		// Token: 0x06000062 RID: 98 RVA: 0x00002940 File Offset: 0x00000B40
		public static uint _RGB(int r, int g, int b)
		{
			r &= 255;
			g &= 255;
			b &= 255;
			return (uint)(r | g << 8 | b << 16);
		}

		// Token: 0x06000063 RID: 99 RVA: 0x00002977 File Offset: 0x00000B77
		public static void RemoveDC(IntPtr hdc)
		{
			Imports.ReleaseDC(IntPtr.Zero, hdc);
			Imports.DeleteDC(hdc);
		}

		// Token: 0x06000064 RID: 100 RVA: 0x00002990 File Offset: 0x00000B90
		public static void invertsquare(IntPtr hdc, int X, int Y, int i, bool usecols, uint col)
		{
			int num = X;
			int num2 = Y;
			bool flag = X == -1;
			if (flag)
			{
				num = Imports.x / 2;
			}
			bool flag2 = Y == -1;
			if (flag2)
			{
				num2 = Imports.y / 2;
			}
			Imports.TernaryRasterOperations dwRop = Imports.TernaryRasterOperations.NOTSRCCOPY;
			IntPtr intPtr = Imports.CreateSolidBrush(col);
			Imports.SelectObject(hdc, intPtr);
			if (usecols)
			{
				dwRop = Imports.TernaryRasterOperations.PATINVERT;
			}
			Imports.StretchBlt(hdc, num - i / 2, num2 - i / 2, i, i, hdc, num - i / 2, num2 - i / 2, i, i, (long)dwRop);
			Imports.DeleteObject(intPtr);
		}

		// Token: 0x06000065 RID: 101
		[DllImport("gdi32.dll")]
		public static extern uint SetBkColor(IntPtr hdc, uint crColor);

		// Token: 0x06000066 RID: 102 RVA: 0x00002A1C File Offset: 0x00000C1C
		public static IntPtr makeDC()
		{
			return Imports.GetDC(IntPtr.Zero);
		}

		// Token: 0x06000067 RID: 103 RVA: 0x00002A38 File Offset: 0x00000C38
		public static IntPtr Mdc(IntPtr hdc)
		{
			return Imports.CreateCompatibleDC(hdc);
		}

		// Token: 0x06000068 RID: 104 RVA: 0x00002A50 File Offset: 0x00000C50
		public static IntPtr bitmap(IntPtr hdc)
		{
			return Imports.CreateCompatibleBitmap(hdc, Imports.x, Imports.y);
		}

		// Token: 0x06000069 RID: 105 RVA: 0x00002A74 File Offset: 0x00000C74
		public static int antiNegative(int xx, int yy)
		{
			int i;
			for (i = xx % yy; i < 0; i += yy)
			{
			}
			return i;
		}

		// Token: 0x0600006A RID: 106 RVA: 0x00002A9C File Offset: 0x00000C9C
		public static double hypot(double x, double y)
		{
			return Math.Sqrt(x * x + y * y);
		}

		// Token: 0x0600006B RID: 107
		[DllImport("user32.dll")]
		public static extern IntPtr LoadIcon(IntPtr hInstance, IntPtr lpIconName);

		// Token: 0x0600006C RID: 108
		[DllImport("user32.dll")]
		public static extern int DrawIcon(IntPtr hDC, int X, int Y, IntPtr hIcon);

		// Token: 0x0600006D RID: 109
		[DllImport("user32.dll")]
		public static extern int DrawIconEx(IntPtr hDC, int X, int Y, IntPtr hIcon, int cw, int ch, uint istepifanicur, IntPtr hbrflg, uint diflags);

		// Token: 0x0600006E RID: 110
		[DllImport("user32.dll")]
		public static extern bool RedrawWindow(IntPtr hWnd, IntPtr lprcUpdate, IntPtr hrgnUpdate, Imports.RedrawWindowFlags flags);

		// Token: 0x0600006F RID: 111
		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		public static extern IntPtr FindWindow(string classname, string windowname);

		// Token: 0x06000070 RID: 112 RVA: 0x00002ABC File Offset: 0x00000CBC
		public static IntPtr MAKEINTRESOURCE(int ñ32513)
		{
			return new IntPtr(ñ32513);
		}

		// Token: 0x06000071 RID: 113 RVA: 0x00002AD4 File Offset: 0x00000CD4
		public static Bitmap getScreen()
		{
			try
			{
				Bitmap bitmap = new Bitmap(Imports.x, Imports.y);
				Graphics.FromImage(bitmap).CopyFromScreen(0, 0, 0, 0, bitmap.Size);
				return bitmap;
			}
			catch
			{
			}
			return new Bitmap(Imports.x, Imports.y);
		}

		// Token: 0x06000072 RID: 114 RVA: 0x00002B38 File Offset: 0x00000D38
		public static void changecols(IntPtr hdc, int rgbcol32)
		{
			try
			{
				Imports.BITMAPINFO bitmapinfo = default(Imports.BITMAPINFO);
				bitmapinfo.bmiHeader.biSize = (uint)Marshal.SizeOf(typeof(Imports.BITMAPINFOHEADER));
				bitmapinfo.bmiHeader.biWidth = Imports.x;
				bitmapinfo.bmiHeader.biHeight = -Imports.y;
				bitmapinfo.bmiHeader.biPlanes = 1;
				bitmapinfo.bmiHeader.biBitCount = 32;
				bitmapinfo.bmiHeader.biCompression = 0U;
				byte[] array = new byte[Imports.x * Imports.y * 4];
				Marshal.Copy(Imports.getScreen().LockBits(new Rectangle(0, 0, Imports.x, Imports.y), ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb).Scan0, array, 0, array.Length);
				for (int i = 0; i < Imports.y; i++)
				{
					for (int j = 0; j < Imports.x; j++)
					{
						int num = (i * Imports.x + j) * 4;
						byte[] array2 = array;
						int num2 = num;
						array2[num2] += (byte)rgbcol32;
						byte[] array3 = array;
						int num3 = num + 1;
						array3[num3] += (byte)(rgbcol32 >> 8);
						byte[] array4 = array;
						int num4 = num + 2;
						array4[num4] += (byte)(rgbcol32 >> 16);
					}
				}
				Imports.SetDIBitsToDevice(hdc, 0, 0, (uint)Imports.x, (uint)Imports.y, 0, 0, 0U, (uint)Imports.y, array, ref bitmapinfo, 0U);
			}
			catch
			{
			}
		}

		// Token: 0x06000073 RID: 115 RVA: 0x00002CB0 File Offset: 0x00000EB0
		public static byte[] randByteArray(int size, byte maxi)
		{
			byte[] array = new byte[size];
			for (int i = 0; i < array.Length; i++)
			{
				array[i] = (byte)(Imports.XorYeet32() % (int)(maxi + 1));
			}
			return array;
		}

		// Token: 0x06000074 RID: 116 RVA: 0x00002CEC File Offset: 0x00000EEC
		public static int[] randIntArray(int size, int maxi)
		{
			int[] array = new int[size];
			for (int i = 0; i < array.Length; i++)
			{
				array[i] = Imports.XorYeet32() % (maxi + 1);
			}
			return array;
		}

		// Token: 0x06000075 RID: 117 RVA: 0x00002D28 File Offset: 0x00000F28
		public static ImageCodecInfo GetEncoderInfo(string mimeType)
		{
			foreach (ImageCodecInfo imageCodecInfo in ImageCodecInfo.GetImageEncoders())
			{
				bool flag = imageCodecInfo.MimeType == mimeType;
				if (flag)
				{
					return imageCodecInfo;
				}
			}
			return null;
		}

		// Token: 0x06000076 RID: 118 RVA: 0x00002D6C File Offset: 0x00000F6C
		public MemoryStream compress(Image img, long quality)
		{
			ImageCodecInfo encoderInfo = Imports.GetEncoderInfo("image/jpeg");
			bool flag = encoderInfo == null;
			if (flag)
			{
				throw new NoNullAllowedException("uhh why is my codec null?");
			}
			EncoderParameters encoderParameters = new EncoderParameters(1);
			encoderParameters.Param[0] = new EncoderParameter(System.Drawing.Imaging.Encoder.Quality, quality);
			MemoryStream memoryStream = new MemoryStream();
			img.Save(memoryStream, encoderInfo, encoderParameters);
			return memoryStream;
		}

		// Token: 0x06000077 RID: 119 RVA: 0x00002DCC File Offset: 0x00000FCC
		public static Image SetOpacity(Image image, float opacity)
		{
			ColorMatrix colorMatrix = new ColorMatrix();
			colorMatrix.Matrix33 = opacity;
			ImageAttributes imageAttributes = new ImageAttributes();
			imageAttributes.SetColorMatrix(colorMatrix, ColorMatrixFlag.Default, ColorAdjustType.Bitmap);
			Bitmap bitmap = new Bitmap(image.Width, image.Height);
			using (Graphics graphics = Graphics.FromImage(bitmap))
			{
				graphics.DrawImage(image, new Rectangle(0, 0, image.Width, image.Height), 0, 0, image.Width, image.Height, GraphicsUnit.Pixel, imageAttributes);
			}
			return bitmap;
		}

		// Token: 0x06000078 RID: 120 RVA: 0x00002E64 File Offset: 0x00001064
		public static void pixelateDC(IntPtr hdc, int amount)
		{
			IntPtr intPtr = Imports.Mdc(hdc);
			IntPtr intPtr2 = Imports.bitmap(hdc);
			Imports.SelectObject(intPtr, intPtr2);
			Imports.CopyToDC(intPtr, hdc);
			Imports.SetStretchBltMode(hdc, Imports.StretchBltMode.STRETCH_DELETESCANS);
			Imports.SetStretchBltMode(intPtr, Imports.StretchBltMode.STRETCH_DELETESCANS);
			Imports.StretchBlt(intPtr, 0, 0, Imports.x / amount, Imports.y / amount, intPtr, 0, 0, Imports.x, Imports.y, Imports.SRCCOPY);
			Imports.StretchBlt(hdc, 0, 0, Imports.x, Imports.y, intPtr, 0, 0, Imports.x / amount, Imports.y / amount, Imports.SRCCOPY);
			Imports.DeleteObject(intPtr2);
			Imports.RemoveDC(intPtr);
		}

		// Token: 0x06000079 RID: 121 RVA: 0x00002F00 File Offset: 0x00001100
		public static string Corrupt_String(string str)
		{
			bool flag = str == "" || str == null;
			string result;
			if (flag)
			{
				result = str;
			}
			else
			{
				char[] array = str.ToCharArray();
				byte[] bytes = Imports.randByteArray(array.Length, byte.MaxValue);
				for (int i = 0; i < array.Length; i++)
				{
					bool flag2 = (Imports.rand() & 3) == 0;
					if (flag2)
					{
						char[] chars = Encoding.ASCII.GetChars(bytes);
						array[i] = chars[Imports.XorYeet32() % chars.Length];
					}
				}
				result = new string(array);
			}
			return result;
		}

		// Token: 0x0600007A RID: 122 RVA: 0x00002F94 File Offset: 0x00001194
		public static void chroma(IntPtr hdc, Imports.typesChr type, int intensity)
		{
			IntPtr intPtr = Imports.Mdc(hdc);
			IntPtr intPtr2 = Imports.bitmap(hdc);
			Imports.SelectObject(intPtr, intPtr2);
			Imports.CopyToDC(intPtr, hdc);
			bool flag = type == Imports.typesChr.VERTICAL;
			if (flag)
			{
				IntPtr intPtr3 = Imports.CreateSolidBrush(Imports._RGB(255, 0, 0));
				Imports.SelectObject(intPtr, intPtr3);
				Imports.BitBlt(intPtr, 0, intensity, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
				Imports.DeleteObject(intPtr3);
				IntPtr intPtr4 = Imports.CreateSolidBrush(Imports._RGB(0, 0, 255));
				Imports.SelectObject(intPtr, intPtr4);
				Imports.BitBlt(intPtr, 0, -intensity, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
				Imports.DeleteObject(intPtr4);
			}
			else
			{
				bool flag2 = type == Imports.typesChr.HORIZONTAL;
				if (flag2)
				{
					IntPtr intPtr5 = Imports.CreateSolidBrush(Imports._RGB(255, 0, 0));
					Imports.SelectObject(intPtr, intPtr5);
					Imports.BitBlt(intPtr, intensity, 0, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
					Imports.DeleteObject(intPtr5);
					IntPtr intPtr6 = Imports.CreateSolidBrush(Imports._RGB(0, 0, 255));
					Imports.SelectObject(intPtr, intPtr6);
					Imports.BitBlt(intPtr, -intensity, 0, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
					Imports.DeleteObject(intPtr6);
				}
				else
				{
					bool flag3 = type == Imports.typesChr.DIAGONAL1;
					if (flag3)
					{
						IntPtr intPtr7 = Imports.CreateSolidBrush(Imports._RGB(255, 0, 0));
						Imports.SelectObject(intPtr, intPtr7);
						Imports.BitBlt(intPtr, intensity, intensity, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
						Imports.DeleteObject(intPtr7);
						IntPtr intPtr8 = Imports.CreateSolidBrush(Imports._RGB(0, 0, 255));
						Imports.SelectObject(intPtr, intPtr8);
						Imports.BitBlt(intPtr, -intensity, -intensity, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
						Imports.DeleteObject(intPtr8);
					}
					else
					{
						bool flag4 = type == Imports.typesChr.DIAGONAL2;
						if (flag4)
						{
							IntPtr intPtr9 = Imports.CreateSolidBrush(Imports._RGB(255, 0, 0));
							Imports.SelectObject(intPtr, intPtr9);
							Imports.BitBlt(intPtr, intensity, -intensity, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
							Imports.DeleteObject(intPtr9);
							IntPtr intPtr10 = Imports.CreateSolidBrush(Imports._RGB(0, 0, 255));
							Imports.SelectObject(intPtr, intPtr10);
							Imports.BitBlt(intPtr, -intensity, intensity, Imports.x, Imports.y, intPtr, 0, 0, Imports.RGBCOPY);
							Imports.DeleteObject(intPtr10);
						}
					}
				}
			}
			Imports.CopyToDC(hdc, intPtr);
			Imports.DeleteObject(intPtr2);
			Imports.RemoveDC(intPtr);
		}

		// Token: 0x0600007B RID: 123 RVA: 0x0000321C File Offset: 0x0000141C
		public static void PixelateBlt(IntPtr hdc, IntPtr source, int amount)
		{
			IntPtr intPtr = Imports.Mdc(hdc);
			IntPtr intPtr2 = Imports.bitmap(hdc);
			Imports.SelectObject(intPtr, intPtr2);
			Imports.CopyToDC(intPtr, source);
			Imports.SetStretchBltMode(intPtr, Imports.StretchBltMode.STRETCH_DELETESCANS);
			Imports.SetStretchBltMode(hdc, Imports.StretchBltMode.STRETCH_DELETESCANS);
			Imports.StretchBlt(intPtr, 0, 0, Imports.x / amount, Imports.y / amount, intPtr, 0, 0, Imports.x, Imports.y, Imports.SRCCOPY);
			Imports.StretchBlt(hdc, 0, 0, Imports.x, Imports.y, intPtr, 0, 0, Imports.x / amount, Imports.y / amount, Imports.SRCCOPY);
			Imports.DeleteObject(intPtr2);
			Imports.RemoveDC(intPtr);
		}

		// Token: 0x0600007C RID: 124 RVA: 0x000032B8 File Offset: 0x000014B8
		public static void weird(IntPtr hdc)
		{
			try
			{
				Imports.BITMAPINFO bitmapinfo = default(Imports.BITMAPINFO);
				bitmapinfo.bmiHeader.biSize = (uint)Marshal.SizeOf(typeof(Imports.BITMAPINFOHEADER));
				bitmapinfo.bmiHeader.biWidth = Imports.x;
				bitmapinfo.bmiHeader.biHeight = -Imports.y;
				bitmapinfo.bmiHeader.biPlanes = 1;
				bitmapinfo.bmiHeader.biBitCount = 32;
				bitmapinfo.bmiHeader.biCompression = 0U;
				byte[] array = new byte[Imports.x * Imports.y * 4];
				Marshal.Copy(Imports.getScreen().LockBits(new Rectangle(0, 0, Imports.x, Imports.y), ImageLockMode.ReadWrite, PixelFormat.Format32bppArgb).Scan0, array, 0, array.Length);
				int num = 0;
				byte b = Imports.XYB();
				byte b2 = Imports.XYB();
				byte b3 = Imports.XYB();
				for (int i = 0; i < Imports.y; i++)
				{
					for (int j = 0; j < Imports.x; j++)
					{
						bool flag = array[num + 2] < b;
						if (flag)
						{
							byte[] array2 = array;
							int num2 = num + 2;
							array2[num2] += b;
						}
						bool flag2 = array[num + 1] < b2;
						if (flag2)
						{
							byte[] array3 = array;
							int num3 = num + 1;
							array3[num3] += b2;
						}
						bool flag3 = array[num] < b3;
						if (flag3)
						{
							byte[] array4 = array;
							int num4 = num;
							array4[num4] += b3;
						}
						num += 4;
					}
				}
				Imports.SetDIBitsToDevice(hdc, 0, 0, (uint)Imports.x, (uint)Imports.y, 0, 0, 0U, (uint)Imports.y, array, ref bitmapinfo, 0U);
			}
			catch
			{
			}
		}

		// Token: 0x0600007D RID: 125 RVA: 0x00003474 File Offset: 0x00001674
		public static byte XYB()
		{
			return (byte)Imports.XorYeet32();
		}

		// Token: 0x0600007E RID: 126 RVA: 0x0000348C File Offset: 0x0000168C
		public static double pow(double xx, double yy)
		{
			return Math.Pow(xx, yy);
		}

		// Token: 0x04000001 RID: 1
		public static ulong SHTDN_REASON_MAJOR_HARDWARE = 65536UL;

		// Token: 0x04000002 RID: 2
		public static ulong SHTDN_REASON_MINOR_POWER_SUPPLY = 10UL;

		// Token: 0x04000003 RID: 3
		public static readonly long SRCCOPY = 13369376L;

		// Token: 0x04000004 RID: 4
		public static readonly long SRCINVERT = 6684742L;

		// Token: 0x04000005 RID: 5
		public static readonly long SRCERASE = 4457256L;

		// Token: 0x04000006 RID: 6
		public static readonly long NOTSRCCOPY = 3342344L;

		// Token: 0x04000007 RID: 7
		public static readonly long NOTSRCERASE = 1114278L;

		// Token: 0x04000008 RID: 8
		public static readonly long MERGECOPY = 12583114L;

		// Token: 0x04000009 RID: 9
		public static readonly long MERGEPAINT = 12255782L;

		// Token: 0x0400000A RID: 10
		public static readonly long PATCOPY = 15728673L;

		// Token: 0x0400000B RID: 11
		public static readonly long PATPAINT = 16452105L;

		// Token: 0x0400000C RID: 12
		public static readonly long PATINVERT = 5898313L;

		// Token: 0x0400000D RID: 13
		public static readonly long DSTINVERT = 5570569L;

		// Token: 0x0400000E RID: 14
		public static readonly long BLACKNESS = 66L;

		// Token: 0x0400000F RID: 15
		public static readonly long WHITENESS = 16711778L;

		// Token: 0x04000010 RID: 16
		public static readonly long CAPTUREBLT = 1073741824L;

		// Token: 0x04000011 RID: 17
		public static readonly long CUSTOM = 1051781L;

		// Token: 0x04000012 RID: 18
		public static readonly long RGBCOPY = 107385454862L;

		// Token: 0x04000013 RID: 19
		public static readonly long SRCOR = 15597702L;

		// Token: 0x04000014 RID: 20
		public static readonly long SRCXOR = 6684742L;

		// Token: 0x04000015 RID: 21
		public static readonly long SRCAND = 8913094L;

		// Token: 0x04000016 RID: 22
		public static int x = Screen.PrimaryScreen.Bounds.Width;

		// Token: 0x04000017 RID: 23
		public static int y = Screen.PrimaryScreen.Bounds.Height;

		// Token: 0x04000018 RID: 24
		public static Imports.XorRandom r = new Imports.XorRandom();

		// Token: 0x04000019 RID: 25
		public static int j = new Random().Next(int.MinValue, int.MaxValue);

		// Token: 0x0400001A RID: 26
		public static int rs = new Random().Next(int.MinValue, int.MaxValue);

		// Token: 0x0400001B RID: 27
		public static object _XUP = 256;

		// Token: 0x0400001C RID: 28
		private const uint MOUSEEVENTF_WHEEL = 2048U;

		// Token: 0x0400001D RID: 29
		private const uint MOUSEEVENTF_HWHEEL = 4096U;

		// Token: 0x0400001E RID: 30
		public const int LR_DEFAULTCOLOR = 0;

		// Token: 0x0400001F RID: 31
		public const int LR_MONOCHROME = 1;

		// Token: 0x04000020 RID: 32
		public const int LR_COPYRETURNORG = 4;

		// Token: 0x04000021 RID: 33
		public const int LR_COPYDELETEORG = 8;

		// Token: 0x04000022 RID: 34
		public const int LR_LOADFROMFILE = 16;

		// Token: 0x04000023 RID: 35
		public const int LR_LOADTRANSPARENT = 32;

		// Token: 0x04000024 RID: 36
		public const int LR_DEFAULTSIZE = 64;

		// Token: 0x04000025 RID: 37
		public const int LR_VGACOLOR = 128;

		// Token: 0x04000026 RID: 38
		public const int LR_LOADMAP3DCOLORS = 4096;

		// Token: 0x04000027 RID: 39
		public const int LR_CREATEDIBSECTION = 8192;

		// Token: 0x04000028 RID: 40
		public const int LR_COPYFROMRESOURCE = 16384;

		// Token: 0x04000029 RID: 41
		public const int LR_SHARED = 32768;

		// Token: 0x0400002A RID: 42
		private const int AC_SRC_OVER = 0;

		// Token: 0x0400002B RID: 43
		private const int AC_SRC_ALPHA = 1;

		// Token: 0x0400002C RID: 44
		public static IntPtr IDI_APPLICATION = Imports.MAKEINTRESOURCE(32512);

		// Token: 0x0400002D RID: 45
		public static IntPtr IDI_ERROR = Imports.MAKEINTRESOURCE(32513);

		// Token: 0x0400002E RID: 46
		public static IntPtr IDI_QUESTION = Imports.MAKEINTRESOURCE(32514);

		// Token: 0x0400002F RID: 47
		public static IntPtr IDI_WARNING = Imports.MAKEINTRESOURCE(32515);

		// Token: 0x04000030 RID: 48
		public static IntPtr IDI_ASTERISK = Imports.MAKEINTRESOURCE(32516);

		// Token: 0x0200000A RID: 10
		public enum SYSTEM_POWER_STATE
		{
			// Token: 0x04000037 RID: 55
			PowerSystemUnspecified,
			// Token: 0x04000038 RID: 56
			PowerSystemWorking,
			// Token: 0x04000039 RID: 57
			PowerSystemSleeping1,
			// Token: 0x0400003A RID: 58
			PowerSystemSleeping2,
			// Token: 0x0400003B RID: 59
			PowerSystemSleeping3,
			// Token: 0x0400003C RID: 60
			PowerSystemHibernate,
			// Token: 0x0400003D RID: 61
			PowerSystemShutdown,
			// Token: 0x0400003E RID: 62
			PowerSystemMaximum
		}

		// Token: 0x0200000B RID: 11
		public enum SHUTDOWN_ACTION
		{
			// Token: 0x04000040 RID: 64
			ShutdownNoReboot,
			// Token: 0x04000041 RID: 65
			ShutdownReboot,
			// Token: 0x04000042 RID: 66
			ShutdownPowerOff
		}

		// Token: 0x0200000C RID: 12
		public enum POWER_ACTION
		{
			// Token: 0x04000044 RID: 68
			PowerActionNone,
			// Token: 0x04000045 RID: 69
			PowerActionReserved,
			// Token: 0x04000046 RID: 70
			PowerActionSleep,
			// Token: 0x04000047 RID: 71
			PowerActionHibernate,
			// Token: 0x04000048 RID: 72
			PowerActionShutdown,
			// Token: 0x04000049 RID: 73
			PowerActionShutdownReset,
			// Token: 0x0400004A RID: 74
			PowerActionShutdownOff,
			// Token: 0x0400004B RID: 75
			PowerActionWarmEject,
			// Token: 0x0400004C RID: 76
			PowerActionDisplayOff
		}

		// Token: 0x0200000D RID: 13
		public struct rgb
		{
			// Token: 0x0600009C RID: 156 RVA: 0x0000439D File Offset: 0x0000259D
			public rgb(byte r, byte g, byte b)
			{
				this.r = r;
				this.g = g;
				this.b = b;
			}

			// Token: 0x0600009D RID: 157 RVA: 0x000043B5 File Offset: 0x000025B5
			public rgb(Imports.RGBQUAD rgbq)
			{
				this.r = rgbq.rgbRed;
				this.g = rgbq.rgbGreen;
				this.b = rgbq.rgbBlue;
			}

			// Token: 0x0600009E RID: 158 RVA: 0x000043DC File Offset: 0x000025DC
			public rgb(Color rgbcol)
			{
				this.r = rgbcol.R;
				this.g = rgbcol.G;
				this.b = rgbcol.B;
			}

			// Token: 0x0600009F RID: 159 RVA: 0x00004406 File Offset: 0x00002606
			public rgb(int rgbwin32)
			{
				this.r = (byte)(rgbwin32 & 255);
				this.g = (byte)(rgbwin32 >> 8 & 255);
				this.b = (byte)(rgbwin32 >> 16 & 255);
			}

			// Token: 0x060000A0 RID: 160 RVA: 0x00004438 File Offset: 0x00002638
			public rgb(Imports.hsv hsv)
			{
				bool flag = hsv.h >= 0.0 && hsv.h < 360.0 && hsv.s >= 0.0 && hsv.s <= 1.0 && hsv.v >= 0.0 && hsv.v <= 1.0;
				if (flag)
				{
					double num = hsv.v * hsv.s;
					double num2 = num * (1.0 - Imports.abs(hsv.h / 60.0 % 2.0 - 1.0));
					double num3 = hsv.v - num;
					double num4 = 0.0;
					double num5 = 0.0;
					double num6 = 0.0;
					bool flag2 = hsv.h >= 0.0 && hsv.h < 60.0;
					if (flag2)
					{
						num4 = num;
						num5 = num2;
						num6 = 0.0;
					}
					else
					{
						bool flag3 = hsv.h >= 60.0 && hsv.h < 120.0;
						if (flag3)
						{
							num4 = num2;
							num5 = num;
							num6 = 0.0;
						}
						else
						{
							bool flag4 = hsv.h >= 120.0 && hsv.h < 180.0;
							if (flag4)
							{
								num4 = 0.0;
								num5 = num;
								num6 = num2;
							}
							else
							{
								bool flag5 = hsv.h >= 180.0 && hsv.h < 240.0;
								if (flag5)
								{
									num4 = 0.0;
									num5 = num2;
									num6 = num;
								}
								else
								{
									bool flag6 = hsv.h >= 240.0 && hsv.h < 300.0;
									if (flag6)
									{
										num4 = num2;
										num5 = 0.0;
										num6 = num;
									}
									else
									{
										bool flag7 = hsv.h >= 300.0 && hsv.h < 360.0;
										if (flag7)
										{
											num4 = num;
											num5 = 0.0;
											num6 = num2;
										}
									}
								}
							}
						}
					}
					this.r = (byte)((num4 + num3) * 255.0);
					this.g = (byte)((num5 + num3) * 255.0);
					this.b = (byte)((num6 + num3) * 255.0);
				}
				else
				{
					this.r = 0;
					this.g = 0;
					this.b = 0;
				}
			}

			// Token: 0x060000A1 RID: 161 RVA: 0x0000470C File Offset: 0x0000290C
			public uint towin32()
			{
				return Imports._RGB(this.r, this.g, this.b);
			}

			// Token: 0x060000A2 RID: 162 RVA: 0x00004738 File Offset: 0x00002938
			public Color tocol()
			{
				return Imports.RGB((int)this.r, (int)this.g, (int)this.b);
			}

			// Token: 0x0400004D RID: 77
			public byte r;

			// Token: 0x0400004E RID: 78
			public byte g;

			// Token: 0x0400004F RID: 79
			public byte b;
		}

		// Token: 0x0200000E RID: 14
		public struct hsv
		{
			// Token: 0x060000A3 RID: 163 RVA: 0x00004761 File Offset: 0x00002961
			public hsv(double h, double s, double l)
			{
				this.h = h;
				this.s = s;
				this.v = l;
			}

			// Token: 0x060000A4 RID: 164 RVA: 0x00004779 File Offset: 0x00002979
			public hsv(Imports.hsv k)
			{
				this.h = k.h;
				this.s = k.s;
				this.v = k.v;
			}

			// Token: 0x060000A5 RID: 165 RVA: 0x000047A0 File Offset: 0x000029A0
			public hsv(Imports.rgb rgb)
			{
				double num = (double)rgb.r / 255.0;
				double num2 = (double)rgb.g / 255.0;
				double num3 = (double)rgb.b / 255.0;
				double num4 = Imports.max(Imports.max(num, num2), num3);
				double num5 = Imports.min(Imports.min(num, num2), num3);
				double num6 = num4 - num5;
				double num7 = 0.0;
				bool flag = num6 == 0.0;
				if (flag)
				{
					num7 = 0.0;
				}
				else
				{
					bool flag2 = num4 == num;
					if (flag2)
					{
						num7 = 60.0 * ((num2 - num3) / num6 % 6.0);
					}
					else
					{
						bool flag3 = num4 == num2;
						if (flag3)
						{
							num7 = 60.0 * ((num3 - num) / num6 + 2.0);
						}
						else
						{
							bool flag4 = num4 == num3;
							if (flag4)
							{
								num7 = 60.0 * ((num - num2) / num6 + 4.0);
							}
						}
					}
				}
				double num8 = (num4 == 0.0) ? 0.0 : (num6 / num4);
				double num9 = num4;
				this.h = num7;
				this.s = num8;
				this.v = num9;
			}

			// Token: 0x060000A6 RID: 166 RVA: 0x00004900 File Offset: 0x00002B00
			public Imports.hsv addhue(double hue)
			{
				this.h += hue;
				this.h %= 360.0;
				this.h = Imports.abs(this.h);
				return this;
			}

			// Token: 0x060000A7 RID: 167 RVA: 0x00004950 File Offset: 0x00002B50
			public Imports.hsv changehue(double hue)
			{
				this.h = hue;
				this.h %= 360.0;
				this.h = Imports.abs(this.h);
				return this;
			}

			// Token: 0x060000A8 RID: 168 RVA: 0x00004998 File Offset: 0x00002B98
			public Imports.hsv changebright(double hue)
			{
				this.v = Imports.abs(Imports.fmod(hue, 1.0));
				return this;
			}

			// Token: 0x060000A9 RID: 169 RVA: 0x000049CC File Offset: 0x00002BCC
			public Imports.hsv changeSAT(double sat)
			{
				this.s = Imports.abs(Imports.fmod(sat, 1.0));
				return this;
			}

			// Token: 0x04000050 RID: 80
			public double h;

			// Token: 0x04000051 RID: 81
			public double s;

			// Token: 0x04000052 RID: 82
			public double v;
		}

		// Token: 0x0200000F RID: 15
		public class XorRandom : Random
		{
			// Token: 0x060000AA RID: 170 RVA: 0x00004A00 File Offset: 0x00002C00
			public int nextXor()
			{
				return Imports.XorYeet32();
			}

			// Token: 0x060000AB RID: 171 RVA: 0x00004A18 File Offset: 0x00002C18
			public int nextXor(int max)
			{
				return Imports.XorYeet32() % max;
			}

			// Token: 0x060000AC RID: 172 RVA: 0x00004A34 File Offset: 0x00002C34
			public int nextXor(int min, int max)
			{
				return Imports.XorYeet32() % (max - min) + min;
			}
		}

		// Token: 0x02000010 RID: 16
		public enum MouseEventFlags : uint
		{
			// Token: 0x04000054 RID: 84
			LEFTDOWN = 2U,
			// Token: 0x04000055 RID: 85
			LEFTUP = 4U,
			// Token: 0x04000056 RID: 86
			MIDDLEDOWN = 32U,
			// Token: 0x04000057 RID: 87
			MIDDLEUP = 64U,
			// Token: 0x04000058 RID: 88
			MOVE = 1U,
			// Token: 0x04000059 RID: 89
			ABSOLUTE = 32768U,
			// Token: 0x0400005A RID: 90
			RIGHTDOWN = 8U,
			// Token: 0x0400005B RID: 91
			RIGHTUP = 16U,
			// Token: 0x0400005C RID: 92
			WHEEL = 2048U,
			// Token: 0x0400005D RID: 93
			XDOWN = 128U,
			// Token: 0x0400005E RID: 94
			XUP = 256U
		}

		// Token: 0x02000011 RID: 17
		public enum MouseEventDataXButtons : uint
		{
			// Token: 0x04000060 RID: 96
			XBUTTON1 = 1U,
			// Token: 0x04000061 RID: 97
			XBUTTON2
		}

		// Token: 0x02000012 RID: 18
		public struct RAMP
		{
			// Token: 0x04000062 RID: 98
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public ushort[] Red;

			// Token: 0x04000063 RID: 99
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public ushort[] Green;

			// Token: 0x04000064 RID: 100
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public ushort[] Blue;
		}

		// Token: 0x02000013 RID: 19
		public struct BITMAPINFO
		{
			// Token: 0x04000065 RID: 101
			public Imports.BITMAPINFOHEADER bmiHeader;

			// Token: 0x04000066 RID: 102
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 1, ArraySubType = UnmanagedType.Struct)]
			public Imports.RGBQUAD[] bmiColors;
		}

		// Token: 0x02000014 RID: 20
		public struct BITMAPINFOHEADER
		{
			// Token: 0x060000AE RID: 174 RVA: 0x00004A5A File Offset: 0x00002C5A
			public void Init()
			{
				this.biSize = (uint)Marshal.SizeOf(this);
			}

			// Token: 0x04000067 RID: 103
			public uint biSize;

			// Token: 0x04000068 RID: 104
			public int biWidth;

			// Token: 0x04000069 RID: 105
			public int biHeight;

			// Token: 0x0400006A RID: 106
			public ushort biPlanes;

			// Token: 0x0400006B RID: 107
			public ushort biBitCount;

			// Token: 0x0400006C RID: 108
			public uint biSizeImage;

			// Token: 0x0400006D RID: 109
			public int biXPelsPerMeter;

			// Token: 0x0400006E RID: 110
			public int biYPelsPerMeter;

			// Token: 0x0400006F RID: 111
			public uint biClrUsed;

			// Token: 0x04000070 RID: 112
			public uint biClrImportant;

			// Token: 0x04000071 RID: 113
			public uint biCompression;
		}

		// Token: 0x02000015 RID: 21
		private enum BitmapCompressionMode : uint
		{
			// Token: 0x04000073 RID: 115
			BI_RGB,
			// Token: 0x04000074 RID: 116
			BI_RLE8,
			// Token: 0x04000075 RID: 117
			BI_RLE4,
			// Token: 0x04000076 RID: 118
			BI_BITFIELDS,
			// Token: 0x04000077 RID: 119
			BI_JPEG,
			// Token: 0x04000078 RID: 120
			BI_PNG
		}

		// Token: 0x02000016 RID: 22
		public enum DIB_Color_Mode : uint
		{
			// Token: 0x0400007A RID: 122
			DIB_RGB_COLORS,
			// Token: 0x0400007B RID: 123
			DIB_PAL_COLORS
		}

		// Token: 0x02000017 RID: 23
		public enum StretchBltMode
		{
			// Token: 0x0400007D RID: 125
			STRETCH_ANDSCANS = 1,
			// Token: 0x0400007E RID: 126
			STRETCH_ORSCANS,
			// Token: 0x0400007F RID: 127
			STRETCH_DELETESCANS,
			// Token: 0x04000080 RID: 128
			STRETCH_HALFTONE
		}

		// Token: 0x02000018 RID: 24
		public struct PAINTSTRUCT
		{
			// Token: 0x04000081 RID: 129
			public IntPtr hdc;

			// Token: 0x04000082 RID: 130
			public bool fErase;

			// Token: 0x04000083 RID: 131
			public Imports.RECT rcPaint;

			// Token: 0x04000084 RID: 132
			public bool fRestore;

			// Token: 0x04000085 RID: 133
			public bool fIncUpdate;

			// Token: 0x04000086 RID: 134
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 32)]
			public byte[] rgbReserved;
		}

		// Token: 0x02000019 RID: 25
		public struct RECT
		{
			// Token: 0x060000AF RID: 175 RVA: 0x00004A73 File Offset: 0x00002C73
			public RECT(int left, int top, int right, int bottom)
			{
				this.Left = left;
				this.Top = top;
				this.Right = right;
				this.Bottom = bottom;
			}

			// Token: 0x060000B0 RID: 176 RVA: 0x00004A93 File Offset: 0x00002C93
			public RECT(Rectangle r)
			{
				this = new Imports.RECT(r.Left, r.Top, r.Right, r.Bottom);
			}

			// Token: 0x17000006 RID: 6
			// (get) Token: 0x060000B1 RID: 177 RVA: 0x00004ABC File Offset: 0x00002CBC
			// (set) Token: 0x060000B2 RID: 178 RVA: 0x00004AD4 File Offset: 0x00002CD4
			public int X
			{
				get
				{
					return this.Left;
				}
				set
				{
					this.Right -= this.Left - value;
					this.Left = value;
				}
			}

			// Token: 0x17000007 RID: 7
			// (get) Token: 0x060000B3 RID: 179 RVA: 0x00004AF4 File Offset: 0x00002CF4
			// (set) Token: 0x060000B4 RID: 180 RVA: 0x00004B0C File Offset: 0x00002D0C
			public int Y
			{
				get
				{
					return this.Top;
				}
				set
				{
					this.Bottom -= this.Top - value;
					this.Top = value;
				}
			}

			// Token: 0x17000008 RID: 8
			// (get) Token: 0x060000B5 RID: 181 RVA: 0x00004B2C File Offset: 0x00002D2C
			// (set) Token: 0x060000B6 RID: 182 RVA: 0x00004B4B File Offset: 0x00002D4B
			public int Height
			{
				get
				{
					return this.Bottom - this.Top;
				}
				set
				{
					this.Bottom = value + this.Top;
				}
			}

			// Token: 0x17000009 RID: 9
			// (get) Token: 0x060000B7 RID: 183 RVA: 0x00004B5C File Offset: 0x00002D5C
			// (set) Token: 0x060000B8 RID: 184 RVA: 0x00004B7B File Offset: 0x00002D7B
			public int Width
			{
				get
				{
					return this.Right - this.Left;
				}
				set
				{
					this.Right = value + this.Left;
				}
			}

			// Token: 0x1700000A RID: 10
			// (get) Token: 0x060000B9 RID: 185 RVA: 0x00004B8C File Offset: 0x00002D8C
			// (set) Token: 0x060000BA RID: 186 RVA: 0x00004BAF File Offset: 0x00002DAF
			public Point Location
			{
				get
				{
					return new Point(this.Left, this.Top);
				}
				set
				{
					this.X = value.X;
					this.Y = value.Y;
				}
			}

			// Token: 0x1700000B RID: 11
			// (get) Token: 0x060000BB RID: 187 RVA: 0x00004BD0 File Offset: 0x00002DD0
			// (set) Token: 0x060000BC RID: 188 RVA: 0x00004BF3 File Offset: 0x00002DF3
			public Size Size
			{
				get
				{
					return new Size(this.Width, this.Height);
				}
				set
				{
					this.Width = value.Width;
					this.Height = value.Height;
				}
			}

			// Token: 0x060000BD RID: 189 RVA: 0x00004C14 File Offset: 0x00002E14
			public static implicit operator Rectangle(Imports.RECT r)
			{
				return new Rectangle(r.Left, r.Top, r.Width, r.Height);
			}

			// Token: 0x060000BE RID: 190 RVA: 0x00004C48 File Offset: 0x00002E48
			public static implicit operator Imports.RECT(Rectangle r)
			{
				return new Imports.RECT(r);
			}

			// Token: 0x060000BF RID: 191 RVA: 0x00004C60 File Offset: 0x00002E60
			public static bool operator ==(Imports.RECT r1, Imports.RECT r2)
			{
				return r1.Equals(r2);
			}

			// Token: 0x060000C0 RID: 192 RVA: 0x00004C7C File Offset: 0x00002E7C
			public static bool operator !=(Imports.RECT r1, Imports.RECT r2)
			{
				return !r1.Equals(r2);
			}

			// Token: 0x060000C1 RID: 193 RVA: 0x00004C9C File Offset: 0x00002E9C
			public bool Equals(Imports.RECT r)
			{
				return r.Left == this.Left && r.Top == this.Top && r.Right == this.Right && r.Bottom == this.Bottom;
			}

			// Token: 0x060000C2 RID: 194 RVA: 0x00004CEC File Offset: 0x00002EEC
			public override bool Equals(object obj)
			{
				bool flag = obj is Imports.RECT;
				bool result;
				if (flag)
				{
					result = this.Equals((Imports.RECT)obj);
				}
				else
				{
					bool flag2 = obj is Rectangle;
					result = (flag2 && this.Equals(new Imports.RECT((Rectangle)obj)));
				}
				return result;
			}

			// Token: 0x060000C3 RID: 195 RVA: 0x00004D3C File Offset: 0x00002F3C
			public override int GetHashCode()
			{
				return this.GetHashCode();
			}

			// Token: 0x060000C4 RID: 196 RVA: 0x00004D68 File Offset: 0x00002F68
			public override string ToString()
			{
				return string.Format(CultureInfo.CurrentCulture, "{{Left={0},Top={1},Right={2},Bottom={3}}}", new object[]
				{
					this.Left,
					this.Top,
					this.Right,
					this.Bottom
				});
			}

			// Token: 0x04000087 RID: 135
			public int Left;

			// Token: 0x04000088 RID: 136
			public int Top;

			// Token: 0x04000089 RID: 137
			public int Right;

			// Token: 0x0400008A RID: 138
			public int Bottom;
		}

		// Token: 0x0200001A RID: 26
		public enum LoadLibraryFlags : uint
		{
			// Token: 0x0400008C RID: 140
			DONT_RESOLVE_DLL_REFERENCES = 1U,
			// Token: 0x0400008D RID: 141
			LOAD_IGNORE_CODE_AUTHZ_LEVEL = 16U,
			// Token: 0x0400008E RID: 142
			LOAD_LIBRARY_AS_DATAFILE = 2U,
			// Token: 0x0400008F RID: 143
			LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE = 64U,
			// Token: 0x04000090 RID: 144
			LOAD_LIBRARY_AS_IMAGE_RESOURCE = 32U,
			// Token: 0x04000091 RID: 145
			LOAD_WITH_ALTERED_SEARCH_PATH = 8U
		}

		// Token: 0x0200001B RID: 27
		public enum PenStyle
		{
			// Token: 0x04000093 RID: 147
			PS_SOLID,
			// Token: 0x04000094 RID: 148
			PS_DASH,
			// Token: 0x04000095 RID: 149
			PS_DOT,
			// Token: 0x04000096 RID: 150
			PS_DASHDOT,
			// Token: 0x04000097 RID: 151
			PS_DASHDOTDOT,
			// Token: 0x04000098 RID: 152
			PS_NULL,
			// Token: 0x04000099 RID: 153
			PS_INSIDEFRAME,
			// Token: 0x0400009A RID: 154
			PS_USERSTYLE,
			// Token: 0x0400009B RID: 155
			PS_ALTERNATE,
			// Token: 0x0400009C RID: 156
			PS_STYLE_MASK = 15,
			// Token: 0x0400009D RID: 157
			PS_ENDCAP_ROUND = 0,
			// Token: 0x0400009E RID: 158
			PS_ENDCAP_SQUARE = 256,
			// Token: 0x0400009F RID: 159
			PS_ENDCAP_FLAT = 512,
			// Token: 0x040000A0 RID: 160
			PS_ENDCAP_MASK = 3840,
			// Token: 0x040000A1 RID: 161
			PS_JOIN_ROUND = 0,
			// Token: 0x040000A2 RID: 162
			PS_JOIN_BEVEL = 4096,
			// Token: 0x040000A3 RID: 163
			PS_JOIN_MITER = 8192,
			// Token: 0x040000A4 RID: 164
			PS_JOIN_MASK = 61440,
			// Token: 0x040000A5 RID: 165
			PS_COSMETIC = 0,
			// Token: 0x040000A6 RID: 166
			PS_GEOMETRIC = 65536,
			// Token: 0x040000A7 RID: 167
			PS_TYPE_MASK = 983040
		}

		// Token: 0x0200001C RID: 28
		public enum TernaryRasterOperations : long
		{
			// Token: 0x040000A9 RID: 169
			SRCCOPY = 13369376L,
			// Token: 0x040000AA RID: 170
			SRCPAINT = 15597702L,
			// Token: 0x040000AB RID: 171
			SRCAND = 8913094L,
			// Token: 0x040000AC RID: 172
			SRCINVERT = 6684742L,
			// Token: 0x040000AD RID: 173
			SRCERASE = 4457256L,
			// Token: 0x040000AE RID: 174
			NOTSRCCOPY = 3342344L,
			// Token: 0x040000AF RID: 175
			NOTSRCERASE = 1114278L,
			// Token: 0x040000B0 RID: 176
			MERGECOPY = 12583114L,
			// Token: 0x040000B1 RID: 177
			MERGEPAINT = 12255782L,
			// Token: 0x040000B2 RID: 178
			PATCOPY = 15728673L,
			// Token: 0x040000B3 RID: 179
			PATPAINT = 16452105L,
			// Token: 0x040000B4 RID: 180
			PATINVERT = 5898313L,
			// Token: 0x040000B5 RID: 181
			DSTINVERT = 5570569L,
			// Token: 0x040000B6 RID: 182
			BLACKNESS = 66L,
			// Token: 0x040000B7 RID: 183
			WHITENESS = 16711778L,
			// Token: 0x040000B8 RID: 184
			CAPTUREBLT = 1073741824L,
			// Token: 0x040000B9 RID: 185
			CUSTOM = 1051781L,
			// Token: 0x040000BA RID: 186
			RGBCOPY = 107385454862L,
			// Token: 0x040000BB RID: 187
			SRCOR = 15597702L,
			// Token: 0x040000BC RID: 188
			SRCXOR = 6684742L
		}

		// Token: 0x0200001D RID: 29
		public struct POINT
		{
			// Token: 0x060000C5 RID: 197 RVA: 0x00004DC7 File Offset: 0x00002FC7
			public POINT(int x, int y)
			{
				this.x = x;
				this.y = y;
			}

			// Token: 0x060000C6 RID: 198 RVA: 0x00004DD8 File Offset: 0x00002FD8
			public static implicit operator Point(Imports.POINT p)
			{
				return new Point(p.x, p.y);
			}

			// Token: 0x060000C7 RID: 199 RVA: 0x00004DFC File Offset: 0x00002FFC
			public static implicit operator Imports.POINT(Point p)
			{
				return new Imports.POINT(p.X, p.Y);
			}

			// Token: 0x040000BD RID: 189
			public int x;

			// Token: 0x040000BE RID: 190
			public int y;
		}

		// Token: 0x0200001E RID: 30
		public struct BLENDFUNCTION
		{
			// Token: 0x060000C8 RID: 200 RVA: 0x00004E21 File Offset: 0x00003021
			public BLENDFUNCTION(byte op, byte flags, byte alpha, byte format)
			{
				this.BlendOp = op;
				this.BlendFlags = flags;
				this.SourceConstantAlpha = alpha;
				this.AlphaFormat = format;
			}

			// Token: 0x040000BF RID: 191
			private byte BlendOp;

			// Token: 0x040000C0 RID: 192
			private byte BlendFlags;

			// Token: 0x040000C1 RID: 193
			private byte SourceConstantAlpha;

			// Token: 0x040000C2 RID: 194
			private byte AlphaFormat;
		}

		// Token: 0x0200001F RID: 31
		public struct GRADIENT_RECT
		{
			// Token: 0x060000C9 RID: 201 RVA: 0x00004E41 File Offset: 0x00003041
			public GRADIENT_RECT(uint upLeft, uint lowRight)
			{
				this.UpperLeft = upLeft;
				this.LowerRight = lowRight;
			}

			// Token: 0x040000C3 RID: 195
			public uint UpperLeft;

			// Token: 0x040000C4 RID: 196
			public uint LowerRight;
		}

		// Token: 0x02000020 RID: 32
		public struct TRIVERTEX
		{
			// Token: 0x060000CA RID: 202 RVA: 0x00004E52 File Offset: 0x00003052
			public TRIVERTEX(int x, int y, ushort red, ushort green, ushort blue, ushort alpha)
			{
				this.x = x;
				this.y = y;
				this.Red = red;
				this.Green = green;
				this.Blue = blue;
				this.Alpha = alpha;
			}

			// Token: 0x040000C5 RID: 197
			public int x;

			// Token: 0x040000C6 RID: 198
			public int y;

			// Token: 0x040000C7 RID: 199
			public ushort Red;

			// Token: 0x040000C8 RID: 200
			public ushort Green;

			// Token: 0x040000C9 RID: 201
			public ushort Blue;

			// Token: 0x040000CA RID: 202
			public ushort Alpha;
		}

		// Token: 0x02000021 RID: 33
		public enum GRADIENT_FILL : uint
		{
			// Token: 0x040000CC RID: 204
			RECT_H,
			// Token: 0x040000CD RID: 205
			RECT_V,
			// Token: 0x040000CE RID: 206
			TRIANGLE,
			// Token: 0x040000CF RID: 207
			OP_FLAG = 255U
		}

		// Token: 0x02000022 RID: 34
		public struct GRADIENT_TRIANGLE
		{
			// Token: 0x060000CB RID: 203 RVA: 0x00004E82 File Offset: 0x00003082
			public GRADIENT_TRIANGLE(uint vertex1, uint vertex2, uint vertex3)
			{
				this.Vertex1 = vertex1;
				this.Vertex2 = vertex2;
				this.Vertex3 = vertex3;
			}

			// Token: 0x040000D0 RID: 208
			public uint Vertex1;

			// Token: 0x040000D1 RID: 209
			public uint Vertex2;

			// Token: 0x040000D2 RID: 210
			public uint Vertex3;
		}

		// Token: 0x02000023 RID: 35
		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		public struct RGBQUAD
		{
			// Token: 0x040000D3 RID: 211
			public byte rgbBlue;

			// Token: 0x040000D4 RID: 212
			public byte rgbGreen;

			// Token: 0x040000D5 RID: 213
			public byte rgbRed;

			// Token: 0x040000D6 RID: 214
			public byte rgbReserved;
		}

		// Token: 0x02000024 RID: 36
		[StructLayout(LayoutKind.Sequential, Pack = 1)]
		public struct RGBTRIPLE
		{
			// Token: 0x040000D7 RID: 215
			public byte rgbtBlue;

			// Token: 0x040000D8 RID: 216
			public byte rgbtGreen;

			// Token: 0x040000D9 RID: 217
			public byte rgbtRed;
		}

		// Token: 0x02000025 RID: 37
		[Flags]
		public enum RedrawWindowFlags : uint
		{
			// Token: 0x040000DB RID: 219
			Invalidate = 1U,
			// Token: 0x040000DC RID: 220
			InternalPaint = 2U,
			// Token: 0x040000DD RID: 221
			Erase = 4U,
			// Token: 0x040000DE RID: 222
			Validate = 8U,
			// Token: 0x040000DF RID: 223
			NoInternalPaint = 16U,
			// Token: 0x040000E0 RID: 224
			NoErase = 32U,
			// Token: 0x040000E1 RID: 225
			NoChildren = 64U,
			// Token: 0x040000E2 RID: 226
			AllChildren = 128U,
			// Token: 0x040000E3 RID: 227
			UpdateNow = 256U,
			// Token: 0x040000E4 RID: 228
			EraseNow = 512U,
			// Token: 0x040000E5 RID: 229
			Frame = 1024U,
			// Token: 0x040000E6 RID: 230
			NoFrame = 2048U
		}

		// Token: 0x02000026 RID: 38
		public enum typesChr
		{
			// Token: 0x040000E8 RID: 232
			VERTICAL,
			// Token: 0x040000E9 RID: 233
			HORIZONTAL,
			// Token: 0x040000EA RID: 234
			DIAGONAL1,
			// Token: 0x040000EB RID: 235
			DIAGONAL2
		}
	}
}
