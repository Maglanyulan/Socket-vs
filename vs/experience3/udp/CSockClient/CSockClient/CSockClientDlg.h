
// CSockClientDlg.h : ͷ�ļ�
//

#pragma once

#include "AddrDlg.h"
#include"MySock.h"

// CCSockClientDlg �Ի���
class CCSockClientDlg : public CDialogEx
{
// ����
public:
	CCSockClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CSOCKCLIENT_DIALOG };

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
protected:
int TryCount;
MySock m_clientSocket;
public:
//char m_szServerAdr[256]; 
afx_msg void OnBnClickedConnet();
afx_msg void OnTimer(UINT_PTR nIDEvent);
afx_msg void OnBnClickedSend();
afx_msg void OnBnClickedExit();
};
