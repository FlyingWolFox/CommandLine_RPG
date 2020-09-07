#include "Player.hpp"

Player::Player(std::pair<int, int> position)
{
	iXPosition = position.first;
	iYPosition = position.second;
	sprite = getSprite(PLAYER_SPRITE); 

}

void Player::move(int direction, int times)
{
	movement(direction, &iYPosition, &iXPosition, times);
	vScrollBackgound(direction, times); // is really necessary?
}
