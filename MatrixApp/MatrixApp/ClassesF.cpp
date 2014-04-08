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

	SimpleM<T> C;
	FileP<T> p1;
	char ch [100];
	strcpy(ch,nm);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			C.SetElem(i,j,GetElem(i,j));
	p->Clear();

    //вычисление матрицы C=A+B
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			a = C.GetElem(i,j);
			b = M.GetElem(i,j);
			c = a+b;
			SetElem(i,j,c);
		}
	return;
}

template <class T> void SimpleM<T> :: operator *= (T a)
{
	T c, b;

	SimpleM<T> C;
	FileP<T> p1;
	char ch [100];
	strcpy(ch,nm);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			C.SetElem(i,j,GetElem(i,j));
	p->Clear();

	//вычисление матрицы X=A*k
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			b = C.GetElem(i,j);
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
	for (int i = 0; i<C.n; i++)
		for (int j = 0; j<C.m; j++)
			C.SetElem(i,j,GetElem(i,j));
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

	p->Clear();
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

template <class T> void SimpleM<T> :: SwapColumns (int col1, int col2)
{
	if ((col1 >= m)||(col2 >= m))
	{
		throw Error();
	}

	SimpleM<T> C;
	FileP<T> p1;
	char ch [100];
	strcpy(ch,nm);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<C.n; i++)
		for (int j = 0; j<C.m; j++)
			C.SetElem(i,j,GetElem(i,j));
	p->Clear();

	T a, b;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			a = C.GetElem(i,col1);
			b = C.GetElem(i,col2);
			if (j == col1)
				SetElem(i,j,b);
			else
				if (j == col2)
					SetElem(i,j,a);
				else
					SetElem(i,j,C.GetElem(i,j));
		}
}

template <class T> void SimpleM<T> :: SwapRows (int row1, int row2)
{
	if ((row1 >= n)||(row2 >= n))
	{
		throw Error();
	}

	SimpleM<T> C;
	FileP<T> p1;
	char ch [100];
	strcpy(ch,nm);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<C.n; i++)
		for (int j = 0; j<C.m; j++)
			C.SetElem(i,j,GetElem(i,j));
	p->Clear();

	T a, b;

	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			a = C.GetElem(row1,j);
			b = C.GetElem(row2,j);
			if (i == row1)
				SetElem(i,j,b);
			else
				if (i == row2)
					SetElem(i,j,a);
				else
					SetElem(i,j,C.GetElem(i,j));
		}
}

template <class T> double SimpleM<T> :: Det()
{
	if (n != m)
	{
		throw Error();
	}

	SimpleM<double> C;
	FileP<double> p1;
	char ch [100];
	strcpy(ch,nm2);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			C.SetElem(i,j,(double)GetElem(i,j));
	
    double det = 1.0;
	int sign = +1;
	for(int i = 0; i < n; ++i) // двигаемся вдоль главной диагонали
	{
		//поиск ненулевого элемента (i,i, n,n)-матрицы
		int x1 = 0, y1 = 0; //"координаты" ненулевого эл-та
		bool f = false; //успех в поиске ненулевого элемента

		for(int x = i; x < n; ++x)
			for(int y = i; y < n; ++y)
				if(!f && C.GetElem(x,y))
				{
					x1 = x;
					y1 = y;
					f = true;
				}

		if(!f) //нет ненулевого эл-та
		{
			det = 0.0;
			break;
		}

		if(x1 != i)
		{
			C.SwapColumns(i, x1);
			sign = -sign;
		}

		if(y1 != i)
		{
			C.SwapRows(i, y1);
			sign = -sign;
		}

		//сейчас matr[i][i] != 0 
		det *= C.GetElem(i,i);
		for(int x = i+1; x <n; x++)
		{
			double a = C.GetElem(x,i);
			a /= C.GetElem(i,i);
			C.SetElem(x,i,a);
		}

		//сейчас matr[i][i] == 1;
		for (int y = i+1; y < n; ++y)
			for (int x = i+1; x <n; x++)
			{
				double a = C.GetElem(x,y);
				a -= C.GetElem(x,i)*C.GetElem(i,y);
				C.SetElem(x,y,a);
			}	
	}
	det *= sign;

	return det;
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
	strcpy(ch,nm2);
	p1.SetFileName(ch);
	p1.Clear();
	C.MakeMatr(n,m,&p1);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			C.SetElem(i,j,(double)GetElem(i,j));
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
	F1.open(fin,ios::out);
	F1.close();
	posin = 0; 
	posout = 0;
	na = ma = -1;
	
}
template <class T> void FileP<T> :: SetFileName (char* s1)
{
	fin = new char [100]; 
	strcpy(fin, s1);
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
	F1.open(fin, ios::in|ios::out);
	if (streamoff(posin) == -1 && bi >= nmatr)
	{
		F1.clear();
		posin = 0;
		bi = 0;
		bj = 0;
	}
	F1.seekg(posin, ios::beg);

	for (int i = 0; i<na && !F1.eof(); i++)
	{
		for (int j = 0; j<ma && !F1.eof(); j++)
		{
			F1>>A[i][j];
		}
	}

	posin = F1.tellg();

	F1.close();
}

template <class T> void FileP<T> :: SetMatr ()
{
	stringstream ss;
	F1.open(fin, ios::in|ios::out);
	F1.seekp(posout, ios::beg); 

	for (int i = 0; i<na && !F1.eof(); i++)
	{
		for (int j = 0; j<ma && !F1.eof(); j++)
		{
			if (A[i][j] <= -842150451)
				break;
			F1 << A[i][j] << " ";
		}
	}

	posout = F1.tellp();

	if (posin.seekpos() == 0 && bi+na>= nmatr)
	{
		F1.clear();
		posout = 0;
	}

	F1.close();
}



