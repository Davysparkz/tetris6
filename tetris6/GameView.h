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
	//std::unique_ptr<GameObject> m_gameObject;
};

