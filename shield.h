#pragma once
#include "settings.h"

class Shield {
public:
	Shield(sf::Vector2f pos);
	void setPosition(sf::Vector2f pos);
	sf::FloatRect getHitBox();
	void draw(sf::RenderWindow& window);
private:
	sf::Sprite sprite;
	sf::Texture texture;
};

Shield::Shield(sf::Vector2f pos) {
	texture.loadFromFile(IMAGES_FOLDER + SHIELD_FILE_NAME);
	sprite.setTexture(texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(pos);
}

void Shield::setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }

sf::FloatRect Shield::getHitBox() { return sprite.getGlobalBounds(); }

void Shield::draw(sf::RenderWindow& window) { window.draw(sprite); }


