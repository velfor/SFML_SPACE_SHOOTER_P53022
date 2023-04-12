#pragma once
#include "settings.h"

class Bonus {
public:
	enum BonusType { MULTI_LASER, HP, SHIELD };
	Bonus(BonusType type, sf::Vector2f position);
	void update();
	void draw(sf::RenderWindow& window);
	sf::FloatRect getHitBox();
	sf::Vector2f getPosition();
	void setDel();
	bool isToDel();
	BonusType getType();
	void act(Player& player);


private:
	sf::Sprite sprite;
	sf::Texture texture;
	BonusType type;
	bool del = false;
};

Bonus::Bonus(BonusType type, sf::Vector2f position) {
	this->type = type;
	switch (type) {
	case MULTI_LASER:
		texture.loadFromFile(IMAGES_FOLDER + MULTI_LASER_BONUS_FILE_NAME);
		break;
	case HP:
		texture.loadFromFile(IMAGES_FOLDER + HP_BONUS_FILE_NAME);
		break;
	}
	sprite.setTexture(texture);
	sprite.setPosition(position);
}

void Bonus::update() { sprite.move(0.f, BONUS_SPEED); }

void Bonus::draw(sf::RenderWindow& window) { window.draw(sprite); }

sf::FloatRect Bonus::getHitBox() { return sprite.getGlobalBounds(); }

sf::Vector2f Bonus::getPosition() { return sprite.getPosition(); }

bool Bonus::isToDel() { return del; }

void Bonus::setDel() { del = true; }

Bonus::BonusType Bonus::getType() { return type; }

void Bonus::act(Player& player){
	switch (type) {
	case MULTI_LASER:
		player.activateThreeLasers();
		break;
	case HP:
		player.increaseHp(HEAL);
		break;
	}
}

