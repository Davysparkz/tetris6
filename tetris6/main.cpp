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

	std::unique_ptr<GameView> gv;
	if (window.RegClass(wcex)) {
		try
		{
			gv = std::make_unique<GameView>();
			window.CreateWithData(gv.get());
			window.Show();
		}
		catch (const TWindowException& twe)
		{
			MessageBoxA(NULL, twe.what(), "ERROR", MB_ICONERROR);
			std::terminate();
		}
	}

	w32::msg_s msg{};

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, 0, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

w32::lresult_t CALLBACK WndProc(w32::hwnd_t hWnd, w32::uint_t message, w32::wparam_t wParam, w32::lparam_t lParam)
{
	static GameView* gv;
	switch (message)
	{
	case WM_CREATE:
	{
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		gv = reinterpret_cast<GameView*>(pCreateStruct->lpCreateParams);
		gv->SetUp();
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (gv) {
			gv->Draw2(hdc, ps.rcPaint);
		}

		EndPaint(hWnd, &ps);
	} break;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			SendMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		case VK_LEFT:
			TInput::KeyLeft([=]() { if (gv) { gv->OnLeftArrowKey(); } });
			break;
		case VK_DOWN:
			TInput::KeyDown([=]() { if (gv) { gv->OnDownArrowKey(); }});
			break;
		case VK_RIGHT:
			TInput::KeyRight([=]() { if (gv) { gv->OnRightArrowKey(); } });
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
	} break;
	case WM_CHAR:
	{
		TInput::KeyChar(nullptr, (char)wParam);
		InvalidateRect(hWnd, NULL, true);
		UpdateWindow(hWnd);
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
