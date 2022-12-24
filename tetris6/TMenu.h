#pragma once
#include "w32_types.h"
#include <string>
#include <memory>
#include <vector>
#include "TGraphics.h"

class TDrawable {
public:
	virtual void Draw(w32::hdc_t hdc) = 0;
};

class TBox {
public:
	TBox() = delete;
	TBox(w32::rect_s bounds);
	TBox(int x, int y, int w, int h);
	TBox(w32::rect_s bounds, w32::rect_s margin);
	TBox(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB);
	TBox(w32::rect_s bounds, w32::rect_s margin, w32::rect_s padding);
	TBox(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB, int padL, int padT, int padR, int padB);
	~TBox();

protected:
	w32::rect_s bounds;
	w32::rect_s padding;
	w32::rect_s margin;
};

class TMenuItem : public TDrawable, public TBox{
public:
	TMenuItem() = delete;
	TMenuItem(w32::rect_s bounds);
	TMenuItem(int x, int y, int w, int h);
	TMenuItem(w32::rect_s bounds, w32::rect_s margin);
	TMenuItem(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB);
	TMenuItem(w32::rect_s bounds, w32::rect_s margin, w32::rect_s padding);
	TMenuItem(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB, int padL, int padT, int padR, int padB);
	
	~TMenuItem();

	TMenuItem & SetContentTextW(std::wstring text,
		TGraphics::TextProps textProps);
	TMenuItem & SetContentTextA(std::string text,
		TGraphics::TextProps textProps);

	friend class TMenu;

private:
	// Inherited via TDrawable
	virtual void Draw(w32::hdc_t hdc) override;

private: 
	std::wstring m_wText;
	std::string m_aText;
	bool m_wide_text_in_use{ false };
	bool m_ascii_text_in_use{ false };
	TGraphics::TextProps m_textProps;
};

class TMenu : public TDrawable, public TBox {
public:
	TMenu() = delete;
	TMenu(w32::rect_s bounds);
	TMenu(int x, int y, int w, int h);
	TMenu(w32::rect_s bounds, w32::rect_s margin);
	TMenu(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB);
	TMenu(w32::rect_s bounds, w32::rect_s margin, w32::rect_s padding);
	TMenu(int x, int y, int w, int h, int mgnL, int mgnT, int mgnR, int mgnB, int padL, int padT, int padR, int padB);
	~TMenu();

	void AddMenuItem(TMenuItem* mi);

	// Inherited via TDrawable
	virtual void Draw(w32::hdc_t hdc) override;

private:
	std::vector<TMenuItem*> m_menuItems;
};

