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
