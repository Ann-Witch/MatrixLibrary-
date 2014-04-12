#include "Classes.h"


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

	if (n*m*sizeof(T) <= maxnum*sizeof(int))
		p->SetSize(n,m,n,m);
	else
		for (int i = 1; ; i++)
		{
			nbuf = n/i;
			if (nbuf*m*sizeof(T) <= maxnum*sizeof(int))
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

// функции класса FileP
template <class T> void FileP<T> :: Clear()
{
	fin = fopen(fname, "wb");
	fclose(fin);
	posin = 0; 
	posout = 0;
	na = ma = -1;
	
}
template <class T> void FileP<T> :: SetFileName (char* s1)
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



