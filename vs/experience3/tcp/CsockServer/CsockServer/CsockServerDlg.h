
// CsockServerDlg.h : 头文件
//
#include "MyServerSocket.h"
#pragma once
#include<afxsock.h>

// CCsockServerDlg 对话框
class CCsockServerDlg : public CDialogEx
{
// 构造
public:
	CCsockServerDlg(CWnd* pParent = NULL);	// 标准构造函数
	CMyServerSocket m_srvrSocket,clientSocket;
// 对话框数据
	enum { IDD = IDD_CSOCKSERVER_DIALOG };

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
	CEdit m_MSG;
	CListBox m_MSGS;
	afx_msg void OnBnClickedOnlisten();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedExit();
};
