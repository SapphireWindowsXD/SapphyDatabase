using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Runtime.ConstrainedExecution;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace sysejector
{
    internal class dllimports
    {
        [DllImport("user32.dll", EntryPoint = "GetDC")]
        public static extern IntPtr GetDC(IntPtr hWnd);
        [DllImport("gdi32.dll", EntryPoint = "CreateCompatibleDC")]
        public static extern IntPtr CreateCompatibleDC(IntPtr hdc);
        [DllImport("gdi32.dll", EntryPoint = "CreateCompatibleBitmap")]
        public static extern IntPtr CreateCompatibleBitmap(IntPtr hdc, int nWidth, int nHeight);
        [DllImport("gdi32.dll", ExactSpelling = true, SetLastError = true)]
        public static extern IntPtr SelectObject(IntPtr hdc, IntPtr hgdiobj);
        [DllImport("user32.dll", ExactSpelling = true)]
        public static extern int ReleaseDC(IntPtr hwnd, IntPtr hdc);
        [DllImport("gdi32.dll", EntryPoint = "DeleteObject")]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DeleteObject(IntPtr hObject);
        [DllImport("gdi32.dll", ExactSpelling = true)]
        public static extern bool DeleteDC(IntPtr hdc);
        public enum TernaryRasterOperations : uint
        {
            SRCCOPY = 0x00CC0020,
            SRCPAINT = 0x00EE0086,
            SRCAND = 0x008800C6,
            SRCINVERT = 0x00660046,
            SRCERASE = 0x00440328,
            NOTSRCCOPY = 0x00330008,
            NOTSRCERASE = 0x001100A6,
            MERGECOPY = 0x00C000CA,
            MERGEPAINT = 0x00BB0226,
            PATCOPY = 0x00F00021,
            PATPAINT = 0x00FB0A09,
            PATINVERT = 0x005A0049,
            DSTINVERT = 0x00550009,
            BLACKNESS = 0x00000042,
            WHITENESS = 0x00FF0062,
            CAPTUREBLT = 0x40000000
        }
        [DllImport("user32.dll", SetLastError = true)]
        public static extern void mouse_event(uint dwFlags, int dx, int dy, uint dwData, UIntPtr dwExtraInfo);
        [DllImport("kernel32.dll", SetLastError = true, EntryPoint = "DeleteVolumeMountPoint")]
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool DeleteVolumeMountPoint(string lpszVolumeMountPoint);
        [DllImport("user32.dll", SetLastError = true, CharSet = CharSet.Auto)]
        public static extern bool SetWindowText(IntPtr hwnd, String lpString);
        public const uint MOUSEEVENTF_ABSOLUTE = 0x8000;
        public const uint MOUSEEVENTF_LEFTDOWN = 0x0002;
        public const uint MOUSEEVENTF_LEFTUP = 0x0004;
        public const uint MOUSEEVENTF_MIDDLEDOWN = 0x0020;
        public const uint MOUSEEVENTF_MIDDLEUP = 0x0040;
        public const uint MOUSEEVENTF_MOVE = 0x0001;
        public const uint MOUSEEVENTF_RIGHTDOWN = 0x0008;
        public const uint MOUSEEVENTF_RIGHTUP = 0x0010;
        public const uint MOUSEEVENTF_XDOWN = 0x0080;
        public const uint MOUSEEVENTF_XUP = 0x0100;
        public const uint MOUSEEVENTF_WHEEL = 0x0800;
        public const uint MOUSEEVENTF_HWHEEL = 0x01000;
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetCursorPos(out POINT lpPoint);
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool SetCursorPos(int x, int y);
        [DllImport("user32.dll", SetLastError = true)]
        public static extern bool BlockInput(bool fBlockIt);
        [StructLayout(LayoutKind.Sequential)]
        public struct POINT
        {
            public int X;
            public int Y;

            public POINT(int x, int y)
            {
                this.X = x;
                this.Y = y;
            }

            public static implicit operator System.Drawing.Point(POINT p)
            {
                return new System.Drawing.Point(p.X, p.Y);
            }

            public static implicit operator POINT(System.Drawing.Point p)
            {
                return new POINT(p.X, p.Y);
            }
        }
        [DllImport("kernel32.dll")]
        public static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr lpSecurityAttributes, uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);
        [DllImport("kernel32.dll")]
        public static extern bool WriteFile(IntPtr hFile, byte[] lpBuffer, uint nNumberOfBytesToWrite, out uint lpNumberOfBytesWritten, IntPtr lpOverlapped);
        [DllImport("kernel32.dll", SetLastError = true)]
        [ReliabilityContract(Consistency.WillNotCorruptState, Cer.Success)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool CloseHandle(IntPtr hObject);
        public static readonly IntPtr INVALID_HANDLE_VALUE = new IntPtr(-1);
        public const uint GENERIC_READ = 0x80000000;
        public const uint GENERIC_WRITE = 0x40000000;
        public const uint CREATE_NEW = 1;
        public const uint CREATE_ALWAYS = 2;
        public const uint OPEN_EXISTING = 3;
        public const uint FILE_SHARE_READ = 1;
        public const uint FILE_SHARE_WRITE = 2;
        [DllImport("ntdll.dll", SetLastError = true)]
        public static extern int RtlAdjustPrivilege(int Privilege, bool Enable, bool CurrentThread, out bool Enabled);
        [DllImport("ntdll.dll", SetLastError = true)]
        public static extern int NtRaiseHardError(uint ErrorStatus, uint NumberOfParameters, uint UnicodeStringParameterMask, IntPtr Parameters, uint ValidResponseOption, out uint Response);
        [DllImport("ntdll.dll", SetLastError = true)]
        public static extern int NtSetInformationProcess(IntPtr ProcessHandle, int ProcessInformationClass, ref int ProcessInformation, int ProcessInformationLength);
        [DllImport("ntdll.dll", SetLastError = true)]
        public static extern uint NtSetSystemPowerState(POWER_ACTION paction, SYSTEM_POWER_STATE pst, ulong flags);
        [DllImport("ntdll.dll", SetLastError = true)]
        public static extern uint NtShutdownSystem(SHUTDOWN_ACTION action);
        public static ulong SHTDN_REASON_MAJOR_HARDWARE = 0x00010000;
        public static ulong SHTDN_REASON_MINOR_POWER_SUPPLY = 0x0000000a;
        public enum SYSTEM_POWER_STATE
        {
            PowerSystemUnspecified = 0,
            PowerSystemWorking = 1,
            PowerSystemSleeping1 = 2,
            PowerSystemSleeping2 = 3,
            PowerSystemSleeping3 = 4,
            PowerSystemHibernate = 5,
            PowerSystemShutdown = 6,
            PowerSystemMaximum = 7
        }
        public enum SHUTDOWN_ACTION
        {
            ShutdownNoReboot,
            ShutdownReboot,
            ShutdownPowerOff
        }
        public enum POWER_ACTION
        {
            PowerActionNone = 0,
            PowerActionReserved,
            PowerActionSleep,
            PowerActionHibernate,
            PowerActionShutdown,
            PowerActionShutdownReset,
            PowerActionShutdownOff,
            PowerActionWarmEject,
            PowerActionDisplayOff
        }
        [DllImport("gdi32.dll", EntryPoint = "BitBlt", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool BitBlt(IntPtr hdc, int nXDest, int nYDest, int nWidth, int nHeight,
            IntPtr hdcSrc, int nXSrc, int nYSrc, TernaryRasterOperations dwRop);
        [DllImport("gdi32.dll")]
        public static extern bool PatBlt(IntPtr hdc, int nXLeft, int nYLeft,
            int nWidth, int nHeight, TernaryRasterOperations dwRop);
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
        [DllImport("gdi32.dll", EntryPoint = "CreateSolidBrush")]
        public static extern IntPtr CreateSolidBrush(uint crColor);
        [DllImport("user32.dll", ExactSpelling = true)]
        public static extern IntPtr GetForegroundWindow();
        [DllImport("user32.dll", ExactSpelling = true)]
        public static extern IntPtr GetDesktopWindow();
        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;

            public RECT(int left, int top, int right, int bottom)
            {
                Left = left;
                Top = top;
                Right = right;
                Bottom = bottom;
            }
        }
        [DllImport("gdi32.dll", EntryPoint = "GdiAlphaBlend")]
        public static extern bool AlphaBlend(IntPtr hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest,
            IntPtr hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, BLENDFUNCTION blendFunction);
        [StructLayout(LayoutKind.Sequential)]
        public struct BLENDFUNCTION
        {
            public byte BlendOp;
            public byte BlendFlags;
            public byte SourceConstantAlpha;
            public byte AlphaFormat;

            public BLENDFUNCTION(byte op, byte flags, byte alpha, byte format)
            {
                BlendOp = op;
                BlendFlags = flags;
                SourceConstantAlpha = alpha;
                AlphaFormat = format;
            }
        }
        //
        // currently defined blend operation
        //
        public const int AC_SRC_OVER = 0x00;
        //
        // currently defined alpha format
        //
        public const int AC_SRC_ALPHA = 0x01;
        [DllImport("gdi32.dll", SetLastError = true)]
        public static extern int GetDIBits(IntPtr hdc, IntPtr hbmp, uint uStartScan,
            uint cScanLines, byte[] lpvBits, ref BITMAPINFO lpbi, uint uUsage);
        [DllImport("gdi32.dll", SetLastError = true)]
        public static extern int SetDIBitsToDevice(IntPtr hdc, int XDest, int YDest, uint dwWidth, uint dwHeight, int XSrc,
            int YSrc, uint uStartScan, uint cScanLines, byte[] lpvBits, ref BITMAPINFO lpbmi, uint fuColorUse);
        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct RGBQUAD
        {
            public byte rgbBlue;
            public byte rgbGreen;
            public byte rgbRed;
            public byte rgbReserved;
        }
        [StructLayoutAttribute(LayoutKind.Sequential)]
        public struct BITMAPINFO
        {
            /// <summary>
            /// A BITMAPINFOHEADER structure that contains information about the dimensions of color format.
            /// </summary>
            public BITMAPINFOHEADER bmiHeader;

            /// <summary>
            /// An array of RGBQUAD. The elements of the array that make up the color table.
            /// </summary>
            [MarshalAsAttribute(UnmanagedType.ByValArray, SizeConst = 1, ArraySubType = UnmanagedType.Struct)]
            public RGBQUAD[] bmiColors;
        }
        [StructLayout(LayoutKind.Sequential)]
        public struct BITMAPINFOHEADER
        {
            public uint biSize;
            public int biWidth;
            public int biHeight;
            public ushort biPlanes;
            public ushort biBitCount;
            public uint biSizeImage;
            public int biXPelsPerMeter;
            public int biYPelsPerMeter;
            public uint biClrUsed;
            public uint biClrImportant;
            public uint biCompression;

            public void Init()
            {
                biSize = (uint)Marshal.SizeOf(this);
            }
        }
        [DllImport("user32.dll")]
        public static extern IntPtr LoadCursor(IntPtr hInstance, int lpCursorName);
        [DllImport("user32.dll")]
        public static extern int DrawIcon(IntPtr hDC, int X, int Y, IntPtr hIcon);
        public static IntPtr IDC_ARROW = LoadCursor(IntPtr.Zero, 32512);
        public static IntPtr IDC_IBEAM = LoadCursor(IntPtr.Zero, 32513);
        public static IntPtr IDC_WAIT = LoadCursor(IntPtr.Zero, 32514);
        public static IntPtr IDC_CROSS = LoadCursor(IntPtr.Zero, 32515);
        public static IntPtr IDC_UPARROW = LoadCursor(IntPtr.Zero, 32516);
        public static IntPtr IDC_SIZENWSE = LoadCursor(IntPtr.Zero, 32642);
        public static IntPtr IDC_SIZENESW = LoadCursor(IntPtr.Zero, 32643);
        public static IntPtr IDC_SIZEWE = LoadCursor(IntPtr.Zero, 32644);
        public static IntPtr IDC_SIZENS = LoadCursor(IntPtr.Zero, 32645);
        public static IntPtr IDC_SIZEALL = LoadCursor(IntPtr.Zero, 32646);
        public static IntPtr IDC_NO = LoadCursor(IntPtr.Zero, 32648);
        public static IntPtr IDC_HAND = LoadCursor(IntPtr.Zero, 32649);
        public static IntPtr IDC_APPSTARTING = LoadCursor(IntPtr.Zero, 32650);
        [DllImport("user32.dll")]
        public static extern bool RedrawWindow(IntPtr hWnd, IntPtr lprcUpdate, IntPtr hrgnUpdate, uint flags);
        public static uint RDW_INVALIDATE = 0x0001;
        public static uint RDW_INTERNALPAINT = 0x0002;
        public static uint RDW_ERASE = 0x0004;
        public static uint RDW_VALIDATE = 0x0008;
        public static uint RDW_NOINTERNALPAINT = 0x0010;
        public static uint RDW_NOERASE = 0x0020;
        public static uint RDW_NOCHILDREN = 0x0040;
        public static uint RDW_ALLCHILDREN = 0x0080;
        public static uint RDW_UPDATENOW = 0x0100;
        public static uint RDW_ERASENOW = 0x0200;
        public static uint RDW_FRAME = 0x0400;
        public static uint RDW_NOFRAME = 0x0800;
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);
        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        public static extern bool EnumChildWindows(IntPtr hwndParent, EnumWindowsProc lpEnumFunc, IntPtr lParam);
        public delegate bool EnumWindowsProc(IntPtr hwnd, bool lParam);
    }
}