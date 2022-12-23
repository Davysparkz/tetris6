#pragma once
#include "w32_types.h"
#include <string>

namespace Colors {
	static w32::colorref_t HEX(std::string value)
	{
		if (value.length() == 7 && value[0] == '#') {
			std::string red{ "0x" + value.substr(1, 2) };
			std::string green{ "0x" + value.substr(3, 2) };
			std::string blue{ "0x" + value.substr(5, 2) };

			int r = std::stoi(red, nullptr, 0);
			int g = std::stoi(green, nullptr, 0);
			int b = std::stoi(blue, nullptr, 0);

			return RGB(r, g, b);
		}
		else if (value.length() == 4 && value[0] == '#') {
			std::string red{ "0x" + value.substr(1, 1) };
			std::string green{ "0x" + value.substr(2, 1) };
			std::string blue{ "0x" + value.substr(3, 1) };

			int r = std::stoi(red, nullptr, 0);
			int g = std::stoi(green, nullptr, 0);
			int b = std::stoi(blue, nullptr, 0);

			return RGB(r*r, g*g, b*b);
		}
		else {
			return RGB(0, 0, 0);
		}
	}

	const w32::colorref_t White = HEX("#ffffff");
	const w32::colorref_t Black = RGB(0, 0, 0);
	const w32::colorref_t Gray = RGB(40, 40, 40);
	const w32::colorref_t Orange = RGB(200, 50, 0);
	const w32::colorref_t MistyRose = RGB(255, 228, 255);
	const w32::colorref_t Lavender = RGB(200, 50, 0);
}

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

	static void DrawRect(w32::hdc_t hdc, int x, int y, int w, int h, bool filled = true, w32::colorref_t color = Colors::White);
	static void DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color = Colors::White);
	static void WriteTextW(w32::hdc_t hdc, std::wstring text, int x, int y, w32::colorref_t color = Colors::White);
	static void WriteTextA(w32::hdc_t hdc, std::string text, int x, int y, w32::colorref_t color = Colors::White);

	static std::wstring FONT_FAMILY;
	static int FONT_SIZE;
	static FW FONT_WEIGHT;

	static int LINE_WIDTH;
};

