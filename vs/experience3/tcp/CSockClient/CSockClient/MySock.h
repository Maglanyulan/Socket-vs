#pragma once

// MySock ����Ŀ��

#include<afxsock.h>

class MySock : public CAsyncSocket
{
public:
	MySock();
	virtual ~MySock();

      BOOL m_bConnected;    //�Ƿ�����
      UINT m_nLength;        //��Ϣ����
      char m_szBuffer[4096];    //��Ϣ������
	virtual void OnSend(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
};


