
// CSocketServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCSocketServerApp:
// �йش����ʵ�֣������ CSocketServer.cpp
//

class CCSocketServerApp : public CWinApp
{
public:
	CCSocketServerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCSocketServerApp theApp;