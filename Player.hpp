#pragma once
#include "graphics.hpp"
#include "direction.hpp"
#include <utility>
class Player
{
	int iXPosition, iYPosition;
public:
	Sprite* sprite;
	Player(std::pair<int, int> position);
	void move(int direction, int times = 1);
};

