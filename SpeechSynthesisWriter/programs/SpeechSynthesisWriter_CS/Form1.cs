using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO.Ports;
using System.Management;
using System.Text.RegularExpressions;
using System.Threading;



namespace SpeechSynthesisWriter_CS
{
    public partial class MainForm : Form
    {
        private List<String> portList = new List<string>();
        private List<TextBox> textboxes = new List<TextBox>();
        private static bool _continue = false;
        private static bool _result = false;
        private static List<String> serialRXList = new List<string>();

        public MainForm()
        {
            InitializeComponent();
        }
        private void MainForm_Load(object sender, EventArgs e)
        {
            //ボーレートリストの初期化
            initbordRateList();

            //COMリストの初期化(シリアル端末の検索も行う)
            initSerialPort();

            initTextBoxes();
        }
        private void initbordRateList()
        {
            //ボーレートリストの追加
            boardRateList.Items.AddRange(new String[] {
                "9600"
                //,"115200"
            });
            //デフォルトで9600bpsを選択
            boardRateList.SelectedIndex = 0;
        }

        private void initSerialPort()
        {
            COMList.Items.Clear();
            //接続済みデバイスの取得
            ManagementClass device = new ManagementClass("Win32_PnPentity");
            //COMポートとデバイス名の取得
            if (device == null)
            {
                MessageBox.Show("device is null");
            }
            foreach (ManagementObject port in device.GetInstances())
            {
                string name = (string)port.GetPropertyValue("Name");

                //COMポートを使ったデバイスの抽出(見つからない場合はindexNum=-1となる)
                int indexNum = -1;
                try
                {
                    indexNum = name.IndexOf("COM");
                }
                catch (NullReferenceException)
                {
                    continue;
                }

                //COMポートとデバイス名の取得
                if (indexNum >= 0)
                {
                    COMList.Items.Add(port.GetPropertyValue("Caption"));
                    portList.Add(name.Substring(indexNum).Replace(")", ""));
                }
                else
                {
                    btnConnectSerial.Enabled = false;
                }
            }
            //複数ディバイスが検出されたら一番上を自動選択する
            if (COMList.Items.Count > 0)
            {
                COMList.SelectedIndex = 0;
                btnConnectSerial.Enabled = true;
            }

        }

        private void initTextBoxes()
        {

            this.textboxes.Add(textBox1);
            this.textboxes.Add(textBox2);
            this.textboxes.Add(textBox3);
            this.textboxes.Add(textBox4);
            this.textboxes.Add(textBox5);
            this.textboxes.Add(textBox6);
            this.textboxes.Add(textBox7);
            this.textboxes.Add(textBox8);
            this.textboxes.Add(textBox9);
            this.textboxes.Add(textBox10);
            this.textboxes.Add(textBox11);
            this.textboxes.Add(textBox12);
            this.textboxes.Add(textBox13);
            this.textboxes.Add(textBox14);
            this.textboxes.Add(textBox15);

        }

        private void MainForm_Close(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen == true)
                serialPort1.Close();
            //MessageBox.Show("Bye :-)");
        }

        private void btnReadData_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show("EEPROMデータを読み込みます", "確認", MessageBoxButtons.YesNo);
            if (result != DialogResult.Yes)
                return;

            //以下に読み込み処理を記述
            if (serialPort1.IsOpen == false)
            {
                close_serial();
                return;
            }
            serialPort1.DiscardInBuffer();
            serialPort1.DiscardOutBuffer();
            serialRXList.Clear(); //受信データを格納するバッファのクリア
            btnReadData.Enabled = false;
            btnReadData.Text = "読み込み中";
            Thread serialReadThread = new Thread(serialRead);
            _continue = true;
            _result = false;

            try
            {
                serialPort1.WriteLine("READ_EEPROM");
                serialPort1.ReadLine();
            }
            catch (TimeoutException ex)
            {
                MessageBox.Show(ex.Message);
                _continue = false;
                _result = false;
                serialPort1.ReadTimeout = 1000;
                btnReadData.Enabled = true;
                return;
            }
            //EEPROMの読み出しに20秒程掛かるので一時的にタイムアウトを25秒に設定
            serialPort1.ReadTimeout = 25000;
            serialReadThread.Start();
            serialReadThread.Join();
            if (_result == true)
            {
                for (int i = 0; i < serialRXList.Count; i++)
                {
                    string[] tmp = serialRXList[i].Split('|');
                    if (tmp[0] == "ERROR")
                    {
                        MessageBox.Show(tmp[0] + ":" + tmp[1]);
                        break;
                    }
                    textboxes[Int32.Parse(tmp[0])].Text = tmp[1];
                }
            }
            else
            {
                MessageBox.Show("データの取得に失敗しました。");
            }
            _continue = false;
            _result = false;
            serialPort1.ReadTimeout = 1000;
            btnReadData.Text = "読み込み";
            btnReadData.Enabled = true;
        }

        //シリアル受信(ポーリング)用スレッド
        private void serialRead()
        {
            while (_continue)
            {
                try
                {
                    string rx = serialPort1.ReadLine();
                    Regex re = new Regex(@"[\r\n]");
                    rx = re.Replace(rx, "");
                    //MessageBox.Show(rx);
                    if (rx == "END")
                    {
                        _continue = false;
                        _result = true;
                        continue;
                    }
                    if (rx == "ACK")
                    {
                        continue;
                    }
                    //MessageBox.Show(rx);
                    serialRXList.Add(rx);
                }
                catch (TimeoutException e)
                {
                    MessageBox.Show(e.Message);
                    _result = false;
                    _continue = false;
                }
            }
        }



        private void btnWriteData_Click(object sender, EventArgs e)
        {
            DialogResult result = MessageBox.Show("EEPROMにデータを書き込みます", "確認", MessageBoxButtons.YesNo);
            if (result != DialogResult.Yes)
                return;

            int textLength = 0;
            //テキストボックスに正しい値が入力されたかチェック
            for (int i = 0; i < 15; i++)
            {
                if (textboxes[i].TextLength == 0)
                {
                    MessageBox.Show((i + 1).ToString() + "番目のテキストボックスが空です。");
                    btnWriteData.Enabled = true;
                    return;
                }
                textLength += textboxes[i].TextLength;

            }
            if (textLength > 940 - 15)
            {
                MessageBox.Show("全体で925文字以下にしてください。(現在" + textLength.ToString() + "文字)");
                btnWriteData.Enabled = true;
                return;
            }
            //文字列チェック終了


            //書き込み処理スタート
            if (serialPort1.IsOpen == false)
            {
                close_serial();
                return;
            }
            serialPort1.DiscardInBuffer(); //入出力バッファクリア
            serialPort1.DiscardOutBuffer();
            btnWriteData.Enabled = false;

            serialPort1.WriteLine("WRITE_MEMORY"); //LPC1114のRAM上に書き込み

            try
            {
                for (int i = 0; i < 15; i++)
                {
                    serialPort1.WriteLine(i.ToString() + "|" + textboxes[i].Text);
                    serialPort1.ReadLine();
                }
            }
            catch (TimeoutException ex)
            {
                MessageBox.Show(ex.Message);
                btnWriteData.Enabled = true;
                return;
            }

            serialPort1.WriteLine("END");
            serialPort1.ReadLine();
            //書き込み終了

            serialPort1.DiscardInBuffer(); //入出力バッファクリア
            serialPort1.DiscardOutBuffer();
            try
            {
                //一時的にタイムアウトを25秒に設定
                serialPort1.ReadTimeout = 25000;
                serialPort1.WriteLine("WRITE_EEPROM"); //マイコンのメモリ上のデータを音声合成ICのEEPROMへ書き込み
                string rx = serialPort1.ReadLine();
                rx = serialPort1.ReadLine();
                serialPort1.ReadTimeout = 1000;
                Regex re = new Regex(@"[\r\n]");
                rx = re.Replace(rx, "");
                if (rx != "ACK")
                {
                    MessageBox.Show("EEPROMの書き込みに失敗しました。");
                }
            }
            catch (TimeoutException ex)
            {
                MessageBox.Show(ex.Message);
                btnWriteData.Enabled = true;
            }
            //全書き込み処理終了
            btnWriteData.Enabled = true;

        }

        private void close_serial()
        {
            serialPort1.Close();
            btnConnectSerial.Text = "接続";
            COMList.Enabled = true;
            boardRateList.Enabled = true;
            btnReadData.Enabled = false;
            btnWriteData.Enabled = false;
            btnTest.Enabled = false;
            MessageBox.Show("接続が切れました");
        }

        private void btnConnectSerial_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == true)
            {
                serialPort1.DiscardInBuffer();
                try
                {
                    //切断処理
                    close_serial();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
            else
            {
                try
                {
                    //接続処理
                    serialPort1.PortName = portList[COMList.SelectedIndex];
                    serialPort1.BaudRate = int.Parse((String)boardRateList.SelectedItem);
                    serialPort1.DataBits = 8;
                    serialPort1.Parity = Parity.None;
                    serialPort1.StopBits = StopBits.One;
                    serialPort1.Handshake = Handshake.None;
                    serialPort1.Encoding = Encoding.ASCII;
                    serialPort1.ReadTimeout = 1000;

                    //Connect
                    serialPort1.Open();
                    serialPort1.DiscardInBuffer();
                    btnConnectSerial.Text = "切断";
                    COMList.Enabled = false;
                    boardRateList.Enabled = false;
                    btnReadData.Enabled = true;
                    btnWriteData.Enabled = true;
                    btnTest.Enabled = true;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message);
                }
            }
        }

        private void btnArg_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Regex rx = new Regex(@"[^0-9]");
            string btnName = rx.Replace(((LinkLabel)sender).Name, "");
            //MessageBox.Show(btnName);
            TextBox textBox = textboxes[Int32.Parse(btnName) - 1];
            ArrangeTextForm f = new ArrangeTextForm(textBox.Text);
            f.ShowDialog();
            string rText = f.rString;
            f.Dispose();
            if (rText != null)
                textBox.Text = rText;

        }

        private void btnTest_Click(object sender, EventArgs e)
        {
            int textboxNum = Decimal.ToInt16(testNum.Value) - 1;
            if (textboxes[textboxNum].TextLength == 0)
            {
                MessageBox.Show((textboxNum + 1).ToString() + "番目のテキストボックスが空です。"); return;
            }

            if (serialPort1.IsOpen == false)
            {
                close_serial();
                return;
            }
            serialPort1.DiscardInBuffer(); //入出力バッファクリア
            serialPort1.DiscardOutBuffer();
            btnTest.Enabled = false;

            try
            {
                serialPort1.WriteLine("TALK_TEST");
                serialPort1.ReadLine();
                serialPort1.WriteLine(textboxes[textboxNum].Text);
            }
            catch (TimeoutException ex)
            {
                MessageBox.Show(ex.Message);
                btnTest.Enabled = true;
                return;
            }
            btnTest.Enabled = true;
        }
    }
}
