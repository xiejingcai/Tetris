
// tetrisView.cpp : CtetrisView 类的实现
//
#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "tetris.h"
#endif
#include "afxwinappex.h"
#include "tetrisDoc.h"
#include "tetrisView.h"

#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define TIMER 1

// CtetrisView

IMPLEMENT_DYNCREATE(CtetrisView, CView)

BEGIN_MESSAGE_MAP(CtetrisView, CView)
	ON_WM_CHAR()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

int screen_array[WINDOW_H/20][WINDOW_W/20];
static int tetris_type[][4][4][4]={
	{
		{
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0}
		},{
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1},
			{0,0,0,1}
		},{
			{0,0,0,0},
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1}
		},{
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0},
			{1,0,0,0}
		}
	},{
		{
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0},
			{0,0,0,0}
		},{
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0},
			{0,0,0,0}
		},{
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0},
			{0,0,0,0}
		},{
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,0,0,0}
		}
	},{
		{
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0},
			{0,0,0,0}
		},{
			{0,1,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},{
		{
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		},{
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		},{
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		},{
			{1,1,0,0},
			{1,1,0,0},
			{0,0,0,0},
			{0,0,0,0}
		}
	}, {
		{
			{ 1, 1, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}, {
			{ 0, 0, 1, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		}, {
			{ 0, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 1, 1, 0 },
			{ 0, 0, 0, 0 }
		}, {
			{ 1, 1, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 1, 0, 0, 0 },
			{ 0, 0, 0, 0 }
		}
	}
};
struct tetris_blocks {
	int x;
	int y;
	int blocks_color;
	int blocks_rindex;
	int blocks_type;
}tetris_blocks_old={WINDOW_W/40-2,2,0,0,0},
tetris_blocks_cur={WINDOW_W/40-2,2,0,0,0};

// CtetrisView 构造/析构
void DrawScreenBlocks(CDC* pDC,int line);
CtetrisView::CtetrisView()
{
	// TODO:  在此处添加构造代码
	level = 1;
	level_auto_change = 1;
	score = 0;
	status = 0;
	most_needed = 0;
	memset(screen_array,0,sizeof(screen_array));
}
CtetrisView::~CtetrisView()
{
}

BOOL CtetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}
void DoDrawTetrisBlocks(int cnt,CDC* pDC, int optionmode)
{
	LPRECT lprc = new CRect(0, 0, 0, 0);
	CBrush *pBrush_r = new CBrush(RGB(255, 0, 0));
	CBrush *pBrush = new CBrush(RGB(0, 0, 0));
	
	int i,j;
	int px = tetris_blocks_cur.x;
	int py = tetris_blocks_cur.y;
	int pox = tetris_blocks_old.x;
	int poy = tetris_blocks_old.y;
	for (i=0;i<cnt;i++)
		for(j=0;j<cnt;j++){
			if(optionmode){
				if(tetris_type[tetris_blocks_cur.blocks_type][tetris_blocks_cur.blocks_rindex][i][j])
					SetRect(lprc,(px+j)*20+1, (py+i)*20+1, (px+j+1)*20-1, (py+i+1)*20-1);
					pDC->FillRect(lprc, pBrush_r);
			}else{
				if(tetris_type[tetris_blocks_old.blocks_type][tetris_blocks_old.blocks_rindex][i][j])
					SetRect(lprc,(pox+j)*20+1, (poy+i)*20+1, (pox+j+1)*20-1, (poy+i+1)*20-1); 
					pDC->FillRect(lprc, pBrush);
			}
		}

	delete lprc;
	delete pBrush_r;
	delete pBrush;
}
void DrawTetrisBlocks(CDC* pDC)
{
	switch(tetris_blocks_cur.blocks_type){
	case 0:
		DoDrawTetrisBlocks(4,pDC,1);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		DoDrawTetrisBlocks(3,pDC,1);
		break;
	}
}
void CleanTetrisBlocks(CDC* pDC)
{	
	switch(tetris_blocks_cur.blocks_type){
	case 0:
		DoDrawTetrisBlocks(4,pDC,0);
		break;
	case 1:
	case 2:
	case 3:
	case 4:
		DoDrawTetrisBlocks(3,pDC,0);
		break;
	}
}

void CtetrisView::MyDraw(CDC* pDC)
{
	//clean old blocks
	CleanTetrisBlocks(pDC);
	//draw current blocks
	DrawTetrisBlocks(pDC);
}
void CtetrisView::OnDraw(CDC* pDC)
{
	char str_score[12]="";
	char str_level[12]="";
	_itoa_s(score,str_score,10);
	_itoa_s(level,str_level,10);
	CString str_s(str_score);
	CString str_l(str_level);

	LPRECT lprc = new CRect(0, 0, 0, 0);
	CBrush *pBrush_g = new CBrush(RGB(0, 255, 0));
	CBrush *pBrush_r = new CBrush(RGB(255, 0, 0));
	CBrush *pBrush_b = new CBrush(RGB(0, 0, 255));
	CBrush *pBrush = new CBrush(RGB(0, 0, 0));
	
	SetRect(lprc,0, 0, WINDOW_W, 40);
	pDC->FillRect(lprc, pBrush_g);
	
	SetRect(lprc,0, 40, WINDOW_W, WINDOW_H);
	pDC->FillRect(lprc, pBrush);

	pDC->SetBkMode(TRANSPARENT);
	SetRect(lprc,0, 0, WINDOW_W/4, 40);
	pDC->DrawText(_T("Score:"),lprc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	SetRect(lprc,WINDOW_W/2, 0,WINDOW_W/2+WINDOW_W/4 , 40);
	pDC->DrawText(_T("Level:"),lprc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	SetRect(lprc,WINDOW_W/4, 0, WINDOW_W/2, 40);
	pDC->DrawText(str_s,lprc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	SetRect(lprc,WINDOW_W/2+WINDOW_W/4, 0, WINDOW_W, 40);
	pDC->DrawText(str_l,lprc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	if (status == 1 || status == -1){
		DrawScreenBlocks(pDC, WINDOW_H / 20 - 1);
		DrawTetrisBlocks(pDC);
	}
	else if (status == 0){
		pDC->SetTextColor(RGB(150, 50, 120));
		SetRect(lprc, 0, 200, WINDOW_W, 20);
		pDC->DrawText(_T("Double-click the left mouse button"), lprc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 0, 200 + 24, WINDOW_W, 20);
		pDC->DrawText(_T("to start the game."), lprc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetTextColor(RGB(100, 50, 100));
		SetRect(lprc, 60, 200 + 24 * 5, WINDOW_W, 20);
		pDC->DrawText(_T("Key A: Move LEFT"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 7, WINDOW_W, 20);
		pDC->DrawText(_T("Key D: Move RIGHT"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 9, WINDOW_W, 20);
		pDC->DrawText(_T("Key S: Move DOWN"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 11, WINDOW_W, 20);
		pDC->DrawText(_T("Key W: Move UP"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 13, WINDOW_W, 20);
		pDC->DrawText(_T("Key K/L: Rotate"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 15, WINDOW_W, 20);
		pDC->DrawText(_T("Key I: Pause"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 17, WINDOW_W, 20);
		pDC->DrawText(_T("Key O: Auto Speed"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 19, WINDOW_W, 20);
		pDC->DrawText(_T("VK-UP: Level +"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 21, WINDOW_W, 20);
		pDC->DrawText(_T("VK-DOWN: Level -"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 60, 200 + 24 * 23, WINDOW_W, 20);
		pDC->DrawText(_T("Key SP: Generate Straight"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		pDC->SetTextColor(RGB(150, 50, 120));
		SetRect(lprc, 0, 200 + 24 * 26, WINDOW_W, 20);
		pDC->DrawText(_T("Have the freedom to replace the file"), lprc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 0, 200 + 24 * 27+4, WINDOW_W, 20);
		pDC->DrawText(_T("background.wav with another wav file,"), lprc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SetRect(lprc, 0, 200 + 24 * 28+4, WINDOW_W, 20);
		pDC->DrawText(_T("but do not change the name !"), lprc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	delete pBrush;
	delete pBrush_r;
	delete pBrush_g;
	delete pBrush_b;
	delete lprc;
}
void CtetrisView::CleanScreen(void)
{
	char str_score[12] = "";
	char str_level[12] = "";
	_itoa_s(score, str_score, 10);
	_itoa_s(level, str_level, 10);
	CString str_s(str_score);
	CString str_l(str_level);

	LPRECT lprc = new CRect(0, 0, 0, 0);
	CBrush *pBrush = new CBrush(RGB(0, 0, 0));
	CBrush *pBrush_g = new CBrush(RGB(0, 255, 0));

	CDC *m_pDC = GetDC();

	SetRect(lprc, 0, 0, WINDOW_W, 40);
	m_pDC->FillRect(lprc, pBrush_g);

	SetRect(lprc, 0, 40, WINDOW_W, WINDOW_H);
	m_pDC->FillRect(lprc, pBrush);

	m_pDC->SetBkMode(TRANSPARENT);

	SetRect(lprc, 0, 0, WINDOW_W / 4, 40);
	m_pDC->DrawText(_T("Score:"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	SetRect(lprc, WINDOW_W / 2, 0, WINDOW_W / 2 + WINDOW_W / 4, 40);
	m_pDC->DrawText(_T("Level:"), lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	SetRect(lprc, WINDOW_W / 4, 0, WINDOW_W / 2, 40);
	m_pDC->DrawText(str_s, lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	SetRect(lprc, WINDOW_W / 2 + WINDOW_W / 4, 0, WINDOW_W, 40);
	m_pDC->DrawText(str_l, lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	delete pBrush;
	delete pBrush_g;
	delete lprc;

	ReleaseDC(m_pDC);
}
void CtetrisView::OnStart(void)
{	
	TCHAR path_name[MAX_PATH];
	char path[MAX_PATH];
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];
	ZeroMemory(path_name, MAX_PATH);
	GetModuleFileName(NULL, path_name, MAX_PATH);
	sprintf_s(path, "%S", path_name);
	_splitpath_s(path, drive, dir, fname, ext);
	swprintf(path_name, MAX_PATH, L"%S%S%S", drive, dir, "background.wav");

	if (status==0){//stop-->start
		status = 1;
		score = 0;
		level = 1;
		GenerateBlocks();
		SetTimer(TIMER, 500, NULL);
		CleanScreen();
		if (PathFileExists(path_name))
			PlaySound(TEXT("background.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}
	else if (status==1){//start-->pause
		status = -1;
		KillTimer(TIMER);
		if (PathFileExists(path_name))
			PlaySound(NULL, NULL, SND_FILENAME);
	}
	else if (status==-1){//pause-->start
		status = 1;
		SetTimer(TIMER, 500/level, NULL);
		if (PathFileExists(path_name))
			PlaySound(TEXT("background.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	}
}
// return 1 if the move option is vaild, else return 0
int MoveCheck(void)
{	
	int i,j;
	int t = tetris_blocks_cur.blocks_type;
	int r = tetris_blocks_cur.blocks_rindex;
	int px = tetris_blocks_cur.x;
	int py = tetris_blocks_cur.y;
	
	if(px >=-3 && px <= (WINDOW_W/20-1) && py <= (WINDOW_H/20-1)){
		for(j=0;j<4;j++)
			for(i=0;i<4;i++){
				if(tetris_type[t][r][j][i]==1){
					if((px+i)<0||(px+i)>(WINDOW_W/20-1)||(py+j)>(WINDOW_H/20-1))
						return 0;
					if(screen_array[py+j][px+i]==1){
						return 0;
					}
				}
			}
		return 1;
	}else{
		return 0;
	}
}
void CtetrisView::OnMoveLeft(void)
{
	if (status==1){
		memcpy(&tetris_blocks_old,&tetris_blocks_cur,sizeof(tetris_blocks_cur));
		tetris_blocks_cur.x--;
		if (MoveCheck()){
			CDC *m_pDC = GetDC();
			MyDraw(m_pDC);
			ReleaseDC(m_pDC);
		}else{
			tetris_blocks_cur.x++;
		}
	}
}
void CtetrisView::OnMoveRight(void)
{
	if (status==1){
		memcpy(&tetris_blocks_old,&tetris_blocks_cur,sizeof(tetris_blocks_cur));
		tetris_blocks_cur.x++;
		if (MoveCheck()){
			CDC *m_pDC = GetDC();
			MyDraw(m_pDC);
			ReleaseDC(m_pDC);
		}else{
			tetris_blocks_cur.x--;
		}
	}
}
void CtetrisView::OnMoveDown(void)
{
	int i,j;
	int t = tetris_blocks_cur.blocks_type;
	int r = tetris_blocks_cur.blocks_rindex;
	int px = tetris_blocks_cur.x;
	int py = tetris_blocks_cur.y;

	if (status==1){
		memcpy(&tetris_blocks_old,&tetris_blocks_cur,sizeof(tetris_blocks_cur));
		tetris_blocks_cur.y++;
		if(MoveCheck()){
			CDC *m_pDC = GetDC();
			MyDraw(m_pDC);
			ReleaseDC(m_pDC);
		}else{
			tetris_blocks_cur.y--;
			for(j=0;j<4;j++)
				for(i=0;i<4;i++)
					if(tetris_type[t][r][j][i]==1)
						screen_array[py+j][px+i] = tetris_type[t][r][j][i];
			OnCheckScore();
			GenerateBlocks();
		}
	}
}
void CtetrisView::OnMoveUp(void)
{
	if (status==1){
		memcpy(&tetris_blocks_old, &tetris_blocks_cur, sizeof(tetris_blocks_cur));
		tetris_blocks_cur.y -= 2;

		if (tetris_blocks_cur.y > 2){
			if (MoveCheck()){
				CDC *m_pDC = GetDC();
				MyDraw(m_pDC);
				ReleaseDC(m_pDC);
			}
		}
		else{
			tetris_blocks_cur.y += 2;
		}
	}
}
void CtetrisView::OnRotate(int r)
{
	int tmp = tetris_blocks_cur.blocks_rindex;
	if(status==1){
		memcpy(&tetris_blocks_old,&tetris_blocks_cur,sizeof(tetris_blocks_cur));
		tetris_blocks_cur.blocks_rindex += r;
		if (tetris_blocks_cur.blocks_rindex > 3)
			tetris_blocks_cur.blocks_rindex = 0;
		else if (tetris_blocks_cur.blocks_rindex < 0){
			tetris_blocks_cur.blocks_rindex = 3;
		}

		if(MoveCheck()){
			CDC *m_pDC = GetDC();
			MyDraw(m_pDC);
			ReleaseDC(m_pDC);
		}else{
			tetris_blocks_cur.blocks_rindex = tmp;
		}
	}
}
void DrawScreenBlocks(CDC* pDC,int line)
{
	LPRECT lprc = new CRect(0, 0, 0, 0);
	CBrush *pBrush_r = new CBrush(RGB(255, 0, 0));
	CBrush *pBrush = new CBrush(RGB(0, 0, 0));

	int i,j;
	for (i=2;i<=line;i++){
		for(j=0;j<WINDOW_W/20;j++){
			SetRect(lprc,j*20+1, i*20+1, (j+1)*20-1, (i+1)*20-1);
			if(screen_array[i][j])
				pDC->FillRect(lprc,pBrush_r);
			else
				pDC->FillRect(lprc,pBrush);
		}
	}
	delete lprc;
	delete pBrush_r;
	delete pBrush;
}

void CtetrisView::OnShowScore(int line)
{
	LPRECT lprc = new CRect(0, 0, 0, 0);
	CBrush *pBrush_g = new CBrush(RGB(0, 255, 0));
	CBrush *pBrush = new CBrush(RGB(0, 0, 0));
	int i;
	
	char str_score[12]="";
	char str_level[12]="";
	_itoa_s(score,str_score,10);
	_itoa_s(level,str_level,10);
	CString str_s(str_score);
	CString str_l(str_level);

	CDC *m_pDC = GetDC();
	m_pDC->SetBkMode(TRANSPARENT);
	SetRect(lprc,WINDOW_W/4, 0, WINDOW_W/2, 40);
	m_pDC->FillRect(lprc,pBrush_g);
	m_pDC->DrawText(str_s,lprc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	SetRect(lprc,WINDOW_W/2+WINDOW_W/4, 0, WINDOW_W, 40);
	m_pDC->FillRect(lprc,pBrush_g);
	m_pDC->DrawText(str_l,lprc,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

	for(i=0;i<WINDOW_W/20;i++){
		SetRect(lprc,i*20+1, line*20+1, (i+1)*20-1, (line+1)*20 -1);
		m_pDC->FillRect(lprc,pBrush);
		Sleep(10);
	}

	DrawScreenBlocks(m_pDC,line);

	ReleaseDC(m_pDC);
	
	delete lprc;
	delete pBrush_g;
	delete pBrush;
}
void CtetrisView::OnCheckScore(void)
{
	int i,j,k,l;
	for(i=WINDOW_H/20-1;i>=2;i--){
		for(j=0;j<WINDOW_W/20;j++){
			if(screen_array[i][j]==0)
				break;
			if(j==(WINDOW_W/20-1)){ 
				for(k=i;k>=2;k--)
					for(l=0;l<WINDOW_W/20;l++)
						screen_array[k][l]= screen_array[k-1][l];
				score++; 
				if((score%SCORESTEP)==0){
					if (level <= LEVEL_MAX && level_auto_change==1){
						level++;
						SetTimer(TIMER,500/level,NULL);
					}
				}
				OnShowScore(i);
				i++;
			}
		}
	}
}
void CtetrisView::GenerateBlocks(void)
{
	tetris_blocks_cur.x = WINDOW_W/40-2;
	tetris_blocks_cur.y = 2;
	tetris_blocks_cur.blocks_color = 0;

	if (most_needed){
		most_needed = 0;
		tetris_blocks_cur.blocks_type = 0;
		tetris_blocks_cur.blocks_rindex = 0;
	}
	else{
		tetris_blocks_cur.blocks_type = rand() % 5;
		tetris_blocks_cur.blocks_rindex = rand() % 4;
	}

	memcpy(&tetris_blocks_old,&tetris_blocks_cur,sizeof(tetris_blocks_cur));
	if(MoveCheck()){
		CDC *m_pDC = GetDC();
		MyDraw(m_pDC);
		ReleaseDC(m_pDC);
	}else{
		status = 0;
		KillTimer(TIMER);
		CleanScreen();
		most_needed = 0;
		memset(screen_array, 0, sizeof(screen_array));
		CDC *m_pDC = GetDC();
		LPRECT lprc = new CRect(0, 40, WINDOW_W, WINDOW_H);
		CBrush *pBrush_r = new CBrush(RGB(255, 0, 0));
		m_pDC->SetBkMode(TRANSPARENT);
		m_pDC->SetTextColor(RGB(250, 20, 20));
		m_pDC->DrawText(_T("GAME OVER"), lprc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		delete lprc;
		delete pBrush_r;
		ReleaseDC(m_pDC);
	}
}


#ifdef _DEBUG
void CtetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CtetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtetrisDoc* CtetrisView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtetrisDoc)));
	return (CtetrisDoc*)m_pDocument;
}
#endif //_DEBUG



void CtetrisView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	switch (nChar)
	{
	case 'a':
	case 'A':
		OnMoveLeft();
		break;

	case 's':
	case 'S':
		OnMoveDown();
		break;

	case 'd':
	case 'D':
		OnMoveRight();
		break;

	case 'l':
	case 'L':
		OnRotate(1);
		break;
	case 'k':
	case 'K':
		OnRotate(-1);
		break;
	case 'w':
	case 'W':
		OnMoveUp();
		break;
	case 'i':
	case 'I':
		OnStart();
		break;
	case 'o':
	case 'O':
		level_auto_change *= -1;
		break;
	case ' ':
		most_needed = 1;
		break;
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CtetrisView::OnTimer(UINT_PTR nIDEvent)
{
	OnMoveDown();
	CView::OnTimer(nIDEvent);
}


void CtetrisView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	OnStart();
	CView::OnLButtonDblClk(nFlags, point);
}


void CtetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LPRECT lprc = new CRect(0, 0, 0, 0);
	CBrush *pBrush_g = new CBrush(RGB(0, 255, 0));
	char str_level[12] = "";

	CDC *m_pDC = GetDC();
	m_pDC->SetBkMode(TRANSPARENT);

	switch (nChar)
	{
	case VK_UP:
		if (level < LEVEL_MAX){
			level++;
			SetTimer(TIMER, 500 / level, NULL);
			_itoa_s(level, str_level, 10);
			CString str_l(str_level);
			SetRect(lprc, WINDOW_W / 2 + WINDOW_W / 4, 0, WINDOW_W, 40);
			m_pDC->FillRect(lprc, pBrush_g);
			m_pDC->DrawText(str_l, lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
		break;
	case VK_DOWN:
		if (level > 1){
			level--;
			SetTimer(TIMER, 500 / level, NULL);
			_itoa_s(level, str_level, 10);
			CString str_l(str_level);
			SetRect(lprc, WINDOW_W / 2 + WINDOW_W / 4, 0, WINDOW_W, 40);
			m_pDC->FillRect(lprc, pBrush_g);
			m_pDC->DrawText(str_l, lprc, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		}
		break;
	}

	delete lprc;
	delete pBrush_g;
	ReleaseDC(m_pDC);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
