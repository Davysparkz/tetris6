// tetris6.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "tetris6.h"
#include "w32_types.h"

#define MAX_LOADSTRING 100

constexpr int WIN_W = 500;
constexpr int WIN_H = 600;


// Global Variables:
w32::hinstance_t hInst;                                // current instance
w32::wchar szTitle[MAX_LOADSTRING];                  // The title bar text
w32::wchar szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
w32::atom_t                MyRegisterClass(w32::hinstance_t hInstance);
w32::bool_t                InitInstance(w32::hinstance_t, int);
w32::lresult_t CALLBACK    WndProc(w32::hwnd_t, w32::uint_t, w32::wparam_t, w32::lparam_t);

int APIENTRY wWinMain(_In_ w32::hinstance_t hInstance,
                     _In_opt_ w32::hinstance_t hPrevInstance,
                     _In_ w32::lpwstr_t    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TETRIS6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    w32::haccel_t hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRIS6));

    w32::msg_t msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
w32::atom_t MyRegisterClass(w32::hinstance_t hInstance)
{
    w32::wndclassexw_t wcex;

    wcex.cbSize = sizeof(w32::wndclass_t);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS6));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (w32::hbrush_t)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL; // no menu
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(w32::hinstance_t, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
w32::bool_t InitInstance(w32::hinstance_t hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   w32::hwnd_t hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, WIN_W, WIN_H, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(w32::hwnd_t, w32::uint_t, w32::wparam_t, w32::lparam_t)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
w32::lresult_t CALLBACK WndProc(w32::hwnd_t hWnd, w32::uint_t message, w32::wparam_t wParam, w32::lparam_t lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            w32::paintstruct_t ps;
            w32::hdc_t hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
