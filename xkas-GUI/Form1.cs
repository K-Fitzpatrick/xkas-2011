using System.IO;
using System.Windows.Forms;
using xkas.Properties;

namespace xkas
{
    public unsafe partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            if (File.Exists(Settings.Default.ASMPath))
                this.tbxASMPath.Text = Settings.Default.ASMPath;
            if (File.Exists(Settings.Default.SrcROMPath))
                this.tbxSrcPath.Text = Settings.Default.SrcROMPath;
            if (File.Exists(Settings.Default.DestROMPath))
                this.tbxDestPath.Text = Settings.Default.DestROMPath;
            this.chkUseSource.Checked = Settings.Default.UseSourceROM;
            this.chkPatchToDest.Checked = Settings.Default.PatchToNewROM;
        }

        private void EnablePatching()
        {
            bool enable = File.Exists(this.tbxASMPath.Text);
            if (this.tbxSrcPath.Enabled)
                enable &= File.Exists(this.tbxSrcPath.Text);
            if (this.tbxDestPath.Enabled)
                enable &= this.tbxDestPath.Text == string.Empty ? false : Directory.Exists(Path.GetDirectoryName(this.tbxDestPath.Text));
            this.btnPatch.Enabled = enable;
        }

        private void btnASMPath_Click(object sender, System.EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "asm";
            dlg.DereferenceLinks = true;
            dlg.Filter = "SNES Assembly Files|*.asm|All Files|*.*";
            if (Directory.Exists(Path.GetDirectoryName(Settings.Default.ASMPath)))
                dlg.InitialDirectory = Path.GetDirectoryName(Settings.Default.ASMPath);
            dlg.Title = "Select Main ASM File";
            if (dlg.ShowDialog() == DialogResult.OK)
                this.tbxASMPath.Text = dlg.FileName;
        }

        private void btnSrcPath_Click(object sender, System.EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = "asm";
            dlg.DereferenceLinks = true;
            dlg.Filter = "Super NES ROMs|*.smc;*.sfc|All Files|*.*";
            if (Directory.Exists(Path.GetDirectoryName(Settings.Default.SrcROMPath)))
                dlg.InitialDirectory = Path.GetDirectoryName(Settings.Default.SrcROMPath);
            dlg.Title = "Select Source ROM File";
            if (dlg.ShowDialog() == DialogResult.OK)
                this.tbxSrcPath.Text = dlg.FileName;
        }

        private void btnDestPath_Click(object sender, System.EventArgs e)
        {
            SaveFileDialog dlg = new SaveFileDialog();
            dlg.DefaultExt = "smc";
            dlg.DereferenceLinks = true;
            dlg.Filter = "Super NES ROMs|*.smc;*.sfc|All Files|*.*";
            if (Directory.Exists(Path.GetDirectoryName(Settings.Default.DestROMPath)))
                dlg.InitialDirectory = Path.GetDirectoryName(Settings.Default.DestROMPath);
            dlg.Title = "Select Destination ROM Path";
            if (dlg.ShowDialog() == DialogResult.OK)
                this.tbxDestPath.Text = dlg.FileName;
        }

        private void chkUseSource_CheckedChanged(object sender, System.EventArgs e)
        {
            this.gbxSrcPath.Enabled = this.chkUseSource.Checked;
            EnablePatching();
        }

        private void chkPatchToDest_CheckedChanged(object sender, System.EventArgs e)
        {
            this.gbxDestPath.Enabled = this.chkPatchToDest.Checked;
            EnablePatching();
        }

        private void tbx_TextChanged(object sender, System.EventArgs e)
        {
            EnablePatching();
        }

        private void btnPatch_Click(object sender, System.EventArgs e)
        {
            if (this.tbxSrcPath.Enabled && this.tbxDestPath.Enabled)
                cskas.Assemble(this.tbxASMPath.Text, this.tbxSrcPath.Text, this.tbxDestPath.Text, false);
            else if (this.tbxSrcPath.Enabled && !this.tbxDestPath.Enabled)
                cskas.Assemble(this.tbxASMPath.Text, this.tbxSrcPath.Text, false);
            else
                cskas.Assemble(this.tbxASMPath.Text, false);

            this.lbxErrors.Items.Clear();
            if (cskas.ErrorCount == 0)
            {
                if (this.tbxDestPath.Enabled)
                    cskas.WriteData(this.tbxDestPath.Text);
                else
                    cskas.WriteData(cskas.DestROMPath);
                MessageBox.Show("File assembled successfully!");
            }
            else
            {
                MessageBox.Show("Patch failed with " + cskas.ErrorCount.ToString() + " errors.");
                this.lbxErrors.Items.AddRange(cskas.GetErrors());
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (File.Exists(this.tbxASMPath.Text))
                Settings.Default.ASMPath = this.tbxASMPath.Text;
            if (File.Exists(this.tbxSrcPath.Text))
                Settings.Default.SrcROMPath = this.tbxSrcPath.Text;
            if (this.tbxDestPath.Text != string.Empty)
                if (Directory.Exists(Path.GetDirectoryName(this.tbxDestPath.Text)))
                    Settings.Default.DestROMPath = this.tbxDestPath.Text;
            Settings.Default.UseSourceROM = this.chkUseSource.Checked;
            Settings.Default.PatchToNewROM = this.chkPatchToDest.Checked;
            Settings.Default.Save();
        }
    }
}