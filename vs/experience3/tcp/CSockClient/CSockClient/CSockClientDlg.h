
// CSockClientDlg.h : 头文件
//

#pragma once

#include"MySock.h"

// CCSockClientDlg 对话框
class CCSockClientDlg : public CDialogEx
{
// 构造
protected:
	int TryCount;
	MySock m_clientSocket;
	UINT m_szPort;
public:
	char m_szServerAdr[256]; 
public:
	CCSockClientDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CSOCKCLIENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV 支持



// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

//	CListBox m_MSG;
//	CButton m_MSGS;
	CEdit m_MSG;
	CListBox m_MSGS;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
