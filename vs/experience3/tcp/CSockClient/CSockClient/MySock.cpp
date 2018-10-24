// MySock.cpp : 实现文件
//

#include "stdafx.h"
#include "MySock.h"
#include "afxdialogex.h"
#include "CSockClient.h"
#include "CSockClientDlg.h"
// MySock

MySock::MySock()
{
	m_nLength=0;
	memset(m_szBuffer,0,sizeof(m_szBuffer));
	m_bConnected=FALSE;
}

MySock::~MySock()
{
	if(m_hSocket!=INVALID_SOCKET)
	Close();
}


// MySock 成员函数

void MySock::OnReceive(int nErrorCode){
m_nLength=Receive(m_szBuffer,sizeof(m_szBuffer),0);
//下面两行代码用来获取对话框指针
CCSockClientApp* pApp=(CCSockClientApp*)AfxGetApp();
CCSockClientDlg* pDlg=(CCSockClientDlg*)pApp->m_pMainWnd;
pDlg->m_MSGS.InsertString(0,m_szBuffer);
memset(m_szBuffer,0,sizeof(m_szBuffer));
CAsyncSocket::OnReceive(nErrorCode);
}

void MySock::OnSend(int nErrorCode){
Send(m_szBuffer,m_nLength,0);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//继续提请一个“读”的网络事件，接收Server消息
AsyncSelect(FD_READ);
CAsyncSocket::OnSend(nErrorCode);
}

void MySock::OnConnect(int nErrorCode){
if (nErrorCode==0)
{
      m_bConnected=TRUE;
      CCSockClientApp* pApp=(CCSockClientApp*)AfxGetApp();
      CCSockClientDlg* pDlg=(CCSockClientDlg*)pApp->m_pMainWnd;
      memcpy(m_szBuffer,"Connected to ",13);
      strncat(m_szBuffer,pDlg->m_szServerAdr,
        sizeof(pDlg->m_szServerAdr));
      pDlg->m_MSGS.InsertString(0,m_szBuffer);
      AsyncSelect(FD_READ);    ////提请一个“读”的网络事件，准备接收
}
CAsyncSocket::OnConnect(nErrorCode);
}