
// SnakeView.cpp : CSnakeView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CSnakeView ����/����

CSnakeView::CSnakeView()
{
	// TODO: �ڴ˴���ӹ������

}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSnakeView ����

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//�û�ˢ��һ������
	CBrush backBrush(RGB(0, 0, 0));
	CBrush *pOldBrush = pDC->SelectObject(&backBrush);
	CRect rect;
	pDC->GetClipBox(&rect);//�õ�һ���ܹ�����������ǰ�ɼ��������С����
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOldBrush);//��һ������ѡ��ָ�����豸������
	pDC->Rectangle(19, 19, 501, 501);
	Init();//����������
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSnakeView ��ӡ


void CSnakeView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CSnakeView ���

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSnakeView ��Ϣ�������


void CSnakeView::OnStart()
{
	SetTimer(1, 3000, NULL);
	AfxMessageBox(_T("3���ʼ��Ϸ"));
	// TODO: �ڴ���������������
}


void CSnakeView::OnPause()
{
	KillTimer(1);
	AfxMessageBox(_T("��ͣ��Ϸ"));
	// TODO: �ڴ���������������
}


void CSnakeView::OnContinue()
{
	SetTimer(1, 500, NULL);
	// TODO: �ڴ���������������
}


void CSnakeView::OnExit()
{
	AfxMessageBox(_T("�˳���Ϸ"));
	exit(0);
	// TODO: �ڴ���������������
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
	// TODO: �ڴ����ר�ô����/����û���
}


void CSnakeView::Init()
{
	CDC *pDC = GetDC();
	CBrush DrawBrush = (RGB(0, 100, 10));//��ˢ
	//����̰���ߵ������ڵ�
	for(int i=0;i<snake[0].len;i++)
		pDC->Rectangle(snake[i].x * 10, snake[i].y * 10, (snake[i].x + 1) * 10, (snake[i].y + 1) * 10);
	pDC->SelectObject(DrawBrush);//�Ѷ���ˢѡ�뵽�豸��������
}


void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC = GetDC();
	CString score;
	if (snake[0].len == 2) SetTimer(1, 370, NULL);
	if (snake[0].len == 3) SetTimer(1, 270, NULL);
	if (snake[0].len == 6) SetTimer(1, 200, NULL);
	if (snake[0].len == 9) SetTimer(1, 100, NULL);
	score.Format(_T("��Ϸ����\n�÷֣�%d"), (snake[0].len-3) * 1);
	//ײ���ж�
	if (snake[0].x * 10 < 29 || snake[0].y * 10 < 29 || snake[0].x * 10 >482 || snake[0].y*10 >482)
	{
		KillTimer(1);
		AfxMessageBox(score);
	}
	//������ײ
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
	//���߷����ж�
	if (snake[0].direct == 1) snake[0].y--;
	if (snake[0].direct == 2) snake[0].y++;
	if (snake[0].direct == 3) snake[0].x--;
	if (snake[0].direct == 4) snake[0].x++;
	pDC->SelectStockObject(BLACK_PEN);
	CBrush DrawBrush = (RGB(0,100,0));
	CBrush *Drawbrush = pDC->SelectObject(&DrawBrush);
	pDC->Rectangle(snake[0].x * 10, snake[0].y * 10, (snake[0].x + 1) * 10, (snake[0].y + 1) * 10);
	pDC->SelectObject(DrawBrush);
	//�жϳ�ʳ������,ײ���ͳ�
	if (snake[0].x * 10 == food.x * 10 && snake[0].y * 10 == food.y * 10)
	{
		snake[0].len++;
		food.isfood = 1;
		snake[snake[0].len - 1].x = snake[snake[0].len - 2].x;
		snake[snake[0].len - 1].y = snake[snake[0].len - 2].y;
	}
	//���ʳ�ﱻ���˾�����
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
