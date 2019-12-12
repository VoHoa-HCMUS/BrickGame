#include "Rect.h"

int Rect::getX() { return _x; }

int Rect::getY() { return _y; }

int Rect::getW() { return _width; }

int Rect::getH() { return _height; }

void Rect::updateHpImg() {
	//change img
	_hp--;
	cout << _hp << endl;
	switch (_hp) {
	case 1:
		_sheet = "PNGFile/rect1.png";
		break;
	case 2:
		_sheet = "PNGFile/rect2.png";
		break;
	}
	brickTexture = textureManager::loadTexture(_sheet.c_str());
}


void Rect::render() {
	SDL_RenderCopy(Game::rendered, brickTexture, NULL, &destRect);
}