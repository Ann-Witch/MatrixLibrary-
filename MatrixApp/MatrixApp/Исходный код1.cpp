#include <conio.h>
#include <clocale> 
#include "ClassesF.cpp"

using namespace std;

void main (int argc, char *argv[])
{
	char name1[100], name2[100], name3[100], name4[100], name5[100], name6[100], name7[100];
	FileP<double> P1, P2, P3, P4, P5, P6, P7, *p;
	BlockM<double> M1;
	SimpleM<double> F0, F1, D0, D1, D2, E0, E1, *b, *x, B, X;
	FILE *f;
	double k[1];
	stringstream ss; 
	string fn;
	Reduction<double> R;
	BlockLU<double> L;
	SimpleLU<double> *S = new SimpleLU<double>;
	//SimpleMethod<double>*met = new SimpleMethod<double>;
	setlocale (LC_CTYPE, "Russian");

	strcpy (name1, "D:\\matr1.dat");
	strcpy (name2, "D:\\matr2.dat");
	strcpy (name3, "D:\\matr3.dat");
	strcpy (name4, "D:\\matr4.dat");
	strcpy (name5, "D:\\matr5.dat");
	strcpy (name6, "D:\\matr6.dat");
	strcpy (name7, "D:\\matr7.dat");


	P1.SetFileName(name1);
	P2.SetFileName(name2);
	P3.SetFileName(name3);
	P4.SetFileName(name4);
	P5.SetFileName(name5);
	P6.SetFileName(name6);
	P7.SetFileName(name7);

	F0.MakeMatr (3,3,&P1);
	F1.MakeMatr (3,3,&P2);
	D0.MakeMatr (3,3,&P3);
	D1.MakeMatr (3,3,&P4);
	D2.MakeMatr (3,3,&P5);
	E0.MakeMatr (3,3,&P6);
	E1.MakeMatr (3,3,&P7);

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

	f = fopen(name3,"wb"); 
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen(name4,"wb"); 
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen(name5,"wb"); 
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 1;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen(name6,"wb"); 
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

	f = fopen(name7,"wb"); 
	k[0] = 0.1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0.1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0;
	fwrite (k,sizeof(double),1,f);
	k[0] = 0.1;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	int n = 3;

	b = new SimpleM<double>[n];
	for (int i = 0; i<n; i++)
	{
			ss<<i;
		    fn = "D:\\b" + ss.str() + ".dat";
		    p = new FileP<double>;
		    p->SetFileName(fn.c_str());
			p->Clear();
		    b[i].MakeMatr(3,1,p);
		    ss.str("");
		    ss.clear();
	}

	x = new SimpleM<double>[n];
	for (int i = 0; i<n; i++)
	{
			ss<<i;
		    fn = "D:\\x" + ss.str() + ".dat";
		    p = new FileP<double>;
		    p->SetFileName(fn.c_str());
			p->Clear();
		    x[i].MakeMatr(3,1,p);
		    ss.str("");
		    ss.clear();
	}

	f = fopen("D:\\b0.dat","wb"); 
	k[0] = 2.2;
	fwrite (k,sizeof(double),1,f);
	k[0] = 4.6;
	fwrite (k,sizeof(double),1,f);
	k[0] = 7;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen("D:\\b1.dat","wb"); 
	k[0] = 2;
	fwrite (k,sizeof(double),1,f);
	k[0] = 9;
	fwrite (k,sizeof(double),1,f);
	k[0] = 11.5;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen("D:\\b2.dat","wb"); 
	k[0] = 0.1;
	fwrite (k,sizeof(double),1,f);
	k[0] = 8.3;
	fwrite (k,sizeof(double),1,f);
	k[0] = 7.5;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	/*f = fopen("D:\\b3.dat","wb"); 
	k[0] = 301;
	fwrite (k,sizeof(double),1,f);
	k[0] = 567;
	fwrite (k,sizeof(double),1,f);
	k[0] = 290;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen("D:\\b4.dat","wb"); 
	k[0] = 74;
	fwrite (k,sizeof(double),1,f);
	k[0] = 140;
	fwrite (k,sizeof(double),1,f);
	k[0] = 80;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen("D:\\b5.dat","wb"); 
	k[0] = 165;
	fwrite (k,sizeof(double),1,f);
	k[0] = 347;
	fwrite (k,sizeof(double),1,f);
	k[0] = 160;
	fwrite (k,sizeof(double),1,f);
	fclose(f);

	f = fopen("D:\\b6.dat","wb"); 
	k[0] = 22;
	fwrite (k,sizeof(double),1,f);
	k[0] = 40;
	fwrite (k,sizeof(double),1,f);
	k[0] = 25;
	fwrite (k,sizeof(double),1,f);
	fclose(f);*/

	M1.MakeMatr(n,3,3);
	M1.SetBlock(1,0,F0);
	M1.SetBlock(1,1,F1);
	M1.SetBlock(2,0,D0);
	M1.SetBlock(2,1,D1);
	M1.SetBlock(2,2,D2);
	M1.SetBlock(3,0,E0);
	M1.SetBlock(3,1,E1);

	L.methodB(M1,b,x,S);

	//R.methodB(M1,b,x,S);

	for (int i = 0; i<n; i++)
		for (int j = 0; j<3; j++)
			cout << x[i].GetElem(j,0) << " ";

	_getch();
	return;
}