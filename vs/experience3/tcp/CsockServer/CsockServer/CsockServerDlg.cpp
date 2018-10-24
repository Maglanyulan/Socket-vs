
// CsockServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CsockServer.h"
#include "CsockServerDlg.h"
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


// CCsockServerDlg 对话框




CCsockServerDlg::CCsockServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCsockServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCsockServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_MSG);
	//  DDX_Control(pDX, IDC_Exit, m_MSGS);
	DDX_Control(pDX, IDC_LIST1, m_MSGS);
}

BEGIN_MESSAGE_MAP(CCsockServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OnListen, &CCsockServerDlg::OnBnClickedOnlisten)
	ON_BN_CLICKED(IDC_Send, &CCsockServerDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_Exit, &CCsockServerDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CCsockServerDlg 消息处理程序

BOOL CCsockServerDlg::OnInitDialog()
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

void CCsockServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCsockServerDlg::OnPaint()
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
HCURSOR CCsockServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCsockServerDlg::OnBnClickedOnlisten()
{
	// TODO: 在此添加控件通知处理程序代码
	if( m_srvrSocket.m_hSocket==INVALID_SOCKET)
{
	 AfxSocketInit();
      BOOL bFlag=m_srvrSocket.Create
         (1088,SOCK_STREAM,FD_ACCEPT);
      if (!bFlag)
      {
		AfxMessageBox("Socket Create Error！");
       m_srvrSocket.Close();
       PostQuitMessage(0);
      return;
      }
}
//“侦听”成功，等待连接请求
if (!m_srvrSocket.Listen(1))
{
      int nErrorCode = m_srvrSocket.GetLastError();
      if (nErrorCode!=WSAEWOULDBLOCK)
      {
       AfxMessageBox("Socket Listen Error！");
       m_srvrSocket.Close();
       PostQuitMessage(0);
      return;
      }
}
else{
	AfxMessageBox("Socket Listen successed！");
	m_srvrSocket.Accept(clientSocket);
}
}


void CCsockServerDlg::OnBnClickedSend()
{
	if(m_srvrSocket.m_bConnected){
	clientSocket.m_nLength=m_MSG.GetWindowText
		(clientSocket.m_szBuffer, sizeof(clientSocket.m_szBuffer));
	clientSocket.AsyncSelect();
	 m_MSG.SetWindowText("");
	}
	else{
	AfxMessageBox("Send Error！");
	clientSocket.Close();
	return;
	}
}



void CCsockServerDlg::OnBnClickedExit()
{
//关闭Socket
m_srvrSocket.ShutDown(2);
//关闭对话框
EndDialog(0); 
}
