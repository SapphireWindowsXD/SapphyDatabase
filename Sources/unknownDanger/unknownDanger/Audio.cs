using System;
using System.IO;
using System.Media;

namespace unknownDanger
{
	// Token: 0x02000004 RID: 4
	internal class Audio
	{
		// Token: 0x06000003 RID: 3 RVA: 0x00002064 File Offset: 0x00000264
		public static void noise()
		{
			for (;;)
			{
				using (MemoryStream memoryStream = new MemoryStream())
				{
					BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
					binaryWriter.Write("RIFF".ToCharArray());
					binaryWriter.Write(0U);
					binaryWriter.Write("WAVE".ToCharArray());
					binaryWriter.Write("fmt ".ToCharArray());
					binaryWriter.Write(16U);
					binaryWriter.Write(1);
					int num = 1;
					int num2 = 48000;
					int num3 = 8;
					binaryWriter.Write((ushort)num);
					binaryWriter.Write((uint)num2);
					binaryWriter.Write((uint)(num2 * num * num3 / 8));
					binaryWriter.Write((ushort)(num * num3 / 8));
					binaryWriter.Write((ushort)num3);
					binaryWriter.Write("data".ToCharArray());
					byte[] array = new byte[num2 * 4];
					double num4 = (double)(Imports.XorYeet32() % 7000) / 1000.0;
					for (int i = 0; i < array.Length; i++)
					{
						array[i] = (byte)((double)i * num4 * Imports.pow(Imports.pow(2.0, 0.08333333333333333), (double)((int)((double)i * num4 / 4096.0)) * (5.0 - num4) % num4 * 12.0) % 256.0 / 3.0 + (double)i * num4 / 4.0 % 256.0 / 3.0 + (double)i * num4 * Imports.pow(Imports.pow(2.0, 0.08333333333333333), (double)((int)((double)i * num4 / 4096.0)) * (5.0 - num4) % (num4 * 5.0) * 12.0) % 256.0 / 3.0);
					}
					binaryWriter.Write((uint)(array.Length * num * num3 / 8));
					foreach (byte value in array)
					{
						binaryWriter.Write(value);
					}
					binaryWriter.Seek(4, SeekOrigin.Begin);
					binaryWriter.Write((uint)(binaryWriter.BaseStream.Length - 8L));
					memoryStream.Seek(0L, SeekOrigin.Begin);
					new SoundPlayer(memoryStream).PlaySync();
				}
			}
		}
	}
}
