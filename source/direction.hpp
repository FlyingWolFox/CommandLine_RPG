#pragma once
#ifdef __linux__
#include <cstddef> //TODO: remove dependence on the size_t type
#endif // Linux

enum direction {
	RIGHT = 1,
	LEFT = 2,
	UP = 4,
	DOWN = 8
};

static inline void movement(int direction, int* iXAxis, int* iYAxis, size_t xTimes, size_t yTimes)
{
	if ((direction & UP) == UP) {
		*iYAxis -= yTimes;
	}
	if ((direction & DOWN) == DOWN) {
		*iYAxis += yTimes;
	}
	if ((direction & LEFT) == LEFT) {
		*iXAxis -= xTimes;
	}
	if ((direction & RIGHT) == RIGHT) {
		*iXAxis += xTimes;
	}
}

static inline void movement(int direction, int* iXAxis, int* iYAxis, size_t times = 1)
{
	/*if ((direction & UP) == UP) {
		*iYAxis -= times;
	}
	if ((direction & DOWN) == DOWN) {
		*iYAxis += times;
	}
	if ((direction & LEFT) == LEFT) {
		*iXAxis -= times;
	}
	if ((direction & RIGHT) == RIGHT) {
		*iXAxis += times;
	}*/
	movement(direction, iXAxis, iYAxis, times, times);
}