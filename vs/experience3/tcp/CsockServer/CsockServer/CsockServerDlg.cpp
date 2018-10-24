
// CsockServerDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCsockServerDlg �Ի���




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


// CCsockServerDlg ��Ϣ�������

BOOL CCsockServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCsockServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCsockServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCsockServerDlg::OnBnClickedOnlisten()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if( m_srvrSocket.m_hSocket==INVALID_SOCKET)
{
	 AfxSocketInit();
      BOOL bFlag=m_srvrSocket.Create
         (1088,SOCK_STREAM,FD_ACCEPT);
      if (!bFlag)
      {
		AfxMessageBox("Socket Create Error��");
       m_srvrSocket.Close();
       PostQuitMessage(0);
      return;
      }
}
//���������ɹ����ȴ���������
if (!m_srvrSocket.Listen(1))
{
      int nErrorCode = m_srvrSocket.GetLastError();
      if (nErrorCode!=WSAEWOULDBLOCK)
      {
       AfxMessageBox("Socket Listen Error��");
       m_srvrSocket.Close();
       PostQuitMessage(0);
      return;
      }
}
else{
	AfxMessageBox("Socket Listen successed��");
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
	AfxMessageBox("Send Error��");
	clientSocket.Close();
	return;
	}
}



void CCsockServerDlg::OnBnClickedExit()
{
//�ر�Socket
m_srvrSocket.ShutDown(2);
//�رնԻ���
EndDialog(0); 
}
