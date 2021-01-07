// Complex.cpp: implementation of the CComplex class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XP00Mandl.h"
#include "Complex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComplex::CComplex()
{

}

CComplex::~CComplex()
{

}

CComplex CComplex::operator +(CComplex& ob) const
{
	return CComplex(real+ob.real,imag+ob.imag);
}

CComplex CComplex::operator -(CComplex& ob) const
{
	return CComplex(real-ob.real,imag-ob.imag);
}

CComplex CComplex::operator *(CComplex& ob) const
{
	return CComplex(real*ob.real-imag*ob.imag, real*ob.imag+imag*ob.real);
}

