#pragma once
#include <map>
#include "w32_types.h"
#include <array>

using namespace w32;

struct DCell {
	//std::pair<uint_t, uint_t> Index;
	// SINCE THIS REPRESENTS A SQUARE, THE SIZE MUST BE SAME
	uint_t Size;
	// PIXEL UNITS
	uint_t X;
	uint_t Y;
	// GRID  UNITS
	uint_t LocX{ 1 };
	uint_t LocY{ 1 };
	bool Marked;
};

//struct DBounds{
//	std::array<DCell, 16> Cells;
//};

class Detris
{
public:
	Detris() = delete;
	Detris(uint_t x, uint_t y, uint_t cellSize, colorref_t color);
	~Detris();

	void MoveLeft();
	void MoveRight();
	void MoveDown();

	void Draw(hdc_t hdc);

	friend bool InLeft(const Detris* d, uint_t left);
	friend bool InRight(const Detris* d, uint_t right);
	friend bool InTop(const Detris* d, uint_t top);

	bool TouchedDown();
	void TouchDown(bool);


	uint_t GetXLoc();
	uint_t GetYLoc();
	void SetXLoc(uint_t xLoc);
	void SetYLoc(uint_t yLoc);

	uint_t GetX();
	uint_t GetY();

	// USEFUL FOR FAST DROPPING THE DETRIS
	void SetY(uint_t y);
private:
	DCell cell;
	colorref_t color;
	bool touched_down;
};

