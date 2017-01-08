
// MainFrm.cpp : CMainFrame ���ʵ��
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

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	// CREATESTRUCT cs ���޸Ĵ��������ʽ
	cs.cx = WINDOW_W;
	cs.cy = WINDOW_H;
	cs.x = (GetSystemMetrics(SM_CXSCREEN)-cs.cx)/2;
	cs.y = (GetSystemMetrics(SM_CYSCREEN)-cs.cy)/2;

	cs.hMenu = NULL;

	cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_BORDER | WS_MINIMIZEBOX;

	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������





int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
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
