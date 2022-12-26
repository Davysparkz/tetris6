#include "stdafx.h"
#include "TGraphics.h"

std::wstring TGraphics::FONT_FAMILY = L"Segoe UI";
int TGraphics::FONT_SIZE = 48;
TGraphics::FontWeight TGraphics::FONT_WEIGHT;

int TGraphics::LINE_WIDTH = 3;

TGraphics::TGraphics()
{
}


TGraphics::~TGraphics()
{
}

void TGraphics::DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color, LineStyle lineStyle, int lineWidth)
{
	auto oldPen = SelectObject(hdc, CreatePen(lineStyle, lineWidth, color));
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, oldPen);
}
void TGraphics::WriteTextW(w32::hdc_t hdc, std::wstring text, w32::rect_s bounds, w32::colorref_t color, int fontSize, TextAlign textAlign, std::wstring fontFamily)
{
	auto oldFont = SelectObject(hdc,
		CreateFontW(fontSize, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, fontFamily.c_str())
	);
	SetBkMode(hdc, TRANSPARENT);

	auto oldColor = SetTextColor(hdc, color);

	DrawTextW(hdc, text.c_str(), -1, &bounds, DT_NOCLIP | textAlign);

	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldFont);
}
void TGraphics::WriteTextA(w32::hdc_t hdc, std::string text, w32::rect_s bounds, w32::colorref_t color, int fontSize, TextAlign textAlign, std::wstring fontFamily)
{
	auto oldFont = SelectObject(hdc,
		CreateFontW(fontSize, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, fontFamily.c_str())
	);
	SetBkMode(hdc, TRANSPARENT);

	auto oldColor = SetTextColor(hdc, color);

	DrawTextA(hdc, text.c_str(), -1, &bounds, DT_NOCLIP | textAlign);

	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldFont);
}

void TGraphics::WriteTextW(w32::hdc_t hdc, std::wstring text, w32::rect_s bounds, TextProps tp)
{
	WriteTextW(hdc, text, bounds, tp.color, tp.fontSize, tp.align, tp.fontFamily);
}

void TGraphics::WriteTextA(w32::hdc_t hdc, std::string text, w32::rect_s bounds, TextProps tp)
{
	WriteTextA(hdc, text, bounds, tp.color, tp.fontSize, tp.align, tp.fontFamily);
}

void TGraphics::DrawStrokedRect(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color, LineStyle lineStyle, int lineWidth)
{
	// top
	DrawLine(hdc, x, y, w, y, color, lineStyle, lineWidth);

	// bottom
	DrawLine(hdc, x, h, w, h, color, lineStyle, lineWidth);

	// left
	DrawLine(hdc, x, y, x, h, color, lineStyle, lineWidth);

	// right
	DrawLine(hdc, w, y, w, h, color, lineStyle, lineWidth);
}

void TGraphics::DrawFilledRect(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color)
{
	auto oldBrush = SelectObject(hdc, CreateSolidBrush(color));
	Rectangle(hdc, x, y, w, h);
	SelectObject(hdc, oldBrush);
}

void TGraphics::DrawStrokedRect(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color, LineStyle lineStyle, int lineWidth)
{
	DrawStrokedRect(hdc, WIDEN_RECT(bounds), color, lineStyle, lineWidth);
}

void TGraphics::DrawFilledRect(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color)
{
	DrawFilledRect(hdc, WIDEN_RECT(bounds), color);
}

void TGraphics::DrawStrokedRect2(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color, LineStyle lineStyle, int lineWidth)
{
	// top
	DrawLine(hdc, x, y, x+w, y, color, lineStyle, lineWidth);

	// bottom
	DrawLine(hdc, x, y+h, x+w, y+h, color, lineStyle, lineWidth);

	// left
	DrawLine(hdc, x, y, x, y+h, color, lineStyle, lineWidth);

	// right
	DrawLine(hdc, x+w, y, x+w, y+h, color, lineStyle, lineWidth);
}

void TGraphics::DrawStrokedRect2(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color, LineStyle lineStyle, int lineWidth)
{
	DrawStrokedRect2(hdc, WIDEN_RECT(bounds), color);
}


