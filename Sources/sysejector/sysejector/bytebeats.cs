using System;
using System.IO;
using System.Media;

namespace sysejector
{
    internal class bytebeats
    {
        public static void bytebeat1(int hz, int secs)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);
            bw.Write("RIFF".ToCharArray());
            bw.Write((UInt32)0);
            bw.Write("WAVE".ToCharArray());
            bw.Write("fmt ".ToCharArray());
            bw.Write((UInt32)16);
            bw.Write((UInt16)1);

            Int32 channels = 1;
            Int32 sampleRate = hz;
            Int32 bitsPerSample = 8;
            bw.Write((UInt16)channels);
            bw.Write((UInt32)sampleRate);
            bw.Write((UInt32)(sampleRate * channels * bitsPerSample / 8));
            bw.Write((UInt16)(channels * bitsPerSample / 8));
            bw.Write((UInt16)bitsPerSample);
            bw.Write("data".ToCharArray());

            int seconds = secs;
            byte[] data = new byte[sampleRate * seconds];
            for (int t = 0; t < data.Length; t++)
            {
                data[t] = (byte)(Math.Sin(t >> 15) * t * 10);
            }
            bw.Write((UInt32)(data.Length * channels * bitsPerSample / 8));
            foreach (byte elt in data)
            {
                bw.Write(elt);
            }
            bw.Seek(4, SeekOrigin.Begin);
            bw.Write((UInt32)(bw.BaseStream.Length - 8));
            ms.Seek(0, SeekOrigin.Begin);
            new SoundPlayer(ms).PlaySync();
        }

        public static void bytebeat2(int hz, int secs)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);
            bw.Write("RIFF".ToCharArray());
            bw.Write((UInt32)0);
            bw.Write("WAVE".ToCharArray());
            bw.Write("fmt ".ToCharArray());
            bw.Write((UInt32)16);
            bw.Write((UInt16)1);

            Int32 channels = 1;
            Int32 sampleRate = hz;
            Int32 bitsPerSample = 8;
            bw.Write((UInt16)channels);
            bw.Write((UInt32)sampleRate);
            bw.Write((UInt32)(sampleRate * channels * bitsPerSample / 8));
            bw.Write((UInt16)(channels * bitsPerSample / 8));
            bw.Write((UInt16)bitsPerSample);
            bw.Write("data".ToCharArray());

            int seconds = secs;
            byte[] data = new byte[sampleRate * seconds];
            for (int t = 0; t < data.Length; t++)
            {
                data[t] = (byte)(Math.Tan(t >> 15) * (t ^ 10) + (t >> 18));
            }
            bw.Write((UInt32)(data.Length * channels * bitsPerSample / 8));
            foreach (byte elt in data)
            {
                bw.Write(elt);
            }
            bw.Seek(4, SeekOrigin.Begin);
            bw.Write((UInt32)(bw.BaseStream.Length - 8));
            ms.Seek(0, SeekOrigin.Begin);
            new SoundPlayer(ms).PlaySync();
        }

        public static void bytebeat3(int hz, int secs)
        {
            MemoryStream ms = new MemoryStream();
            BinaryWriter bw = new BinaryWriter(ms);
            bw.Write("RIFF".ToCharArray());
            bw.Write((UInt32)0);
            bw.Write("WAVE".ToCharArray());
            bw.Write("fmt ".ToCharArray());
            bw.Write((UInt32)16);
            bw.Write((UInt16)1);

            Int32 channels = 1;
            Int32 sampleRate = hz;
            Int32 bitsPerSample = 8;
            bw.Write((UInt16)channels);
            bw.Write((UInt32)sampleRate);
            bw.Write((UInt32)(sampleRate * channels * bitsPerSample / 8));
            bw.Write((UInt16)(channels * bitsPerSample / 8));
            bw.Write((UInt16)bitsPerSample);
            bw.Write("data".ToCharArray());

            int seconds = secs;
            byte[] data = new byte[sampleRate * seconds];
            for (int t = 0; t < data.Length; t++)
            {
                data[t] = (byte)(Math.Tan(t >> 10) * (t >> 4) + (t >> 1));
            }
            bw.Write((UInt32)(data.Length * channels * bitsPerSample / 8));
            foreach (byte elt in data)
            {
                bw.Write(elt);
            }
            bw.Seek(4, SeekOrigin.Begin);
            bw.Write((UInt32)(bw.BaseStream.Length - 8));
            ms.Seek(0, SeekOrigin.Begin);
            new SoundPlayer(ms).PlaySync();
        }
    }
}