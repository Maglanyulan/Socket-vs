// AddrDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSockClient.h"
#include "AddrDlg.h"
#include "afxdialogex.h"


// CAddrDlg �Ի���

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


// CAddrDlg ��Ϣ�������
