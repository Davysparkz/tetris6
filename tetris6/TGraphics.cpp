#include "stdafx.h"
#include "TGraphics.h"


TGraphics::TGraphics()
{
}


TGraphics::~TGraphics()
{
}

void TGraphics::DrawRect(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color) {
	auto old = SelectObject(hdc, CreateSolidBrush(color));
	Rectangle(hdc, x, y, w, h);
	SelectObject(hdc, old);
}
void TGraphics::DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color) {
	auto old = SelectObject(hdc, CreatePen(PS_SOLID, 2, color));
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, old);
}
void TGraphics::WriteTextW(w32::hdc_t hdc, w32::lpwstr_t text, w32::rect_t r, w32::colorref_t color)
{
	auto oldFont = SelectObject(hdc,
		CreateFontW(FONT_SIZE, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, FONT_FAMILY)
	);

	auto oldColor = SetTextColor(hdc, color);
	DrawTextW(hdc, text, -1, &r, DT_NOCLIP);

	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldFont);
}
void TGraphics::WriteTextA(w32::hdc_t hdc, w32::lpstr_t text, w32::rect_t r, w32::colorref_t color)
{
	auto oldFont = SelectObject(hdc,
		CreateFontW(FONT_SIZE, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, FONT_FAMILY)
	);

	auto oldColor = SetTextColor(hdc, color);
	DrawTextA(hdc, text, -1, &r, DT_NOCLIP);

	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldFont);
}
