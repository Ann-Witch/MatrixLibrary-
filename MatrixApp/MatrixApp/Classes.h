#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

template <class T> class Provider;
class Error;

template <class T> class Matrix
{
protected:
	int n, m;

public:
	T Norm1(); //!
	double Det();
	Matrix<T>* InvM();
	Matrix<T>* operator + (Matrix<T>* M); //!
	Matrix<T>* operator * (Matrix<T>* M); //!
	Matrix<T>* operator * (T a); //!
	Matrix<T>* operator = (Matrix<T>* M); //!
	virtual T GetElem (int i, int j) = 0;
	virtual void SetElem (int i, int j, T a) = 0;
};

template <class T> class SimpleM: public Matrix<T>
{
	Provider<T>* p;
public:
	void MakeMatr (int n, int m, Provider<T>* p);
	T GetElem (int i, int j);
	void SetElem (int i, int j, T a);
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
protected:
	T** A;

public:
	void GetMatr() = 0;
	void SetMatr() = 0;

};

template <class T> class FileP: public Provider<T>
{
	char* fin;
	int bi, bj, na, ma;
	ifstream F1;
	ofstream F2;

public:
	void Setfilename (char* s1); //!
	void GetMatr ();
	void SetMatr ();
};

template <class T> class MemoryP: public Provider<T>
{
};

class Error
{
};



