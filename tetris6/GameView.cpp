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
	// BEFORE GAME STARTS, DRAW MENU
	// DrawMenu(hdc, bounds); // TODO: REALLY WORK ON THIS FUNCTION
	// WHEN GAME STARTS, DRAW GAME AREA

	int x{ 20 }, y{ 20 }, w{ bounds.right - 20 }, h{ 80 };
	// Draw Scoreboard
	DrawScoreBoard(hdc, w32::GetRect(x, y, w, h), Colors::Azure);

	y = 100;
	h = bounds.bottom - 20;

	// Draw Gameboard
	DrawGameBoard(hdc, w32::GetRect(x, y, w, h), Colors::Orange);

	w = x + 44;
	h = y + 44;
	// Draw Tetriminoes
	DrawLineTetris(hdc, w32::GetRect(x, y, w, h), Colors::Coral);

	y = y + 88;
	w = x + 44;
	h = y + 44;
	DrawBoxTetris(hdc, w32::GetRect(x, y, w, h), Colors::Lime);

	y = y + 132;
	w = x + 44;
	h = y + 44;
	DrawLTetris(hdc, w32::GetRect(x, y, w, h), Colors::MidnightBlue);
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

void GameView::DrawScoreBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color)
{
	// DRAW FRAME
	TGraphics::DrawStrokedRect(hdc, WIDEN_RECT(bounds), color);
	int x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 }, m{ 5 };

	// WRITE TOTAL SCORE
	x = bounds.left + m;
	w = x + 120;
	y = bounds.top + m;
	h = y + 20;
	TGraphics::WriteTextA(
		hdc,
		"Total Score: 0000",
		w32::GetRect(x, y, w, h)
	);
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::DarkGreen,
		TGraphics::LineStyle::SOLID,
		1
	);

	y = h + m;
	h = y + 20;
	// WRITE TOTAL TETRIMINO ON SCREEN
	TGraphics::WriteTextA(
		hdc,
		"Total Blocks: 0",
		w32::GetRect(x, y, w, h)
	);
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::DarkGreen,
		TGraphics::LineStyle::SOLID,
		1
	);

	// WRITE GAME TIME
	x = w + (3 * m);
	w = x + 120;
	y = bounds.top + m;
	h = y + 20;
	TGraphics::WriteTextA(
		hdc,
		"Elapsed Time: 00:00",
		w32::GetRect(x, y, w, h)
	);
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::DarkGreen,
		TGraphics::LineStyle::SOLID,
		1
	);

	// DRAW FRAME FOR NEXT TETRIMINO : towards the right of the boundary
	w = bounds.right - m;
	x = w - 80;
	y = bounds.top + m;
	h = bounds.bottom - m;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		Colors::DarkGreen,
		TGraphics::LineStyle::SOLID,
		1
	);

}

void GameView::DrawGameBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color)
{
	// DRAW BOARD BOUNDARY
	TGraphics::DrawStrokedRect(hdc, WIDEN_RECT(bounds), color);

	int x{ bounds.left + 2 };
	int sz{ 44 };
	// DRAW BOARD VERTICAL GRID
	for (int i = 1; i < 12; i++) {
		TGraphics::DrawLine(
			hdc,
			x,
			bounds.top, 
			x, 
			bounds.bottom,
			Colors::DarkSlateGray,
			TGraphics::LineStyle::DASH,
			1
			);
		x += sz;
	}

	int y{ bounds.top };
	// DRAW BOARD HORIZONTAL GRID
	for (int i = 1; i < 14; i++) {
		TGraphics::DrawLine(
			hdc,
			bounds.left,
			y,
			bounds.right,
			y,
			Colors::DarkSlateGray,
			TGraphics::LineStyle::DASH,
			1
		);
		y += sz;
	}
}

void GameView::DrawMenu(w32::hdc_t hdc, w32::rect_s bounds)
{ // TODO: REALLY WORK ON 'GameView::DrawMenu()'
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

void GameView::DrawLineTetris(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color)
{
	int x{ bounds.left }, y{ bounds.top }, w{ bounds.right }, h{ bounds.bottom };

	// DRAW FIRST BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	int diff{ w - x };
	x = w;
	w = x + diff;
	// DRAW SECOND BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diff = w - x;
	x = w;
	w = x + diff;
	// DRAW THIRD BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diff = w - x;
	x = w;
	w = x + diff;
	// DRAW FOURTH BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);
}

void GameView::DrawBoxTetris(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color)
{
	int x{ bounds.left }, y{ bounds.top }, w{ bounds.right }, h{ bounds.bottom };
	int diffX, diffY;

	// DRAW FIRST BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);


	diffX =  w - x ;
	x = w;
	w = x + diffX;
	// DRAW SECOND BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diffY = h - y;
	diffX = w - x;
	y = h;
	h = y + diffY;
	x = bounds.left;
	w = x + diffX;
	// DRAW THIRD BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diffY = h - y;
	diffX = w - x;
	x = w;
	w = x + diffX;
	// DRAW FOURTH BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);
}

void GameView::DrawLTetris(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color)
{
	int x{ bounds.left }, y{ bounds.top }, w{ bounds.right }, h{ bounds.bottom };
	int diffX, diffY;

	// DRAW FIRST BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diffY = h - y;
	diffX = w - x;
	y = h;
	h = y + diffY;
	x = bounds.left;
	w = x + diffX;
	// DRAW THIRD BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diffY = h - y;
	diffX = w - x;
	x = w;
	w = x + diffX;
	// DRAW FOURTH BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);

	diffY = h - y;
	diffX = w - x;
	x = w;
	w = x + diffX;
	// DRAW FOURTH BOX
	TGraphics::DrawStrokedRect(
		hdc,
		w32::GetRect(x, y, w, h),
		color
	);
}

