
// MFCApplication5.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFCApplication5App: 
// �аѾ\��@�����O�� MFCApplication5.cpp
//

class CMFCApplication5App : public CWinApp
{
public:
	CMFCApplication5App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication5App theApp;