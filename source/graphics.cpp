#include "graphics.hpp"

int iXScreenSize, iYScreenSize;
int iXCameraPosition, iYCameraPosition;
int iXBackgroundSize, iYBackgroundSize;
//TODO: implement color buffers
//TODo: implement color buffer using less memory (optimization)
char* backgroundLayer, * spriteLayer, * windowLayer, * screenBuffer; //TODO: implement all layers
Sprite* sprites, *onScreenSprites;
size_t uNumOfOnScreenSprites = 0;

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
	//std::sort()
}

Sprite* vLoadSpriteToScreen(unsigned uSpriteNum)
{
	uNumOfOnScreenSprites++;
	Sprite* tmp = (Sprite*)realloc(onScreenSprites, uNumOfOnScreenSprites * sizeof(Sprite));
	if (tmp != NULL)
		onScreenSprites = tmp;
	free(onScreenSprites); // TODO: ?!?!?!
	//onScreenSprites = (Sprite*) realloc(onScreenSprites, uNumOfOnScreenSprites * sizeof(Sprite));
	return nullptr;
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

	// TODO: split the directional movement in X and Y movement (abandon the times variable)
	// TODO: find why scrolling is inverted between X and Y
	// TODO: times is not zero when scrolling past map border?
	if (iXNewCameraPosition + iXScreenSize >= iXBackgroundSize || iXNewCameraPosition < 0)
		uXMovement = std::max(iXCameraPosition + iXScreenSize - iXBackgroundSize, 0);
	if (iYNewCameraPosition + iYScreenSize >= iYBackgroundSize || iYNewCameraPosition < 0)
		uYMovement = std::max(iYCameraPosition + iYScreenSize - iYBackgroundSize, 0);

	movement(direction, &iXCameraPosition, &iYCameraPosition, uXMovement, uYMovement);

	for (int i = 0; i < iYScreenSize; i++)
	{
		if (i == iYBackgroundSize)
			break;

		for (int j = 0; j < iXScreenSize; j++)
		{
			if (j == iXBackgroundSize)
			{
				if (i != iYScreenSize - 1)
					screenBuffer[iXScreenSize * i + j] = '\n';
				
				break;
			}
			screenBuffer[i * iXScreenSize + j] = backgroundLayer[((iYCameraPosition + i) * iXBackgroundSize) + (iXCameraPosition + j)];
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
