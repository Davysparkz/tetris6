#pragma once
#include "w32_types.h"
#include <string>

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
	};

	static void DrawRect(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color = WHITE);
	static void DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color = WHITE);
	static void WriteTextW(w32::hdc_t hdc, std::wstring text, int x, int y, w32::colorref_t color = WHITE);
	static void WriteTextA(w32::hdc_t hdc, std::string text, int x, int y, w32::colorref_t color = WHITE);

	static w32::colorref_t WHITE;
	static w32::colorref_t BLACK;
	static w32::colorref_t GRAY;

	static std::wstring FONT_FAMILY;
	static int FONT_SIZE;
	static FW FONT_WEIGHT;

	static int LINE_WIDTH;
};

