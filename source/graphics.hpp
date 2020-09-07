#pragma once
#include "direction.hpp"
#include "loader.hpp"
#include <iostream>
#include <algorithm>
extern "C" {
#include "ansi_escapes.h"
}

enum spritePriority {
	NO_PRIORITY = 0,
	ENEMY,
	ENEMY_ATTACK,
	RESERVED,
	PLAYER_ATTACK,
	PLAYER
};

enum spriteList {
		PLAYER_SPRITE = 0,
		ENEMY_SPRITE
};

struct Sprite {
	int iXPosition, iYPosition;
	int iXSize, iYSize;
	char* data;
	int iPriority;
	bool operator < (const Sprite sprite2)
	{
		return iPriority < sprite2.iPriority;
	}
	bool operator > (const Sprite sprite2)
	{
		return iPriority > sprite2.iPriority;
	}
	bool operator == (const Sprite sprite2)
	{
		return iPriority == sprite2.iPriority;
	}
	bool operator != (const Sprite sprite2)
	{
		return iPriority != sprite2.iPriority;
	}
	char operator [] (const size_t position)
	{
		return *(data + position);
	}
	static int compar(const void* p1, const void* p2)
	{
		Sprite* sprite1 = (Sprite*)p1;
		Sprite* sprite2 = (Sprite*)p2;

		if (sprite1 == sprite2)
			return 0;

		return sprite1 < sprite2 ? -1 : 1;
	}
	~Sprite()
	{
		delete(data);
	}
};


void vStartUp();
void vRender();
Sprite* vLoadSpriteToScreen(unsigned uSpriteNum);
void vFillSpriteLayer();
void vScrollBackgound(int direction, int times = 1);
void vGetResolution();
bool bResolutionChanged();
Sprite* getSprite(int spriteNum);
