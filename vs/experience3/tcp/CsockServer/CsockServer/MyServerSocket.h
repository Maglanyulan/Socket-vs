//#include "CnewSocket.h"

#pragma once
// CMyServerSocket 命令目标

class CMyServerSocket : public CAsyncSocket
{
public:
	CMyServerSocket();
	virtual ~CMyServerSocket();
	virtual void OnAccept(int nErrorCode);
	CMyServerSocket* m_pSocket;
	BOOL m_bConnected;
	UINT m_nLength;        //消息长度
	char m_szBuffer[4096];    //消息缓冲区
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


