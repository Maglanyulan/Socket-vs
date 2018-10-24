// AddrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CSockClient.h"
#include "AddrDlg.h"
#include "afxdialogex.h"


// CAddrDlg 对话框

IMPLEMENT_DYNAMIC(CAddrDlg, CDialog)

CAddrDlg::CAddrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddrDlg::IDD, pParent)
{

	m_Port = 0;
}

CAddrDlg::~CAddrDlg()
{
}

void CAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_IP,m_Addr);
	DDX_Text(pDX, IDC_EDIT_Port, m_Port);
}


BEGIN_MESSAGE_MAP(CAddrDlg, CDialog)
END_MESSAGE_MAP()


// CAddrDlg 消息处理程序
