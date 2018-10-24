// MySock.cpp : ʵ���ļ�
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


// MySock ��Ա����


void MySock::OnSend(int nErrorCode)
{

SendTo(m_szBuffer,m_nLength,(SOCKADDR*)&ServerAddr,len,0);
m_nLength=0;
memset(m_szBuffer,0,sizeof(m_szBuffer));
//��������һ���������������¼�������Server��Ϣ
AsyncSelect(FD_READ);
CAsyncSocket::OnSend(nErrorCode);
}


void MySock::OnReceive(int nErrorCode)
{
//int len=sizeof(SOCKADDR_IN);
m_nLength=ReceiveFrom(m_szBuffer,sizeof(m_szBuffer),(SOCKADDR*)&ServerAddr,&len,0);
//�������д���������ȡ�Ի���ָ��
CCSockClientApp* pApp=(CCSockClientApp*)AfxGetApp();
CCSockClientDlg* pDlg=(CCSockClientDlg*)pApp->m_pMainWnd;
pDlg->m_MSGS.InsertString(0,m_szBuffer);
memset(m_szBuffer,0,sizeof(m_szBuffer));
CAsyncSocket::OnReceive(nErrorCode);
}
