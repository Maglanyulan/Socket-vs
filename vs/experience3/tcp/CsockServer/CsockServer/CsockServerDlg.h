
// CsockServerDlg.h : ͷ�ļ�
//
#include "MyServerSocket.h"
#pragma once
#include<afxsock.h>

// CCsockServerDlg �Ի���
class CCsockServerDlg : public CDialogEx
{
// ����
public:
	CCsockServerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CMyServerSocket m_srvrSocket,clientSocket;
// �Ի�������
	enum { IDD = IDD_CSOCKSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
