// MySock.cpp : ʵ���ļ�
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


// MySock ��Ա����

void MySock::OnReceive(int nErrorCode){
m_nLength=Receive(m_szBuffer,sizeof(m_szBuffer),0);
//�������д���������ȡ�Ի���ָ��
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
//��������һ���������������¼�������Server��Ϣ
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
      AsyncSelect(FD_READ);    ////����һ���������������¼���׼������
}
CAsyncSocket::OnConnect(nErrorCode);
}