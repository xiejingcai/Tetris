
// tetrisView.h : CtetrisView ��Ľӿ�
//

#pragma once 
class CtetrisView : public CView
{
protected: // �������л�����
	CtetrisView();
	DECLARE_DYNCREATE(CtetrisView)

// ����
public:
	CtetrisDoc* GetDocument() const;

// ����
public:
	void OnStart(void);
	void OnMoveLeft(void);
	void OnMoveRight(void);
	void OnMoveDown(void);
	void OnRotate(int);
	void OnShowScore(int);
	void OnCheckScore(void);
	void GenerateBlocks(void);
	void OnMoveUp(void);
	void CleanScreen(void);
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void MyDraw(CDC* pDC);
protected:

// ʵ��
public:
	virtual ~CtetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// global parameter 
	int level;
	int level_auto_change;
	int score;
	int status;
	int most_needed;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // tetrisView.cpp �еĵ��԰汾
inline CtetrisDoc* CtetrisView::GetDocument() const
   { return reinterpret_cast<CtetrisDoc*>(m_pDocument); }
#endif

