#include "stdafx.h"
#include "GameView.h"
#include "GameObject.h"
#include "TGraphics.h"
#include "Detris.h"
#include <random>
#include <sstream>

uint_t GameView::CellsX[CellXCount];
uint_t GameView::CellsY[CellYCount];

GameView::GameView()
{
	m_detris = nullptr;
	for (int i = 0; i < CellXCount; i++) {
		CellsX[i] = i + 1;
	}
	for (int i = 0; i < CellYCount; i++) {
		CellsY[i] = i + 1;
	}
}


GameView::~GameView()
{
}

void GameView::SetUp()
{
	//m_gameObject = std::make_unique<GameObject>(); // using default constructor
	m_detris = new Detris(GameboardX, GameboardY, CellSize, Colors::DarkSalmon);

}

void GameView::SpawnObjects()
{
	// (1 ??? ) DELETE THE PREVIOUS DETRIS AND SET TO NULL
	// (2) ALLOCATE A NEW RANDOM DETRIS
	w32::colorref_t colors[7] = { Colors::Red, Colors::Green, Colors::Blue,
	Colors::Yellow, Colors::Purple, Colors::Cyan, Colors::AntiqueWhite };

	std::random_device rd;
	std::default_random_engine re{ rd() };
	std::uniform_int_distribution<int> uid(0, 6);

	auto color = colors[uid(re)];

	m_detris = new Detris(
		GameboardX + (3 * CellSize),
		GameboardY,
		CellSize,
		color
	);
}

void GameView::Draw2(w32::hdc_t hdc, w32::rect_s bounds)
{
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

	// LOOP THROUGH THE DETRIS VECTOR AND DRAW ALL ITEMS
	for (auto d : m_detris_vec) {
		d->Draw(hdc);
	}

	// DRAW THE CURRENT DETRIS
	if (m_detris) {
		m_detris->Draw(hdc);
	}
}

void GameView::Update()
{
	//if (m_gameObject) {

	//}
	if (!m_detris) return;

	m_detris->SetXLoc(
		(m_detris->GetX() / CellSize) + 1
	);

	m_detris->SetYLoc(
		((m_detris->GetY() / CellSize) - 2) + 1
	);

	std::stringstream ssX;
	ssX << "X Loc: " << m_detris->GetXLoc() << std::endl;
	OutputDebugStringA(ssX.str().c_str());

	std::stringstream ssY;
	ssY << "Y Loc: " << m_detris->GetYLoc() << std::endl;
	OutputDebugStringA(ssY.str().c_str());

	// COLLISION WITH THE TOP OF A DRAWN DETRIS
	for (auto d : m_detris_vec) {
		// IF THE CURRENT DETRIS IS FALLING IN THE SAME COLUMN
		// AS THE DRAWN DETRIS
		auto cX = m_detris->GetXLoc();
		auto pX = d->GetXLoc();

		if (cX == pX) {
			// THEN CHECK FOR COLLISION BETWEEN THE BOTTOM OF THE CURRENT
			// DETRIS AND THE TOP OF THE DRAWN DETRIS IN THIS COLUMN
			if (InTop(m_detris, d->GetY())) {
				// (1) SET ITS TOUCHDOWN FLAG TO TRUE
				// (2) MAKE IT STAY ONE LEVEL ABOVE THE DRAWN DETRIS IN THE COLUMN
				// (3) ADD IT TO THE LIST OF ALREADY SPAWNED DETRIS
				// (4) SPAWN A NEW DETRIS AT THE TOP
				m_detris->TouchDown(true);
				m_detris_vec.push_back(m_detris);
				m_scoreboard_data.totalBlocks = m_detris_vec.size();
				SpawnObjects();

				return;
			}
		}
	}
	// COLLISION WITH THE BOTTOM OF THE GAME AREA
	if (!InTop(m_detris, GameboardH)) {
		m_detris->MoveDown();
	}
	else
	{
		// (1) PREVENT DETRIS FROM MOVING ANY FURTHER
		// (2) ADD THIS DETRIS TO THE LIST OF TOUCHED DOWN DETRIS
		// (3 - OPTIONAL) SPAWN A NEW DETRIS AT THE TOP
		m_detris->TouchDown(true);
		m_detris_vec.push_back(m_detris);
		m_scoreboard_data.totalBlocks = m_detris_vec.size();
		SpawnObjects();
	}
}

void GameView::OnLeftArrowKey()
{
	//if (m_gameObject) {

	//}

	OutputDebugString(L"\nGameView::OnLeftArrowKey\n");
	if (m_detris) {
		// COLLISION WITH THE LEFT SIDE OF THE GAME AREA
		if (!InLeft(m_detris, GameboardX)) {
			m_detris->MoveLeft();
		}
	}
}

void GameView::OnRightArrowKey()
{
	//if (m_gameObject) {

	//}
	OutputDebugString(L"\nGameView::OnRightArrowKey\n");
	if (m_detris) {
		// COLLISION WITH THE RIGHT SIDE OF THE GAME AREA
		if (!InRight(m_detris, GameboardW)) {
			m_detris->MoveRight();
		}
	}
}

void GameView::OnDownArrowKey()
{
	//if (m_gameObject) {

	//}
	OutputDebugString(L"\nGameView::OnDownArrowKey\n");


	if (!m_detris) {
		return;
	}

	// IF THE DOWN ARROW IS PRESSED,
	// (1) LOOP THROUGH ALL THE DRAWN DETRIS
	// - IF THE CURRENT DETRIS IS ON THE SAME COLUMN AS THE DRAWN
	//   DETRIS, IT SHOULD DROP ON TOP THE DRAWN DETRIS
	// (2) IF THERE IS NO DRAWN DETRIS AT THAT COLUMN, THEN
	//      THE CURRENT DETRIS SHOULD JUST DROP TO THE BOTTOM OF 
	//      THE GAME AREA.

	// COLLISION WITH THE TOP OF A DRAWN DETRIS

	// GET THE DRAWN DETRIS WITH THE LEAST YLOC
	uint_t leastY = CellYCount;
	for (size_t i = 0; i < m_detris_vec.size(); i++) {
		auto prev = m_detris_vec.at(i);
		auto next = m_detris_vec.at(i + 1);

		//  SORT ALL DRAWN DETRIS IN ASCENDING ORDER
		// THE ONE CLOSEST TO THE TOP OF THE SORT SHOULD BE THE ONE
		//  TO BE TESTED AGAINST.
		if (prev->GetYLoc() < next->GetYLoc()) {
			leastY = prev->GetYLoc();
		}
	}

	for (auto d : m_detris_vec) {

		// IF THE CURRENT DETRIS IS FALLING IN THE SAME COLUMN
		// AS THE DRAWN DETRIS
		auto cX = m_detris->GetXLoc();
		auto pX = d->GetXLoc();

		if (cX == pX) {
			m_detris->SetYLoc(leastY - 1);
			m_detris->SetY(d->GetY() - CellSize);
			m_detris->TouchDown(true);
			m_detris_vec.push_back(m_detris);
			m_scoreboard_data.totalBlocks = m_detris_vec.size();
			SpawnObjects();
			return;
		}
	}



	// COLLISION WITH THE BOTTOM OF THE GAME AREA
	m_detris->SetYLoc(
		CellsY[CellYCount-1]
	);
	m_detris->SetY(GameboardH - CellSize);
	m_detris->TouchDown(true);
	m_detris_vec.push_back(m_detris);
	m_scoreboard_data.totalBlocks = m_detris_vec.size();
	SpawnObjects();
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

	std::stringstream totalScore;
	totalScore << "Total Score: " << m_scoreboard_data.totalScore;
	TGraphics::WriteTextA(
		hdc,
		totalScore.str(),
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
	std::stringstream totalBlocks;
	totalBlocks << "Total Blocks: " << m_scoreboard_data.totalBlocks;

	TGraphics::WriteTextA(
		hdc,
		totalBlocks.str(),
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
