#pragma once

// MySocket 命令目标

class MySocket : public CSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	UINT m_nLength;        //消息长度
    char m_szBuffer[4096];    //消息缓冲区
	UINT nPort;
	CString szIP;
};


