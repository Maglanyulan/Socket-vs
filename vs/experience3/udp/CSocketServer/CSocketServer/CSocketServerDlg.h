
// CSocketServerDlg.h : ͷ�ļ�
//

#pragma once
#include"MySocket.h"

// CCSocketServerDlg �Ի���
class CCSocketServerDlg : public CDialogEx
{
// ����
public:
	CCSocketServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CSOCKETSERVER_DIALOG };

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
