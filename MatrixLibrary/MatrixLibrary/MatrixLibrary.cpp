// MatrixLibrary.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"

 #pragma warning(disable : 4996)

#define EXPORTABLE_CLASS __declspec(dllexport)
#include "MatrixLibrary.h"

// функции класса SimpleM
template <class T> void SimpleM<T> :: MakeMatr (int n1, int m1, Provider<T>* p1)
{
	n = n1;
	m = m1;
	p = p1;
}

template <class T> void SimpleM<T> :: CheckSize()
{
	int nbuf;

	if (n*m*sizeof(T) <= maxnum*sizeof(double))
		p->SetSize(n,m,n,m);
	else
		for (int i = 1; ; i++)
		{
			nbuf = n/i;
			if (nbuf*m*sizeof(T) <= maxnum*sizeof(double))
			{
				p->SetSize(nbuf,m,n,m);
				break;
			}
		}
}

template <class T> T SimpleM<T> :: GetElem (int i, int j)
{
	if (i>=n || j>=m)
		throw Error();

	if (p->ma == -1 || p->na == -1)
	{
		CheckSize();
		p->GetMatr();
	}

	check:
	if ((p->bi<=i)&&(i<=p->bi+p->na-1)&&(p->bj<=j)&&(j<p->ma))
		return p->A[i-p->bi][j-p->bj];
	else
	{
		p->SetMatr();
		p->GetMatr();
		goto check;
	}
}

template <class T> void SimpleM<T> :: SetElem (int i, int j, T a)
{
	if (i>=n || j>=m)
		throw Error();

	if (p->ma == -1 || p->na == -1)
	{
		CheckSize();
		p->GetMatr();
	}

	check:
	if ((p->bi<=i)&&(i<=p->bi+p->na-1)&&(p->bj<=j)&&(j<p->ma))
	{
		p->A[i-p->bi][j-p->bj] = a;
		return;
	}
	else
	{
		p->SetMatr();
		p->GetMatr();
		goto check;
	}
}

template <class T> void SimpleM<T> :: operator += (SimpleM<T>& M)
{
	T a, b, c;

	if ((n != M.n)||(m != M.m)) 
	{
		throw Error();
	}

    //вычисление матрицы C=A+B
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			a = GetElem(i,j);
			b = M.GetElem(i,j);
			c = a+b;
			SetElem(i,j,c);
		}
	return;
}

template <class T> void SimpleM<T> :: operator *= (T a)
{
	T c, b;

	//вычисление матрицы X=A*k
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			b = GetElem(i,j);
			c = a*b;
			SetElem(i,j,c);
		}

	return;
}

template <class T> void SimpleM<T> :: operator *= (SimpleM<T>& M)
{
	if (m != M.n) 
	{
		throw Error();
	}

	T a, b, c;

	SimpleM<T> C;
	FileP<T> p1;
	char ch [100];
	strcpy(ch,nm);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	C = *this;
	p->Clear();
	m = M.m;

	//умножение матриц A и B
	for (int i=0; i<n; i++)
		for (int j=0; j<M.m; j++)
		{
	//цикл для умножения i-й строки матрицы А на j-й столбец матрицы В
		c = 0;
		for (int k=0; k<M.n; k++)
		{
			a = C.GetElem(i,k);
			b = M.GetElem(k,j);
			c = c + a*b;
		}
		SetElem(i,j,c);
		}

	return;
}

template <class T> SimpleM<T>& SimpleM<T> :: operator = (SimpleM<T>& M)
{
	if ((n != M.n)||(m != M.m))
	{
		throw Error();
	}

	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			SetElem(i,j,M.GetElem(i,j));

	return *this;
}

template <class T> bool SimpleM<T> :: operator == (SimpleM<T> M)
{
	if (M.n!=n || M.m!=m)
		return false;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			if (GetElem(i,j)!=M.GetElem(i,j))
				return false;
	return true;
}

template <class T> T SimpleM<T> :: Norm1()
{
    T* summ = new T[m]; //Вектор с суммами строк
    for(int i = 0; i < m; i++)
        summ[i] = 0;

    for(int j = 0; j<m; j++)
    {
        for(int i = 0; i<n; i++)
        {
            summ[j] += abs(GetElem(i,j));
        }
    }
    T max = summ[0];
    for(int j = 0; j<m; j++)
    {
        if(summ[j] > max) max = summ[j];
    }

    return max;
}

template <class T> void SimpleM<T> :: InvM()
{
	if (n != m)
	{
		throw Error();
	}

	SimpleM<double> C;
	FileP<double> p1;
	char ch [100];
	strcpy(ch,nm);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			C.SetElem(i,j,GetElem(i,j));
	p->Clear();
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			SetElem(i,j,0);
		SetElem(i,i,1);
	}

	//прямой ход методом Гаусса
		double c, d;
		for(int i = 0; i < n; i++)
		{ 
			c = C.GetElem(i,i);
			for(int j = i+1; j < n; j++)
			{
				d = C.GetElem(j,i);
				for(int k = 0; k < n; k++)
				{
					C.SetElem(j,k,C.GetElem(i,k)*d - C.GetElem(j,k)*c);
					SetElem(j,k,GetElem(i,k)*d - GetElem(j,k)*c);
				}
			}
		}
	
		//обратный ход вычисления элементов обратной матрицы
		double sum;
		for(int i = 0; i < n; i++)
		{
			for(int j = n-1; j >= 0; j--)
			{
				sum = 0;
				for(int k = n-1; k > j; k--)
					sum += C.GetElem(j,k)*GetElem(k,i);
				
				if(C.GetElem(j,j) == 0)  //если придется делить на нуль
				{
					throw Error();
				}
				else	SetElem(j,i,(GetElem(j,i)-sum)/C.GetElem(j,j));
			}
		}
}

// функции класса BlockM
template <class T> void BlockM<T> :: MakeMatr (int k1, int n1, int m1)
{
	stringstream ss;
	string fn;
	FileP<T> *p;

	k = k1; n = n1; m = m1;
	F = new SimpleM<T>[k-1];
	for (int i = 0; i<k-1; i++)
	{
		ss<<i;
		fn = "D:\\fb" + ss.str() + ".dat";
		p = new FileP<T>;
		p->SetFileName(fn.c_str());
		p->Clear();
		F[i].MakeMatr(n,m,p);
		ss.str("");
		ss.clear();
	}
	D = new SimpleM<T>[k];
	for (int i = 0; i<k; i++)
	{
		ss<<i;
		fn = "D:\\db" + ss.str() + ".dat";
		p = new FileP<T>;
		p->SetFileName(fn.c_str());
		p->Clear();
		D[i].MakeMatr(n,m,p);
		ss.str("");
		ss.clear();
	}
	E = new SimpleM<T>[k-1];
	for (int i = 0; i<k-1; i++)
	{
		ss<<i;
		fn = "D:\\eb" + ss.str() + ".dat";
		p = new FileP<T>;
		p->SetFileName(fn.c_str());
		p->Clear();
		E[i].MakeMatr(n,m,p);
		ss.str("");
		ss.clear();
	}
}

template <class T> void BlockM<T> :: SetBlock (int diag, int ind, SimpleM<T>& M)
{
	if (diag == 1)
		F[ind] = M;
	else
		if (diag == 2)
			D[ind] = M;
		else
			if (diag == 3)
				E[ind] = M;
			else
				throw Error();
}

template <class T> void BlockM<T> :: GetBlock (int diag, int ind, SimpleM<T>& M)
{
	if (diag == 1)
		M = F[ind];
	else
		if (diag == 2)
			M = D[ind];
		else
			if (diag == 3)
				M = E[ind];
			else
				throw Error();
}

template <class T> void BlockM<T> :: GetParams(int &k1, int &m1, int &n1)
{
	k1 = k; m1 = m; n1 = n;
}

// функции класса FileP
template <class T> void FileP<T> :: Clear()
{
	fin = fopen(fname, "wb");
	fclose(fin);
	posin = 0; 
	posout = 0;
	na = ma = -1;
	
}
template <class T> void FileP<T> :: SetFileName (const char* s1)
{
	fname = new char [100]; 
	strcpy(fname, s1);
	na = ma = -1;
	posin = posout = 0;
}

template <class T> void FileP<T> :: SetSize (int n, int m, int nm, int mm)
{
	na = n;
	ma = m;
	bi = -1*na;
	bj = -1*ma;
	nmatr = nm;
	mmatr = mm;
}

template <class T> void FileP<T> :: GetMatr ()
{
	A = new T* [na];
	for (int i = 0; i<na; i++)
		A[i] = new T [ma];
	bi+=na;
	bj = 0;
	fin = fopen (fname, "rb");
	if (posin >= nmatr*mmatr*sizeof(T))
	{
		posin = 0;
		bi = 0;
		bj = 0;
	}
	fseek(fin, posin, SEEK_SET);

	for (int i = 0; i<na && !feof(fin); i++)
	{
		for (int j = 0; j<ma; j++) 
		{
			fread (A[i]+j,sizeof(T),1,fin);
			if (A[i][j] <= -842150451)
			{
				fseek(fin,sizeof(T),SEEK_CUR);
			}
		}
	}

	posin = ftell(fin);

	fclose(fin);
}

template <class T> void FileP<T> :: SetMatr ()
{
	bool fl = false;
	fin = fopen(fname, "r+b");
	fseek(fin, posout, SEEK_SET); 

	for (int i = 0; i<na; i++)
	{
		for (int j = 0; j<ma; j++)
		{
			if (A[i][j] <= -842150451)
				break;
			fwrite (A[i]+j,sizeof(T),1,fin);
			posout = ftell(fin);
			if (posout >= nmatr*mmatr*sizeof(T))
			{
				fl = true;
			    break;
			}
		}

		if (fl)
			break;
	}

	if (fl)
	{
		posout = 0;
	}

	fclose(fin);
}

// функции класса SimpleLU
template <class T> void SimpleLU<T> :: methodS (SimpleM<T>M, SimpleM<T>b, SimpleM<T>x)
{
	int n1, m1, n2, m2;
	string fn = "D:\\LUS.dat";
	SimpleM<double> LUS, y;
	FileP<double> *p1;

	p1 = new FileP<double>;
	p1->SetFileName(fn.c_str());
	p1->Clear();
	M.GetSize(n1,m1);
	LUS.MakeMatr(n1,m1,p1);
	if (n1!=m1)
		throw Error();
	b.GetSize(n2,m2);
	if (m2!=1 || n2!=n1)
		throw Error();
	x.GetSize(n2,m2);
	if (m2!=1 || n2!=n1)
		throw Error();
	for (int i = 0; i<n1; i++)
		for (int j = 0; j<m1; j++)
			LUS.SetElem(i,j,M.GetElem(i,j));

	for(int k=0;k<n1;k++)
    {
        for(int i=k+1;i<n1;i++)
        {
			if (LUS.GetElem(k,k) == 0)
				throw Error();
            LUS.SetElem(i,k,LUS.GetElem(i,k)/LUS.GetElem(k,k));    
        }
        for(int i=k+1;i<n1;i++)
        {
            for(int j=k+1;j<n1;j++)
				LUS.SetElem(i,j,LUS.GetElem(i,j)-LUS.GetElem(i,k)*LUS.GetElem(k,j));
        }
	}

	p1 = new FileP<double>;
	fn = "D:\\yLU.dat";
	p1->SetFileName(fn.c_str());
	p1->Clear();
	b.GetSize(n2,m2);
	y.MakeMatr(n2,m2,p1);
	double mu;

	y.SetElem(0,0,b.GetElem(0,0));
	for (int k = 1; k<n2; k++)
	{
		mu = 0;
		for (int i = k-1; i>=0; i--)
		{
			mu+=LUS.GetElem(k,i)*y.GetElem(i,0);
		}
		y.SetElem(k,0,b.GetElem(k,0)-mu);
	}
	
	if (LUS.GetElem(n1-1,m1-1) == 0)
		throw Error();
	x.SetElem(n1-1,0,y.GetElem(n1-1,0)/LUS.GetElem(n1-1,m1-1));
	for (int k = n1-2; k>=0; k--)
	{
		mu = 0;
		for (int i = k+1; i<n1; i++)
		{
			mu+=LUS.GetElem(k,i)*x.GetElem(i,0);
		}
		x.SetElem(k,0,(y.GetElem(k,0)-mu)/LUS.GetElem(k,k));
	}

	remove("D:\\LUS.dat");
	remove("D:\\yLU.dat");
}

// функции класса Reduction
template <class T> void Reduction<T> :: Red (SimpleM<T>*f, SimpleM<T>*d, SimpleM<T>**b, int q, int k)
{
	int r;
	SimpleM<T> C;
	FileP<T> p1;
	char ch [100];
	strcpy(ch,nm2);
	p1.SetFileName(ch);

	for (int i = 1; i<=k-1; i++)
	{
		p1.Clear();
		C.MakeMatr(q,q,&p1);
		C = f[i-1];
		C*=f[i-1];
		f[i] = C;
		C*=2;
		d[i] = C;
		C = d[i-1];
		C*=d[i-1];
		C*=-1;
		d[i]+=C;
		r = pow(2,i);
		for (int j = 1; j<pow(2,k-i); j++)
		{
			p1.Clear();
			C.MakeMatr(q,q,&p1);
			C = f[i-1];
			C*=b[i-1][j*r-r/2-1];
			b[i][j*r-1] = C;
			p1.Clear();
			C.MakeMatr(q,q,&p1);
			C = f[i-1];
			C*= b[i-1][j*r+r/2-1];
			b[i][j*r-1]+=C;
			p1.Clear();
			C.MakeMatr(q,q,&p1);
			C = d[i-1];
			C*=(-1);
			C*=b[i-1][j*r-1];
			b[i][j*r-1]+=C;
		}
	}
}

template <class T> void Reduction<T> :: methodB (BlockM<T>m, SimpleM<T>*b, SimpleM<T>*x, SimpleMethod<T>*met)
{
	int n1, m1, k1, q;
	m.GetParams(k1, m1, n1);
	if (n1!=m1)
		throw Error();
	else
		q = n1;
	int n = pow(2,k1)-1;
	SimpleM<T>*F = new SimpleM<T>[k1], *D = new SimpleM<T>[k1], **B = new SimpleM<T>*[k1]; 
	FileP<T> *p1;
	stringstream ss;
	string fn;

	int r;
	SimpleM<T> C, E;
	FileP<T> p, p2;
	char ch [100];
	strcpy(ch,nm2);
	p.SetFileName(ch);
	p.Clear();
	C.MakeMatr(q,q,&p);
	strcpy(ch,nm3);
	p2.SetFileName(ch);
	p2.Clear();
	E.MakeMatr(q,q,&p2);

	for (int i = 0; i<k1; i++)
	{
		ss<<i;
		fn = "D:\\f" + ss.str() + ".dat";
		p1 = new FileP<T>;
		p1->SetFileName(fn.c_str());
		p1->Clear();
		F[i].MakeMatr(q,q,p1);
		ss.str("");
		ss.clear();
	}
	m.GetBlock(1,0,F[0]);

	for (int i = 0; i<k1; i++)
	{
		ss<<i;
		fn = "D:\\d" + ss.str() + ".dat";
		p1 = new FileP<T>;
		p1->SetFileName(fn.c_str());
		p1->Clear();
		D[i].MakeMatr(q,q,p1);
		ss.str("");
		ss.clear();
	}
	m.GetBlock(2,0,D[0]);

	C = F[0];
	C*=D[0];
	E = D[0];
	E*=F[0];
	if (!(C==E))
		throw Error();

	for (int i = 0; i<k1; i++)
	{
		B[i] = new SimpleM<T>[n];
		for (int j = 0; j<n; j++)
		{
			ss<<i<<j;
		    fn = "D:\\b" + ss.str() + ".dat";
		    p1 = new FileP<T>;
		    p1->SetFileName(fn.c_str());
			p1->Clear();
		    B[i][j].MakeMatr(q,1,p1);
		    ss.str("");
		    ss.clear();
		}
	}
	for (int i = 0; i<n; i++)
		B[0][i] = b[i];

	Red(F,D,B,q,k1);

	int cur = pow (2,k1-1);

	met->methodS(D[k1-1],B[k1-1][cur-1],x[cur-1]);

	for (int i = k1-2; i>=0; i--)
	{
		r = pow(2,i);
		for (int j = 1; j<=pow(2,k1-i-1); j++)
		{
			p.Clear();
			C.MakeMatr(q,q,&p);
			p2.Clear();
	        E.MakeMatr(q,q,&p2);
			if (j==1)
			{
				C = F[i];
				C*=-1;
				C*=x[2*j*r-1];
				C+=B[i][(2*j-1)*r-1];
			}
			else
				if (j==pow(2,k1-i-1))
			    {
					C = F[i];
				    C*=-1;
				    C*=x[(2*j-2)*r-1];
				    C+=B[i][(2*j-1)*r-1];
				}
				else
				{
					C = F[i];
				    C*=-1;
				    C*=x[(2*j-2)*r-1];
					E = F[i];
					E*=-1;
					E*= x[2*j*r-1];
					C+=E;
				    C+=B[i][(2*j-1)*r-1];
			    }

				met->methodS(D[i],C,x[(2*j-1)*r-1]);
		}
	}

	for (int i = 0; i<k1; i++)
	{
		ss<<i;
		fn = "D:\\f" + ss.str() + ".dat";
		remove(fn.c_str());
		fn = "D:\\d" + ss.str() + ".dat";
		remove(fn.c_str());
		ss.str("");
		ss.clear();
		for (int j = 0; j<n; j++)
		{
			ss<<i<<j;
		    fn = "D:\\b" + ss.str() + ".dat";
			remove(fn.c_str());
		    ss.str("");
		    ss.clear();
		}
		ss.str("");
		ss.clear();	
	}
}

template <class T> void BlockLU<T> :: methodB (BlockM<T>m, SimpleM<T>*b, SimpleM<T>*x, SimpleMethod<T>*met)
{
	int n1, m1, k1, q;
	stringstream ss;
	string fn;
	FileP<T> *p1;
	SimpleM<T> *y;
	T a, d, c;
	m.GetParams(k1, m1, n1);
	if (n1!=m1)
		throw Error();
	else
		q = n1;

	SimpleM<T> C;
	FileP<T> p2;
	char ch [100];
	strcpy(ch,nm2);
	p2.SetFileName(ch);
	p2.Clear();
	C.MakeMatr(q,q,&p2);

	m.GetBlock(2,0,C);
	C.InvM();
	a = C.Norm1();
	m.GetBlock(3,0,C);
	d = C.Norm1();
	if (a*d>=1)
		throw Error();
	m.GetBlock(2,k1-1,C);
	C.InvM();
	a = C.Norm1();
	m.GetBlock(1,k1-2,C);
	c = C.Norm1();
	if (a*c>=1)
		throw Error();
	for (int i = 1; i<k1-1; i++)
	{
		m.GetBlock(2,i,C);
		C.InvM();
	    a = C.Norm1();
	    m.GetBlock(3,i,C);
	    d = C.Norm1();
	    m.GetBlock(1,i-1,C);
	    c = C.Norm1();
	    if (a*(d+c)>=1)
			throw Error();
	}

	SimpleM<T>*U = new SimpleM<T>[k1], *L = new SimpleM<T>[k1-1];

	for (int i = 0; i<k1; i++)
	{
		ss<<i;
		fn = "D:\\u" + ss.str() + ".dat";
		p1 = new FileP<T>;
		p1->SetFileName(fn.c_str());
		p1->Clear();
		U[i].MakeMatr(q,q,p1);
		ss.str("");
		ss.clear();
	}

	m.GetBlock(2,0,U[0]);

	for (int i = 0; i<k1-1; i++)
	{
		ss<<i;
		fn = "D:\\l" + ss.str() + ".dat";
		p1 = new FileP<T>;
		p1->SetFileName(fn.c_str());
		p1->Clear();
		L[i].MakeMatr(q,q,p1);
		ss.str("");
		ss.clear();
	}

	for (int i = 1; i<k1; i++)
	{
		m.GetBlock(3,i-1,C);
		L[i-1] = U[i-1];
		L[i-1].InvM();
		L[i-1]*=C;

		m.GetBlock(2,i,U[i]);
		m.GetBlock(1,i-1,C);
		C*=L[i-1];
		C*=-1;
		U[i]+=C;
	}

	y = new SimpleM<T> [k1];
	for (int j = 0; j<k1; j++)
	{
		ss<<j;
		fn = "D:\\yBLU" + ss.str() + ".dat";
		p1 = new FileP<T>;
		p1->SetFileName(fn.c_str());
	    p1->Clear();
		y[j].MakeMatr(q,1,p1);
		ss.str("");
		ss.clear();
    }

	for (int i = 0; i<q; i++)
		y[0].SetElem(i,0,b[0].GetElem(i,0));

	for (int i = 1; i<k1; i++)
	{
		p2.Clear();
	    C.MakeMatr(q,q,&p2);
		C = L[i-1];
		C*=y[i-1];
		C*=-1;
		C+=b[i];
		for (int j = 0; j<q; j++)
			y[i].SetElem(j,0,C.GetElem(j,0));
	}

	met->methodS(U[k1-1],y[k1-1],x[k1-1]);

	for (int i = k1-2; i>=0; i--)
	{
		p2.Clear();
	    C.MakeMatr(q,q,&p2);
		m.GetBlock(1,i,C);
		C*=x[i+1];
		C*=-1;
		C+=y[i];
		met->methodS(U[i],C,x[i]);
	}

	for (int i = 0; i<k1; i++)
	{
		ss<<i;
		fn = "D:\\u" + ss.str() + ".dat";
		remove(fn.c_str());
		fn = "D:\\yBLU" + ss.str() + ".dat";
		remove(fn.c_str());
		ss.str("");
		ss.clear();
	}

	for (int i = 0; i<k1-1; i++)
	{
		ss<<i;
		fn = "D:\\l" + ss.str() + ".dat";
		remove(fn.c_str());
		ss.str("");
		ss.clear();
	}

}

template class Matrix<int>;
template class Matrix<long int>;
template class Matrix<long long int>;
template class Matrix<float>;
template class Matrix<double>;

template class SimpleM<int>;
template class SimpleM<long int>;
template class SimpleM<long long int>;
template class SimpleM<float>;
template class SimpleM<double>;

template class BlockM<int>;
template class BlockM<long int>;
template class BlockM<long long int>;
template class BlockM<float>;
template class BlockM<double>;

template class Provider<int>;
template class Provider<long int>;
template class Provider<long long int>;
template class Provider<float>;
template class Provider<double>;

template class FileP<int>;
template class FileP<long int>;
template class FileP<long long int>;
template class FileP<float>;
template class FileP<double>;

template class SimpleMethod<float>;
template class SimpleMethod<double>;

template class SimpleLU<float>;
template class SimpleLU<double>;

template class BlockMethod<float>;
template class BlockMethod<double>;

template class Reduction<float>;
template class Reduction<double>;

template class BlockLU<float>;
template class BlockLU<double>;





		






	










