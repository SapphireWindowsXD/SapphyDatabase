using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace sysejector
{
    internal class functions
    {
        public static readonly Random r = new Random();
        public static int w = Screen.PrimaryScreen.Bounds.Width;
        public static int h = Screen.PrimaryScreen.Bounds.Height;

        public static string generateUnicode(int length)
        {
            StringBuilder sb = new StringBuilder(length);
            for (int i = 0; i < length; i++)
            {
                sb.Append(char.ConvertFromUtf32(r.Next(0x20, 0xFF)));
            }
            return sb.ToString();
        }

        public static string generateLetters(int length)
        {
            StringBuilder sb = new StringBuilder();
            string letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            for (int i = 0; i < length; i++)
            {
                sb.Append(letters[r.Next(letters.Length)]);
            }
            return sb.ToString();
        }
    }
}