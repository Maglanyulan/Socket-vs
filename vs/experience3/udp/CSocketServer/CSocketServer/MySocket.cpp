// MySocket.cpp : 实现文件
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


// MySocket 成员函数


void MySocket::OnSend(int nErrorCode)
{
SendTo(m_szBuffer,m_nLength,nPort,szIP);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//继续提请一个“读”的网络事件，接收Server消息
AsyncSelect(FD_READ);
CSocket::OnSend(nErrorCode);
}


void MySocket::OnReceive(int nErrorCode)
{
m_nLength=ReceiveFrom(m_szBuffer,sizeof(m_szBuffer),szIP,nPort);
//下面两行代码用来获取对话框指针
CCSocketServerApp* pApp=(CCSocketServerApp*)AfxGetApp();
CCSocketServerDlg* pDlg=(CCSocketServerDlg*)pApp->m_pMainWnd;
pDlg->m_MSGS.InsertString(0,m_szBuffer);
memset(m_szBuffer,0,sizeof(m_szBuffer));
CSocket::OnReceive(nErrorCode);
}
