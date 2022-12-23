#include "stdafx.h"
#include "TWindow.h"


TWindow::TWindow(
	hinstance_t hInst, 
	std::wstring wndClsName, 
	std::wstring wndTitle, 
	uint_t wndW, 
	uint_t wndH
) 
{
	this->m_hinstance = hInst;
	this->m_wndClsName = wndClsName;
	this->m_wndTitle = wndTitle;
	this->m_width = wndW;
	this->m_height = wndH;
	this->m_created = false;
	this->m_registered = false;
}


TWindow::~TWindow()
{
}

void TWindow::Create(Styles styles) throw (TWindowException)
{
	if (!this->m_registered) {
		throw TWindowException("TWindow::Register() must be called before TWindow::Create");
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
		nullptr
	);

	if (hWnd) {
		this->m_hwnd = hWnd;
		this->m_created = true;
	}
}

bool TWindow::RegClass(wndclassexw_s wcex)
{
	if (this->m_registered) { // preventing registering more than once
		return true;
	}

	if (wcex.cbSize != sizeof(wndclassex_s)) {
		wcex.cbSize = sizeof(wndclassex_s);
	}

	if (::RegisterClassExW(&wcex) > 0) {
		this->m_registered = true;
		return true;
	}
	return false;
}

hwnd_t TWindow::getHandle() throw (TWindowException)
{
	if (!this->m_registered) {
		throw TWindowException("TWindow::Register() has to be called before TWindow::getHandle()");
	}
	if (!this->m_created) {
		throw TWindowException("TWindow::Create() has to be called before TWindow::getHandle()");
	}
	return this->m_hwnd;
}

void TWindow::Show() throw(TWindowException)
{
	if (!this->m_registered) {
		throw TWindowException("TWindow::Register() has to be called before TWindow::Show()");
	}
	if (!this->m_created) {
		throw TWindowException("TWindow::Create() has to be called before TWindow::Show()");
	}
	ShowWindow(this->m_hwnd, SW_NORMAL);
	UpdateWindow(this->m_hwnd);
}

TWindowException::TWindowException(const std::string & errmsg) : 
	std::runtime_error{ errmsg.c_str() } 
{
}
