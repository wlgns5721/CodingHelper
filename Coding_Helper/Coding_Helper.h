
// Coding_Helper.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCoding_HelperApp:
// �� Ŭ������ ������ ���ؼ��� Coding_Helper.cpp�� �����Ͻʽÿ�.
//

class CCoding_HelperApp : public CWinApp
{
public:
	CCoding_HelperApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCoding_HelperApp theApp;