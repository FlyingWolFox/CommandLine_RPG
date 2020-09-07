#pragma once
#include <cstring>
#include <iostream> //TODO: remove iostream
#include <list>
#include <tuple>
#include "pugixml.hpp"

char* loadMap(int* pXMapSize, int* pYMapSize);
std::list<std::tuple<int, int, char*, int>> loadSprites(size_t spriteSheet = 0);
