// YUV.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "YUV.h"
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100


int pixel_w = 176;
int pixel_h = 144;
int screen_w =176;
int screen_h = 144;
int FrameNum = 2000;
//FILE *yuv_in = fopen_s(&yuv_in, "E:\\learn\\C\\YUV\\YUV\\yuv420.yuv", "rb");     "E:\\learn\\C\\YUV\\YUV\\yuv420.yuv"
//FILE *yuv_in = fopen("C:\\Users\\LabUser20\\Downloads\\tulips_yuv420_prog_planar_qcif.yuv", "rb");
FILE *yuv_in = fopen( "E:\\learn\\C\\YUV\\YUV\\yuv420.yuv", "rb");
const int Width_i = 176;
const int Height_i = 144;
unsigned char Framebuffer[Width_i*Height_i * 3 / 2];
unsigned char RGBframe[176 * 144 * 3];
//int RGBframe[176 * 144 * 3];
//int Framebuffer[Width_i*Height_i * 3 / 2];


inline unsigned char CONVERT_ADJUST(double tmp)
{
	return (unsigned char)((tmp >= 0 && tmp <= 255) ? tmp : (tmp < 0 ? 0 : 255));
}

//inline int CONVERT_ADJUST(double tmp)
//{
//	return (int)((tmp >= 0 && tmp <= 255) ? tmp : (tmp < 0 ? 0 : 255));
//}


// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	////自己写的
	//const int Width_i = 176;
	//const int Height_i = 144;
	//unsigned char Framebuffer[Width_i*Height_i * 3 / 2];
	//FILE *yuv_in = NULL;
	//fopen_s(&yuv_in,"C:\\Users\\LabUser20\\Downloads\\tulips_yuv420_prog_planar_qcif.yuv", "rb");

	//for (int i = 0; i < Width_i*Height_i * 3 / 2; i++)
	//{
	//	fread(&Framebuffer[i], sizeof(unsigned char), 1, yuv_in);
	//}

	///*unsigned char RGBframe[Width_i*Height_i*3];*/
	//for (int j = 0; j < Width_i*Height_i; j++)
	//{
	//	char y, u, v, r, g, b;
	//	y = Framebuffer[j];
	//	//Yi对应的Ui次序
	//	int Uorder = (j + 1) / (2 * Width_i)*(Width_i / 2) + ((j + 1) % Width_i) / 2 + ((j + 1) % Width_i % 2) - 1;
	//	u = Framebuffer[Width_i*Height_i + Uorder];
	//	v = Framebuffer[Width_i*Height_i + Width_i*Height_i / 4 + Uorder];
	//	//u = 0, v = 0;
	//	/*r = CONVERT_ADJUST (y + 1.14*v);
	//	g = CONVERT_ADJUST( y - 0.39*u - 0.58*v);
	//	b = CONVERT_ADJUST(y + 2.03*u);*/

	//	r = CONVERT_ADJUST((y + (1.4075 * (v - 128))));
	//	g = CONVERT_ADJUST((y - (0.3455 * (u - 128) - 0.7169 * (v - 128))));
	//	b = CONVERT_ADJUST((y + (1.7790 * (u - 128))));

	//	RGBframe[3 * j] = b;
	//	RGBframe[3 * j + 1] = g;
	//	RGBframe[3 * j + 2] = r;
	//}














	//HWND hwnd = NULL;
	//hwnd = CreateWindow(_T("GDI"), _T("Simplest Video Play GDI"), WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hInstance, NULL);
	///*if (hwnd == NULL)
	//	return -1;*/
	////int nShowCmd = 1;
	//ShowWindow(hwnd, nCmdShow);
	//UpdateWindow(hwnd);

	//HDC hdc = GetDC(hwnd);
//
//	HWND hWnd;
//
//	hInst = hInstance; // 将实例句柄存储在全局变量中
//
//	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//
//	/*if (!hWnd)
//	{
//		return FALSE;
//	}
//*/
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_YUV, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YUV));

	// 主消息循环: 
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
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YUV));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_YUV);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   for (int k = 1; k < FrameNum;k++)
   {

	   
	   /*  const int Width_i = 176;
		 const int Height_i = 144;
		 unsigned char Framebuffer[Width_i*Height_i * 3 / 2];*/
	   /*FILE *yuv_in = NULL;*/


	   /* for (int i = 0; i < Width_i*Height_i * 3 / 2; i++)
		{
		fread(&Framebuffer[i], sizeof(unsigned char), 1, yuv_in);
		}*/

	   //  fread(Framebuffer, sizeof(Framebuffer), 1, yuv_in);
	   
	   if (fread(Framebuffer, sizeof(Framebuffer), 1, yuv_in) == EOF)
	   {
		   fseek(yuv_in, 0, SEEK_SET);
		   fread(Framebuffer, sizeof(Framebuffer), 1, yuv_in);
	   }

	  

	   /*unsigned char RGBframe[Width_i*Height_i*3];*/
	   for (int j = 0; j < Width_i*Height_i; j++)
	   {
	    int y, u, v, r, g, b;
	    y = Framebuffer[j];
	    //Yi对应的Ui次序
	    int Uorder = (j + 1) / (2 * Width_i)*(Width_i / 2) + ((j + 1) % Width_i) / 2 + ((j + 1) % Width_i % 2) - 1;
	    u = Framebuffer[Width_i*Height_i + Uorder];
	    v = Framebuffer[Width_i*Height_i + Width_i*Height_i / 4 + Uorder];
	    //u = 0, v = 0;
	    /*r = CONVERT_ADJUST (y + 1.14*v);
	    g = CONVERT_ADJUST( y - 0.39*u - 0.58*v);
	    b = CONVERT_ADJUST(y + 2.03*u);*/

		//KE YONG
	    r = CONVERT_ADJUST((y + (1.4075 * (v - 128))));
	    g = CONVERT_ADJUST((y - (0.3455 * (u - 128) - 0.7169 * (v - 128))));
	    b = CONVERT_ADJUST((y + (1.7790 * (u - 128))));

		/*r = CONVERT_ADJUST((y + (1.14 * (v - 128))));
		g = CONVERT_ADJUST((y - (0.39 * (u - 128) - 0.58 * (v - 128))));
		b = CONVERT_ADJUST((y + (2.03* (u - 128))));*/

	    RGBframe[3 * j] = b;
	    RGBframe[3 * j + 1] = g;
	    RGBframe[3 * j + 2] = r;
	   }



	  // unsigned char y, u, v, r, g, b;
	  // for (int i = 0; i < Height_i; ++i)
	  // for (int j = 0; j < Width_i; ++j){
		 //  y = Framebuffer[i*Width_i + j];
		 //  u = Framebuffer[Height_i*Width_i + i / 2 * Width_i / 2 + j / 2];
		 //  v = Framebuffer[Height_i*Width_i + Height_i*Width_i / 4 + i / 2 * Width_i / 2 + j / 2];
		 //  r = CONVERT_ADJUST(y + 1.4075 *(v - 128));
		 //  g = CONVERT_ADJUST(y - 0.3455 *(u - 128) - 0.7169 *(v - 128));
		 //  b = CONVERT_ADJUST(y + 1.779  *(u - 128));
		 //  /*r=trunc(r);
		 //  g=trunc(g);
		 //  b=trunc(b);
		 //  rgb24[((HEIGHT-i-1)*WIDTH + j)*3] = b;
		 //  rgb24[((HEIGHT-i-1)*WIDTH+ j)*3 + 1]= g;
		 //  rgb24[((HEIGHT-i-1)*WIDTH+ j)*3 + 2] = r;
		 //  */

		 //  /* rgb24[((HEIGHT - i - 1)*WIDTH + j) * 3] = CONVERT_ADJUST(b);
			//rgb24[((HEIGHT - i - 1)*WIDTH + j) * 3 + 1] = (g);
			//rgb24[((HEIGHT - i - 1)*WIDTH + j) * 3 + 2] = (r);*/

		 //  RGBframe[(i)*Width_i + j] = r;
		 //  RGBframe[(i)*Width_i + j + 1] = g;
		 //  RGBframe[(i)*Width_i + j + 2] = b;
	  // }



	   //BMP Header  
	   BITMAPINFO m_bmphdr = { 0 };
	   DWORD dwBmpHdr = sizeof(BITMAPINFO);
	   //24bit  
	   m_bmphdr.bmiHeader.biBitCount = 24;
	   m_bmphdr.bmiHeader.biClrImportant = 0;
	   m_bmphdr.bmiHeader.biSize = dwBmpHdr;
	   m_bmphdr.bmiHeader.biSizeImage = 0;
	   m_bmphdr.bmiHeader.biWidth = pixel_w;
	   //Notice: BMP storage pixel data in opposite direction of Y-axis (from bottom to top).  
	   //So we must set reverse biHeight to show image correctly.  
	   m_bmphdr.bmiHeader.biHeight = -pixel_h;
	   m_bmphdr.bmiHeader.biXPelsPerMeter = 0;
	   m_bmphdr.bmiHeader.biYPelsPerMeter = 0;
	   m_bmphdr.bmiHeader.biClrUsed = 0;
	   m_bmphdr.bmiHeader.biPlanes = 1;
	   m_bmphdr.bmiHeader.biCompression = BI_RGB;

	   HDC hdc = GetDC(hWnd);
	   StretchDIBits(hdc,
		   0, 0,
		   screen_w, screen_h,
		   0, 0,
		   pixel_w, pixel_h,
		   RGBframe,
		   &m_bmphdr,
		   DIB_RGB_COLORS,
		   SRCCOPY);

	   ReleaseDC(hWnd, hdc);

	   Sleep(1000/20);
	  // if (fgetc(yuv_in) == EOF) break;
	  if( feof(yuv_in)) break;
   }







   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
		// 分析菜单选择: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		// TODO:  在此添加任意绘图代码...
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

// “关于”框的消息处理程序。
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
