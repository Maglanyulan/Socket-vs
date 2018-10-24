// MySock.cpp : 实现文件
//

#include "stdafx.h"
#include "CSockClient.h"
#include "MySock.h"
#include"CSockClientDlg.h"

// MySock

MySock::MySock()
{
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
len=sizeof(ServerAddr);
}

MySock::~MySock()
{
	if(m_hSocket!=INVALID_SOCKET)
      Close();
}


// MySock 成员函数


void MySock::OnSend(int nErrorCode)
{

SendTo(m_szBuffer,m_nLength,(SOCKADDR*)&ServerAddr,len,0);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//继续提请一个“读”的网络事件，接收Server消息
AsyncSelect(FD_READ);
CAsyncSocket::OnSend(nErrorCode);
}


void MySock::OnReceive(int nErrorCode)
{
//int len=sizeof(SOCKADDR_IN);
m_nLength=ReceiveFrom(m_szBuffer,sizeof(m_szBuffer),(SOCKADDR*)&ServerAddr,&len,0);
//下面两行代码用来获取对话框指针
CCSockClientApp* pApp=(CCSockClientApp*)AfxGetApp();
CCSockClientDlg* pDlg=(CCSockClientDlg*)pApp->m_pMainWnd;
pDlg->m_MSGS.InsertString(0,m_szBuffer);
memset(m_szBuffer,0,sizeof(m_szBuffer));
CAsyncSocket::OnReceive(nErrorCode);
}
