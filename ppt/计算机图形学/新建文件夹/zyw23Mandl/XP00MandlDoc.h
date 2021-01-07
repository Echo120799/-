// XP00MandlDoc.h : interface of the CXP00MandlDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_XP00MANDLDOC_H__A96E40A3_640E_45A2_83EC_5C00F5507612__INCLUDED_)
#define AFX_XP00MANDLDOC_H__A96E40A3_640E_45A2_83EC_5C00F5507612__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CXP00MandlDoc : public CDocument
{
protected: // create from serialization only
	CXP00MandlDoc();
	DECLARE_DYNCREATE(CXP00MandlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXP00MandlDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXP00MandlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CXP00MandlDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XP00MANDLDOC_H__A96E40A3_640E_45A2_83EC_5C00F5507612__INCLUDED_)
