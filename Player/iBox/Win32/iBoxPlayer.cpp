// iBoxPlayer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "iBoxPlayer.h"
#include "CBoxPlayer.h"

#define MAX_LOADSTRING		100

#define WND_WIDTH			818
#define	WND_HEIGHT			498

// Global Variables:
HINSTANCE		g_hInst;								// current instance
TCHAR			szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR			szWindowClass[MAX_LOADSTRING];			// the main window class name
CBoxPlayer *	g_Player = NULL;
TCHAR			g_szCmdLine[1024];

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IBOXPLAYER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	memset (g_szCmdLine, 0, sizeof (g_szCmdLine));
	if (_tcslen (lpCmdLine) > 0)
	{
		if (lpCmdLine[0] == _T('"'))
			lpCmdLine++;
		if (lpCmdLine[_tcslen (lpCmdLine)-1] == _T('"'))
			lpCmdLine[_tcslen (lpCmdLine)-1] = 0;
		_tcscpy (g_szCmdLine, lpCmdLine);
	}

	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IBOXPLAYER));
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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_IBOXPLAYER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(WHITE_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MENU_LIST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	g_hInst = hInstance; // Store instance handle in our global variable
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, //WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_THICKFRAME,
						CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hWnd)
		return FALSE;

	SetWindowLong (hWnd, GWL_EXSTYLE, WS_EX_ACCEPTFILES);
	SetWindowPos (hWnd, NULL, (GetSystemMetrics (SM_CXSCREEN) - WND_WIDTH) / 2, (GetSystemMetrics (SM_CYSCREEN) - WND_HEIGHT - 100 ) / 2, WND_WIDTH, WND_HEIGHT, 0);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	g_Player = new CBoxPlayer (g_hInst);
	if (_tcslen (g_szCmdLine) > 0)
		g_Player->Create (hWnd, g_szCmdLine);
	else
		g_Player->Create (hWnd, NULL);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	if (g_Player != NULL)
	{
		int nRC = g_Player->MsgProc (hWnd, message, wParam, lParam);
		if (nRC != S_FALSE)
			return nRC;
	}

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		YY_DEL_P (g_Player);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		{
			RECT			rcDlg;
			GetClientRect (hDlg, &rcDlg);
			SetWindowPos (hDlg, NULL, (GetSystemMetrics (SM_CXSCREEN) - rcDlg.right) / 2, 
							(GetSystemMetrics (SM_CYSCREEN) - rcDlg.bottom ) / 2, 0, 0, SWP_NOSIZE);

		}
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
