#pragma once
#include "w32_types.h"
#include <string>

// WEB COLORS
namespace Colors {


	// <summary>converts a hex value to an rgb value</summary>
	//
	// <param name="value">the hex value starting with a '#'</param>
	//
	// <returns>returns a COLORREF</returns>
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

	//const w32::colorref_t Orange = RGB(200, 50, 0);

	// GRAY AND BLACK COLORS
	const w32::colorref_t Black = HEX("#000000");
	const w32::colorref_t DarkSlateGray = HEX("#2F4F4F");
	const w32::colorref_t DimGray = HEX("#696969");
	const w32::colorref_t SlateGray = HEX("#708090");
	const w32::colorref_t Gray = HEX("#808080");
	const w32::colorref_t LightSlateGray = HEX("#778899");
	const w32::colorref_t Silver = HEX("#C0C0C0");
	const w32::colorref_t LightGray = HEX("#D3D3D3");
	const w32::colorref_t Gainsboro = HEX("#DCDCDC");

	// WHITE COLORS
	const w32::colorref_t MistyRose = HEX("#FFE4E1");
	const w32::colorref_t AntiqueWhite = HEX("#FAEBD7");
	const w32::colorref_t Linen = HEX("#FAF0E6");
	const w32::colorref_t Beige = HEX("#F5F5DC");
	const w32::colorref_t WhiteSmoke = HEX("#F5F5F5");
	const w32::colorref_t LavenderBlush = HEX("#FFF0F5");
	const w32::colorref_t OldLace = HEX("#FDF5E6");
	const w32::colorref_t AliceBlue = HEX("#F0F8FF");
	const w32::colorref_t Seashell = HEX("#FFF5EE");
	const w32::colorref_t GhostWhite = HEX("#F8F8FF");
	const w32::colorref_t Honeydew = HEX("#F0FFF0");
	const w32::colorref_t FloralWhite = HEX("#FFFAF0");
	const w32::colorref_t Azure = HEX("#F0FFFF");
	const w32::colorref_t MintCream = HEX("#F5FFFA");
	const w32::colorref_t Snow = HEX("#FFFAFA");
	const w32::colorref_t Ivory = HEX("#FFFFF0");
	const w32::colorref_t White = HEX("#FFFFFF");

	// GREEN COLORS
	const w32::colorref_t DarkGreen = HEX("#006400");
	const w32::colorref_t Green = HEX("#008000");
	const w32::colorref_t DarkOliveGreen = HEX("#556B2F");
	const w32::colorref_t ForestGreen = HEX("#228B57");
	const w32::colorref_t SeaGreen = HEX("#2E8B57");
	const w32::colorref_t Olive = HEX("#808000");
	const w32::colorref_t OliveDrab = HEX("#6B8E23");
	const w32::colorref_t MediumSeaGreen = HEX("#3CB371");
	const w32::colorref_t LimeGreen = HEX("#32CD32");
	const w32::colorref_t Lime = HEX("#00FF00");
	const w32::colorref_t SpringGreen = HEX("#00FF7F");
	const w32::colorref_t MediumSpringGreen = HEX("#00FA9A");
	const w32::colorref_t DarkSeaGreen = HEX("#8FBC8F");
	const w32::colorref_t MediumAquamarine = HEX("#66CDAA");
	const w32::colorref_t YellowGreen = HEX("#9ACD32");
	const w32::colorref_t LawnGreen = HEX("#7CFC00");
	const w32::colorref_t Chartreuse = HEX("#7FFF00");
	const w32::colorref_t LightGreen = HEX("#90EE90");
	const w32::colorref_t GreenYellow = HEX("#ADFF2F");
	const w32::colorref_t PaleGreen = HEX("#98FB98");

	// CYAN COLORS
	const w32::colorref_t Teal = HEX("#008080");
	const w32::colorref_t DarkCyan = HEX("#008B8B");
	const w32::colorref_t LightSeaGreen = HEX("#20B2AA");
	const w32::colorref_t CadetBlue = HEX("#5F9EA0");
	const w32::colorref_t DarkTurquoise = HEX("#00CED1");
	const w32::colorref_t MediumTurquoise = HEX("#48D1CC");
	const w32::colorref_t Turquoise = HEX("#40E0D0");
	const w32::colorref_t Aqua = HEX("#00FFFF");
	const w32::colorref_t Cyan = HEX("#00FFFF");
	const w32::colorref_t Aquamarine = HEX("#7FFFD4");
	const w32::colorref_t PaleTurquoise = HEX("#AFEEEE");
	const w32::colorref_t LightCyan = HEX("#E0FFFF");

	// BLUE COLORS
	const w32::colorref_t MidnightBlue = HEX("#191970");
	const w32::colorref_t Navy = HEX("#000080");
	const w32::colorref_t DarkBlue = HEX("#00008B");
	const w32::colorref_t MediumBlue = HEX("#0000CD");
	const w32::colorref_t Blue = HEX("#0000FF");
	const w32::colorref_t RoyalBlue = HEX("#4169E1");
	const w32::colorref_t SteelBlue = HEX("#4682B4");
	const w32::colorref_t DodgerBlue = HEX("#1E90FF");
	const w32::colorref_t DeepSkyBlue = HEX("#00BFFF");
	const w32::colorref_t CornflowerBlue = HEX("#6495EB");
	const w32::colorref_t SkyBlue = HEX("#87CEEB");
	const w32::colorref_t LightSkyBlue = HEX("#87CEFA");
	const w32::colorref_t LightSteelBlue = HEX("#B0C4DE");
	const w32::colorref_t LightBlue = HEX("#ADD8E6");
	const w32::colorref_t PowderBlue = HEX("#B0E0E6");

	// PURPLE, VIOLET, AND MAGENTA COLORS
	const w32::colorref_t Indigo = HEX("#4B0082");
	const w32::colorref_t Purple = HEX("#800080");
	const w32::colorref_t DarkMagenta = HEX("#8B008B");
	const w32::colorref_t DarkViolet = HEX("#9400D3");
	const w32::colorref_t DarkSlateBlue = HEX("#483D8B");
	const w32::colorref_t BlueViolet = HEX("#8A2BE2");
	const w32::colorref_t DarkOrchid = HEX("#9932CC");
	const w32::colorref_t Fuchsia = HEX("#FF00FF");
	const w32::colorref_t Magenta = HEX("#FF00FF");
	const w32::colorref_t SlateBlue = HEX("#6A5ACD");
	const w32::colorref_t MediumSlateBlue = HEX("#7B68EE");
	const w32::colorref_t MediumOrchid = HEX("#BA55D3");
	const w32::colorref_t MediumPurple = HEX("#9370DB");
	const w32::colorref_t Orchid = HEX("#DA70D6");
	const w32::colorref_t Violet = HEX("#EE82EE");
	const w32::colorref_t Plum = HEX("#DDA0DD");
	const w32::colorref_t Thistle = HEX("#D8BFD8");
	const w32::colorref_t Lavender = HEX("#E6E6FA");

	// BROWN COLORS
	const w32::colorref_t Maroon = HEX("#800000");
	const w32::colorref_t Brown = HEX("#A52A2A");
	const w32::colorref_t SaddleBrown = HEX("#8B4513");
	const w32::colorref_t Sienna = HEX("#A0522D");
	const w32::colorref_t Chocolate = HEX("#D2691E");
	const w32::colorref_t DarkGoldenrod = HEX("#B8863F");
	const w32::colorref_t Peru = HEX("#CD853F");
	const w32::colorref_t RosyBrown = HEX("#BC8F8F");
	const w32::colorref_t Goldenrod = HEX("#DAA520");
	const w32::colorref_t SandyBrown = HEX("#F4A460");
	const w32::colorref_t Tan = HEX("#D2B48C");
	const w32::colorref_t Burlywood = HEX("#DEB887");
	const w32::colorref_t Wheat = HEX("#F5DEB3");
	const w32::colorref_t NavajoWhite = HEX("#FFDEAD");
	const w32::colorref_t Bisque = HEX("#FFE4C4");
	const w32::colorref_t BlanchedAlmond = HEX("#FFEBCD");
	const w32::colorref_t Cornsilk = HEX("#FFF8DC");

	// YELLOW COLORS
	const w32::colorref_t DarkKhaki = HEX("#BDB76B");
	const w32::colorref_t Gold = HEX("#FFD700");
	const w32::colorref_t Khaki = HEX("#F0E68C");
	const w32::colorref_t PeachPuff = HEX("#FFDA89");
	const w32::colorref_t Yellow = HEX("#FFFF00");
	const w32::colorref_t PaleGoldenrod = HEX("#EEE8AA");
	const w32::colorref_t Moccasin = HEX("#FFE4B5");
	const w32::colorref_t PapayaWhip = HEX("#FFEFD5");
	const w32::colorref_t LightGoldenrodYellow = HEX("#FAFAD2");
	const w32::colorref_t LemonChiffon = HEX("#FFFACD");
	const w32::colorref_t LightYellow = HEX("#FFFFE0");

	// ORANGE COLORS
	const w32::colorref_t OrangeRed = HEX("#FF4500");
	const w32::colorref_t Tomato = HEX("#FF6347");
	const w32::colorref_t DarkOrange = HEX("#FF8C00");
	const w32::colorref_t Coral = HEX("#FF7F50");
	const w32::colorref_t Orange = HEX("#FFA500");

	// RED COLORS
	const w32::colorref_t DarkRed = HEX("#8B0000");
	const w32::colorref_t Red = HEX("#FF0000");
	const w32::colorref_t Firebrick = HEX("#B22222");
	const w32::colorref_t Crimson = HEX("#DC143C");
	const w32::colorref_t IndianRed = HEX("#CD5C5C");
	const w32::colorref_t LightCoral = HEX("#F08080");
	const w32::colorref_t Salmon = HEX("#FA8072");
	const w32::colorref_t DarkSalmon = HEX("#E9967A");
	const w32::colorref_t LightSalmon = HEX("#FFA07A");

	// PINK COLORS
	const w32::colorref_t MediumVioletRed = HEX("#C71585");
	const w32::colorref_t DeepPink = HEX("#FF1493");
	const w32::colorref_t PaleVioletRed = HEX("#DB7093");
	const w32::colorref_t HotPink = HEX("#FF69B4");
	const w32::colorref_t LightPink = HEX("#FFB6C1");
	const w32::colorref_t Pink = HEX("#FFC0CB");
}

class TGraphics
{
public:
	TGraphics();
	~TGraphics();

	enum FontWeight {
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

	enum LineStyle {
		SOLID = 0,
		DASH = 1,     /* -------  */
		DOT = 2,   /* .......  */
		DASHDOT = 3,     /* _._._._  */
		DASHDOTDOT = 4,       /* _.._.._  */

		ENDCAP_ROUND = 0x00000000,
		ENDCAP_SQUARE = 0x00000100,
		ENDCAP_FLAT = 0x00000200,
		ENDCAP_MASK = 0x00000F00,

		JOIN_ROUND = 0x00000000,
		JOIN_BEVEL = 0x00001000,
		JOIN_MITER = 0x00002000,
		JOIN_MASK = 0x0000F000,
	};

	enum TextAlign {
	//	TOP = 0x00000000, // NOT WORKING
		LEFT = 0x00000000,
		CENTER = 0x00000001,
		RIGHT = 0x00000002,
	//	VCENTER = 0x00000004, // NOT WORKING
		//BOTTOM = 0x00000008, // NOT WORKING
	};

	struct TextProps {
		w32::colorref_t color{Colors::White};
		int fontSize{ 16 };
		std::wstring fontFamily{ L"Segoe UI" };
		TGraphics::TextAlign align{ TGraphics::TextAlign::LEFT };
	};

	static void DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color = Colors::White, LineStyle lineStyle = SOLID, int lineWidth = 3);
	static void WriteTextW(
		w32::hdc_t hdc,
		std::wstring text,
		w32::rect_s bounds, 
		w32::colorref_t color = Colors::White, 
		int fontSize = 16, 
		TextAlign textAlign = TextAlign::LEFT,
		std::wstring fontFamily = L"Segoe UI"
	);
	static void WriteTextA(
		w32::hdc_t hdc,
		std::string text,
		w32::rect_s bounds,
		w32::colorref_t color = Colors::White,
		int fontSize = 16,
		TextAlign textAlign = TextAlign::LEFT,
		std::wstring fontFamily = L"Segoe UI"
	);
	static void WriteTextW(
		w32::hdc_t hdc,
		std::wstring text,
		w32::rect_s bounds,
		TextProps textProps
	);
	static void WriteTextA(
		w32::hdc_t hdc,
		std::string text,
		w32::rect_s bounds,
		TextProps textProps
	);
	static void DrawStrokedRect(w32::hdc_t, int x, int y, int w, int h, w32::colorref_t color = Colors::White, LineStyle lineStyle = SOLID, int lineWidth = 3);
	static void DrawFilledRect(w32::hdc_t, int x, int y, int w, int h, w32::colorref_t color = Colors::White);
	static void DrawStrokedRect(w32::hdc_t, w32::rect_s bounds, w32::colorref_t color = Colors::White, LineStyle lineStyle = SOLID, int lineWidth = 3);
	static void DrawFilledRect(w32::hdc_t, w32::rect_s bounds, w32::colorref_t color = Colors::White);

	static std::wstring FONT_FAMILY;
	static int FONT_SIZE;
	static FontWeight FONT_WEIGHT;

	static int LINE_WIDTH;
};

