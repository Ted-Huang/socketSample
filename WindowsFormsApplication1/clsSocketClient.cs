using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Runtime.InteropServices;

namespace WindowsFormsApplication1
{
    class clsSocketClient
    {
        public Int32 m_iSleepTime = 0;
        public Double m_dALVCKTime = 0;
        public Boolean m_isOK = true;
        public Boolean m_isFlag = true;
        public Boolean m_isALVCK = true;
        public String m_strGUID = "";
        private Socket mySocket;
        private NetworkStream myNetworkStream;
        private String m_strIP = "";
        private String m_strPort = "";
        private char SplitChar = (char)0x01;

        #region DLLImport
        [DllImport("winmm.dll")]
        internal static extern uint timeBeginPeriod(uint period);
        [DllImport("winmm.dll")]
        internal static extern uint timeEndPeriod(uint period);
        #endregion

        public clsSocketClient(Socket SocketClient, String strGUID, String strIP, String strPort)
        {
            mySocket = SocketClient;
            m_strGUID = strGUID;
            m_strIP = strIP;
            m_strPort = strPort;
            //Concord.SDK.Logging.ConcordLogger.Logger.Info("物件 GUID: " + m_strGUID + " Client IP: " + m_strIP + " Port: " + m_strPort + " 產生 !");
        }

        ~clsSocketClient()
        {
            myNetworkStream = null;
            mySocket = null;
        }

        public void ThreadProcess()
        {
            try
            {
                DateTime dtOld = DateTime.Now;
                DateTime dtNew = DateTime.Now;
                mySocket.ReceiveBufferSize = Int32.MaxValue;
                mySocket.SendBufferSize = Int32.MaxValue;
                myNetworkStream = new NetworkStream(mySocket);
                while ((mySocket.Connected) && (m_isFlag.Equals(true)))
                {
                    // 是否要送出 ALVCK
                    dtNew = DateTime.Now;
                    
                    if (DateTime.Compare(dtNew.AddSeconds(m_dALVCKTime), dtOld) > 0)
                    {
                        if (m_isALVCK.Equals(true))
                        {
                            String strWrite = "08TFE10   201704280000000100100264000983925704F12000    9839257     SLR TXFE7     S 010426000                     0001000020170502085737   5        TC3N0384                   0001                                              00104260000            一般Test!                                            00000000P";
                            Byte[] myByte = Encoding.GetEncoding("Big5").GetBytes(strWrite);
                            myNetworkStream.Write(myByte, 0, myByte.Length);
                            dtOld = DateTime.Now;
                            Concord.SDK.Logging.ConcordLogger.Logger.Info("物件 GUID: " + m_strGUID + " Client IP: " + m_strIP + " Port: " + m_strPort + " 送出: " + strWrite.ToString());
                        }
                    }
                    else
                    {
                        if (mySocket.Available.Equals(0))
                        {
                            Thread.Sleep(m_iSleepTime);
                        }
                    }
                    timeBeginPeriod(1);
                    Thread.Sleep(2000);
                    timeEndPeriod(1);
                }
                mySocket.Close();
                m_isOK = false;
            }
            catch (Exception ex)
            {
                Concord.SDK.Logging.ConcordLogger.Logger.Error("ThreadProcess 物件 GUID: " + m_strGUID + " Error!!錯誤原因:" + ex.ToString());
                mySocket.Close();
                m_isOK = false;
                Concord.SDK.Logging.ConcordLogger.Logger.Info("物件 GUID: " + m_strGUID + " Client IP: " + m_strIP + " Port: " + m_strPort + " 關閉連線 ! ");
            }
        }
    }
}
