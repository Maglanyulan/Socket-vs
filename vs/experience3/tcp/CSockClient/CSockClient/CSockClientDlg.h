
// CSockClientDlg.h : ͷ�ļ�
//

#pragma once

#include"MySock.h"

// CCSockClientDlg �Ի���
class CCSockClientDlg : public CDialogEx
{
// ����
protected:
	int TryCount;
	MySock m_clientSocket;
	UINT m_szPort;
public:
	char m_szServerAdr[256]; 
public:
	CCSockClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CSOCKCLIENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV ֧��



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

//	CListBox m_MSG;
//	CButton m_MSGS;
	CEdit m_MSG;
	CListBox m_MSGS;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedConnect();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
