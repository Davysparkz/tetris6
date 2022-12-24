// tetris6.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "main.h"
#include "w32_types.h"
#include "TInput.h"
#include "TGraphics.h"
#include "TWindow.h"
#include "GameView.h"
#include "TMenu.h"

constexpr w32::uint_t MAX_LOADSTRING = 100;
constexpr w32::uint_t WIN_W = 500;
constexpr w32::uint_t WIN_H = 700;

// Forward declarations of functions included in this code module:
w32::lresult_t CALLBACK    WndProc(w32::hwnd_t, w32::uint_t, w32::wparam_t, w32::lparam_t);

int APIENTRY wWinMain(_In_ w32::hinstance_t hInstance,
	_In_opt_ w32::hinstance_t hPrevInstance,
	_In_ w32::lpwstr_t    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	w32::wchar szTitle[MAX_LOADSTRING];                  // The title bar text
	w32::wchar szWindowClass[MAX_LOADSTRING];            // the main window class name

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TETRIS6, szWindowClass, MAX_LOADSTRING);

	TWindow window{
		hInstance, 
		std::wstring{szWindowClass},
		std::wstring{szTitle},
		WIN_W,
		WIN_H
	};

	w32::wndclassexw_s wcex;

	wcex.cbSize = sizeof(w32::wndclassex_s);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TETRIS6));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (w32::hbrush_s)(CreateSolidBrush(Colors::Black));
	wcex.lpszMenuName = NULL; // no menu
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	if (window.RegClass(wcex)) {
		try
		{
			window.Create();
			window.Show();
		}
		catch (const TWindowException& twe)
		{
			MessageBoxA(NULL, twe.what(), "ERROR", MB_ICONERROR);
			std::terminate();
		}
	}

	w32::msg_s msg;
	bool done{ false };

	// Main message loop:
	while (!done) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				done = true;
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
	}

	return (int)msg.wParam;
}

w32::lresult_t CALLBACK WndProc(w32::hwnd_t hWnd, w32::uint_t message, w32::wparam_t wParam, w32::lparam_t lParam)
{
	static std::unique_ptr<GameView> gv;
	switch (message)
	{
	case WM_CREATE:
	{
		gv = std::make_unique<GameView>();
	} break;
	case WM_PAINT:
	{
		w32::paintstruct_s ps;
		w32::hdc_t hdc = BeginPaint(hWnd, &ps);

		//TGraphics::DrawLine(hdc, 0, 10, WIN_W, 10, RGB(200, 50, 0));
		//TGraphics::DrawRect(hdc, 50, 50, 100, 100);

		//TGraphics::WriteTextA(hdc, "Hello World", 100, 10, RGB(220, 100, 0));
		//TGraphics::WriteTextA(hdc, "Hello World", 100, 40, RGB(220, 100, 0));

		//TGraphics::DrawRect(hdc, 50, 50, WIN_W, WIN_H, TGraphics::BLACK);

		gv->Draw(hdc, ps.rcPaint);

		//std::unique_ptr<TMenu> o = std::make_unique<TMenu>(
		//	w32::GetRect(50, 50, ps.rcPaint.right-50, ps.rcPaint.bottom-50)
		//	);

		//auto m1 = new TMenuItem(0, 0, 100, 100);
		//TGraphics::TextProps tp;
		//tp.align = static_cast<TGraphics::TextAlign>( TGraphics::TextAlign::TOP);
		//m1->SetContentTextA("Welcome", tp);
		//o->AddMenuItem(m1);
		//o->Draw(hdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case VK_LEFT:
			TInput::KeyLeft(nullptr);
			break;
		case VK_DOWN:
			TInput::KeyDown(nullptr);
			break;
		case VK_RIGHT:
			TInput::KeyRight(nullptr);
			break;
		default:
			break;
		}
	} break;
	case WM_CHAR:
	{
		TInput::KeyChar(nullptr, (char)wParam);
	} break;
	case WM_GETMINMAXINFO:
	{
		// prevent resizing
		((minmaxinfo_s*)lParam)->ptMinTrackSize.x = static_cast<uint_t>(WIN_W);
		((minmaxinfo_s*)lParam)->ptMinTrackSize.y = static_cast<uint_t>(WIN_H);

		((minmaxinfo_s*)lParam)->ptMaxTrackSize.x = static_cast<uint_t>(WIN_W);
		((minmaxinfo_s*)lParam)->ptMaxTrackSize.y = static_cast<uint_t>(WIN_H);

	} break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
