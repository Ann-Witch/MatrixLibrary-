#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <sstream>

using namespace std;

const int maxnum = 800; 
const char nm[15] = "D:\\Bufer1.dat";
const char nm2[15] = "D:\\Bufer2.dat";
const char nm3[15] = "D:\\Bufer3.dat";

template <class T> class EXPORTABLE_CLASS Provider;
class EXPORTABLE_CLASS Error;

template <class T> class EXPORTABLE_CLASS Matrix
{
protected:
	int n, m;

public:
	void GetSize (int &n1, int &m1) {n1 = n; m1 = m;}
	virtual T GetElem (int i, int j) = 0;
	virtual void SetElem (int i, int j, T a) = 0;
};

template <class T> class EXPORTABLE_CLASS SimpleM: public Matrix<T>
{
	Provider<T>* p;
	void CheckSize (); 
	
public:
	void MakeMatr (int n1, int m1, Provider<T>* p1); 
	T GetElem (int i, int j); 
	void SetElem (int i, int j, T a); 
	T Norm1(); 
	void InvM();
	void operator += (SimpleM<T>& M); 
	void operator *= (SimpleM<T>& M); 
	void operator *= (T a); 
	SimpleM<T>& operator = (SimpleM<T>& M);
};

template <class T> class EXPORTABLE_CLASS BlockM: public Matrix<T>
{
	int k;
	SimpleM<T> *F, *D, *E;
	T GetElem (int i, int j) {return 1;}
	void SetElem (int i, int j, T a) {}
public:
	void MakeMatr (int k1, int n1, int m1);
	void GetParams (int &k1, int &m1, int &n1);
	void SetBlock (int diag, int ind, SimpleM<T>& M);
    void GetBlock (int diag, int ind, SimpleM<T>& M);
};

template <class T> class EXPORTABLE_CLASS Provider
{
public:
	T** A;
	int bi, bj, na, ma, nmatr, mmatr;

	virtual void Clear() = 0;
	virtual void GetMatr() = 0;
	virtual void SetMatr() = 0;
	virtual void SetSize(int n, int m, int nm, int mm) = 0;

};

template <class T> class EXPORTABLE_CLASS FileP: public Provider<T>
{
	char* fname;
	FILE *fin;
	long posin, posout; 

public:
	void Clear ();
	void SetFileName (const char* s1); 
	void SetSize (int n, int m, int nm, int mm); 
	void GetMatr (); 
	void SetMatr (); 
};

class EXPORTABLE_CLASS Error
{
};

template <class T> class EXPORTABLE_CLASS SimpleMethod
{
public:
	virtual void methodS (SimpleM<T>M, SimpleM<T>b, SimpleM<T>x) = 0;
};

template <class T> class EXPORTABLE_CLASS SimpleLU : public SimpleMethod<T>
{
public:
	void methodS (SimpleM<T>M, SimpleM<T>b, SimpleM<T>x);
};

template <class T> class EXPORTABLE_CLASS BlockMethod
{
public:
	virtual void methodB (BlockM<T>m, SimpleM<T>*b, SimpleM<T>*x, SimpleMethod<T>*met)=0;
};

template <class T> class EXPORTABLE_CLASS Reduction : public BlockMethod<T>
{
	void Red (SimpleM<T>*f, SimpleM<T>*d, SimpleM<T>**b, int q, int k);
public:
	void methodB (BlockM<T>m, SimpleM<T>*b, SimpleM<T>*x, SimpleMethod<T>*met);
};

template <class T> class EXPORTABLE_CLASS BlockLU : public BlockMethod<T>
{
public:
	void methodB (BlockM<T>m, SimpleM<T>*b, SimpleM<T>*x, SimpleMethod<T>*met);
};







