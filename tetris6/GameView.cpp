#include "stdafx.h"
#include "GameView.h"
#include "GameObject.h"
#include "TGraphics.h"

GameView::GameView()
{
}


GameView::~GameView()
{
}

void GameView::SetUp()
{
	//m_gameObject = std::make_unique<GameObject>(); // using default constructor
}

void GameView::Draw(w32::hdc_t hdc, w32::rect_s bounds)
{
	//if (m_gameObject) {

	//}
	const auto MENU_W = 200;
	const auto MENU_H = 200;

	const auto MENU_X = bounds.right / 2 - MENU_W / 2;
	const auto MENU_Y = bounds.bottom / 2 - MENU_H / 2;

	int PADDING = 8;
	int MENUITEM_H = 40;

	int x = MENU_X;
	int y = MENU_Y;
	int w = MENU_X + MENU_W;
	int h = MENU_Y + MENU_H;

	// DRAW MENU BOUND BOX
	TGraphics::DrawStrokedRect( 
		hdc, 
		x, 
		y, 
		w, 
		h,
		Colors::Firebrick
	);

	x = x + PADDING;
	w = w - PADDING;
	y = y + PADDING; 
	h = y + MENUITEM_H;
	// DRAW MENUITEM BOUND BOX
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::DodgerBlue,
		TGraphics::LineStyle::SOLID,
		1
	);

	
	// WRITE MENUITEM CONTENT
	TGraphics::WriteTextA(
		hdc,
		"New Game",
		w32::GetRect(x, y, w, h),
		Colors::AliceBlue,
		MENUITEM_H,
		TGraphics::TextAlign::CENTER
	);


	x = x;
	w = w;
	y = h + PADDING;
	h = y + MENUITEM_H;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::Red,
		TGraphics::LineStyle::SOLID,
		1
	);

	
	// WRITE MENUITEM CONTENT
	TGraphics::WriteTextA(
		hdc,
		"High Scores",
		w32::GetRect(x, y, w, h),
		Colors::AliceBlue,
		MENUITEM_H,
		TGraphics::TextAlign::CENTER
	);

	x = x;
	w = w;
	y = h + PADDING;
	h = y + MENUITEM_H;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::Green,
		TGraphics::LineStyle::SOLID,
		1
	);

	
	// WRITE MENUITEM CONTENT
	TGraphics::WriteTextA(
		hdc,
		"Settings",
		w32::GetRect(x, y, w, h),
		Colors::AliceBlue,
		MENUITEM_H,
		TGraphics::TextAlign::CENTER
	);

	x = x;
	w = w;
	y = h + PADDING;
	h = y + MENUITEM_H;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::Lavender,
		TGraphics::LineStyle::SOLID,
		1
	);

	
	 // WRITE MENUITEM CONTENT
	TGraphics::WriteTextA(
		hdc,
		"About",
		w32::GetRect(x, y, w, h),
		Colors::AliceBlue,
		MENUITEM_H,
		TGraphics::TextAlign::CENTER
	);

	
}

void GameView::Update()
{
	//if (m_gameObject) {

	//}
}

void GameView::OnLeftArrowKey()
{
	//if (m_gameObject) {

	//}
}

void GameView::OnRightArrowKey()
{
	//if (m_gameObject) {

	//}
}

void GameView::OnDownArrowKey()
{
	//if (m_gameObject) {

	//}
}

void GameView::OnCharKey()
{
	//if (m_gameObject) {

	//}
}

void GameView::CleanUp()
{
	//if (m_gameObject) {

	//}
}
