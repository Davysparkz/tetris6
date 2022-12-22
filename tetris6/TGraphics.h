#pragma once
#include "w32_types.h"

class TGraphics
{
public:
	TGraphics();
	~TGraphics();

	enum FW {
		THIN = 100,
		EXTRALIGHT = 200,
		LIGHT = 300,
		NORMAL = 400,
		MEDIUM = 500,
		SEMIBOLD = 600,
		BOLD = 700,
		EXTRABOLD = 800,
		HEAVY = 900,
		ULTRALIGHT = EXTRALIGHT,
		REGULAR = NORMAL,
		DEMIBOLD = SEMIBOLD,
		ULTRABOLD = EXTRABOLD,
		BLACK = HEAVY,
	};

	static void DrawRect(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color = WHITE);
	static void DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color = WHITE);
	static void WriteTextW(w32::hdc_t hdc, w32::lpwstr_t text, w32::rect_t r, w32::colorref_t color = WHITE);
	static void WriteTextA(w32::hdc_t hdc, w32::lpstr_t text, w32::rect_t r, w32::colorref_t color = WHITE);

	static w32::colorref_t WHITE;

	static w32::lpwstr_t FONT_FAMILY;
	static int FONT_SIZE;
	static FW FONT_WEIGHT;
};


w32::colorref_t TGraphics::WHITE = RGB(255, 255, 255);
w32::lpwstr_t TGraphics::FONT_FAMILY = TEXT("Segoe UI");
int TGraphics::FONT_SIZE = 48;
TGraphics::FW TGraphics::FONT_WEIGHT;