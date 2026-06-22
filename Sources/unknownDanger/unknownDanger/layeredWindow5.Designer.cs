namespace unknownDanger
{
	// Token: 0x02000006 RID: 6
	public partial class layeredWindow5 : global::System.Windows.Forms.Form
	{
		// Token: 0x06000089 RID: 137 RVA: 0x000037D0 File Offset: 0x000019D0
		protected override void Dispose(bool disposing)
		{
			bool flag = disposing && this.components != null;
			if (flag)
			{
				this.components.Dispose();
			}
			base.Dispose(disposing);
		}

		// Token: 0x0600008A RID: 138 RVA: 0x00003808 File Offset: 0x00001A08
		private void InitializeComponent()
		{
			this.components = new global::System.ComponentModel.Container();
			this.timer1 = new global::System.Windows.Forms.Timer(this.components);
			this.pictureBox1 = new global::System.Windows.Forms.PictureBox();
			((global::System.ComponentModel.ISupportInitialize)this.pictureBox1).BeginInit();
			base.SuspendLayout();
			this.timer1.Tick += new global::System.EventHandler(this.timer1_Tick);
			this.pictureBox1.Image = global::unknownDanger.Properties.Resources._3dgifmaker28930;
			this.pictureBox1.Location = new global::System.Drawing.Point(0, 0);
			this.pictureBox1.Name = "pictureBox1";
			this.pictureBox1.Size = new global::System.Drawing.Size(100, 50);
			this.pictureBox1.SizeMode = global::System.Windows.Forms.PictureBoxSizeMode.StretchImage;
			this.pictureBox1.TabIndex = 0;
			this.pictureBox1.TabStop = false;
			base.AutoScaleDimensions = new global::System.Drawing.SizeF(6f, 13f);
			base.AutoScaleMode = global::System.Windows.Forms.AutoScaleMode.Font;
			base.ClientSize = new global::System.Drawing.Size(800, 450);
			base.Controls.Add(this.pictureBox1);
			base.Name = "layeredWindow5";
			this.Text = "layeredWindow5";
			base.Load += new global::System.EventHandler(this.layeredWindow5_Load);
			((global::System.ComponentModel.ISupportInitialize)this.pictureBox1).EndInit();
			base.ResumeLayout(false);
		}

		// Token: 0x04000031 RID: 49
		private global::System.ComponentModel.IContainer components = null;

		// Token: 0x04000032 RID: 50
		private global::System.Windows.Forms.Timer timer1;

		// Token: 0x04000033 RID: 51
		private global::System.Windows.Forms.PictureBox pictureBox1;
	}
}
