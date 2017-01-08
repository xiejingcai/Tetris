
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "tetris.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)

	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	// CREATESTRUCT cs 来修改窗口类或样式
	cs.cx = WINDOW_W;
	cs.cy = WINDOW_H;
	cs.x = (GetSystemMetrics(SM_CXSCREEN)-cs.cx)/2;
	cs.y = (GetSystemMetrics(SM_CYSCREEN)-cs.cy)/2;

	cs.hMenu = NULL;

	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序





int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	int delta_x, delta_y;
	CRect client_Rect;
	GetClientRect(&client_Rect);
	CRect win_Rect;
	GetWindowRect(&win_Rect);
	delta_x = WINDOW_W - client_Rect.Width() + 4;
	delta_y = WINDOW_H - client_Rect.Height() + 4;
	SetRect(&win_Rect, win_Rect.left, win_Rect.top, 
		win_Rect.right + delta_x, win_Rect.bottom + delta_y);
	MoveWindow(&win_Rect);

	return 0;
}
