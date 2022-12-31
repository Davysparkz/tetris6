#pragma once

namespace w32 {
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	// Windows Header Files
#include <windows.h>
#include <windowsx.h> // EXTENDED WINDOWS HEADER

	// OPAQUE types
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
	using hwnd_t = HWND;
	using hdc_t = HDC;
	using colorref_t = COLORREF;
	using hgdiobj_t = HGDIOBJ;
	using dword_t = DWORD;
	using long_t = LONG;
	using ulonglong_t = ULONGLONG;
	using longptr_t = LONG_PTR;

	// STRUCTS
	using msg_s = MSG;
	using wndclassexw_s = WNDCLASSEXW;
	using wndclassex_s = WNDCLASSEX;
	using hbrush_s = HBRUSH;
	using paintstruct_s = PAINTSTRUCT;
	using rect_s = RECT;
	using logbrush_s = LOGBRUSH;
	using minmaxinfo_s = MINMAXINFO;
	using hbitmap_s = HBITMAP;
	using largeinteger_s = LARGE_INTEGER;
	using lpcreatestruct_s = LPCREATESTRUCT;
	using point_s = POINT;

#define WIDEN_RECT(r) r.left, r.top, r.right, r.bottom

	static rect_s GetRect(long_t x, long_t y, long_t w, long_t h) {
		rect_s rc;
		rc.left = x;
		rc.top = y;
		rc.right = w;
		rc.bottom = h;
		return rc;
	}
}
