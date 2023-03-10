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

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
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
		w32::lpcreatestruct_s pCreateStruct = reinterpret_cast<w32::lpcreatestruct_s>(lParam);
		gv = reinterpret_cast<GameView*>(pCreateStruct->lpCreateParams);
		gv->SetUp(hWnd);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<w32::longptr_t>(pCreateStruct->lpCreateParams));
	}
	return 0;
	case WM_ACTIVATE:
		if (GET_WM_ACTIVATE_STATE(wParam, lParam) == WA_INACTIVE)
		{
			if (gv) {
				gv->Suspend();
			}
		}
		else {
			if (gv) {
				gv->Resume();
			}
		}
		return 0;
	case WM_PAINT:
	{
		w32::paintstruct_s ps;
		w32::hdc_t hdc = BeginPaint(hWnd, &ps);

		auto c_hDC = CreateCompatibleDC(hdc);
		auto c_hBMP = CreateCompatibleBitmap(hdc, ps.rcPaint.right, ps.rcPaint.bottom);
		auto o_hBMP = (w32::hbitmap_s)SelectObject(c_hDC, c_hBMP);

		if (gv) {

			gv->Draw2(c_hDC, ps.rcPaint);

			BitBlt(hdc, WIDEN_RECT(ps.rcPaint), c_hDC, 0, 0, SRCCOPY);
		}
		SelectObject(c_hDC, o_hBMP);
		DeleteObject(c_hBMP);
		DeleteObject(c_hDC);

		EndPaint(hWnd, &ps);
	}
	return 0;
	case WM_TIMER: {
		if (gv) {
			gv->Update();
			if (gv->IsGameOver()) {
				gv->CleanUp();
			}
		}
		InvalidateRect(hWnd, NULL, FALSE);
	} return 0;
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
			TInput::KeyDown([=]() { if (gv) { gv->OnDownArrowKey(); } });
			break;
		case VK_RIGHT:
			TInput::KeyRight([=]() { if (gv) { gv->OnRightArrowKey(); } });
			break;
		default:
			break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
	return 0;
	case WM_CHAR:
	{
		TInput::KeyChar(nullptr, (char)wParam);
		InvalidateRect(hWnd, NULL, FALSE);

	}
	return 0;
	case WM_GETMINMAXINFO:
	{
		// prevent resizing
		((minmaxinfo_s*)lParam)->ptMinTrackSize.x = static_cast<uint_t>(WIN_W);
		((minmaxinfo_s*)lParam)->ptMinTrackSize.y = static_cast<uint_t>(WIN_H);

		((minmaxinfo_s*)lParam)->ptMaxTrackSize.x = static_cast<uint_t>(WIN_W);
		((minmaxinfo_s*)lParam)->ptMaxTrackSize.y = static_cast<uint_t>(WIN_H);

	}
	return 0;
	case WM_DESTROY:
	{
		//if (c_hDC) {
		//	SelectObject(c_hDC, o_hBMP);
		//	DeleteObject(c_hBMP);
		//	DeleteObject(c_hDC);
		//}
		if (gv) {
			gv->CleanUp();
		}
		PostQuitMessage(0);
	}
	return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
