#pragma once

// MySocket ����Ŀ��

class MySocket : public CSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	UINT m_nLength;        //��Ϣ����
    char m_szBuffer[4096];    //��Ϣ������
	UINT nPort;
	CString szIP;
};


