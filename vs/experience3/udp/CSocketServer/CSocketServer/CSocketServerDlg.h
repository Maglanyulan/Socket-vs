
// CSocketServerDlg.h : 头文件
//

#pragma once
#include"MySocket.h"

// CCSocketServerDlg 对话框
class CCSocketServerDlg : public CDialogEx
{
// 构造
public:
	CCSocketServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CSOCKETSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	CListBox m_MSGS;
	afx_msg void OnBnClickedCreate();
protected:
MySocket m_clientSocket;
//UINT m_port;
afx_msg void OnBnClickedSend();
afx_msg void OnBnClickedExit();
public:
	CEdit m_MSG;
	//char m_Adde[256];
		SOCKADDR_IN addr;

};
