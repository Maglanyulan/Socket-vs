
// CSockClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSockClient.h"
#include "CSockClientDlg.h"
#include "afxdialogex.h"
#include "AddrDlg.h"
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


// CCSockClientDlg �Ի���




CCSockClientDlg::CCSockClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCSockClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCSockClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LIST1, m_MSG);
	//  DDX_Control(pDX, IDC_Send, m_MSGS);
	DDX_Control(pDX, IDC_EDIT1, m_MSG);
	DDX_Control(pDX, IDC_LIST1, m_MSGS);
}

BEGIN_MESSAGE_MAP(CCSockClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_Send, &CCSockClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(ID_Exit, &CCSockClientDlg::OnBnClickedExit)

	ON_BN_CLICKED(ID_Connect, &CCSockClientDlg::OnBnClickedConnect)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCSockClientDlg ��Ϣ�������

BOOL CCSockClientDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCSockClientDlg::OnPaint()
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
HCURSOR CCSockClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCSockClientDlg::OnBnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
AfxSocketInit();
m_clientSocket.ShutDown(2);
m_clientSocket.m_hSocket=INVALID_SOCKET;
m_clientSocket.m_bConnected=FALSE;
CAddrDlg m_Dlg;
//Ĭ�϶˿�1088
m_Dlg.m_Port=1088;
m_Dlg.m_Addr="127.0.0.1";
if (m_Dlg.DoModal()==IDOK && !m_Dlg.m_Addr.IsEmpty())
{
      memcpy(m_szServerAdr,m_Dlg.m_Addr,sizeof(m_szServerAdr));
      m_szPort=m_Dlg.m_Port;
      //������ʱ����ÿ1�볢������һ�Σ�ֱ�����ϻ�TryCount>10
SetTimer(1,1000,NULL);
      TryCount=0;
}
}



void CCSockClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

if (m_clientSocket.m_hSocket==INVALID_SOCKET)
{
      BOOL bFlag=m_clientSocket.Create(0,SOCK_STREAM,FD_CONNECT);
      if(!bFlag)
      {
       AfxMessageBox("Socket Create Error!");
       m_clientSocket.Close();
       PostQuitMessage(0);
       return;
      }
	  AfxMessageBox("Socket success!");
}
    
m_clientSocket.Connect(m_szServerAdr,m_szPort);
TryCount++;
if (TryCount >=10 || m_clientSocket.m_bConnected)
{ 
      KillTimer(1);
      if (TryCount >=10)
       AfxMessageBox("Connect Failed!");
      return;
}
CDialog::OnTimer(nIDEvent);
}


void CCSockClientDlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_clientSocket.m_bConnected)
	{
		m_clientSocket.m_nLength=m_MSG.GetWindowText
		(m_clientSocket.m_szBuffer, sizeof(m_clientSocket.m_szBuffer));
		 m_clientSocket.AsyncSelect(FD_WRITE);
		  m_MSG.SetWindowText("");
	}
}


void CCSockClientDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�ر�Socket
	m_clientSocket.ShutDown(2);
	//�رնԻ���
	EndDialog(0); 
}




