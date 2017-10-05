namespace xkas
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.tbxASMPath = new System.Windows.Forms.TextBox();
            this.btnASMPath = new System.Windows.Forms.Button();
            this.gbxASMPath = new System.Windows.Forms.GroupBox();
            this.gbxSrcPath = new System.Windows.Forms.GroupBox();
            this.tbxSrcPath = new System.Windows.Forms.TextBox();
            this.btnSrcPath = new System.Windows.Forms.Button();
            this.chkPatchToDest = new System.Windows.Forms.CheckBox();
            this.btnPatch = new System.Windows.Forms.Button();
            this.lbxErrors = new System.Windows.Forms.ListBox();
            this.chkUseSource = new System.Windows.Forms.CheckBox();
            this.gbxDestPath = new System.Windows.Forms.GroupBox();
            this.tbxDestPath = new System.Windows.Forms.TextBox();
            this.btnDestPath = new System.Windows.Forms.Button();
            this.gbxASMPath.SuspendLayout();
            this.gbxSrcPath.SuspendLayout();
            this.gbxDestPath.SuspendLayout();
            this.SuspendLayout();
            // 
            // tbxASMPath
            // 
            this.tbxASMPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbxASMPath.Location = new System.Drawing.Point(6, 19);
            this.tbxASMPath.Name = "tbxASMPath";
            this.tbxASMPath.Size = new System.Drawing.Size(292, 20);
            this.tbxASMPath.TabIndex = 0;
            this.tbxASMPath.TextChanged += new System.EventHandler(this.tbx_TextChanged);
            // 
            // btnASMPath
            // 
            this.btnASMPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnASMPath.Location = new System.Drawing.Point(304, 17);
            this.btnASMPath.Name = "btnASMPath";
            this.btnASMPath.Size = new System.Drawing.Size(26, 23);
            this.btnASMPath.TabIndex = 1;
            this.btnASMPath.Text = "...";
            this.btnASMPath.UseVisualStyleBackColor = true;
            this.btnASMPath.Click += new System.EventHandler(this.btnASMPath_Click);
            // 
            // gbxASMPath
            // 
            this.gbxASMPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gbxASMPath.Controls.Add(this.tbxASMPath);
            this.gbxASMPath.Controls.Add(this.btnASMPath);
            this.gbxASMPath.Location = new System.Drawing.Point(12, 12);
            this.gbxASMPath.Name = "gbxASMPath";
            this.gbxASMPath.Size = new System.Drawing.Size(336, 49);
            this.gbxASMPath.TabIndex = 0;
            this.gbxASMPath.TabStop = false;
            this.gbxASMPath.Text = "ASM Path";
            // 
            // gbxSrcPath
            // 
            this.gbxSrcPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gbxSrcPath.Controls.Add(this.tbxSrcPath);
            this.gbxSrcPath.Controls.Add(this.btnSrcPath);
            this.gbxSrcPath.Location = new System.Drawing.Point(12, 67);
            this.gbxSrcPath.Name = "gbxSrcPath";
            this.gbxSrcPath.Size = new System.Drawing.Size(336, 49);
            this.gbxSrcPath.TabIndex = 1;
            this.gbxSrcPath.TabStop = false;
            this.gbxSrcPath.Text = "Source ROM Path";
            // 
            // tbxSrcPath
            // 
            this.tbxSrcPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbxSrcPath.Location = new System.Drawing.Point(6, 19);
            this.tbxSrcPath.Name = "tbxSrcPath";
            this.tbxSrcPath.Size = new System.Drawing.Size(292, 20);
            this.tbxSrcPath.TabIndex = 0;
            this.tbxSrcPath.TextChanged += new System.EventHandler(this.tbx_TextChanged);
            // 
            // btnSrcPath
            // 
            this.btnSrcPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnSrcPath.Location = new System.Drawing.Point(304, 17);
            this.btnSrcPath.Name = "btnSrcPath";
            this.btnSrcPath.Size = new System.Drawing.Size(26, 23);
            this.btnSrcPath.TabIndex = 1;
            this.btnSrcPath.Text = "...";
            this.btnSrcPath.UseVisualStyleBackColor = true;
            this.btnSrcPath.Click += new System.EventHandler(this.btnSrcPath_Click);
            // 
            // chkPatchToDest
            // 
            this.chkPatchToDest.AutoSize = true;
            this.chkPatchToDest.Checked = true;
            this.chkPatchToDest.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkPatchToDest.Location = new System.Drawing.Point(209, 181);
            this.chkPatchToDest.Name = "chkPatchToDest";
            this.chkPatchToDest.Size = new System.Drawing.Size(139, 17);
            this.chkPatchToDest.TabIndex = 5;
            this.chkPatchToDest.Text = "Output patch to new file";
            this.chkPatchToDest.UseVisualStyleBackColor = true;
            this.chkPatchToDest.CheckedChanged += new System.EventHandler(this.chkPatchToDest_CheckedChanged);
            // 
            // btnPatch
            // 
            this.btnPatch.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.btnPatch.Enabled = false;
            this.btnPatch.Location = new System.Drawing.Point(12, 177);
            this.btnPatch.Name = "btnPatch";
            this.btnPatch.Size = new System.Drawing.Size(75, 23);
            this.btnPatch.TabIndex = 3;
            this.btnPatch.Text = "Patch";
            this.btnPatch.UseVisualStyleBackColor = true;
            this.btnPatch.Click += new System.EventHandler(this.btnPatch_Click);
            // 
            // lbxErrors
            // 
            this.lbxErrors.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.lbxErrors.FormattingEnabled = true;
            this.lbxErrors.HorizontalScrollbar = true;
            this.lbxErrors.Location = new System.Drawing.Point(0, 210);
            this.lbxErrors.Name = "lbxErrors";
            this.lbxErrors.Size = new System.Drawing.Size(360, 121);
            this.lbxErrors.TabIndex = 6;
            // 
            // chkUseSource
            // 
            this.chkUseSource.AutoSize = true;
            this.chkUseSource.Checked = true;
            this.chkUseSource.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkUseSource.Location = new System.Drawing.Point(93, 181);
            this.chkUseSource.Name = "chkUseSource";
            this.chkUseSource.Size = new System.Drawing.Size(110, 17);
            this.chkUseSource.TabIndex = 4;
            this.chkUseSource.Text = "Use Source ROM";
            this.chkUseSource.UseVisualStyleBackColor = true;
            this.chkUseSource.CheckedChanged += new System.EventHandler(this.chkUseSource_CheckedChanged);
            // 
            // gbxDestPath
            // 
            this.gbxDestPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.gbxDestPath.Controls.Add(this.tbxDestPath);
            this.gbxDestPath.Controls.Add(this.btnDestPath);
            this.gbxDestPath.Location = new System.Drawing.Point(12, 122);
            this.gbxDestPath.Name = "gbxDestPath";
            this.gbxDestPath.Size = new System.Drawing.Size(336, 49);
            this.gbxDestPath.TabIndex = 2;
            this.gbxDestPath.TabStop = false;
            this.gbxDestPath.Text = "Destination ROM Path";
            // 
            // tbxDestPath
            // 
            this.tbxDestPath.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.tbxDestPath.Location = new System.Drawing.Point(6, 19);
            this.tbxDestPath.Name = "tbxDestPath";
            this.tbxDestPath.Size = new System.Drawing.Size(292, 20);
            this.tbxDestPath.TabIndex = 0;
            this.tbxDestPath.TextChanged += new System.EventHandler(this.tbx_TextChanged);
            // 
            // btnDestPath
            // 
            this.btnDestPath.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnDestPath.Location = new System.Drawing.Point(304, 17);
            this.btnDestPath.Name = "btnDestPath";
            this.btnDestPath.Size = new System.Drawing.Size(26, 23);
            this.btnDestPath.TabIndex = 1;
            this.btnDestPath.Text = "...";
            this.btnDestPath.UseVisualStyleBackColor = true;
            this.btnDestPath.Click += new System.EventHandler(this.btnDestPath_Click);
            // 
            // Form1
            // 
            this.AcceptButton = this.btnPatch;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(360, 333);
            this.Controls.Add(this.gbxDestPath);
            this.Controls.Add(this.chkUseSource);
            this.Controls.Add(this.chkPatchToDest);
            this.Controls.Add(this.lbxErrors);
            this.Controls.Add(this.btnPatch);
            this.Controls.Add(this.gbxSrcPath);
            this.Controls.Add(this.gbxASMPath);
            this.Name = "Form1";
            this.Text = "xkas-GUI";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.gbxASMPath.ResumeLayout(false);
            this.gbxASMPath.PerformLayout();
            this.gbxSrcPath.ResumeLayout(false);
            this.gbxSrcPath.PerformLayout();
            this.gbxDestPath.ResumeLayout(false);
            this.gbxDestPath.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox tbxASMPath;
        private System.Windows.Forms.Button btnASMPath;
        private System.Windows.Forms.GroupBox gbxASMPath;
        private System.Windows.Forms.GroupBox gbxSrcPath;
        private System.Windows.Forms.TextBox tbxSrcPath;
        private System.Windows.Forms.Button btnSrcPath;
        private System.Windows.Forms.CheckBox chkPatchToDest;
        private System.Windows.Forms.Button btnPatch;
        private System.Windows.Forms.ListBox lbxErrors;
        private System.Windows.Forms.CheckBox chkUseSource;
        private System.Windows.Forms.GroupBox gbxDestPath;
        private System.Windows.Forms.TextBox tbxDestPath;
        private System.Windows.Forms.Button btnDestPath;
    }
}

