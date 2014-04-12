#include <conio.h>
#include <clocale> 
#include "ClassesF.cpp"

using namespace std;

void main (int argc, char *argv[])
{
	char name1 [100], name2 [100], name3[100], name4[100];
	FileP<double> P1, P2, P3, P4;
	SimpleM<double> M1, M2, M3, M4;
	int n, m, N;
	FILE *f;
	double k[1];
	setlocale (LC_CTYPE, "Russian");

	strcpy (name1, "D:\matr1.dat");
	strcpy (name2, "D:\matr2.dat");
	strcpy (name3, "D:\matr3.dat");
	strcpy (name4, "D:\matr4.dat");
	P1.SetFileName(name1);
	P2.SetFileName(name2);
	P3.SetFileName(name3);
	P4.SetFileName(name4);
	n = 41;
	m = 20;
	M1.MakeMatr(n,m,&P1); 
	M2.MakeMatr(n,m,&P2);
	M3.MakeMatr(m,n,&P3); 
	M4.MakeMatr(n,n,&P4);

	f = fopen(name1,"wb"); // создаем матрицу M1
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			k[0] = i+j;
			fwrite (k,sizeof(double),1,f);
		}
	fclose(f);

	f = fopen(name2,"wb"); // создаем матрицу M2
	for (int i = 0; i<n; i++)
		for (int j = 0; j<m; j++)
		{
			k[0] = (i+j) % 2;
			fwrite (k,sizeof(double),1,f);
		}
	fclose(f);

	f = fopen(name3,"wb"); // создаем матрицу M3
	for (int i = 0; i<m; i++)
		for (int j = 0; j<n; j++)
		{
			k[0] = i;
			fwrite (k,sizeof(double),1,f);
		}
	fclose(f);

	f = fopen(name4,"wb"); // создаем матрицу M4
	for (int i = 0; i<n; i++)
		for (int j = 0; j<n; j++)
		{
			if (i == j)
				k[0] = 1;
			else
				k[0] = 0;
			fwrite (k,sizeof(double),1,f);
		}
	fclose(f);

	cout << "M1\n"; // выводим матрицу M1
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}

	M1.SetElem(31,10,1000); // изменение элемента матрицы M1

	cout << "new M1\n"; // выводим новую матрицу M1
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}

	cout << "M2\n"; // выводим матрицу M2
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M2.GetElem(i,j) << " ";
		cout << "\n";
	}

	M1+=M2; // сложение M1 и ћ2 и вывод результата
	cout << "M1+M2\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}

	M2 *=2; // умножение ћ2 на 2 и вывод результата
	cout << "M2*2\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<m; j++)
			cout << M2.GetElem(i,j) << " ";
		cout << "\n";
	}

	cout << "M3\n"; // выводим матрицу M3
	for (int i = 0; i<m; i++)
	{
		for (int j = 0; j<n; j++)
			cout << M3.GetElem(i,j) << " ";
		cout << "\n";
	}

	cout << "M4\n"; // выводим матрицу M4
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			cout << M4.GetElem(i,j) << " ";
		cout << "\n";
	}

	M1*=M3; // умножение ћ1 на ћ3 и вывод результата, теперь ћ1 - квадратна€ матрица nxn
	cout << "M1*M3\n";
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			cout << M1.GetElem(i,j) << " ";
		cout << "\n";
	}

	N = M1.Norm1(); // перва€ норма матрицы ћ1
	cout << "1-st norm of M1 = " << N << "\n";

	//cout << "Determinant of M4 = " << M4.Det() << "\n"; // определитель единичной матрицы 
	M4.InvM();
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n; j++)
			cout << M4.GetElem(i,j) << " ";
		cout << "\n";
	}

	_getch();
	return;
}