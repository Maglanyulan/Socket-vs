#pragma once
#include "AddrDlg.h"
// MySock 命令目标

class MySock : public CSocket
{
public:
	MySock();
	virtual ~MySock();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	UINT m_nLength;        //消息长度
    char m_szBuffer[4096];    //消息缓冲区
	SOCKADDR_IN ServerAddr;
	int len;
};


