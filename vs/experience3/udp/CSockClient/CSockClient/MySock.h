#pragma once
#include "AddrDlg.h"
// MySock ����Ŀ��

class MySock : public CSocket
{
public:
	MySock();
	virtual ~MySock();
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	UINT m_nLength;        //��Ϣ����
    char m_szBuffer[4096];    //��Ϣ������
	SOCKADDR_IN ServerAddr;
	int len;
};


