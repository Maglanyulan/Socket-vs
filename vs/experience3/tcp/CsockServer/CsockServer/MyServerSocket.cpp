// MyServerSocket.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CsockServer.h"
#include"CsockServerDlg.h"
#include "MyServerSocket.h"


// CMyServerSocket

CMyServerSocket::CMyServerSocket()
{
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
m_bConnected=FALSE;
}

CMyServerSocket::~CMyServerSocket()
{
	if(m_hSocket!=INVALID_SOCKET)
      Close();
}


// CMyServerSocket ��Ա����


void CMyServerSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	//�������������󣬵���Accept����
if(nErrorCode==0)
{
m_bConnected=TRUE;
AsyncSelect(FD_READ);
}

CAsyncSocket::OnAccept(nErrorCode);
}


void CMyServerSocket::OnSend(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
Send(m_szBuffer,m_nLength,0);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//��������һ���������������¼�������Server��Ϣ
AsyncSelect(FD_READ);
CAsyncSocket::OnSend(nErrorCode);
}


void CMyServerSocket::OnReceive(int nErrorCode)
{
	m_nLength=Receive(m_szBuffer,sizeof(m_szBuffer),0);
CCsockServerApp* pApp=(CCsockServerApp*)AfxGetApp();
CCsockServerDlg* pDlg=(CCsockServerDlg*)pApp->m_pMainWnd;
pDlg->m_MSGS.InsertString(0,m_szBuffer);
memset(m_szBuffer,0,sizeof(m_szBuffer));
//AsyncSelect(FD_WRITE);
CAsyncSocket::OnReceive(nErrorCode);
}
