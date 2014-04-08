#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <sstream>

using namespace std;

const int maxnum = 800; 
const char nm[14] = "D:\Bufer1.txt";
const char nm2[14] = "D:\Bufer2.txt";

template <class T> class Provider;
class Error;

template <class T> class Matrix
{
protected:
	int n, m;

public:
	virtual T GetElem (int i, int j) = 0;
	virtual void SetElem (int i, int j, T a) = 0;
};

template <class T> class SimpleM: public Matrix<T>
{
	Provider<T>* p;
	void CheckSize (); //!
	
public:
	void MakeMatr (int n1, int m1, Provider<T>* p1); //!
	T GetElem (int i, int j); //!
	void SetElem (int i, int j, T a); //!
	T Norm1(); //!
	double Det(); //!
	void InvM();
	void operator += (SimpleM<T>& M); //!
	void operator *= (SimpleM<T>& M); //!
	void operator *= (T a); //!
	SimpleM<T>& operator = (SimpleM<T>& M);
	void SwapColumns (int col1, int col2); //!
	void SwapRows (int row1, int row2); //!
};

template <class T> class BlockM: public Matrix<T>
{
	int k;
	SimpleM<T>* D, E, F;

public:
	void MakeMatr (int k, int n, int m);
	T GetElem (int i, int j);
	void SetElem (int i, int j, T a);
};

template <class T> class Provider
{
public:
	T** A;
	int bi, bj, na, ma, nmatr, mmatr;

	virtual void Clear() = 0;
	virtual void GetMatr() = 0;
	virtual void SetMatr() = 0;
	virtual void SetSize(int n, int m, int nm, int mm) = 0;

};

template <class T> class FileP: public Provider<T>
{
	char* fin;
	fstream F1;
	streampos posin, posout; 

public:
	void Clear ();
	void SetFileName (char* s1); //!
	void SetSize (int n, int m, int nm, int mm); //!
	void GetMatr (); //!
	void SetMatr (); //!
};

class Error
{
};



