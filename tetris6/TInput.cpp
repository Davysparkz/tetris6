#include "stdafx.h"
#include "TInput.h"


TInput::TInput()
{
}


TInput::~TInput()
{
}

void TInput::KeyUp(std::function<void()> cb) {
//	OutputDebugString(L"KEYUP\n");
	if (cb) {
		cb();
	}
}
void TInput::KeyDown(std::function<void()> cb) {
//	OutputDebugString(L"KEYDOWN\n");
	if (cb) {
		cb();
	}
}
void TInput::KeyRight(std::function<void()> cb) {
	//OutputDebugString(L"KEYRIGHT\n");
	if (cb) {
		cb();
	}
}
void TInput::KeyLeft(std::function<void()> cb) {
	//OutputDebugString(L"KEYLEFT\n");
	if (cb) {
		cb();
	}
}
void TInput::KeyChar(std::function<void(char)> cb, char value) {
	OutputDebugString(L"KEYCHAR\n");
	if (cb) {
		cb(value);
	}
}