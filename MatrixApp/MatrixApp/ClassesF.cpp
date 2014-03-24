#include "Classes.h"

// функции класса Matrix
template <class T> Matrix<T>* Matrix<T> :: operator + (Matrix<T>* M)
{
	Matrix<T>* C = new Marix<T>;
	T a, b, c;

	if ((n != M->n)||(m != M->m)) 
	{
		throw Error();
	}

    //вычисление матрицы C=A+B
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			a = GetElem(i,j);
			b = M->GetElem(i,j);
			c = a+b;
			C->SetElem(i,j,c);
		}
	return C;
}

template <class T> Matrix<T>* Matrix<T> :: operator * (T a)
{
	Matrix<T>* C = new Marix<T>;
	T b, c;

	//вычисление матрицы X=A*k
	for (int i=0; i<n; i++)
		for (int j=0; j<m; j++)
		{
			b = GetElem(i,j);
			c = a*b;
			C->SetElem(i,j,c);
		}

	return C;
}

template <class T> Matrix<T>* Matrix<T> :: operator * (Matrix<T>* M)
{
	if (m != M->n) 
	{
		throw Error();
	}

	T a, b, c;

	Matrix<T>* C = new Marix<T>;
	C->n = n;
	C->m = M->m;
	for (int i = 0; i<C->n; i++)
		for (int j = 0; j<C->m; j++)
			C->SetElem(i,j,0);

	//умножение матриц A и B
	for (int i=0; i<n; i++)
		for (int j=0; j<M->m; j++)
	//цикл для умножения i-й строки матрицы А на j-й столбец матрицы В
		for (int k=0; k<m; k++)
		{
			a = GetElem(i,k);
			b = M->GetElem(k,j);
			c = C->GetElem(i,j);
			c = c + a*b;
			C->SetElem(i,j,c);
		}

	return C;
}

template <class T> Matrix<T>* Matrix<T> :: operator = (Matrix<T>* M)
{
	if ((n != M->n)||(m != M->m))
	{
		throw Error();
	}

	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
			SetElem(i,j,M->GetElem(i,j));

	return *this;
}

template <class T> T Matrix<T> :: Norm1()
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
    for(int j = 0; j<m; i++)
    {
        if(summ[j] > max) max = summ[j];
    }

    return max;
}

// функции класса FileP
template <class T> void FileP<T> :: Setfilename (char* s1)
{
	strcpy(fin, s1);
}

