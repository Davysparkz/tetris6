#pragma once
#include <functional>
class TInput
{
public:
	TInput();
	~TInput();

	static void KeyUp(std::function<void()> cb);
	static void KeyDown(std::function<void()> cb);
	static void KeyRight(std::function<void()> cb);
	static void KeyLeft(std::function<void()> cb);
	static void KeyChar(std::function<void(char)> cb, char);
};

