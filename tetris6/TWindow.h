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

