#pragma once


// CAddrDlg �Ի���

class CAddrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddrDlg)

public:
	CAddrDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddrDlg();

// �Ի�������
	enum { IDD = IDD_ADDRDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Addr;
	int m_Port;
};