
// CSockClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CSockClient.h"
#include "CSockClientDlg.h"
#include "afxdialogex.h"
#include"winsock2.h"
#pragma comment(lib, "ws2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCSockClientDlg 对话框




CCSockClientDlg::CCSockClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCSockClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSockClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_MSG);
	DDX_Control(pDX, IDC_LIST1, m_MSGS);
}

BEGIN_MESSAGE_MAP(CCSockClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_Connet, &CCSockClientDlg::OnBnClickedConnet)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_Send, &CCSockClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(ID_Exit, &CCSockClientDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CCSockClientDlg 消息处理程序

BOOL CCSockClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCSockClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCSockClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCSockClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCSockClientDlg::OnBnClickedConnet()
{
m_clientSocket.ShutDown(2);
m_clientSocket.m_hSocket=INVALID_SOCKET;
//m_clientSocket.m_bConnected=FALSE;
CAddrDlg m_Dlg;
//默认端口1088
m_Dlg.m_Port=1088;
m_Dlg.m_Addr="127.0.0.1";
if (m_Dlg.DoModal()==IDOK && !m_Dlg.m_Addr.IsEmpty())
{

	m_clientSocket.ServerAddr.sin_family=AF_INET;
	m_clientSocket.ServerAddr.sin_port=htons(m_Dlg.m_Port);
	char *cip=m_Dlg.m_Addr.GetBuffer(m_Dlg.m_Addr.GetLength());
	m_clientSocket.ServerAddr.sin_addr.S_un.S_addr=inet_addr(cip);
	//建立计时器，每1秒尝试连接一次，直到连上或TryCount>10
	SetTimer(1,1000,NULL);
	TryCount=0;
}
}


void CCSockClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
if (m_clientSocket.m_hSocket==INVALID_SOCKET)
{
	AfxSocketInit();
	TryCount++;
   BOOL bFlag=m_clientSocket.Create(0,SOCK_DGRAM,NULL);
      if(TryCount >=10 ||bFlag)
      { KillTimer(1);
      if (TryCount >=10){
       AfxMessageBox("Socket Create Failed!");
	   m_clientSocket.Close(); 
	   PostQuitMessage(0);
      return;
	  }
	  else{
		  AfxMessageBox("Socket Create Successed!");
		   m_clientSocket.m_szBuffer[0]=1;
		  m_clientSocket.m_nLength=sizeof(m_clientSocket.m_szBuffer);
		  m_clientSocket.AsyncSelect(FD_WRITE);
 m_clientSocket.AsyncSelect(FD_READ);
	  }
	  return;
	}
CDialog::OnTimer(nIDEvent);
}

}


void CCSockClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码

m_clientSocket.m_nLength=m_MSG.GetWindowText
(m_clientSocket.m_szBuffer, sizeof(m_clientSocket.m_szBuffer));
m_clientSocket.AsyncSelect(FD_WRITE);
m_MSG.SetWindowText("");

}


void CCSockClientDlg::OnBnClickedExit()
{
//关闭Socket
m_clientSocket.ShutDown(2);
//关闭对话框
EndDialog(0); 
}
