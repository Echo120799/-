// XP00MandlView.h : interface of the CXP00MandlView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XP00MANDLVIEW_H__A4DFC8A7_3448_4953_B9F4_BE2A4D94B3F9__INCLUDED_)
#define AFX_XP00MANDLVIEW_H__A4DFC8A7_3448_4953_B9F4_BE2A4D94B3F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXP00MandlView : public CView
{
protected: // create from serialization only
	CXP00MandlView();
	DECLARE_DYNCREATE(CXP00MandlView)

// Attributes
public:
	CXP00MandlDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXP00MandlView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXP00MandlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_nWinHeight;
	int m_nWinWidth;
	float m_fXmin, m_fXmax,	m_fYmin, m_fYmax;
	int m_nIterationTimes;

// Generated message map functions
protected:
	//{{AFX_MSG(CXP00MandlView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawMandelbrot(CDC* pDC);
};

#ifndef _DEBUG  // debug version in XP00MandlView.cpp
inline CXP00MandlDoc* CXP00MandlView::GetDocument()
   { return (CXP00MandlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XP00MANDLVIEW_H__A4DFC8A7_3448_4953_B9F4_BE2A4D94B3F9__INCLUDED_)
