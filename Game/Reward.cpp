#include "Reward.h"

int Reward::getX() { return _x; }

int Reward::getY() { return _y; }

int Reward::getW() { return _width; }

int Reward::getH() { return _height; }

void Reward::update() {
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _width;
	destRect.h = _height;
}

void Reward::render() {
	SDL_RenderCopy(Game::rendered, rewardTexture, NULL, &destRect);
}
