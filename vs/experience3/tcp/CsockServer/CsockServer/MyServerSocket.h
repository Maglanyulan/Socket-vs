//#include "CnewSocket.h"

#pragma once
// CMyServerSocket ����Ŀ��

class CMyServerSocket : public CAsyncSocket
{
public:
	CMyServerSocket();
	virtual ~CMyServerSocket();
	virtual void OnAccept(int nErrorCode);
	CMyServerSocket* m_pSocket;
	BOOL m_bConnected;
	UINT m_nLength;        //��Ϣ����
	char m_szBuffer[4096];    //��Ϣ������
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


