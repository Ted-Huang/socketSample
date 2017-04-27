using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                //Listen();
                new Thread(new ThreadStart(Listen)).Start();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.ToString());
            }
        }
        ////Client連線
        private TcpListener myTcpListener;
        private void Listen()
        {
            // 設定聽取的 Port
            myTcpListener = new TcpListener(IPAddress.Parse("192.168.1.103"), Int32.Parse("9999"));
            String strGUID = "";
            Boolean isGUID = false;
            //BKWClientListen.ReportProgress(0);
            while (true)
            {
                try
                {
                    // 等待接收
                    myTcpListener.Start();
                    Socket mySocket = myTcpListener.AcceptSocket();
                    myTcpListener.Stop();
                    // 產生 GUID 
                    isGUID = false;
                    //while (isGUID.Equals(false))
                    //{
                    //    strGUID = System.Guid.NewGuid().ToString().ToUpper();
                    //    if (myHashTable_GUID.ContainsKey(strGUID).Equals(false))
                    //    {
                    //        myHashTable_GUID.Add(strGUID, strGUID);
                    //        isGUID = true;
                    //    }
                    //}
                    // 取得連線用戶端相關的網路連線資訊
                    IPEndPoint ClientInfo = (IPEndPoint)mySocket.RemoteEndPoint;
                    // 判斷是否為 F5 偵測
                    //if (myHashTable_F5.ContainsKey(ClientInfo.Address.ToString()))
                    //{
                    //    dCount_F5 = dCount_F5 + 1;
                    //}
                    //else
                    {
                        //dCount_Total = dCount_Total + 1;
                        // 產生物件
                        clsSocketClient mySocketClient = new clsSocketClient(mySocket, strGUID, ClientInfo.Address.ToString(), ClientInfo.Port.ToString());
                        mySocketClient.m_isALVCK = true;
                        mySocketClient.m_dALVCKTime = 10000;
                        //myArrayList_Socket.Add(mySocketClient);
                        // 啟動執行緒
                        ThreadStart ServerThreadStart = new ThreadStart(mySocketClient.ThreadProcess);
                        Thread ServerThread = new Thread(ServerThreadStart);
                        ServerThread.Priority = ThreadPriority.AboveNormal;
                        ServerThread.Start();
                        // 加入訊息列
                        //DateTime dtLocal = DateTime.Now;
                        //DataRow dr = dtData.NewRow();
                        //dr["ClientIP"] = ClientInfo.Address.ToString();
                        //dr["ClientPort"] = ClientInfo.Port.ToString();
                        //dr["ConnectedTime"] = dtLocal.Hour.ToString("00") + ":" + dtLocal.Minute.ToString("00") + ":" + dtLocal.Second.ToString("00") + "." + dtLocal.Millisecond.ToString("000");
                        //dr["GUID"] = strGUID;
                        //AddShow(dr);
                    }
                    //BKWClientListen.ReportProgress(0);
                }
                catch (Exception ex)
                {
                    Concord.SDK.Logging.ConcordLogger.Logger.Error(ex.StackTrace.ToString() + " 錯誤: " + ex.ToString());
                }
            }
        }
    }
}
