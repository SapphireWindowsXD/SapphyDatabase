using System;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using unknownDanger.Properties;

namespace unknownDanger
{
	// Token: 0x02000006 RID: 6
	public partial class layeredWindow5 : Form
	{
		// Token: 0x17000001 RID: 1
		// (get) Token: 0x06000081 RID: 129 RVA: 0x00003665 File Offset: 0x00001865
		[Browsable(true)]
		protected override bool ShowWithoutActivation
		{
			get
			{
				return true;
			}
		}

		// Token: 0x06000082 RID: 130
		[DllImport("user32.dll")]
		public static extern bool SetForegroundWindow(IntPtr hWnd);

		// Token: 0x06000083 RID: 131
		[DllImport("user32.dll", SetLastError = true)]
		private static extern int GetWindowLong(IntPtr hWnd, int nIndex);

		// Token: 0x06000084 RID: 132
		[DllImport("user32.dll")]
		private static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

		// Token: 0x06000085 RID: 133 RVA: 0x00003668 File Offset: 0x00001868
		public layeredWindow5()
		{
			this.InitializeComponent();
			base.FormBorderStyle = FormBorderStyle.None;
			base.WindowState = FormWindowState.Maximized;
			base.SetStyle(ControlStyles.SupportsTransparentBackColor, true);
			base.TransparencyKey = this.BackColor;
			base.Opacity = 0.5;
			layeredWindow5.SetForegroundWindow(base.Handle);
			base.TopMost = true;
			base.ShowIcon = false;
			base.ShowInTaskbar = false;
		}

		// Token: 0x06000086 RID: 134 RVA: 0x000036EC File Offset: 0x000018EC
		protected override void OnLoad(EventArgs e)
		{
			base.OnLoad(e);
			int windowLong = layeredWindow5.GetWindowLong(base.Handle, -20);
			layeredWindow5.SetWindowLong(base.Handle, -20, windowLong | 524288 | 32);
		}

		// Token: 0x06000087 RID: 135 RVA: 0x00003728 File Offset: 0x00001928
		private void timer1_Tick(object sender, EventArgs e)
		{
			base.Location = new Point(0);
			base.Size = new Size(Screen.PrimaryScreen.Bounds.Width, Screen.PrimaryScreen.Bounds.Height);
			this.pictureBox1.Width = Screen.PrimaryScreen.Bounds.Width;
			this.pictureBox1.Height = Screen.PrimaryScreen.Bounds.Height;
			this.pictureBox1.Location = new Point(0);
		}

		// Token: 0x06000088 RID: 136 RVA: 0x000037C1 File Offset: 0x000019C1
		private void layeredWindow5_Load(object sender, EventArgs e)
		{
			this.timer1.Start();
		}
	}
}
