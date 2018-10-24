#pragma once

// MySock 命令目标

#include<afxsock.h>

class MySock : public CAsyncSocket
{
public:
	MySock();
	virtual ~MySock();

      BOOL m_bConnected;    //是否连接
      UINT m_nLength;        //消息长度
      char m_szBuffer[4096];    //消息缓冲区
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
};


