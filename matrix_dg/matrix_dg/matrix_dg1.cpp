// matrix_dg.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <cmath>
#include <stdio.h>

using namespace std;

void Norm1(double** matrix, int n, int m)
{
    int pos = 0;

    double* summ = new double[m]; //������ � ������� �����
    for(int i = 0; i < m; i++)
        summ[i] = 0;

    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j<n; j++)
        {
            summ[pos] += abs(matrix[j][i]);
        }
        pos++;
    }

    double max = summ[0];
    for(int i = 0; i < pos; i++)
    {
        if(summ[i] > max) max = summ[i];
    }
    cout<<"������ ����� �����: "<<max<<endl;
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

bool Determinant(double** matrix, int n)
{
	double det = 1.0;
	int sign = +1;
	for(int i = 0; i < n; ++i) // ��������� ����� ������� ���������
	{
		//����� ���������� �������� (i,i, n,n)-�������
		int x1 = 0, y1 = 0; //"����������" ���������� ��-��
		bool f = false; //����� � ������ ���������� ��������

		for(int x = i; x < n; ++x)
			for(int y = i; y < n; ++y)
				if(!f && matrix[x][y])
				{
					x1 = x;
					y1 = y;
					f = true;
				}

		if(!f) //��� ���������� ��-��
		{
			det = 0.0;
			break;
		}

		if(x1 != i)
		{
			SwapColumns(matrix, i, x1);
			sign = -sign;
		}

		if(y1 != i)
		{
			SwapRows(matrix, i, y1, n);
			sign = -sign;
		}

		//������ matr[i][i] != 0  !!!
		det *= matrix[i][i];
		for(int x = n-1; x >= i; --x)
			matrix[x][i] /= matrix[i][i];

		//������ matr[i][i] == 1;
		for (int y = i+1; y < n; ++y)
			for (int x = n-1; x >= i; --x)
				matrix[x][y] -= matrix[x][i]*matrix[i][y];
			
	}
	det *= sign;

	cout<<"������������ �������: "<<det<<endl;

	if (det == 0)
	{	
		cout<<"������� ���������!"<<endl;
		return false;
	}
	else return true;
}

double ReverseMatrix(double** a, int n)
{
	double** a_obr; 

	while (Determinant(a, n))
	{
		//�������� ��������� �������
		a_obr = new double* [n];
		for(int i = 0; i < n; i++)
		{
			a_obr[i] = new double [n];
			for(int j = 0; j < n; j++) 
				a_obr[i][j] = 0;
			a_obr[i][i] = 1;
		}

		//������ ��� ������� ������
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
	
		//�������� ��� ���������� ��������� �������� �������
		double sum;
		for(int i = 0; i < n; i++)
		{
			for(int j = n-1; j >= 0; j--)
			{
				sum = 0;
				for(int k = n-1; k > j; k--)
					sum += a[j][k]*a_obr[k][i];
				/*
				if(a[j][j] == 0)  //���� �� ��������� ����
				{
					for(i = 0; i < n; i++)
						delete []a_obr[i];
					delete []a_obr;
					return 0;
				}
				*/
				a_obr[j][i]=(a_obr[j][i]-sum)/a[j][j];
			}
		}
	}

	cout<<"�������� ������� "<<endl;
	for (int i = 0; i < n; cout<<endl, i++)
		for (int j = 0; j < n; j++)
			cout<<a_obr[i][j]<<"\t";

	return **a_obr;
}


int main()
{
    int n, m;

    cout<<"������� ���������� ����� (n): ";		cin>>n;
    cout<<"������� ���������� �������� (m): ";	cin>>m;
    
	// ��������� ������ ��� ������� �
	double** a = new double*[n];
    for(int i = 0; i<n; i++)
        a[i] = new double[m];
    
	//������� �������
	cout<<"������� ������� a(m*n): ";		
	for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
			cin>>a[i][j];
			cout<<endl;
        }
        cout<<endl;
    }

	//�������� ������� �����1
    Norm1(a, n, m);

	//�������� �-�� ������������
	Determinant(a, n);

	//�������� �-�� �������� �������
	ReverseMatrix(a, n);

	//������� ������
    for(int i=0;i<n;i++)
        delete[] a[i];
    delete[] a;
   
	getch();
    return 0;
}
 