#include "Skills.h"

Skills::Skills(vector<vector<Brick*>>& table, int loot, int pos, int missile_num, BallObject*& ball) {
	_pos = pos;
	_loot = loot;
	_missile = missile_num;
	switch (loot) {
	case 1:
		_start = SDL_GetTicks();
		execHp(ball);
		_duration = 500;
		break;
	case 2: // laser
		_start = SDL_GetTicks();
		execLaser(table,ball);
		_duration = 1000;
		break;
	case 3:
		execMissile(table);
		_duration = 1000;
		break;
	}
}

void Skills::setTexture(string sheet) {
	skillTexture = textureManager::loadTexture(sheet.c_str());
}

void Skills::render() {
	SDL_RenderCopyF(Game::rendered, skillTexture, NULL, &destRect);
}

void Skills::update() {
	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _w;
	destRect.h = _h;
}

void Skills::execLaser(vector<vector<Brick*>>& table,BallObject*& ball) {
	setTexture("PNGFile/laser_x.png");
	_x = _pos * 80 + 10;
	_y = 0;
	_w = 60;
	_h = 688;

	for (size_t i = 0; i < 5; i++) {
		if (table[i][_pos] != NULL && table[i][_pos]->getType() == "rect")
			ball->setScore(ball->getScore_1() + 10);
		table[i][_pos] = NULL;
	}
}

void Skills::renderExplosion(int x, int y) {
	_start = SDL_GetTicks();
	destRect.x = x;
	destRect.y = y;
	destRect.w = 100;
	destRect.h = 100;
	setTexture("PNGFile/missile_end1.png");
}

bool Skills::isTouchWithTarget(Brick* target) {
	if (destRect.x + 27 >= target->getDestx() &&
		destRect.x <= target->getDestx() + target->getW() &&
		destRect.y + 27 >= target->getDesty() &&
		destRect.y <= target->getDesty() + target->getH())
		return true;
	return false;
}

void Skills::updateMissile(vector<vector<Brick*>>& table) {
	int targetY;
	int targetX;
	size_t targetRow;
	size_t targetCol;
	if (_missile == 1) {
		if (_start == 0) {
			destRect.x = _x;
			destRect.y -= 4;
			destRect.w = _w;
			destRect.h = _h;
			targetY = 0;
			targetRow = 0;
			targetCol = _pos;
			for (size_t i = 0; i < 5; i++) {
				if (table[i][_pos] != NULL && table[i][_pos]->getType() == "rect") {
					targetY = table[i][_pos]->getDesty();
					targetRow = i;
				}
			}

			if (destRect.y <= targetY) {
				renderExplosion(_pos * 80 - 10, destRect.y - 30);
				if (targetY != 0)
					table[targetRow][targetCol] = NULL;
			}
		}
	}
	else if (_missile == 2) {
		if (_start == 0) {
			destRect.x -= 1.865;
			destRect.y -= 4;
			destRect.w = _w;
			destRect.h = _h;
			for (size_t i = 0; i < 5; i++) {
				for (size_t j = 0; j < _pos; j++) {
					Brick* target = table[i][j];
					if (target != NULL && target->getType() == "rect" && isTouchWithTarget(target)) {
						renderExplosion(destRect.x - 10, destRect.y - 30);												table[i][j] = NULL;
						return;
					}
				}
			}
			if (destRect.y <= 0 || destRect.x <= 0)
				renderExplosion(destRect.x - 10, destRect.y - 30);
		}

	}
	else if (_missile == 3) {
		if (_start == 0) {
			destRect.x += 1.865;
			destRect.y -= 4;
			destRect.w = _w;
			destRect.h = _h;
			for (size_t i = 0; i < 5; i++) {
				for (size_t j = _pos; j < 10; j++) {
					Brick* target = table[i][j];
					if (target != NULL && target->getType() == "rect" && isTouchWithTarget(target)) {
						renderExplosion(destRect.x, destRect.y - 90);
						table[i][j] = NULL;
						return;
					}
				}
			}
			if (destRect.y <= 0 || destRect.x + destRect.w >= WINDOW_WIDTH)
				renderExplosion(destRect.x - 10, destRect.y - 30);
		}
	}
}

void Skills::execMissile(vector<vector<Brick*>>& table) {
	string texture;
	if (_missile == 1) {
		texture = "PNGFile/missile_x1.png";
		_x = _pos * 80 + 25;
		_w = 30;
		_h = 100;
	} else if (_missile == 2) {
		texture = "PNGFile/missile_x2.png";
		_x = _pos * 80;
		_w = 54;
		_h = 95;
	} else if (_missile == 3) {
		texture = "PNGFile/missile_x3.png";
		_x = _pos * 80 + 26;
		_w = 54;
		_h = 95;
	}
	setTexture(texture);
	_y = 688;

	destRect.x = _x;
	destRect.y = _y;
	destRect.w = _w;
	destRect.h = _h;
	render();
}


void Skills::execHp(BallObject*& ball) {
	int x = ball->getLife() + 1;
	ball->setLife(x);
}