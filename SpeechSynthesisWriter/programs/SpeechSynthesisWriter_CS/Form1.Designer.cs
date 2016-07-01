namespace SpeechSynthesisWriter_CS
{
    partial class MainForm
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.COMList = new System.Windows.Forms.ComboBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnConnectSerial = new System.Windows.Forms.Button();
            this.boardRateList = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.testNum = new System.Windows.Forms.NumericUpDown();
            this.btnReadData = new System.Windows.Forms.Button();
            this.btnWriteData = new System.Windows.Forms.Button();
            this.btnArg1 = new System.Windows.Forms.LinkLabel();
            this.btnArg2 = new System.Windows.Forms.LinkLabel();
            this.btnArg3 = new System.Windows.Forms.LinkLabel();
            this.btnArg4 = new System.Windows.Forms.LinkLabel();
            this.btnArg5 = new System.Windows.Forms.LinkLabel();
            this.btnArg6 = new System.Windows.Forms.LinkLabel();
            this.btnArg7 = new System.Windows.Forms.LinkLabel();
            this.btnArg8 = new System.Windows.Forms.LinkLabel();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.btnArg9 = new System.Windows.Forms.LinkLabel();
            this.label12 = new System.Windows.Forms.Label();
            this.textBox10 = new System.Windows.Forms.TextBox();
            this.btnArg10 = new System.Windows.Forms.LinkLabel();
            this.label13 = new System.Windows.Forms.Label();
            this.textBox11 = new System.Windows.Forms.TextBox();
            this.btnArg11 = new System.Windows.Forms.LinkLabel();
            this.label14 = new System.Windows.Forms.Label();
            this.textBox12 = new System.Windows.Forms.TextBox();
            this.btnArg12 = new System.Windows.Forms.LinkLabel();
            this.label15 = new System.Windows.Forms.Label();
            this.textBox13 = new System.Windows.Forms.TextBox();
            this.btnArg13 = new System.Windows.Forms.LinkLabel();
            this.label16 = new System.Windows.Forms.Label();
            this.textBox14 = new System.Windows.Forms.TextBox();
            this.btnArg14 = new System.Windows.Forms.LinkLabel();
            this.label17 = new System.Windows.Forms.Label();
            this.textBox15 = new System.Windows.Forms.TextBox();
            this.btnArg15 = new System.Windows.Forms.LinkLabel();
            this.label18 = new System.Windows.Forms.Label();
            this.btnTest = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.testNum)).BeginInit();
            this.SuspendLayout();
            // 
            // COMList
            // 
            this.COMList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.COMList.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.COMList.FormattingEnabled = true;
            this.COMList.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.COMList.Location = new System.Drawing.Point(53, 26);
            this.COMList.Name = "COMList";
            this.COMList.Size = new System.Drawing.Size(121, 23);
            this.COMList.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnConnectSerial);
            this.groupBox1.Controls.Add(this.boardRateList);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.COMList);
            this.groupBox1.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(441, 62);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "接続設定";
            // 
            // btnConnectSerial
            // 
            this.btnConnectSerial.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnConnectSerial.Location = new System.Drawing.Point(377, 26);
            this.btnConnectSerial.Name = "btnConnectSerial";
            this.btnConnectSerial.Size = new System.Drawing.Size(58, 23);
            this.btnConnectSerial.TabIndex = 3;
            this.btnConnectSerial.Text = "接続";
            this.btnConnectSerial.UseVisualStyleBackColor = true;
            this.btnConnectSerial.Click += new System.EventHandler(this.btnConnectSerial_Click);
            // 
            // boardRateList
            // 
            this.boardRateList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.boardRateList.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.boardRateList.FormattingEnabled = true;
            this.boardRateList.Location = new System.Drawing.Point(256, 26);
            this.boardRateList.Name = "boardRateList";
            this.boardRateList.Size = new System.Drawing.Size(112, 23);
            this.boardRateList.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label2.Location = new System.Drawing.Point(185, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "ボーレート";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label1.Location = new System.Drawing.Point(10, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 15);
            this.label1.TabIndex = 1;
            this.label1.Text = "端末";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label3.ImageAlign = System.Drawing.ContentAlignment.MiddleRight;
            this.label3.Location = new System.Drawing.Point(22, 83);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(18, 15);
            this.label3.TabIndex = 4;
            this.label3.Text = "1.";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label4.Location = new System.Drawing.Point(22, 111);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(18, 15);
            this.label4.TabIndex = 11;
            this.label4.Text = "2.";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label5.Location = new System.Drawing.Point(22, 139);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(18, 15);
            this.label5.TabIndex = 12;
            this.label5.Text = "3.";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label6.Location = new System.Drawing.Point(22, 167);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(18, 15);
            this.label6.TabIndex = 13;
            this.label6.Text = "4.";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label7.Location = new System.Drawing.Point(22, 195);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(18, 15);
            this.label7.TabIndex = 14;
            this.label7.Text = "5.";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label8.Location = new System.Drawing.Point(22, 223);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(18, 15);
            this.label8.TabIndex = 15;
            this.label8.Text = "6.";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label9.Location = new System.Drawing.Point(22, 251);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(18, 15);
            this.label9.TabIndex = 16;
            this.label9.Text = "7.";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label10.Location = new System.Drawing.Point(22, 279);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(18, 15);
            this.label10.TabIndex = 17;
            this.label10.Text = "8.";
            // 
            // testNum
            // 
            this.testNum.BackColor = System.Drawing.SystemColors.Window;
            this.testNum.Cursor = System.Windows.Forms.Cursors.Default;
            this.testNum.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.testNum.ImeMode = System.Windows.Forms.ImeMode.Close;
            this.testNum.Location = new System.Drawing.Point(18, 510);
            this.testNum.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.testNum.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.testNum.Name = "testNum";
            this.testNum.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.testNum.Size = new System.Drawing.Size(41, 22);
            this.testNum.TabIndex = 12;
            this.testNum.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.testNum.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // btnReadData
            // 
            this.btnReadData.Enabled = false;
            this.btnReadData.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnReadData.Location = new System.Drawing.Point(205, 506);
            this.btnReadData.Name = "btnReadData";
            this.btnReadData.Size = new System.Drawing.Size(102, 27);
            this.btnReadData.TabIndex = 13;
            this.btnReadData.Text = "読み込み";
            this.btnReadData.UseVisualStyleBackColor = true;
            this.btnReadData.Click += new System.EventHandler(this.btnReadData_Click);
            // 
            // btnWriteData
            // 
            this.btnWriteData.Enabled = false;
            this.btnWriteData.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnWriteData.Location = new System.Drawing.Point(313, 506);
            this.btnWriteData.Name = "btnWriteData";
            this.btnWriteData.Size = new System.Drawing.Size(102, 27);
            this.btnWriteData.TabIndex = 14;
            this.btnWriteData.Text = "書き込み";
            this.btnWriteData.UseVisualStyleBackColor = true;
            this.btnWriteData.Click += new System.EventHandler(this.btnWriteData_Click);
            // 
            // btnArg1
            // 
            this.btnArg1.AutoSize = true;
            this.btnArg1.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg1.Location = new System.Drawing.Point(416, 83);
            this.btnArg1.Name = "btnArg1";
            this.btnArg1.Size = new System.Drawing.Size(36, 20);
            this.btnArg1.TabIndex = 4;
            this.btnArg1.TabStop = true;
            this.btnArg1.Text = "編集";
            this.btnArg1.UseCompatibleTextRendering = true;
            this.btnArg1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg2
            // 
            this.btnArg2.AutoSize = true;
            this.btnArg2.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg2.Location = new System.Drawing.Point(416, 111);
            this.btnArg2.Name = "btnArg2";
            this.btnArg2.Size = new System.Drawing.Size(37, 15);
            this.btnArg2.TabIndex = 5;
            this.btnArg2.TabStop = true;
            this.btnArg2.Text = "編集";
            this.btnArg2.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg3
            // 
            this.btnArg3.AutoSize = true;
            this.btnArg3.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg3.Location = new System.Drawing.Point(416, 139);
            this.btnArg3.Name = "btnArg3";
            this.btnArg3.Size = new System.Drawing.Size(37, 15);
            this.btnArg3.TabIndex = 6;
            this.btnArg3.TabStop = true;
            this.btnArg3.Text = "編集";
            this.btnArg3.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg4
            // 
            this.btnArg4.AutoSize = true;
            this.btnArg4.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg4.Location = new System.Drawing.Point(416, 167);
            this.btnArg4.Name = "btnArg4";
            this.btnArg4.Size = new System.Drawing.Size(37, 15);
            this.btnArg4.TabIndex = 7;
            this.btnArg4.TabStop = true;
            this.btnArg4.Text = "編集";
            this.btnArg4.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg5
            // 
            this.btnArg5.AutoSize = true;
            this.btnArg5.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg5.Location = new System.Drawing.Point(416, 195);
            this.btnArg5.Name = "btnArg5";
            this.btnArg5.Size = new System.Drawing.Size(37, 15);
            this.btnArg5.TabIndex = 8;
            this.btnArg5.TabStop = true;
            this.btnArg5.Text = "編集";
            this.btnArg5.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg6
            // 
            this.btnArg6.AutoSize = true;
            this.btnArg6.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg6.Location = new System.Drawing.Point(416, 223);
            this.btnArg6.Name = "btnArg6";
            this.btnArg6.Size = new System.Drawing.Size(37, 15);
            this.btnArg6.TabIndex = 9;
            this.btnArg6.TabStop = true;
            this.btnArg6.Text = "編集";
            this.btnArg6.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg7
            // 
            this.btnArg7.AutoSize = true;
            this.btnArg7.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg7.Location = new System.Drawing.Point(416, 251);
            this.btnArg7.Name = "btnArg7";
            this.btnArg7.Size = new System.Drawing.Size(37, 15);
            this.btnArg7.TabIndex = 10;
            this.btnArg7.TabStop = true;
            this.btnArg7.Text = "編集";
            this.btnArg7.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // btnArg8
            // 
            this.btnArg8.AutoSize = true;
            this.btnArg8.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg8.Location = new System.Drawing.Point(416, 279);
            this.btnArg8.Name = "btnArg8";
            this.btnArg8.Size = new System.Drawing.Size(37, 15);
            this.btnArg8.TabIndex = 11;
            this.btnArg8.TabStop = true;
            this.btnArg8.Text = "編集";
            this.btnArg8.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox1.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox1.Location = new System.Drawing.Point(46, 80);
            this.textBox1.MaxLength = 127;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(364, 22);
            this.textBox1.TabIndex = 29;
            this.textBox1.TabStop = false;
            // 
            // textBox2
            // 
            this.textBox2.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox2.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox2.Location = new System.Drawing.Point(46, 108);
            this.textBox2.MaxLength = 127;
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(364, 22);
            this.textBox2.TabIndex = 30;
            this.textBox2.TabStop = false;
            // 
            // textBox3
            // 
            this.textBox3.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox3.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox3.Location = new System.Drawing.Point(46, 136);
            this.textBox3.MaxLength = 127;
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(364, 22);
            this.textBox3.TabIndex = 31;
            this.textBox3.TabStop = false;
            // 
            // textBox4
            // 
            this.textBox4.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox4.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox4.Location = new System.Drawing.Point(46, 164);
            this.textBox4.MaxLength = 127;
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(364, 22);
            this.textBox4.TabIndex = 32;
            this.textBox4.TabStop = false;
            // 
            // textBox5
            // 
            this.textBox5.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox5.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox5.Location = new System.Drawing.Point(46, 192);
            this.textBox5.MaxLength = 127;
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(364, 22);
            this.textBox5.TabIndex = 33;
            this.textBox5.TabStop = false;
            // 
            // textBox6
            // 
            this.textBox6.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox6.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox6.Location = new System.Drawing.Point(46, 220);
            this.textBox6.MaxLength = 127;
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(364, 22);
            this.textBox6.TabIndex = 34;
            this.textBox6.TabStop = false;
            // 
            // textBox7
            // 
            this.textBox7.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox7.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox7.Location = new System.Drawing.Point(46, 248);
            this.textBox7.MaxLength = 127;
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(364, 22);
            this.textBox7.TabIndex = 35;
            this.textBox7.TabStop = false;
            // 
            // textBox8
            // 
            this.textBox8.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox8.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox8.Location = new System.Drawing.Point(46, 276);
            this.textBox8.MaxLength = 127;
            this.textBox8.Name = "textBox8";
            this.textBox8.Size = new System.Drawing.Size(364, 22);
            this.textBox8.TabIndex = 36;
            this.textBox8.TabStop = false;
            // 
            // textBox9
            // 
            this.textBox9.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox9.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox9.Location = new System.Drawing.Point(46, 304);
            this.textBox9.MaxLength = 127;
            this.textBox9.Name = "textBox9";
            this.textBox9.Size = new System.Drawing.Size(364, 22);
            this.textBox9.TabIndex = 39;
            this.textBox9.TabStop = false;
            // 
            // btnArg9
            // 
            this.btnArg9.AutoSize = true;
            this.btnArg9.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg9.Location = new System.Drawing.Point(416, 307);
            this.btnArg9.Name = "btnArg9";
            this.btnArg9.Size = new System.Drawing.Size(37, 15);
            this.btnArg9.TabIndex = 37;
            this.btnArg9.TabStop = true;
            this.btnArg9.Text = "編集";
            this.btnArg9.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label12.Location = new System.Drawing.Point(22, 307);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(18, 15);
            this.label12.TabIndex = 38;
            this.label12.Text = "9.";
            // 
            // textBox10
            // 
            this.textBox10.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox10.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox10.Location = new System.Drawing.Point(45, 331);
            this.textBox10.MaxLength = 127;
            this.textBox10.Name = "textBox10";
            this.textBox10.Size = new System.Drawing.Size(364, 22);
            this.textBox10.TabIndex = 42;
            this.textBox10.TabStop = false;
            // 
            // btnArg10
            // 
            this.btnArg10.AutoSize = true;
            this.btnArg10.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg10.Location = new System.Drawing.Point(415, 334);
            this.btnArg10.Name = "btnArg10";
            this.btnArg10.Size = new System.Drawing.Size(37, 15);
            this.btnArg10.TabIndex = 40;
            this.btnArg10.TabStop = true;
            this.btnArg10.Text = "編集";
            this.btnArg10.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label13.Location = new System.Drawing.Point(14, 334);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(26, 15);
            this.label13.TabIndex = 41;
            this.label13.Text = "10.";
            // 
            // textBox11
            // 
            this.textBox11.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox11.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox11.Location = new System.Drawing.Point(45, 359);
            this.textBox11.MaxLength = 127;
            this.textBox11.Name = "textBox11";
            this.textBox11.Size = new System.Drawing.Size(364, 22);
            this.textBox11.TabIndex = 45;
            this.textBox11.TabStop = false;
            // 
            // btnArg11
            // 
            this.btnArg11.AutoSize = true;
            this.btnArg11.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg11.Location = new System.Drawing.Point(415, 362);
            this.btnArg11.Name = "btnArg11";
            this.btnArg11.Size = new System.Drawing.Size(37, 15);
            this.btnArg11.TabIndex = 43;
            this.btnArg11.TabStop = true;
            this.btnArg11.Text = "編集";
            this.btnArg11.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label14.Location = new System.Drawing.Point(14, 362);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(26, 15);
            this.label14.TabIndex = 44;
            this.label14.Text = "11.";
            // 
            // textBox12
            // 
            this.textBox12.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox12.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox12.Location = new System.Drawing.Point(46, 387);
            this.textBox12.MaxLength = 127;
            this.textBox12.Name = "textBox12";
            this.textBox12.Size = new System.Drawing.Size(364, 22);
            this.textBox12.TabIndex = 48;
            this.textBox12.TabStop = false;
            // 
            // btnArg12
            // 
            this.btnArg12.AutoSize = true;
            this.btnArg12.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg12.Location = new System.Drawing.Point(416, 390);
            this.btnArg12.Name = "btnArg12";
            this.btnArg12.Size = new System.Drawing.Size(37, 15);
            this.btnArg12.TabIndex = 46;
            this.btnArg12.TabStop = true;
            this.btnArg12.Text = "編集";
            this.btnArg12.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label15.Location = new System.Drawing.Point(15, 390);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(26, 15);
            this.label15.TabIndex = 47;
            this.label15.Text = "12.";
            // 
            // textBox13
            // 
            this.textBox13.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox13.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox13.Location = new System.Drawing.Point(45, 415);
            this.textBox13.MaxLength = 127;
            this.textBox13.Name = "textBox13";
            this.textBox13.Size = new System.Drawing.Size(364, 22);
            this.textBox13.TabIndex = 51;
            this.textBox13.TabStop = false;
            // 
            // btnArg13
            // 
            this.btnArg13.AutoSize = true;
            this.btnArg13.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg13.Location = new System.Drawing.Point(415, 418);
            this.btnArg13.Name = "btnArg13";
            this.btnArg13.Size = new System.Drawing.Size(37, 15);
            this.btnArg13.TabIndex = 49;
            this.btnArg13.TabStop = true;
            this.btnArg13.Text = "編集";
            this.btnArg13.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label16.Location = new System.Drawing.Point(14, 418);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(26, 15);
            this.label16.TabIndex = 50;
            this.label16.Text = "13.";
            // 
            // textBox14
            // 
            this.textBox14.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox14.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox14.Location = new System.Drawing.Point(45, 443);
            this.textBox14.MaxLength = 127;
            this.textBox14.Name = "textBox14";
            this.textBox14.Size = new System.Drawing.Size(364, 22);
            this.textBox14.TabIndex = 54;
            this.textBox14.TabStop = false;
            // 
            // btnArg14
            // 
            this.btnArg14.AutoSize = true;
            this.btnArg14.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg14.Location = new System.Drawing.Point(415, 446);
            this.btnArg14.Name = "btnArg14";
            this.btnArg14.Size = new System.Drawing.Size(37, 15);
            this.btnArg14.TabIndex = 52;
            this.btnArg14.TabStop = true;
            this.btnArg14.Text = "編集";
            this.btnArg14.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label17.Location = new System.Drawing.Point(14, 446);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(26, 15);
            this.label17.TabIndex = 53;
            this.label17.Text = "14.";
            // 
            // textBox15
            // 
            this.textBox15.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.textBox15.ImeMode = System.Windows.Forms.ImeMode.Disable;
            this.textBox15.Location = new System.Drawing.Point(45, 471);
            this.textBox15.MaxLength = 127;
            this.textBox15.Name = "textBox15";
            this.textBox15.Size = new System.Drawing.Size(364, 22);
            this.textBox15.TabIndex = 57;
            this.textBox15.TabStop = false;
            // 
            // btnArg15
            // 
            this.btnArg15.AutoSize = true;
            this.btnArg15.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnArg15.Location = new System.Drawing.Point(415, 474);
            this.btnArg15.Name = "btnArg15";
            this.btnArg15.Size = new System.Drawing.Size(37, 15);
            this.btnArg15.TabIndex = 55;
            this.btnArg15.TabStop = true;
            this.btnArg15.Text = "編集";
            this.btnArg15.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.btnArg_LinkClicked);
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.label18.Location = new System.Drawing.Point(14, 474);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(26, 15);
            this.label18.TabIndex = 56;
            this.label18.Text = "15.";
            // 
            // btnTest
            // 
            this.btnTest.Enabled = false;
            this.btnTest.Font = new System.Drawing.Font("MS UI Gothic", 11F);
            this.btnTest.Location = new System.Drawing.Point(65, 506);
            this.btnTest.Name = "btnTest";
            this.btnTest.Size = new System.Drawing.Size(65, 27);
            this.btnTest.TabIndex = 58;
            this.btnTest.Text = "テスト";
            this.btnTest.UseVisualStyleBackColor = true;
            this.btnTest.Click += new System.EventHandler(this.btnTest_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(484, 549);
            this.Controls.Add(this.btnTest);
            this.Controls.Add(this.textBox15);
            this.Controls.Add(this.btnArg15);
            this.Controls.Add(this.label18);
            this.Controls.Add(this.textBox14);
            this.Controls.Add(this.btnArg14);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.textBox13);
            this.Controls.Add(this.btnArg13);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.textBox12);
            this.Controls.Add(this.btnArg12);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.textBox11);
            this.Controls.Add(this.btnArg11);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.textBox10);
            this.Controls.Add(this.btnArg10);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.textBox9);
            this.Controls.Add(this.btnArg9);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.textBox8);
            this.Controls.Add(this.textBox7);
            this.Controls.Add(this.textBox6);
            this.Controls.Add(this.textBox5);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.textBox2);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.btnArg8);
            this.Controls.Add(this.btnArg7);
            this.Controls.Add(this.btnArg6);
            this.Controls.Add(this.btnArg5);
            this.Controls.Add(this.btnArg4);
            this.Controls.Add(this.btnArg3);
            this.Controls.Add(this.btnArg2);
            this.Controls.Add(this.btnArg1);
            this.Controls.Add(this.btnWriteData);
            this.Controls.Add(this.btnReadData);
            this.Controls.Add(this.testNum);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.groupBox1);
            this.MaximumSize = new System.Drawing.Size(500, 588);
            this.Name = "MainForm";
            this.Text = "音声合成書き込みツール";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_Close);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.testNum)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.ComboBox COMList;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox boardRateList;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.NumericUpDown testNum;
        private System.Windows.Forms.Button btnReadData;
        private System.Windows.Forms.Button btnWriteData;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Button btnConnectSerial;
        private System.Windows.Forms.LinkLabel btnArg2;
        private System.Windows.Forms.LinkLabel btnArg3;
        private System.Windows.Forms.LinkLabel btnArg4;
        private System.Windows.Forms.LinkLabel btnArg5;
        private System.Windows.Forms.LinkLabel btnArg6;
        private System.Windows.Forms.LinkLabel btnArg7;
        private System.Windows.Forms.LinkLabel btnArg8;
        public System.Windows.Forms.LinkLabel btnArg1;
        private System.Windows.Forms.TextBox textBox9;
        private System.Windows.Forms.LinkLabel btnArg9;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBox14;
        private System.Windows.Forms.LinkLabel btnArg14;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.TextBox textBox15;
        private System.Windows.Forms.LinkLabel btnArg15;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.LinkLabel btnArg13;
        private System.Windows.Forms.TextBox textBox13;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.LinkLabel btnArg12;
        private System.Windows.Forms.TextBox textBox12;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.LinkLabel btnArg11;
        private System.Windows.Forms.TextBox textBox11;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.LinkLabel btnArg10;
        private System.Windows.Forms.TextBox textBox10;
        private System.Windows.Forms.Button btnTest;
    }
}

