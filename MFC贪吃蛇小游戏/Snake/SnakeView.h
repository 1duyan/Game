
// SnakeView.h : CSnakeView 类的接口
//

#pragma once

struct SNAKE
{
	int x, y;
	int len;
	int direct;
};
struct Food
{
	int x;
	int y;
	int isfood;
};
class CSnakeView : public CView
{
protected: // 仅从序列化创建
	CSnakeView();
	DECLARE_DYNCREATE(CSnakeView)

// 特性
public:
	CSnakeDoc* GetDocument() const;
	struct SNAKE snake[50];
	struct Food food;
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSnakeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg void OnExit();
	virtual void OnInitialUpdate();
	void Init();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // SnakeView.cpp 中的调试版本
inline CSnakeDoc* CSnakeView::GetDocument() const
   { return reinterpret_cast<CSnakeDoc*>(m_pDocument); }
#endif

