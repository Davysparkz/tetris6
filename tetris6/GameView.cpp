#include "stdafx.h"
#include "GameView.h"
#include "GameObject.h"
#include "TGraphics.h"
#include "Detris.h"
#include <random>
#include <sstream>
#include <algorithm>
#include <functional>

uint_t  GameView::TIMER_ID = 1;
uint_t  GameView::TIMER_TIME = 200;

// ROW #1 --> YLOC = GAMEOVER
// ROW #2 --> YLOC = 1
// ROW #3 --> YLOC = 2
// ROW #4 --> YLOC = 3
// ROW #5 --> YLOC = 4
// ROW #6 --> YLOC = 5
// ROW #7 --> YLOC = 6
// ROW #8 --> YLOC = 7
// ROW #9 --> YLOC = 8
// ROW #10 --> YLOC = 9
// ROW #11 --> YLOC = 10
// ROW #12 --> YLOC = 11

GameView::GameView()
{
	m_detris = nullptr;
}


GameView::~GameView()
{
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
	for (auto d : m_drawable_items) {
		d->Draw(hdc);
	}

	// DRAW THE CURRENT DETRIS
	if (m_detris) {
		m_detris->Draw(hdc);
	}

	//if (m_gameover) {
//		ShowMenu();
	//}
}


void GameView::SetUp(w32::hwnd_t hWnd)
{
	m_hwnd = hWnd;

	SetTimer(hWnd, TIMER_ID, TIMER_TIME, NULL);
}

void GameView::SpawnObjects()
{
	// (1 ??? ) DELETE THE PREVIOUS DETRIS AND SET TO NULL
	// (2) ALLOCATE A NEW RANDOM DETRIS
	w32::colorref_t colors[7] = { Colors::Red, Colors::Green, Colors::Blue,
	Colors::Yellow, Colors::Purple, Colors::Cyan, Colors::AntiqueWhite };

	std::random_device rd;
	std::default_random_engine re{ rd() };
	std::uniform_int_distribution<int> uid_col(0, 6);
	std::uniform_int_distribution<int> uid_loc(0, CellXCount - 1);

	auto color = colors[uid_col(re)];
	auto loc = uid_loc(re);

	loc = 1;

	m_detris = new Detris(
		GameboardX + (loc * CellSize),
		GameboardY,
		CellSize,
		color
	);

}

void GameView::ResolveObjects()
{
	m_detris->TouchDown(true);

	auto yLoc = m_detris->GetYLoc();
	auto xLoc = m_detris->GetXLoc();

	m_drawable_items.push_back(m_detris);
	m_map_of_xloc[xLoc] = m_detris;
	m_map_of_yloc[yLoc] = m_detris;

	std::for_each(m_map_of_xloc.begin(), m_map_of_xloc.end(), [&](std::pair<uint_t, Detris*> item) {
		if (item.first == xLoc) {
			m_map_of_columns[xLoc].push_back(item.second);
		}
	});
	std::for_each(m_map_of_yloc.begin(), m_map_of_yloc.end(), [&](std::pair<uint_t, Detris*> item) {
		if (item.first == yLoc) {
			m_map_of_rows[yLoc].push_back(item.second);
		}
	});

	m_scoreboard_data.totalBlocks = m_drawable_items.size();

	Stats();
}


void GameView::Update()
{
	CheckGameOver();
	// THIS TEST POSES AN IMPORTANT ONE AT BEST
	if (m_gameover) { return; }

	if (!m_detris) {
		SpawnObjects();
	}

	m_detris->MoveDown();

	auto xLoc = ((m_detris->GetX() - GameboardX) / CellSize);
	m_detris->SetXLoc(
		xLoc
	);
	auto yLoc = ((m_detris->GetY() - GameboardY) / CellSize);
	m_detris->SetYLoc(
		yLoc
	);

	// COLLISION WITH THE TOP OF A DRAWN DETRIS
	uint_t leastY = GameboardH;
	if (m_map_of_columns.find(m_detris->GetXLoc()) != m_map_of_columns.end()) {
		std::map<uint_t, std::vector<Detris*>> map(m_map_of_columns);

		std::sort(
			map[m_detris->GetXLoc()].begin(),
			map[m_detris->GetXLoc()].end(),
			[](Detris* a, Detris* b) {
			return a->GetYLoc() < b->GetYLoc();
		});
		leastY = map[m_detris->GetXLoc()][0]->GetY();

		// IF THE CURRENT DETRIS IS FALLING IN THE SAME COLUMN
		//	 AS THE DRAWN DETRIS
		if (
			InTop(m_detris, leastY)
			) {
			ResolveObjects();

			SpawnObjects();
			return;
		}
	}

	// COLLISION WITH THE BOTTOM OF THE GAME AREA
	if (
		InTop(m_detris, GameboardH)
		) {
		// (1) PREVENT DETRIS FROM MOVING ANY FURTHER
		// (2) ADD THIS DETRIS TO THE LIST OF TOUCHED DOWN DETRIS
		// (3) SPAWN A NEW DETRIS AT THE TOP

		ResolveObjects();

		SpawnObjects();
	}

}

void GameView::OnLeftArrowKey()
{
	if (m_gameover) return;

	if (m_detris) {

		// COLLISION WITH THE LEFT SIDE OF AN ALREADY 
		// DRAWN DETRIS
		auto leftXLoc = m_detris->GetXLoc() - 1;
		if (m_map_of_xloc.find(leftXLoc) != m_map_of_xloc.end()) {
			uint_t leastYLoc = CellYCount;
			uint_t leastY = GameboardH;
			std::map<uint_t, std::vector<Detris*>> map(m_map_of_columns);

			std::sort(
				map[leftXLoc].begin(),
				map[leftXLoc].end(),
				[](Detris* a, Detris* b) {
				return a->GetYLoc() < b->GetYLoc();
			});
			leastYLoc = map[leftXLoc][0]->GetYLoc();

			// PREVENT FROM MOVING TO THE LEFT IF THERE IS
			// ALREADY A DETRIS TO ITS LEFT
			auto l = m_detris->GetYLoc();
			auto r = (leastYLoc - 1);
			if (l >= r) {
				return;
			}
		}

		// COLLISION WITH THE LEFT SIDE OF THE GAME AREA
		if (!InLeft(m_detris, GameboardX)) {
			m_detris->MoveLeft();
			//auto xLoc = ((m_detris->GetX() - GameboardX) / CellSize);
			//m_detris->SetXLoc(
			//	xLoc
			//);
		}
	}
}

void GameView::OnRightArrowKey()
{
	if (m_gameover) return;

	if (m_detris) {

		// COLLISION WITH THE RIGHT SIDE OF AN ALREADY 
		// DRAWN DETRIS
		auto rightXLoc = m_detris->GetXLoc() + 1;
		if (m_map_of_xloc.find(rightXLoc) != m_map_of_xloc.end()) {
			uint_t leastYLoc = CellYCount;
			uint_t leastY = GameboardH;
			std::map<uint_t, std::vector<Detris*>> map(m_map_of_columns);

			std::sort(
				map[rightXLoc].begin(),
				map[rightXLoc].end(),
				[](Detris* a, Detris* b) {
				return a->GetYLoc() < b->GetYLoc();
			});
			leastYLoc = map[rightXLoc][0]->GetYLoc();

			// PREVENT FROM MOVING TO THE RIGHT IF THERE IS
			// ALREADY A DETRIS TO ITS RIGHT
			auto l = m_detris->GetYLoc();
			auto r = (leastYLoc - 1);
			if (l >= r) {
				return;
			}
		}

		// COLLISION WITH THE RIGHT SIDE OF THE GAME AREA
		if (!InRight(m_detris, GameboardW)) {
			m_detris->MoveRight();
			//auto xLoc = ((m_detris->GetX() - GameboardX) / CellSize);
			//m_detris->SetXLoc(
			//	xLoc
			//);
		}
	}
}

void GameView::OnDownArrowKey()
{
	if (m_gameover) return;

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
	uint_t leastYLoc = CellYCount;
	auto xLoc = ((m_detris->GetX() - GameboardX) / CellSize);
	if (m_map_of_xloc.find(xLoc) != m_map_of_xloc.end()) {
		std::map<uint_t, std::vector<Detris*>> map(m_map_of_columns);

		std::sort(
			map[xLoc].begin(),
			map[xLoc].end(),
			[](Detris* a, Detris* b) {
			return a->GetYLoc() < b->GetYLoc();
		});
		leastYLoc = map[xLoc][0]->GetYLoc();

		// IF THE CURRENT DETRIS IS FALLING IN THE SAME COLUMN
		//	 AS THE DRAWN DETRIS
		m_detris->SetYLoc(
			leastYLoc - 1
		);
		auto y = GameboardY + (m_detris->GetYLoc() * CellSize);

		m_detris->SetY(
			y
		);
	}
	else {
		// COLLISION WITH THE BOTTOM OF THE GAME AREA
		m_detris->SetYLoc(
			LastRow
		);
		auto y = GameboardY + (m_detris->GetYLoc() * CellSize);
		m_detris->SetY(
			y
		);
	}

	ResolveObjects();
	SpawnObjects();
}

void GameView::Stats()
{
	std::stringstream ss;
	for (auto m : m_map_of_columns) {
		ss << "Column #" << m.first << ": " << m.second.size() << " DETRIS\n";

		//if (m.second.size() > 9) {
			for (auto i : m.second) {
				ss << " --> " << i->GetYLoc() << "\n";
			}
	//	}
	}
	OutputDebugStringA(ss.str().c_str());
}

void GameView::CheckGameOver()
{

	// (1) CHECK THE MAP OF ROWS TO FIND IF ROW #0 CONTAINS
	//     AT LEAST AN ITEM IN ITS LIST
	// (2) IF SUCH AN ITEM EXISTS, RETURN TRUE AS A SIGNAL THAT 
	//      THE GAME IS OVER.

	for (auto row : m_map_of_columns) {

		for (auto item : row.second) {
			auto yLoc = item->GetYLoc();
			auto x = item->GetX();
			auto againstX = m_detris->GetX();
			// IT IS UTTERLY IMPORTANT TO TEST AGAINST THE INCOMING DETRIS'
			// X-POS IN FAVOUR OF ITS X-LOC, AS ON CREATION, ITS X-POS IS MORE
			// UP TO DATE THAN ITS X-LOC
			if (
				yLoc == FirstRow &&
				x == againstX
				)
			{
				m_gameover = true;
				return;
			}
		}
	}

}


void GameView::OnCharKey()
{
	OutputDebugString(L"\nGameView::OnCharKey\n");
}

void GameView::CleanUp()
{
	KillTimer(m_hwnd, TIMER_ID);
}

bool GameView::IsRunning()
{
	return !this->m_paused;
}

bool GameView::IsGameOver()
{
	return m_gameover;
}

void GameView::Suspend()
{
	if (m_gameover) return;
	m_paused = true;
	KillTimer(m_hwnd, TIMER_ID);
}

void GameView::Resume()
{
	if (m_gameover) return;
	m_paused = false;
	SetTimer(m_hwnd, TIMER_ID, TIMER_TIME, NULL);
}

void GameView::ShowMenu()
{
	DrawMenu(
		GetDC(m_hwnd),
		w32::GetRect(GameboardX, GameboardY, GameboardW, GameboardH)
	);
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

	const auto MENU_X = bounds.left + ((bounds.right - bounds.left) / 2) - (MENU_W / 2);
	const auto MENU_Y = bounds.top + ((bounds.bottom - bounds.top) / 2) - (MENU_H / 2);

	int PADDING = 8;
	int MENUITEM_H = 40;

	int x = MENU_X;
	int y = MENU_Y;
	int w = MENU_X + MENU_W;
	int h = MENU_Y + MENU_H;

	w32::point_s mouse;
	GetCursorPos(&mouse);

	w32::colorref_t hoverClr = Colors::Beige;
	w32::colorref_t borderClr;

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

	borderClr = !PtInRect(&w32::GetRect(x, y, w, h), mouse) ? Colors::DodgerBlue : hoverClr;

	// DRAW MENUITEM BOUND BOX
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		borderClr,
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
	borderClr = !PtInRect(&w32::GetRect(x, y, w, h), mouse) ? Colors::Red : hoverClr;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		borderClr,
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
	borderClr = !PtInRect(&w32::GetRect(x, y, w, h), mouse) ? Colors::Green : hoverClr;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		borderClr,
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
	borderClr = !PtInRect(&w32::GetRect(x, y, w, h), mouse) ? Colors::Lavender : hoverClr;
	TGraphics::DrawStrokedRect(
		hdc,
		x,
		y,
		w,
		h,
		borderClr,
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
