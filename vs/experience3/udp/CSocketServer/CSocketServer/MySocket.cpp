// MySocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CSocketServer.h"
#include "MySocket.h"
#include"CSocketServerDlg.h"

// MySocket

MySocket::MySocket()
{
	m_nLength=0;
	memset(m_szBuffer,0,sizeof(m_szBuffer));

}

MySocket::~MySocket()
{
	if(m_hSocket!=INVALID_SOCKET)
      Close();
}


// MySocket ��Ա����


void MySocket::OnSend(int nErrorCode)
{
SendTo(m_szBuffer,m_nLength,nPort,szIP);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//��������һ���������������¼�������Server��Ϣ
AsyncSelect(FD_READ);
CSocket::OnSend(nErrorCode);
}


void MySocket::OnReceive(int nErrorCode)
{
m_nLength=ReceiveFrom(m_szBuffer,sizeof(m_szBuffer),szIP,nPort);
//�������д���������ȡ�Ի���ָ��
CCSocketServerApp* pApp=(CCSocketServerApp*)AfxGetApp();
CCSocketServerDlg* pDlg=(CCSocketServerDlg*)pApp->m_pMainWnd;
pDlg->m_MSGS.InsertString(0,m_szBuffer);
memset(m_szBuffer,0,sizeof(m_szBuffer));
CSocket::OnReceive(nErrorCode);
}
