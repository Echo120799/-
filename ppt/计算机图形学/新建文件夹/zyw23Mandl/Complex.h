// Complex.h: interface for the CComplex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEX_H__89FC24BD_9FA0_4114_874E_BDAADEAE5260__INCLUDED_)
#define AFX_COMPLEX_H__89FC24BD_9FA0_4114_874E_BDAADEAE5260__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComplex  
{
public:
	CComplex();
	CComplex(float real,float imag) { this->real=real;  this->imag=imag; }
	CComplex(CComplex& ob) { real=ob.real;  imag=ob.imag; }
	virtual ~CComplex();
	CComplex operator +(CComplex& ob) const; 
	CComplex operator -(CComplex& ob) const; 
	CComplex operator *(CComplex& ob) const; 
public:
	float real, imag;
};

#endif // !defined(AFX_COMPLEX_H__89FC24BD_9FA0_4114_874E_BDAADEAE5260__INCLUDED_)
