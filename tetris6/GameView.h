#pragma once
#include "w32_types.h"
#include <memory>
#include "Detris.h"
#include <vector>
#include <string>
#include <map>
#include "TTimer.h"
//class GameObject;

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

	void SetUp();

	void SpawnObjects();

	//void Draw(w32::hwnd_t hWnd, w32::rect_s bounds);
	void Draw2(w32::hdc_t hdc, w32::rect_s bounds);
	void Update();

	void OnLeftArrowKey();
	void OnRightArrowKey();
	void OnDownArrowKey();

	void OnCharKey();

	void CleanUp();

	void ResetTimer();
	void Tick();
	void StopTimer();
	bool IsRunning();

	void Suspend();
	void Resume();

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
	bool m_paused{ false };
	bool m_minimized{ false };
private: 
	//std::unique_ptr<GameObject> m_gameObject;
	// THE CURRENT DETRIS IN MOTION
	Detris *m_detris; 

	// THE LIST OF DETRIS ALREADY TOUCHED DOWN
	std::vector<Detris*> m_detris_vec;
	std::map<uint_t, Detris*> m_detris_map_x_loc;
	std::map<uint_t, std::vector<Detris*>> m_map_of_columns;

	ScoreboardData m_scoreboard_data;
	// THE CELL LOCATIONS OF THE ENTIRE GAMEBOARD.
	static uint_t CellsX[CellXCount];
	static uint_t CellsY[CellYCount];
	
	static float StepFactor;

	TTimer m_timer;
};

