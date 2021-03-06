﻿#include "graphics.hpp"
#include "direction.hpp"
#include "loader.hpp"
int main(int argc, char** argv) {
	vStartUp();

	while (true)
	{
		char c = getchar();
		int direction = 0;
		if (c == '8')
			direction |= UP;
		if (c == '2')
			direction |= DOWN;
		if (c == '4')
			direction |= LEFT;
		if (c == '6')
			direction |= RIGHT;
		if (direction == 0)
			continue;
		vScrollBackgound(direction);
		vRender();
	}
	return 0;
}


