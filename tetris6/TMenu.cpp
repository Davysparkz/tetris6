#include "stdafx.h"
#include "TMenu.h"
#include "TGraphics.h"
#include <algorithm>

TBox::TBox(w32::rect_s bounds)
{
	this->bounds = bounds;
}
TBox::TBox(int x, int y, int w, int h) 
{
	this->bounds = w32::GetRect(x, y, w, h);
}
TBox::TBox(w32::rect_s bounds, w32::rect_s margin)
{
	this->bounds = bounds;
	this->margin = margin;

}
TBox::TBox(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB)
{
	this->bounds = w32::GetRect(x, y, w, h);
	this->margin = w32::GetRect(mgnL, mgnT, mgnR, mgnB);
}
TBox::TBox(w32::rect_s bounds, w32::rect_s margin, w32::rect_s padding)
{
	this->bounds = bounds;
	this->margin = margin;
	this->padding = padding;
}
TBox::TBox(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB, int padL, int padT, int padR, int padB)
{
	this->bounds = w32::GetRect(x, y, w, h);
	this->margin = w32::GetRect(mgnL, mgnT, mgnR, mgnB);
	this->padding = w32::GetRect(padL, padT, padR, padB);
}
TBox::~TBox()
{

}

TMenuItem::TMenuItem(w32::rect_s bounds) :
	TBox(bounds)
{

}
TMenuItem::TMenuItem(int x, int y, int w, int h) :
	TBox(x, y, w, h)
{

}
TMenuItem::TMenuItem(w32::rect_s bounds, w32::rect_s margin) :
	TBox(bounds, margin)
{

}
TMenuItem::TMenuItem(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB) :
	TBox(x, y, w, h, mgnL, mgnT, mgnR, mgnB)
{

}
TMenuItem::TMenuItem(w32::rect_s bounds, w32::rect_s margin, w32::rect_s padding) :
	TBox(bounds, margin, padding)
{

}
TMenuItem::TMenuItem(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB, int padL, int padT, int padR, int padB) :
	TBox(x, y, w, h, mgnL, mgnT, mgnR, mgnB)
{

}



TMenuItem::~TMenuItem()
{

}

TMenuItem & TMenuItem::SetContentTextW(std::wstring text,
	TGraphics::TextProps textProps)
{
	this->m_wText = text;
	this->m_textProps = textProps;
	this->m_wide_text_in_use = true;
	this->m_ascii_text_in_use = false;
	return *this;
}
TMenuItem & TMenuItem::SetContentTextA(std::string text,
	TGraphics::TextProps textProps)
{
	this->m_aText = text;
	this->m_textProps = textProps;
	this->m_wide_text_in_use = false;
	this->m_ascii_text_in_use = true;
	return *this;
}

void TMenuItem::Draw(w32::hdc_t hdc)
{
	// DRAW BOUNDARY
	TGraphics::DrawStrokedRect(
		hdc,
		WIDEN_RECT(this->bounds),
		Colors::Blue
	);

	// DRAW TEXT CONTENT
	if (m_ascii_text_in_use && !m_aText.empty()) {
		TGraphics::WriteTextA(
			hdc,
			this->m_aText,
			this->bounds,
			this->m_textProps
		);
	}
	if (m_wide_text_in_use && !m_wText.empty()) {
		TGraphics::WriteTextW(
			hdc,
			this->m_wText,
			this->bounds,
			this->m_textProps
		);
	}
}

TMenu::TMenu(w32::rect_s bounds) :
	TBox(bounds)
{

}
TMenu::TMenu(int x, int y, int w, int h) : 
	TBox(x, y, w, h)
{

}
TMenu::TMenu(w32::rect_s bounds, w32::rect_s margin) :
	TBox(bounds, margin)
{

}
TMenu::TMenu(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB) :
	TBox(x, y, w, h, mgnL, mgnT, mgnR, mgnB)
{

}
TMenu::TMenu(w32::rect_s bounds, w32::rect_s margin, w32::rect_s padding) :
	TBox(bounds, margin, padding)
{

}
TMenu::TMenu(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB, int padL, int padT, int padR, int padB) :
	TBox(x, y, w, h, mgnL, mgnT, mgnR, mgnB, padL, padT, padR, padB)
{

}

TMenu::~TMenu()
{

}

void TMenu::AddMenuItem(TMenuItem* mi) 
{
	this->m_menuItems.push_back(mi);
}

void TMenu::Draw(w32::hdc_t hdc)
{
	// DRAW SELF
	TGraphics::DrawStrokedRect(
		hdc,
		WIDEN_RECT(this->bounds),
		Colors::Yellow
	);

	// DRAW MENU ITEMS
	std::for_each(
		this->m_menuItems.begin(),
		this->m_menuItems.end(),
		[=](auto mi) {
			mi->Draw(hdc);
		}
	);
}
