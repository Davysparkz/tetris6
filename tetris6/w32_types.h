#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

namespace w32 {
	using hinstance_t = HINSTANCE;
	using wchar = WCHAR;
	using atom_t = ATOM;
	using wparam_t = WPARAM;
	using lparam_t = LPARAM;
	using uint_t = UINT;
	using lpwstr_t = LPWSTR;
	using lpstr_t = LPSTR;
	using bool_t = BOOL;
	using lresult_t = LRESULT;
	using haccel_t = HACCEL;
	using msg_t = MSG;
	using wndclassexw_t = WNDCLASSEXW;
	using wndclass_t = WNDCLASSEX;
	using hbrush_t = HBRUSH;
	using hwnd_t = HWND;
	using paintstruct_t = PAINTSTRUCT;
	using hdc_t = HDC;
	using rect_t = RECT;
	using colorref_t = COLORREF;
	using logbrush_t = LOGBRUSH;
	using hgdiobj_t = HGDIOBJ;
}