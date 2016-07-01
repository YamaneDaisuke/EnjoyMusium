using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SpeechSynthesisWriter_CS
{
    public partial class ArrangeTextForm : Form
    {
        private string[] args;
        public string rString;

        public ArrangeTextForm(params string[] args)
        {
            //MainFormから値を取得
            this.args = args;
            InitializeComponent();
        }

        private void ArrangeTextForm_Load(object sender, EventArgs e)
        {
            this.argTextBox.Text = args[0];
        }

        private void btnOK_Click(object sender, EventArgs e)
        {
            this.rString = argTextBox.Text.Replace(Environment.NewLine, "");
            if (this.rString == "")
            {
                this.rString = null;
            }
            this.Close();
        }

        private void ArrangeTextForm_Close(object sender, EventArgs e)
        {
            if (rString == null)
                this.rString = null;
        }

        //デバック用
        static public string showMiniFrom(string s)
        {
            ArrangeTextForm f = new ArrangeTextForm(s);
            f.ShowDialog();
            string reternString = f.rString;
            f.Dispose();
            return reternString;
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
