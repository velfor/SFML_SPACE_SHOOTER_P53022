#pragma once
#include <list>
#include "settings.h"
#include "laser.h"

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speedx;
	std::list<Laser*> laserSprites;
	sf::Clock timer;

public:
	Player() {
		texture.loadFromFile(IMAGES_FOLDER + PLAYER_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(PLAYER_START_POS);
		speedx = 0.f;
		timer.restart();
	}
	void fire() {
		int now = timer.getElapsedTime().asMilliseconds();
		if (now > FIRE_COOLDOWN) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
				sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				sf::Vector2f pos = sprite.getPosition();
				sf::FloatRect bounds = sprite.getGlobalBounds();
				sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,	pos.y + bounds.height / 2 };
				Laser* laser = new Laser(posCenter);
				laserSprites.push_back(laser);
				timer.restart();
			}
		}
	}

	void update() {
		fire();
		for (auto laser : laserSprites) {
			laser->update();
		}
	}

	void draw(sf::RenderWindow& window) {
		for (auto laser : laserSprites) {
			window.draw(laser->getSprite());
		}
		window.draw(sprite);
	}

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	
};


