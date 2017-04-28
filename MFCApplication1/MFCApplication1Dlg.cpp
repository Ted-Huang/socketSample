
// MFCApplication1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 對話方塊



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 訊息處理常式

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

struct MsgInstDataParam 
{
	char	szData[1024];
};

// 期權回報04
struct ReportTFEData
{
	char cProdType;		// 期貨'F'/選擇權'O'
	char arOP[2];		// OP
	char arBrokerID[7];	// Broker ID
	char arTradeID[7];	// Account ID
	char arOrderNo[5];	// 委託書號
	char cBuySell;		// B/S
	char cOrderType;	// 市價'M'/限價'L'
	char cOrderKind;	// 委託條件: FOK'F'/IOC'I'/ROD'R', 唯 市價 不支援 ROD
	char cOpenCode;		// 開平倉碼, 開倉'0'/平倉'1'/當沖'2', (當沖 僅適用期貨)
	char arCommID1[10];	// 商品代號1
	char cBS1;			// 買賣別1, B/S
	char arPrice1[10];	// 價位1, S9(6)V9(3)
						// 複式單委託, 為價差/價和
	char arCommID2[10];	// 商品代號2
	char cBS2;			// 買賣別2, B/S
	char arPrice2[10];	// 價位2, S9(6)V9(3)
						// 以上3個欄位只用在 複式單
	char arQty[4];		// 數量
						//  改量: 更改後數量, 刪單: 取消數量, 均不含成交
	char arQtyBefore[4];// 改量前(only valid for 改量): 改量前數量, 均不含成交
	char arDate[8];		// 委託/成交日期, YYYYMMDD
	char arTime[6];		// 委託/成交時間, HHMMSS
	char arSales[3];	// 營業員
	char cDataSrc;		// 資料來源
	char arMatchNo[8];	// 交易所成交序號 9(8)
	char arSeqNo[8];	// 網路序號 X(8)
	char cPrgmType;		// 智慧下單類型, 1:通知,2:一般單回報,3:智慧單回報
	char arPrgmINSQ[10];	// 智慧下單網路序號
	char arSubID[6];		// 子帳號
	char arGMatchNo[2];	// 子帳號成交序號
	char cTradeType;	// 交易方式 '0':單式單, '1':複式第一隻腳, '2':複式第二隻腳, '3':複式單, ' ':不做特別處理
	char arSeqNo2[12];	// 網路序號2 KGI因真正OID過長，所以為 arSeqNo + arSeqNo2
						/*char arPriceBefore[10];	// 改價前 價位, S9(6)V9(3)
						// 複式單委託, 為價差/價和
						char cOrderTypeBefore;	// 改價前 市價'M'/限價'L'
						char cOrderKindBefore;	// 改價前 委託條件: FOK'F'/IOC'I'/ROD'R', 唯 市價 不支援 ROD*/
	char arError[4];	// Error Message
	char arROID[16];
	char arCodeID[16];
	char arNewPrice1[12];   // 價位1, S9(7)V9(4)
							// 複式單委託, 為價差/價和
	char arNewPrice2[12];   // 價位2, S9(7)V9(4)
	char arError2[51];
	char arTDQty[4];		// 總成交數量
	char arCQty[4];		// 搓合取消數量
	char arSession[1];		// 盤別代碼
};

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AfxSocketInit();
	CSocket aSocket;
	CString strIP("192.168.103.86");
	CString strPort("9999");
	CString strText("");
	//初始化 CSocket 对象, 因为客户端不需要绑定任何端口和地址, 所以用默认参数即可  
	if (!aSocket.Create())
	{
		char szMsg[1024] = { 0 };

		sprintf_s(szMsg, "create faild: %d", aSocket.GetLastError());

		AfxMessageBox(szMsg);
		return;
	}
	//转换需要连接的端口内容类型  
	int nPort = atoi(strPort);
	//连接指定的地址和端口  

	if (aSocket.Connect(strIP, nPort))
	{
		BYTE* b[1024] = { 0 };
		
		//aSocket.Send(strText, strText.GetLength()); //发送内容给服务器  
		aSocket.Receive((void *)b, 1024); //接收服务器发送回来的内容(该方法会阻塞, 在此等待有内容接收到才继续向下执行)  
		MsgInstDataParam* pParam = (MsgInstDataParam*)b;
		char* szRecValue = pParam->szData;
		ReportTFEData* pData = (ReportTFEData*)szRecValue;
		pData->arError2[51] = '\0';
		AfxMessageBox(pData->arError2);

	}
	else
	{
		char szMsg[1024] = { 0 };
		sprintf_s(szMsg, "create faild: %d", aSocket.GetLastError());
		AfxMessageBox(szMsg);
	}
	aSocket.Close();
}
