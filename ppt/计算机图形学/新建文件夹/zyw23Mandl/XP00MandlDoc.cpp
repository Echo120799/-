// XP00MandlDoc.cpp : implementation of the CXP00MandlDoc class
//

#include "stdafx.h"
#include "XP00Mandl.h"

#include "XP00MandlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlDoc

IMPLEMENT_DYNCREATE(CXP00MandlDoc, CDocument)

BEGIN_MESSAGE_MAP(CXP00MandlDoc, CDocument)
	//{{AFX_MSG_MAP(CXP00MandlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlDoc construction/destruction

CXP00MandlDoc::CXP00MandlDoc()
{
	// TODO: add one-time construction code here

}

CXP00MandlDoc::~CXP00MandlDoc()
{
}

BOOL CXP00MandlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CXP00MandlDoc serialization

void CXP00MandlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlDoc diagnostics

#ifdef _DEBUG
void CXP00MandlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXP00MandlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXP00MandlDoc commands
