#pragma once

namespace w32 {
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
	// Windows Header Files
#include <windows.h>

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

	// STRUCTS
	using msg_s = MSG;
	using wndclassexw_s = WNDCLASSEXW;
	using wndclassex_s = WNDCLASSEX;
	using hbrush_s = HBRUSH;
	using paintstruct_s = PAINTSTRUCT;
	using rect_s = RECT;
	using logbrush_s = LOGBRUSH;
	using minmaxinfo_s = MINMAXINFO;

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

	//inline Styles operator | (Styles s1, Styles s2) {
	//	return static_cast<Styles>(s1) | static_cast<Styles>(s2);
	//}

	//inline Styles operator ^ (Styles s1, Styles s2) {
	//	return static_cast<Styles>(s1) ^ static_cast<Styles>(s2);
	//}

	//inline Styles operator & (Styles s1, Styles s2) {
	//	return static_cast<Styles>(s1) & static_cast<Styles>(s2);
	//}
}
