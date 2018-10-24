#pragma once


// CAddrDlg 对话框

class CAddrDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddrDlg)

public:
	CAddrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddrDlg();

// 对话框数据
	enum { IDD = IDD_Addr };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Addr;
	int m_Port;
};
