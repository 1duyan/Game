
// SnakeView.cpp : CSnakeView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif

#include "SnakeDoc.h"
#include "SnakeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSnakeView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_32771, &CSnakeView::OnStart)
	ON_COMMAND(ID_32772, &CSnakeView::OnPause)
	ON_COMMAND(ID_32773, &CSnakeView::OnContinue)
	ON_COMMAND(ID_32774, &CSnakeView::OnExit)
	ON_WM_KEYDOWN()
//	ON_WM_TIMER()
ON_WM_TIMER()
END_MESSAGE_MAP()

// CSnakeView 构造/析构

CSnakeView::CSnakeView()
{
	// TODO: 在此处添加构造代码

}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSnakeView 绘制

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//用画刷画一个背景
	CBrush backBrush(RGB(0, 0, 0));
	CBrush *pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);//得到一个能够完整包含当前可见区域的最小矩形
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);//把一个对象选入指定的设备描述表
	pDC->Rectangle(19, 19, 501, 501);
	Init();//画三个矩形
	// TODO: 在此处为本机数据添加绘制代码
}


// CSnakeView 打印


void CSnakeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CSnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CSnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CSnakeView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSnakeView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSnakeView 诊断

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSnakeView 消息处理程序


void CSnakeView::OnStart()
{
	SetTimer(1, 3000, NULL);
	AfxMessageBox(_T("3秒后开始游戏"));
	// TODO: 在此添加命令处理程序代码
}


void CSnakeView::OnPause()
{
	KillTimer(1);
	AfxMessageBox(_T("暂停游戏"));
	// TODO: 在此添加命令处理程序代码
}


void CSnakeView::OnContinue()
{
	SetTimer(1, 500, NULL);
	// TODO: 在此添加命令处理程序代码
}


void CSnakeView::OnExit()
{
	AfxMessageBox(_T("退出游戏"));
	exit(0);
	// TODO: 在此添加命令处理程序代码
}


void CSnakeView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	snake[0].x = 10;
	snake[0].y = 10;
	snake[1].x = 11;
	snake[1].y = 10;
	snake[2].x = 12;
	snake[2].y = 10;
	snake[0].direct = 3;
	snake[0].len = 3;
	food.isfood = 1;
	// TODO: 在此添加专用代码和/或调用基类
}


void CSnakeView::Init()
{
	CDC *pDC = GetDC();
	CBrush DrawBrush = (RGB(0, 100, 10));//画刷
	//画出贪吃蛇的三个节点
	for(int i=0;i<snake[0].len;i++)
		pDC->Rectangle(snake[i].x * 10, snake[i].y * 10, (snake[i].x + 1) * 10, (snake[i].y + 1) * 10);
	pDC->SelectObject(DrawBrush);//把对象画刷选入到设备描述表中
}


void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_UP:if (snake[0].direct != 2) snake[0].direct = 1; break;
	case VK_DOWN:if (snake[0].direct != 1) snake[0].direct = 2; break;
	case VK_LEFT:if (snake[0].direct != 4) snake[0].direct = 3; break;
	case VK_RIGHT:if (snake[0].direct != 3) snake[0].direct = 4; break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CSnakeView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDC *pDC = GetDC();
	CString score;
	if (snake[0].len == 2) SetTimer(1, 370, NULL);
	if (snake[0].len == 3) SetTimer(1, 270, NULL);
	if (snake[0].len == 6) SetTimer(1, 200, NULL);
	if (snake[0].len == 9) SetTimer(1, 100, NULL);
	score.Format(_T("游戏结束\n得分：%d"), (snake[0].len-3) * 1);
	//撞界判断
	if (snake[0].x * 10 < 29 || snake[0].y * 10 < 29 || snake[0].x * 10 >482 || snake[0].y*10 >482)
	{
		KillTimer(1);
		AfxMessageBox(score);
	}
	//蛇身相撞
	if (snake[0].len>3)
		for (int sn = snake[0].len - 1; sn > 0; sn--)
		{
			if (snake[0].x * 10 == snake[sn].x * 10 && snake[0].y * 10 == snake[sn].y * 10)
			{
				KillTimer(1);
				AfxMessageBox(score);
			}
		}
	pDC->SelectStockObject(WHITE_PEN);
	pDC->Rectangle(snake[snake[0].len - 1].x * 10, snake[snake[0].len - 1].y * 10, (snake[snake[0].len - 1].x + 1) * 10, (snake[snake[0].len - 1].y + 1) * 10);
	for (int i = snake[0].len - 1; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
	//行走方向判断
	if (snake[0].direct == 1) snake[0].y--;
	if (snake[0].direct == 2) snake[0].y++;
	if (snake[0].direct == 3) snake[0].x--;
	if (snake[0].direct == 4) snake[0].x++;
	pDC->SelectStockObject(BLACK_PEN);
	CBrush DrawBrush = (RGB(0,100,0));
	CBrush *Drawbrush = pDC->SelectObject(&DrawBrush);
	pDC->Rectangle(snake[0].x * 10, snake[0].y * 10, (snake[0].x + 1) * 10, (snake[0].y + 1) * 10);
	pDC->SelectObject(DrawBrush);
	//判断吃食物条件,撞到就吃
	if (snake[0].x * 10 == food.x * 10 && snake[0].y * 10 == food.y * 10)
	{
		snake[0].len++;
		food.isfood = 1;
		snake[snake[0].len - 1].x = snake[snake[0].len - 2].x;
		snake[snake[0].len - 1].y = snake[snake[0].len - 2].y;
	}
	//如果食物被吃了就生成
	if (food.isfood == 1)
	{
		srand((unsigned)time(NULL));
		do
		{
			for(int isfo=snake[0].len-1;isfo>=0;isfo--)
				if (snake[0].x * 10 == snake[isfo].x * 10 && snake[0].y * 10 == snake[isfo].y * 10)
				{
					food.x = (rand()%482)/10*10;
					food.y = (rand()%5482)/10*10;
				}
		} while (food.x * 10 < 30 || food.y * 10 < 30 || food.x * 10 > 480 || food.y * 10 > 480);
		pDC->Rectangle(food.x * 10, food.y * 10, (food.x + 1) * 10, (food.y + 1) * 10);
		food.isfood = 0;
	}
	CView::OnTimer(nIDEvent);
}
