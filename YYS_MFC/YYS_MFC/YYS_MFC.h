
// YYS_MFC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CYYS_MFCApp: 
// �йش����ʵ�֣������ YYS_MFC.cpp
//

class CYYS_MFCApp : public CWinApp
{
public:
	CYYS_MFCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CYYS_MFCApp theApp;