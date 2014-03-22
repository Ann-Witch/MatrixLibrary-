// matrix_dg.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cmath>
#include <stdio.h>


using namespace std;

void Norm1(double** a, int n)
{
    int pos = 0;

    double* summ = new double[n]; //Вектор с суммами строк
    for(int i = 0; i < n; i++)
        summ[i] = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j<n; j++)
        {
            summ[pos] += abs(a[j][i]);
        }
        pos++;
    }

    double max = summ[0];
    for(int i = 0; i < pos; i++)
    {
        if(summ[i] > max) max = summ[i];
    }
    cout<<"Первая норма равна: "<<max<<endl;
}

void SwapColumns(double** a, int col1, int col2)
{
	double* temp = a[col1];
	a[col1] = a[col2];
	a[col2] = temp;
}

void SwapRows(double** a, int row1, int row2, int n)
{
	double temp;
	for(int i = 0; i < n; ++i)
	{
		temp = a[i][row1];
		a[i][row1] = a[i][row2];
		a[i][row2] = temp;
	}
}

bool Determinant(double** a, int n)
{
	double** b = new double*[n];
    for(int i = 0; i < n; i++)
        b[i] = new double[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			b[i][j]=a[i][j];

	double det = 1.0;
	int sign = +1;
	for(int i = 0; i < n; ++i) // двигаемся вдоль главной диагонали
	{
		//поиск ненулевого элемента (i,i, n,n)-матрицы
		int x1 = 0, y1 = 0; //"координаты" ненулевого эл-та
		bool f = false; //успех в поиске ненулевого элемента

		for(int x = i; x < n; ++x)
			for(int y = i; y < n; ++y)
				if(!f && b[x][y])
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
			SwapColumns(b, i, x1);
			sign = -sign;
		}

		if(y1 != i)
		{
			SwapRows(b, i, y1, n);
			sign = -sign;
		}

		//сейчас matr[i][i] != 0 
		det *= b[i][i];
		for(int x = n-1; x >= i; --x)
			b[x][i] /= b[i][i];

		//сейчас matr[i][i] == 1;
		for (int y = i+1; y < n; ++y)
			for (int x = n-1; x >= i; --x)
				b[x][y] -= b[x][i]*b[i][y];
			
	}
	det *= sign;

	cout<<"Определитель матрицы: "<<det<<endl;

	for(int i=0;i<n;i++)
        delete[] b[i];
    delete[] b;

	if (det == 0)
	{	
		cout<<"Матрица вырождена!"<<endl;
		return false;
	}
	else return true;
	//return det;
}

double ReverseMatrix(double** a, int n, double** &a_obr)
{ 
	//bool d = Determinant(a, n);
	//if (d)
	//{
		//создание единичной матрицы
		//a_obr = new double* [n];
		for(int i = 0; i < n; i++)
		{
			//a_obr[i] = new double [n];
			for(int j = 0; j < n; j++) 
				a_obr[i][j] = 0;
			a_obr[i][i] = 1;
		}

		//прямой ход методом Гаусса
		double c, d;
		for(int i = 0; i < n; i++)
		{ 
			c = a[i][i];
			for(int j = i+1; j < n; j++)
			{
				d = a[j][i];
				for(int k = 0; k < n; k++)
				{
					a[j][k] = a[i][k]*d - a[j][k]*c;
					a_obr[j][k] = a_obr[i][k]*d - a_obr[j][k]*c;
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
					sum += a[j][k]*a_obr[k][i];
				
				if(a[j][j] == 0)  //если придется делить на нуль
				{
					cout<<"Ай-яй-яй! Деление на нуль ждет тебя"<<endl;
					for(i = 0; i < n; i++)
						delete []a_obr[i];
					delete []a_obr;
					return 0;
				}
				else	a_obr[j][i]=(a_obr[j][i]-sum)/a[j][j];
			}
		}
	

		cout<<"Обратная матрица: "<<endl;
		for (int i = 0; i < n; cout<<endl, i++)
			for (int j = 0; j < n; j++)
				cout<<a_obr[i][j]<<"\t";

		return **a_obr;
	//}
}


int main()
{
	setlocale(LC_ALL, "Russian");
    int n;

	cout<<"Введите размер матрицы: "; cin>>n;
    
	// Выделение памяти для матрицы а
	double** a = new double*[n];
    for(int i = 0; i<n; i++)
        a[i] = new double[n];
    
	//Введите матрицу
	cout<<"Введите матрицу: ";		
	for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
			cin>>a[i][j];
			cout<<endl;
        }
        cout<<endl;
    }

	//Вызываем функцию нормы1
    Norm1(a, n);

	//Вызываем ф-ию определителя
	Determinant(a, n);

	if (Determinant(a, n))
	{
		//Вызываем ф-ию обратной матрицы
		double** a_obr;
		a_obr = new double* [n];
		for(int i = 0; i < n; i++)
			a_obr[i] = new double [n];

		ReverseMatrix(a, n, a_obr);
		
		for(int i = 0; i < n; i++)
				delete []a_obr[i];
			delete []a_obr;
	}

	//Очищаем память
    for(int i=0;i<n;i++)
        delete[] a[i];
    delete[] a;

	
   
	getch();
    return 0;
}
 