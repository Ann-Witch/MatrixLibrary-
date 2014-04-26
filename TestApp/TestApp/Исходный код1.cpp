#define _CRT_SECURE_NO_WARNINGS
#pragma comment (lib, "MatrixLibrary.lib")
#include <conio.h>
#include <clocale> 
#include <Windows.h>

#define EXPORTABLE_CLASS __declspec(dllimport)
#include <MatrixLibrary.h>

using namespace std;

void main (int argc, char *argv[])
{
	char name1[100], name2[100];
	FileP<double> P1, P2;
	SimpleM<double> F0, F1;
	FILE *f;
	double k[1];
	setlocale (LC_CTYPE, "Russian");

	strcpy (name1, "D:\\matr1.dat");
	strcpy (name2, "D:\\matr2.dat");


	P1.SetFileName(name1);
	P2.SetFileName(name2);

	F0.MakeMatr (3,3,&P1);
	F1.MakeMatr (3,3,&P2);

	f = fopen(name1,"wb"); 
	k[0] = 0.2;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0.2;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0.2;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen(name2,"wb"); 
	k[0] = 0.5;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0.5;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0.5;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	F0+=F1;

	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<3; j++)
			cout << F0.GetElem(i,j) << " ";
		cout << "\n";
	}
	
	_getch();
	return;
}