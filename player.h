#pragma once
#include "settings.h"

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speedx;

public:
	Player() {
		texture.loadFromFile(PLAYER_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(PLAYER_START_POS);
		speedx = 0.f;
	}

	void update() {

	}

	void draw(sf::RenderWindow& window) {

	}
};


