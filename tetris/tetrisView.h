
// tetrisView.h : CtetrisView 类的接口
//

#pragma once 
class CtetrisView : public CView
{
protected: // 仅从序列化创建
	CtetrisView();
	DECLARE_DYNCREATE(CtetrisView)

// 特性
public:
	CtetrisDoc* GetDocument() const;

// 操作
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
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void MyDraw(CDC* pDC);
protected:

// 实现
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
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // tetrisView.cpp 中的调试版本
inline CtetrisDoc* CtetrisView::GetDocument() const
   { return reinterpret_cast<CtetrisDoc*>(m_pDocument); }
#endif

