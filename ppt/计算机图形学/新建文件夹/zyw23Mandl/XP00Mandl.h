// XP00Mandl.h : main header file for the XP00MANDL application
//

#if !defined(AFX_XP00MANDL_H__687A9311_E86D_4DFB_8B13_6116DE8B4B83__INCLUDED_)
#define AFX_XP00MANDL_H__687A9311_E86D_4DFB_8B13_6116DE8B4B83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlApp:
// See XP00Mandl.cpp for the implementation of this class
//

class CXP00MandlApp : public CWinApp
{
public:
	CXP00MandlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXP00MandlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CXP00MandlApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XP00MANDL_H__687A9311_E86D_4DFB_8B13_6116DE8B4B83__INCLUDED_)
