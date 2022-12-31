#pragma once
#include "w32_types.h"
#include <memory>
#include "Detris.h"
#include <vector>
#include <string>
#include <map>

class GameView
{
public:
	struct ScoreboardData {
		int totalScore{ 0 };
		int totalBlocks{ 0 };
	};
public:
	GameView();
	~GameView();

	void SetUp(w32::hwnd_t hWnd);

	//void Draw(w32::hwnd_t hWnd, w32::rect_s bounds);
	void Draw2(w32::hdc_t hdc, w32::rect_s bounds);
	void Update();

	void OnLeftArrowKey();
	void OnRightArrowKey();
	void OnDownArrowKey();

	void OnCharKey();

	void CleanUp();

	bool IsRunning();
	bool IsGameOver();

	void Suspend();
	void Resume();
	
	void ShowMenu();

public:
	enum Props {
		Margin = 20,
		CellSize = 44,

		CellXCount = 10,
		CellYCount = 12,

		ScoreboardX = Margin,
		ScoreboardY = Margin,
		ScoreboardH = 4 * Margin,
		ScoreboardW = ScoreboardX + CellXCount * CellSize,

		GameboardX = Margin,
		GameboardY = ScoreboardH + Margin,
		GameboardH = GameboardY + CellYCount * CellSize,
		GameboardW = GameboardX + CellXCount * CellSize,

		FirstRow = 1,
		LastRow = 11,
		FirstCol = 0,
		LastCol = 9,
	};

private:
	void DrawScoreBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);
	void DrawGameBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);
	void DrawMenu(w32::hdc_t hdc, w32::rect_s bounds);
	void Stats();
	void SpawnObjects();
	void ResolveObjects();
	void CheckGameOver();
	//bool CanAddScores();
private:
	bool m_paused{ false };
	bool m_minimized{ false };
	bool m_gameover{ false };
private: 
	// THE CURRENT DETRIS IN MOTION
	Detris *m_detris; 

	// THE LIST OF DETRIS ALREADY TOUCHED DOWN
	std::vector<Detris*> m_drawable_items;

	// key = XLOC
	// value = THE CURRENT DETRIS IN XLOC
	std::map<uint_t, Detris*> m_map_of_xloc;
	// key = YLOC
	// value = THE CURRENT DETRIS IN YLOC
	std::map<uint_t, Detris*> m_map_of_yloc;
	// key = XLOC
	// value = THE LIST OF DETRIS IN COLUMN XLOC
	std::map<uint_t, std::vector<Detris*>> m_map_of_columns;
	// key = YLOC
	// value = THE LIST OF DETRIS IN ROW YLOC
	std::map<uint_t, std::vector<Detris*>> m_map_of_rows;

	ScoreboardData m_scoreboard_data;

	static uint_t TIMER_ID;
	static uint_t TIMER_TIME;

	hwnd_t m_hwnd;
};

