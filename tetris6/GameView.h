#pragma once
#include "w32_types.h"
#include <memory>
#include "Detris.h"

//class GameObject;

class GameView
{
public:
	GameView();
	~GameView();

	void SetUp();

	//void Draw(w32::hwnd_t hWnd, w32::rect_s bounds);
	void Draw2(w32::hdc_t hdc, w32::rect_s bounds);
	void Update();

	void OnLeftArrowKey();
	void OnRightArrowKey();
	void OnDownArrowKey();

	void OnCharKey();

	void CleanUp();

public:
	enum Props {
		Margin  = 20,
		CellSize = 44,

		CellXCount = 10,
		CellYCount = 12,

		ScoreboardX = Margin, 
		ScoreboardY = Margin, 
		ScoreboardH = 4*Margin,
		ScoreboardW = ScoreboardX + CellXCount * CellSize,

		GameboardX = Margin,
		GameboardY = ScoreboardH + Margin,
		GameboardH = GameboardY + CellYCount * CellSize,
		GameboardW = GameboardX + CellXCount * CellSize,
	};

private:
	void DrawScoreBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);
	void DrawGameBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);
	void DrawMenu(w32::hdc_t hdc, w32::rect_s bounds);
private: 
	//std::unique_ptr<GameObject> m_gameObject;
	Detris *detris;
};

