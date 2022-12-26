#include "stdafx.h"
#include "Detris.h"
#include "TGraphics.h"

Detris::Detris(uint_t x, uint_t y, colorref_t color)
{
	this->cell.X = x;
	this->cell.Y = y;
	this->color = color;
}


Detris::~Detris()
{
}

void Detris::MoveLeft()
{
	this->cell.X -= this->cell.Size;
}

void Detris::MoveRight()
{
	this->cell.X += this->cell.Size;
}

void Detris::MoveDown()
{
	this->cell.Y += this->cell.Size;
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

bool InLeft(const Detris & d, uint_t left)
{
	if (d.cell.X <= left) {
		return true;
	}
	return false;
}

bool InRight(const Detris & d, uint_t right)
{
	if ((d.cell.X+d.cell.Size) >= right) {
		return true;
	}
	return false;
}

bool InBottom(const Detris & d, uint_t bottom)
{
	if ((d.cell.Y + d.cell.Size) >= bottom) {
		return true;
	}
	return false;
}
