#include "stdafx.h"
#include "GameView.h"
#include "GameObject.h"
#include "TGraphics.h"
#include "Detris.h"

GameView::GameView()
{
}


GameView::~GameView()
{
}

void GameView::SetUp()
{
	//m_gameObject = std::make_unique<GameObject>(); // using default constructor
	detris = new Detris(GameboardX, GameboardY, Colors::DarkSalmon);
}

void GameView::Draw(w32::hdc_t hdc, w32::rect_s bounds)
{
	//if (m_gameObject) {

	//}
	// BEFORE GAME STARTS, DRAW MENU
	// DrawMenu(hdc, bounds); // TODO: REALLY WORK ON THIS FUNCTION

	// WHEN GAME STARTS, DRAW GAME AREA

	// Draw Scoreboard
	DrawScoreBoard(hdc, 
		w32::GetRect(ScoreboardX, ScoreboardY, ScoreboardW, ScoreboardH), 
		Colors::Azure
	);

	// Draw Gameboard
	DrawGameBoard(hdc, 
		w32::GetRect(GameboardX, GameboardY, GameboardW, GameboardH), 
		Colors::Orange
	);

	if (detris) {
		detris->Draw(hdc);
	}

	// Draw Tetriminoes
	// LEFT SIDE
	//{ // BOX TETRIS
	//	DCell cell;
	//	cell.X = GameboardX;
	//	cell.Y = GameboardY;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::Aquamarine
	//	);
	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::Aquamarine
	//	);
	//	cell.X = GameboardX;
	//	cell.Y = GameboardY + cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::Aquamarine
	//	);

	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY + cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::Aquamarine
	//	);
	//}

	//{ // LINE TETRIS
	//	DCell cell;
	//	cell.X = GameboardX;
	//	cell.Y = GameboardY + 3*cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumBlue
	//	);
	//	
	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY + 3 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumBlue
	//	);

	//	cell.X = GameboardX + 2*cell.Size;
	//	cell.Y = GameboardY + 3 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumBlue
	//	);

	//	cell.X = GameboardX + 3*cell.Size;
	//	cell.Y = GameboardY + 3 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumBlue
	//	);
	//}

	//{ // L TETRIS
	//	DCell cell;
	//	cell.X = GameboardX;
	//	cell.Y = GameboardY + 5 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumPurple
	//	);

	//	cell.X = GameboardX;
	//	cell.Y = GameboardY + 6 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumPurple
	//	);

	//	cell.X = GameboardX;
	//	cell.Y = GameboardY + 7 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumPurple
	//	);

	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY + 7 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumPurple
	//	);
	//}

	//{ // L TETRIS
	//	DCell cell;
	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY + 9 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumSeaGreen
	//	);

	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY + 10 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumSeaGreen
	//	);

	//	cell.X = GameboardX + cell.Size;
	//	cell.Y = GameboardY + 11 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumSeaGreen
	//	);

	//	cell.X = GameboardX;
	//	cell.Y = GameboardY + 11 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumSeaGreen
	//	);
	//}

	//// RIGHT SIDE
	//{ // S TETRIS
	//	DCell cell;
	//	cell.X = GameboardW - cell.Size;
	//	cell.Y = GameboardY+ 10* cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumOrchid
	//	);

	//	cell.X = GameboardW - 2*cell.Size;
	//	cell.Y = GameboardY + 10 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumOrchid
	//	);


	//	cell.X = GameboardW - 2 * cell.Size;
	//	cell.Y = GameboardY + 11 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumOrchid
	//	);


	//	cell.X = GameboardW - 3 * cell.Size;
	//	cell.Y = GameboardY + 11 * cell.Size;

	//	TGraphics::DrawStrokedRect2(
	//		hdc,
	//		cell.X, cell.Y, cell.Size, cell.Size,
	//		Colors::MediumOrchid
	//	);
	//}

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

	OutputDebugString(L"GameView::OnLeftArrowKey");
	if (detris) {
		detris->MoveLeft();
	}
}

void GameView::OnRightArrowKey()
{
	//if (m_gameObject) {

	//}
	OutputDebugString(L"\nGameView::OnRightArrowKey\n");
	if (detris) {
		detris->MoveRight();
	}
}

void GameView::OnDownArrowKey()
{
	//if (m_gameObject) {

	//}
	OutputDebugString(L"\nGameView::OnDownArrowKey\n");
	if (detris) {
		detris->MoveDown();
	}
}

void GameView::OnCharKey()
{
	//if (m_gameObject) {

	//}
	OutputDebugString(L"\nGameView::OnCharKey\n");
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

	int x{ bounds.left };
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
