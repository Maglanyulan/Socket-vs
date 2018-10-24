// MyServerSocket.cpp : 实现文件
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


// CMyServerSocket 成员函数


void CMyServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	//侦听到连接请求，调用Accept函数
if(nErrorCode==0)
{
m_bConnected=TRUE;
AsyncSelect(FD_READ);
}

CAsyncSocket::OnAccept(nErrorCode);
}


void CMyServerSocket::OnSend(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
Send(m_szBuffer,m_nLength,0);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//继续提请一个“读”的网络事件，接收Server消息
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
