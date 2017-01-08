
// tetris.h : tetris 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#define	WINDOW_W	320
#define	WINDOW_H	540
#define VIEW_X		24
#define VIEW_Y		27
#define LEVEL_MAX	7
#define SCORESTEP	10

// CtetrisApp:
// 有关此类的实现，请参阅 tetris.cpp
//

class CtetrisApp : public CWinApp
{
public:
	CtetrisApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtetrisApp theApp;
