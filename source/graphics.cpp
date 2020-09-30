#include "graphics.hpp"

int iXScreenSize, iYScreenSize;
int iXCameraPosition, iYCameraPosition;
int iXBackgroundSize, iYBackgroundSize;
//TODO: implement color buffers
//TODo: implement color buffer using less memory (optimization)
char* backgroundLayer, * spriteLayer, * windowLayer, * screenBuffer; //TODO: implement all layers
Sprite* sprites; //TODO: use vector
std::vector<Sprite> onScreenSprites;

void vStartUp() {
	// load background and sprites
	/*tip: if there's need for more	backgrounds
	and spritesheet mode, implement in their own
	load functions, being start up just be setup the console*/
	backgroundLayer = loadMap(&iXBackgroundSize, &iYBackgroundSize);
	auto spritesData = loadSprites();
	sprites = new Sprite[spritesData.size()];
	for (const auto& spriteData : spritesData)
	{
		int i = 0;
		sprites[i].iXSize = std::get<0>(spriteData);
		sprites[i].iYSize = std::get<1>(spriteData);
		sprites[i].data = std::get<2>(spriteData);
		sprites[i].iPriority = std::get<3>(spriteData);
	}

	setupConsole();
	vGetResolution();

	//TODO: initialize all layers here
	//TODO: also, fix this warnings
	spriteLayer = new char[iXScreenSize * iYScreenSize + 1];
	
	screenBuffer = new char[iXScreenSize * iYScreenSize + 1];
	screenBuffer[iXScreenSize * iYScreenSize] = '\0';

	iXCameraPosition = 0;
	iYCameraPosition = 0;
}

void vShutDowm()
{
	// TODO: unload things
	restoreConsole();
}

void vRender()
{
	// TODO: render sprites
	// TODO: sort sprites

	/*if scroll and rendering 
	won't happen at the same time
	make a scoll verification first
	(we need to scroll?)*/
	//vScrollBackgound();

	

	// "render" screen
	clearScreenToTop();
	moveTo(0, 0);
	printf(screenBuffer);
}

void vFillSpriteLayer()
{
	//TODO: this
	//TODO: fill sprite layer with "nulls"
	if(onScreenSprites.size() > 1)
		std::sort(onScreenSprites.begin(), onScreenSprites.end());
	for (auto sprite : onScreenSprites)
	{
		auto xFinalPosition = std::min(iXScreenSize, sprite.iXPosition + sprite.iXSize);
		auto yFinalPosition = std::min(iYScreenSize, sprite.iYPosition + sprite.iYSize);
		for (auto x = sprite.iXPosition; x < xFinalPosition; x++)
		{
			for (auto y = sprite.iYPosition; y < yFinalPosition; y++)
				spriteLayer[y * iXScreenSize + x] = sprite.data[(y - sprite.iYPosition) * sprite.iXSize + x - sprite.iXPosition];
		}
	}
}

Sprite* sLoadSpriteToScreen(unsigned uSpriteNum)
{
	//TODO: this
	Sprite newSprite = sprites[uSpriteNum];
	return nullptr; //TODO: remove this
}

void vLoadSpriteSheet(unsigned uSheetNum)
{
	auto spritesData = loadSprites(uSheetNum);
	sprites = new Sprite[spritesData.size()];
	for (const auto& spriteData : spritesData)
	{
		int i = 0;
		sprites[i].iXSize = std::get<0>(spriteData);
		sprites[i].iYSize = std::get<1>(spriteData);
		sprites[i].data = std::get<2>(spriteData);
		sprites[i].iPriority = std::get<3>(spriteData);
	}
}

void vScrollBackgound(int direction, int times)
{
	if (bResolutionChanged())
	{
		delete[] screenBuffer;
		vGetResolution();
		screenBuffer = new char[iXScreenSize * iYScreenSize + 1];
		screenBuffer[iXScreenSize * iYScreenSize] = '\0';
	}

	/*if (iYCameraPosition + iYScreenSize >= iYBackgroundSize)
		return;
	if (iXCameraPosition + iXScreenSize >= iXBackgroundSize)
		return;*/

	size_t uXMovement = times * (direction & (LEFT | RIGHT)) / direction;
	size_t uYMovement = times * (direction & (UP | DOWN)) / direction;

	/*int iXNewCameraPosition = iXCameraPosition + uXMovement;
	int iYNewCameraPosition = iYCameraPosition + uYMovement;*/
	int iXNewCameraPosition = iXCameraPosition;
	int iYNewCameraPosition = iYCameraPosition;

	movement(direction, &iXNewCameraPosition, &iYNewCameraPosition, uXMovement, uYMovement);

	// TODO: times is not zero when scrolling past map border?
	if (iXNewCameraPosition + iXScreenSize >= iXBackgroundSize || iXNewCameraPosition < 0)
		uXMovement = std::max(iXCameraPosition + iXScreenSize - iXBackgroundSize, 0);
	if (iYNewCameraPosition + iYScreenSize >= iYBackgroundSize || iYNewCameraPosition < 0)
		uYMovement = std::max(iYCameraPosition + iYScreenSize - iYBackgroundSize, 0);

	movement(direction, &iXCameraPosition, &iYCameraPosition, uXMovement, uYMovement);

	for (int x = 0; x < iXScreenSize; x++)
	{
		if (x == iXBackgroundSize)
		{
			for (int y = 0; y < iYScreenSize - 1; y++)
				screenBuffer[y * iXScreenSize + x] = '\n';
			break;
		}

		for (int y = 0; y < iYScreenSize; y++)
		{
			if (y == iYBackgroundSize)
				break;

			screenBuffer[y * iXScreenSize + x] = backgroundLayer[((iYCameraPosition + y) * iXBackgroundSize) + (iXCameraPosition + x)];
		}
	}
}

//TODO: resolution scaling
void vGetResolution()
{
	moveTo(999, 999);
	getCursorPosition(&iYScreenSize, &iXScreenSize);
	moveTo(0, 0);
}

bool bResolutionChanged() {
	//TODO: this already gets the resolution, isn't convenient to return it when changed?
	//TODO: define behavior
	int iX, iY;
	moveTo(999, 999);
	getCursorPosition(&iY, &iX);
	moveTo(0, 0);

	if (iXScreenSize != iX || iYScreenSize != iY)
		return true;

	return false;
}

Sprite* getSprite(int spriteNum)
{
	return sprites + spriteNum;
}
