#pragma once
#include <map>
#include "w32_types.h"
#include <array>

using namespace w32;

struct DCell {
	//std::pair<uint_t, uint_t> Index;
	const uint_t Size{ 44 };
	uint_t X;
	uint_t Y;
	bool Marked;
};

//struct DBounds{
//	std::array<DCell, 16> Cells;
//};

class Detris
{
public:
	Detris() = delete;
	Detris(uint_t x, uint_t y, colorref_t color);
	~Detris();

	void MoveLeft();
	void MoveRight();
	void MoveDown();

	void Draw(hdc_t hdc);

	friend bool InLeft(const Detris& d, uint_t left);
	friend bool InRight(const Detris& d, uint_t right);
	friend bool InBottom(const Detris& d, uint_t bottom);
private:
	DCell cell;
	colorref_t color;
};

