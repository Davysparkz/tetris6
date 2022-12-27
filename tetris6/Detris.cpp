#include "stdafx.h"
#include "Detris.h"
#include "TGraphics.h"

Detris::Detris(uint_t x, uint_t y, uint_t cellSize, colorref_t color)
{
	this->cell.X = x;
	this->cell.Y = y;
	this->color = color;
	this->touched_down = false;
	this->cell.LocY = 1;
	this->cell.Size = cellSize;
}


Detris::~Detris()
{
}

void Detris::MoveLeft()
{
	if (this->touched_down) return;
	this->cell.X -= this->cell.Size;
	this->cell.LocX = this->cell.X / this->cell.Size;
}

void Detris::MoveRight()
{
	if (this->touched_down) return;
	this->cell.X += this->cell.Size;
	this->cell.LocX = this->cell.X / this->cell.Size;
}

void Detris::MoveDown()
{
	if (this->touched_down) return;
	this->cell.Y += this->cell.Size;
	this->cell.LocY = (this->cell.Y / this->cell.Size) - 3;
}

bool Detris::TouchedDown() {
	return touched_down;
}

void Detris::TouchDown(bool td) {
	this->touched_down = td;
}

uint_t Detris::GetXLoc()
{
	return this->cell.LocX;
}

uint_t Detris::GetYLoc()
{
	return this->cell.LocY;
}

void Detris::SetXLoc(uint_t xLoc)
{
	this->cell.LocX = xLoc;
}

void Detris::SetYLoc(uint_t yLoc)
{
	this->cell.LocY = yLoc;
}

uint_t Detris::GetX()
{
	return this->cell.X;
}

uint_t Detris::GetY()
{
	return this->cell.Y;
}

void Detris::SetY(uint_t y)
{
	this->cell.Y = y;
}

void Detris::Draw(hdc_t hdc)
{
	TGraphics::DrawStrokedRect2(
		hdc,
		this->cell.X,
		this->cell.Y,
		this->cell.Size,
		this->cell.Size,
		color
	);
}

bool InLeft(const Detris * d, uint_t left)
{
	if (d) {
		if (d->cell.X <= left) {
			return true;
		}
	}
	return false;
}

bool InRight(const Detris * d, uint_t right)
{
	if (d) {
		if ((d->cell.X + d->cell.Size) >= right) {
			return true;
		}
	}
	return false;
}

bool InTop(const Detris * d, uint_t top)
{
	if (d) {
		if ((d->cell.Y + d->cell.Size) >= top) {
			return true;
		}
	}
	return false;
}
