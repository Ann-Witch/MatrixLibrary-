// Application.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Application.h"
#include <Commdlg.h>
#include <stdio.h>
#include <stdlib.h>

#define EXPORTABLE_CLASS __declspec(dllimport)
#include <MatrixLibrary.h>
#pragma warning(disable : 4996)
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр
TCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
TCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна
HWND hWnd;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Red(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	LU(HWND, UINT, WPARAM, LPARAM);

void CreateFileDialog(HWND hWnd, OPENFILENAME *ofn, LPWSTR fname, int size, LPWSTR filter) {
	ZeroMemory(ofn, sizeof(OPENFILENAME));
	ofn->lStructSize = sizeof(OPENFILENAME);
	ofn->hwndOwner = hWnd;
	ofn->lpstrFile = fname;
	ofn->nMaxFile = size;
	ofn->lpstrFilter = filter;
	ofn->nFilterIndex = 1;
	ofn->lpstrFileTitle = NULL;
	ofn->nMaxFileTitle = 0;
	ofn->lpstrInitialDir = NULL;
	ofn->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: разместите код здесь.
	MSG msg;
	HACCEL hAccelTable;

	// Инициализация глобальных строк
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_APPLICATION, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_APPLICATION));

	// Цикл основного сообщения:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_APPLICATION);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND	- обработка меню приложения
//  WM_PAINT	-Закрасить главное окно
//  WM_DESTROY	 - ввести сообщение о выходе и вернуться.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_RED:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_REDBOX), hWnd, Red);
			break;
		case IDM_LU:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LUBOX), hWnd, LU);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: добавьте любой код отрисовки...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK Red(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn;
	wchar_t fname[250];
	char* filename1 = new char[500],*bname = new char[500];
	wchar_t tmp[6];
	stringstream ss;
	string fn;
	FILE* fin;
	double buf[1];

	FileP<double> *P1 = new FileP<double>(), *P2 = new FileP<double>(), *p;
	int n, m, k, N;
	SimpleM<double> F0, D0, *b, *x;
	BlockM<double> M1;
	Reduction<double> R1;
	SimpleLU<double> LU1;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON5:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON1:
			CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			if(GetOpenFileName(&ofn))
			{
				SetDlgItemText(hDlg,FILE_F,fname);
			}
			break;
		case IDC_BUTTON2:
			CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			if(GetOpenFileName(&ofn))
			{
				SetDlgItemText(hDlg,FILE_D,fname);
			}
			break;
		case IDC_BUTTON3:
			CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			if(GetOpenFileName(&ofn))
			{
				SetDlgItemText(hDlg,FILE_B,fname);
			}
			break;
		case IDC_BUTTON4:
			GetDlgItemText(hDlg, KOEFF_K, tmp, 6);
			k = _wtoi(tmp);
			GetDlgItemText(hDlg, SIZE_N, tmp, 6);
			n = _wtoi(tmp);
			GetDlgItemText(hDlg, SIZE_M, tmp, 6);
			m = _wtoi(tmp);
			if (n!=m)
			{
				MessageBox(NULL, L"Блоки должны быть квадратными!", L"Error!", MB_OK | MB_ICONERROR);
			    EndDialog(hDlg, LOWORD(wParam));
			    break;
			}

			GetDlgItemText(hDlg,FILE_F,fname,250);
			WideCharToMultiByte(CP_ACP,0,fname,500,filename1,500,NULL,NULL);
			P1->SetFileName(filename1);
			GetDlgItemText(hDlg,FILE_D,fname,250);
			WideCharToMultiByte(CP_ACP,0,fname,500,filename1,500,NULL,NULL);
			P2->SetFileName(filename1);
			GetDlgItemText(hDlg,FILE_B,fname,250);
			WideCharToMultiByte(CP_ACP,0,fname,500,bname,500,NULL,NULL);
			
			F0.MakeMatr(n,m,P1);
			D0.MakeMatr(n,m,P2);
			M1.MakeMatr(k,n,m);
			M1.SetBlock(1,0,F0);
			M1.SetBlock(2,0,D0);

			N = (int)pow((float)2.0,k)-1;

			b = new SimpleM<double>[N];
			fin = fopen(bname,"rb");
	        for (int i = 0; i<N; i++)
	        {
				ss<<i;
		        fn = "D:\\b" + ss.str() + ".dat";
		        p = new FileP<double>;
		        p->SetFileName(fn.c_str());
			    p->Clear();
		        b[i].MakeMatr(n,1,p);
		        ss.str("");
		        ss.clear();
				for (int j = 0; j<n; j++)
				{
					fread(buf,sizeof(double),1,fin);
					b[i].SetElem(j,0,buf[0]);
				}
			}
			fclose (fin);

	       x = new SimpleM<double>[N];
	       for (int i = 0; i<N; i++)
	       {
			   ss<<i;
		       fn = "D:\\x" + ss.str() + ".dat";
		       p = new FileP<double>;
		       p->SetFileName(fn.c_str());
			   p->Clear();
		       x[i].MakeMatr(n,1,p);
		       ss.str("");
		       ss.clear();
		   }

		   try
		   {
			   R1.methodB(M1,b,x,&LU1);
		   } 
		   catch (Error)
		   {
			   MessageBox(NULL, L"Ошибка!", L"Result", MB_OK | MB_ICONERROR);
			   EndDialog(hDlg, LOWORD(wParam));
			   break;
		   }

		   fin = fopen ("D:\\ResultX_Reduction.txt","wt");
		   for (int i = 0; i<N; i++)
			   for (int j = 0; j<n; j++)
			   {
				   fprintf(fin,"%3.0f",x[i].GetElem(j,0));
				   putc(' ',fin);
			   }
		   fclose (fin);

		   for (int i = 0; i<N; i++)
		   {
			   ss<<i;
		       fn = "D:\\b" + ss.str() + ".dat";
			   remove(fn.c_str());
		       fn = "D:\\x" + ss.str() + ".dat";
			   remove(fn.c_str());
		       ss.str("");
		       ss.clear();
		   }
		   remove("D:\\Bufer1.dat");
		   remove("D:\\Bufer2.dat");
		   remove("D:\\Bufer3.dat");

		   EndDialog(hDlg, LOWORD(wParam));
			    
		   MessageBox(NULL, L"Уравнение решено. Результат смотрите в файле 'D:\\ResultX_Reduction.txt'", L"Result", MB_OK | MB_ICONINFORMATION);

		   break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK LU(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	OPENFILENAME ofn;
	wchar_t fname[250];
	char* filename1 = new char[500],*bname = new char[500];
	wchar_t tmp[6];
	stringstream ss;
	string fn;
	FILE* fin;
	double buf[1];

	FileP<double> *p;
	int n, m, N;
	SimpleM<double> *F0, *D0, *E0, *b, *x;
	BlockM<double> M1;
	BlockLU<double> BLU1;
	SimpleLU<double> LU1;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		switch(LOWORD(wParam)) 
		{
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON7:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON6:
			GetDlgItemText(hDlg, SIZE_K, tmp, 6);
			N = _wtoi(tmp);
			GetDlgItemText(hDlg, SIZE_N2, tmp, 6);
			n = _wtoi(tmp);
			GetDlgItemText(hDlg, SIZE_M2, tmp, 6);
			m = _wtoi(tmp);
			if (n!=m)
			{
				MessageBox(NULL, L"Блоки должны быть квадратными!", L"Error!", MB_OK | MB_ICONERROR);
			    EndDialog(hDlg, LOWORD(wParam));
			    break;
			}

			F0 = new SimpleM<double> [N-1];
			D0 = new SimpleM<double> [N];
			E0 = new SimpleM<double> [N-1];

			if (MessageBox(NULL, L"Выберите входные файлы для блоков F", L"Data", MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				for (int i = 0; i<N-1; i++)
				{
					CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			        if(GetOpenFileName(&ofn))
			        {
						WideCharToMultiByte(CP_ACP,0,fname,500,filename1,500,NULL,NULL);
						p = new FileP<double>();
						p->SetFileName(filename1);
						F0[i].MakeMatr(n,m,p);
					}
				}
			}
			else
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			if (MessageBox(NULL, L"Выберите входные файлы для блоков D", L"Data", MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				for (int i = 0; i<N; i++)
				{
					CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			        if(GetOpenFileName(&ofn))
			        {
						WideCharToMultiByte(CP_ACP,0,fname,500,filename1,500,NULL,NULL);
						p = new FileP<double>();
						p->SetFileName(filename1);
						D0[i].MakeMatr(n,m,p);
					}
				}
			}
			else
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			if (MessageBox(NULL, L"Выберите входные файлы для блоков E", L"Data", MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
				for (int i = 0; i<N-1; i++)
				{
					CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			        if(GetOpenFileName(&ofn))
			        {
						WideCharToMultiByte(CP_ACP,0,fname,500,filename1,500,NULL,NULL);
						p = new FileP<double>();
						p->SetFileName(filename1);
						E0[i].MakeMatr(n,m,p);
					}
				}
			}
			else
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			if (MessageBox(NULL, L"Выберите входной файл для вектора правой части", L"Data", MB_YESNO | MB_ICONQUESTION)==IDYES)
			{
					CreateFileDialog(hWnd, &ofn, fname, sizeof(fname), L"All\0*.*\0Text\0*.TXT\0");
			        if(GetOpenFileName(&ofn))
			        {
						WideCharToMultiByte(CP_ACP,0,fname,500,bname,500,NULL,NULL);
					}
			}
			else
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}

			M1.MakeMatr(N,n,m);
			for (int i = 0; i<N-1; i++)
			{
				M1.SetBlock(1,i,F0[i]);
			    M1.SetBlock(3,i,E0[i]);
			}
			for (int i = 0; i<N; i++)
				M1.SetBlock(2,i,D0[i]);

			b = new SimpleM<double>[N];
			fin = fopen(bname,"rb");
	        for (int i = 0; i<N; i++)
	        {
				ss<<i;
		        fn = "D:\\b" + ss.str() + ".dat";
		        p = new FileP<double>;
		        p->SetFileName(fn.c_str());
			    p->Clear();
		        b[i].MakeMatr(n,1,p);
		        ss.str("");
		        ss.clear();
				for (int j = 0; j<n; j++)
				{
					fread(buf,sizeof(double),1,fin);
					b[i].SetElem(j,0,buf[0]);
				}
			}
			fclose (fin);

	       x = new SimpleM<double>[N];
	       for (int i = 0; i<N; i++)
	       {
			   ss<<i;
		       fn = "D:\\x" + ss.str() + ".dat";
		       p = new FileP<double>;
		       p->SetFileName(fn.c_str());
			   p->Clear();
		       x[i].MakeMatr(n,1,p);
		       ss.str("");
		       ss.clear();
		   }

		   try
		   {
			   BLU1.methodB(M1,b,x,&LU1);
		   } 
		   catch (Error)
		   {
			   MessageBox(NULL, L"Ошибка!", L"Result", MB_OK | MB_ICONERROR);
			   EndDialog(hDlg, LOWORD(wParam));
			   break;
		   }

		   fin = fopen ("D:\\ResultX_BlockLU.txt","wt");
		   for (int i = 0; i<N; i++)
			   for (int j = 0; j<n; j++)
			   {
				   fprintf(fin,"%3.0f",x[i].GetElem(j,0));
				   putc(' ',fin);
			   }
		   fclose (fin);

		   for (int i = 0; i<N; i++)
		   {
			   ss<<i;
		       fn = "D:\\b" + ss.str() + ".dat";
			   remove(fn.c_str());
		       fn = "D:\\x" + ss.str() + ".dat";
			   remove(fn.c_str());
		       ss.str("");
		       ss.clear();
		   }
		   remove("D:\\Bufer1.dat");
		   remove("D:\\Bufer2.dat");
		   remove("D:\\Bufer3.dat");

		   EndDialog(hDlg, LOWORD(wParam));
			    
		   MessageBox(NULL, L"Уравнение решено. Результат смотрите в файле 'D:\\ResultX_BlockLU.txt'", L"Result", MB_OK | MB_ICONINFORMATION);

		   break;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

