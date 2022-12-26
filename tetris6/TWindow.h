#pragma once

#pragma warning (disable : 4290) // C++ exception specification ignored except to indicate ...

#include "w32_types.h"
#include <string>
#include <exception>

using namespace w32;

class TWindowException : public std::runtime_error {
public:
	TWindowException(const std::string& errmsg);
};

class TWindow
{
public:
	enum Styles : dword_t {
		OVERLAPPED = 0x00000000L,
		POPUP = 0x80000000L,
		CHILD = 0x40000000L,
		MINIMIZE = 0x20000000L,
		VISIBLE = 0x10000000L,
		DISABLED = 0x08000000L,
		CLIPSIBLINGS = 0x04000000L,
		CLIPCHILDREN = 0x02000000L,
		MAXIMIZE = 0x01000000L,
		CAPTION = 0x00C00000L,     /* BORDER | DLGFRAME  */
		BORDER = 0x00800000L,
		DLGFRAME = 0x00400000L,
		VSCROLL = 0x00200000L,
		HSCROLL = 0x00100000L,
		SYSMENU = 0x00080000L,
		THICKFRAME = 0x00040000L,
		GROUP = 0x00020000L,
		TABSTOP = 0x00010000L,
		MINIMIZEBOX = 0x00020000L,
		MAXIMIZEBOX = 0x00010000L,
		TILED = OVERLAPPED,
		ICONIC = MINIMIZE,
		SIZEBOX = THICKFRAME,
		OVERLAPPEDWINDOW = (OVERLAPPED | CAPTION | SYSMENU | THICKFRAME | MINIMIZEBOX | MAXIMIZEBOX),
		POPUPWINDOW = (POPUP | BORDER | SYSMENU),
		TILEDWINDOW = OVERLAPPEDWINDOW,
		CHILDWINDOW = CHILD
	};
public:
	TWindow() = delete;
	TWindow(
		hinstance_t hInst, 
		std::wstring wndClsName, 
		std::wstring wndTitle, 
		uint_t wndW,
		uint_t wndH
	);
	~TWindow();

	void Create(Styles styles = static_cast<Styles>(
		Styles::OVERLAPPED |
		Styles::CAPTION |
		Styles::SYSMENU |
		Styles::THICKFRAME |
		Styles::MINIMIZEBOX
		^ Styles::THICKFRAME)
	) throw (TWindowException);

	template <typename T>
	void CreateWithData(T* data, Styles styles = static_cast<Styles>(
		Styles::OVERLAPPED |
		Styles::CAPTION |
		Styles::SYSMENU |
		Styles::THICKFRAME |
		Styles::MINIMIZEBOX
		^ Styles::THICKFRAME)
	) throw (TWindowException);


	bool RegClass(wndclassexw_s wcex);

	hwnd_t getHandle() throw (TWindowException);

	void Show() throw (TWindowException);
private:
	hwnd_t m_hwnd;
	hinstance_t m_hinstance;
	std::wstring m_wndClsName;
	std::wstring m_wndTitle;
	uint_t m_width;
	uint_t m_height;

	bool m_created;
	bool m_registered;
};

template<typename T>
inline void TWindow::CreateWithData(T * data, Styles styles) throw(TWindowException)
{
	if (!this->m_registered) {
		throw TWindowException("TWindow::Register() must be called before TWindow::CreateWithData");
	}
	if (this->m_created) { // preventing creating more than once
		return;
	}

	int scrnW = ::GetSystemMetrics(SM_CXSCREEN);
	int scrnH = ::GetSystemMetrics(SM_CYSCREEN);

	rect_s wndRc{ 0, 0, static_cast<long>(this->m_width), static_cast<long>(this->m_height) };

	int wndW = wndRc.right - wndRc.left;
	int wndH = wndRc.bottom - wndRc.top;

	int wndX = max(0, (scrnW - wndW) / 2);
	int wndY = max(0, (scrnH - wndH) / 2);

	hwnd_t hWnd = ::CreateWindowExW(
		0,
		this->m_wndClsName.c_str(),
		this->m_wndTitle.c_str(),
		styles,
		wndX,
		wndY,
		wndW,
		wndH,
		nullptr,
		nullptr,
		this->m_hinstance,
		data
	);

	if (hWnd) {
		this->m_hwnd = hWnd;
		this->m_created = true;
	}
}
