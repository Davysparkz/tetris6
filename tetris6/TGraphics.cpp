#include "stdafx.h"
#include "TGraphics.h"

w32::colorref_t TGraphics::WHITE = RGB(255, 255, 255);
w32::colorref_t TGraphics::BLACK = RGB(0, 0, 0);
w32::colorref_t TGraphics::GRAY = RGB(40, 40, 40);

std::wstring TGraphics::FONT_FAMILY = L"Segoe UI";
int TGraphics::FONT_SIZE = 48;
TGraphics::FW TGraphics::FONT_WEIGHT;

int TGraphics::LINE_WIDTH = 3;

TGraphics::TGraphics()
{
}


TGraphics::~TGraphics()
{
}

void TGraphics::DrawRect(w32::hdc_t hdc, int x, int y, int w, int h, w32::colorref_t color) {
	auto oldBrush = SelectObject(hdc, CreateSolidBrush(color));
	Rectangle(hdc, x, y, w, h);
	SelectObject(hdc, oldBrush);
}
void TGraphics::DrawLine(w32::hdc_t hdc, int x1, int y1, int x2, int y2, w32::colorref_t color) {
	auto oldPen = SelectObject(hdc, CreatePen(PS_SOLID, LINE_WIDTH, color));
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
	SelectObject(hdc, oldPen);
}
void TGraphics::WriteTextW(w32::hdc_t hdc, std::wstring text, int x, int y, w32::colorref_t color)
{
	auto oldFont = SelectObject(hdc,
		CreateFontW(FONT_SIZE, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, FONT_FAMILY.c_str())
	);
	SetBkMode(hdc, TRANSPARENT);

	auto oldColor = SetTextColor(hdc, color);

	w32::rect_t rc;
	SetRect(&rc, x, y, 0, 0);
	DrawTextW(hdc, text.c_str(), -1, &rc, DT_NOCLIP);

	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldFont);
}
void TGraphics::WriteTextA(w32::hdc_t hdc, std::string text, int x, int y, w32::colorref_t color)
{
	auto oldFont = SelectObject(hdc,
		CreateFontW(FONT_SIZE, 0, 0, 0, FONT_WEIGHT, FALSE, FALSE, FALSE, 0, 0, 0, 0, 0, FONT_FAMILY.c_str())
	);
	SetBkMode(hdc, TRANSPARENT);

	auto oldColor = SetTextColor(hdc, color);

	w32::rect_t rc;
	SetRect(&rc, x, y, 0, 0);
	DrawTextA(hdc, text.c_str(), -1, &rc, DT_NOCLIP);

	SetTextColor(hdc, oldColor);
	SelectObject(hdc, oldFont);
}
