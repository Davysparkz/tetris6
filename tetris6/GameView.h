#pragma once
#include "w32_types.h"
#include <memory>

//class GameObject;

class GameView
{
public:
	GameView();
	~GameView();

	void SetUp();

	void Draw(w32::hdc_t hdc, w32::rect_s bounds);
	void Update();

	void OnLeftArrowKey();
	void OnRightArrowKey();
	void OnDownArrowKey();

	void OnCharKey();

	void CleanUp();

private:
	void DrawScoreBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);
	void DrawGameBoard(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);
	void DrawMenu(w32::hdc_t hdc, w32::rect_s bounds);
	void DrawLineTetris(w32::hdc_t hdc, w32::rect_s bound, w32::colorref_t color);
	void DrawBoxTetris(w32::hdc_t hdc, w32::rect_s bound, w32::colorref_t color);
	void DrawLTetris(w32::hdc_t hdc, w32::rect_s bounds, w32::colorref_t color);

private: 
	//std::unique_ptr<GameObject> m_gameObject;
};

