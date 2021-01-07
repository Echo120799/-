// XP00MandlView.cpp : implementation of the CXP00MandlView class
//

#include "stdafx.h"
#include "XP00Mandl.h"
#include "math.h"

#include "XP00MandlDoc.h"
#include "XP00MandlView.h"
#include "Complex.h"
#include "Mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlView

IMPLEMENT_DYNCREATE(CXP00MandlView, CView)

BEGIN_MESSAGE_MAP(CXP00MandlView, CView)
	//{{AFX_MSG_MAP(CXP00MandlView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlView construction/destruction

CXP00MandlView::CXP00MandlView()
{
	// TODO: add construction code here
	m_nWinWidth = 800; // ��ʾ���ڿ��
	m_nWinHeight = 600; // ��ʾ���ڸ߶�
	m_nIterationTimes = 500;  // ���ͼ�ξ�ϸ�̶Ȳ���ʱ�����Ӹ�ֵ

	// Mandlebrot����ȡֵ��Χ����Ҫ�޸����е�ֵ��ʹ������ֻ��ʾ����һ���ֲ�
	m_fXmin=-1;
	m_fXmax=2;
	m_fYmin=0.5;
    m_fYmax=3.5;
}

CXP00MandlView::~CXP00MandlView()
{
}

BOOL CXP00MandlView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlView drawing

void CXP00MandlView::OnDraw(CDC* pDC)
{
	CXP00MandlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
 	DrawMandelbrot(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlView diagnostics

#ifdef _DEBUG
void CXP00MandlView::AssertValid() const
{
	CView::AssertValid();
}

void CXP00MandlView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXP00MandlDoc* CXP00MandlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXP00MandlDoc)));
	return (CXP00MandlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlView message handlers

void CXP00MandlView::DrawMandelbrot(CDC* pDC)
{
  float fThreshold=15.0;  // ������ֵ�����޸ģ�
  float dx=(m_fXmax-m_fXmin)/m_nWinWidth;
  float dy=(m_fYmax-m_fYmin)/m_nWinHeight;
  int n;
  CComplex compC(0,0); // ������
  for(int i=0;i<m_nWinWidth;i++)
  {
	compC.real = m_fXmin+i*dx;// ȡ��ƽ���ϵ��ʵ��
	for(int j=0;j<m_nWinHeight;j++)
	{
		compC.imag = m_fYmin+j*dy; // ȡ��ƽ���ϵ���鲿
		CComplex compZ(0,0);
		for(int n=0;n<m_nIterationTimes;n++)
		{
			compZ = compZ * compZ + compC; // ������ʽ�� Z = Z^2 + C
			if(fabs(compZ.real+compZ.imag) > fThreshold) break;
			COLORREF color = RGB(n * 30, n * 5, n*i*j * 40); // ��ɫ���ã����޸ģ�
			pDC->SetPixel(i, j, color);
		}
   }
  }
}

void CXP00MandlView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString str; //����һ���ַ���
	CStatusBar* pStatus;

	pStatus = (CStatusBar*)AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);//��ȡ״̬������ָ��

	if(pStatus) //�����ȡָ��ɹ�(��Ϊ��)
	{
		if ( point.x <= m_nWinWidth && point.y <= m_nWinHeight )
		{
//			str.Format("x = %3d, y = %3d", point.x, point.y);//������д���ַ���
			float dx=(m_fXmax-m_fXmin)/m_nWinWidth;
			float dy=(m_fYmax-m_fYmin)/m_nWinHeight;
			float x = m_fXmin+point.x*dx; 
			float y = m_fYmin+point.y*dy;
			str.Format("x = %8.4f, y = %8.4f", x, y);//������д���ַ���
			pStatus->SetPaneText(1, str);//���ַ���������ڶ�������
		}
	}

	CView::OnMouseMove(nFlags, point);
}
