#include <conio.h>
#include <clocale> 
#include "ClassesF.cpp"

using namespace std;

void main (int argc, char *argv[])
{
	char name1 [100], name2 [100];
	stringstream ss;
	ofstream F2;
	FileP<int> P1, P2;
	SimpleM<int> M1, M2;
	int n, m, k, N;

	setlocale (LC_CTYPE, "Russian");

	strcpy (name1, "D:\matr1.txt");
	strcpy (name2, "D:\matr2.txt");
	P1.SetFileName(name1);
	P2.SetFileName(name2);
	n = 20;
	m = 20;
	M1.MakeMatr(n,m,&P1);
	M2.MakeMatr(m,n,&P2);

	F2.open(name1,ios::out);
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			if (i == j)
				k = 1;
			else
				k = 0;
			F2 << k << " ";
		}
	F2.close();

	/*F2.open(name2,ios::out);
	for (int i = 0; i<m; i++)
		for (int j = 0; j<n; j++)
		{
			if (i == j)
				k = 1;
			else
				k = 0;
			F2 << k << " ";
		}
	F2.close();*/

	cout << "M1\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}

	cout << "Determinant: " << M1.Det() << "\n";

	/*cout << "M2\n";
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++)
			cout << M2.GetElem(i,j) << " ";
		cout << "\n";
	}

	M1*=M2;

	cout << "M1*M2\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}


	/*M2 = M1;
	N = M2.Norm1();
	cout << "M2 and norm\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M2.GetElem(i,j) << " ";
		cout << "\n";
	}

	cout << N << "\n";

	M1 *=2;
	cout << "new M1\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}

	M1+=M2;
	cout << "M1+M2\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}*/

	_getch();
	return;
}