
// tetris.h : tetris Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#define	WINDOW_W	320
#define	WINDOW_H	540
#define VIEW_X		24
#define VIEW_Y		27
#define LEVEL_MAX	7
#define SCORESTEP	10

// CtetrisApp:
// �йش����ʵ�֣������ tetris.cpp
//

class CtetrisApp : public CWinApp
{
public:
	CtetrisApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtetrisApp theApp;
