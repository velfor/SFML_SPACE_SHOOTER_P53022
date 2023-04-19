#pragma once
#include <list>
#include "settings.h"
#include "laser.h"
#include "textobj.h"
#include "shield.h"

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speedx = 0.f;
	std::list<Laser*> laserSprites;
	sf::Clock timer;
	int hp = 100;
	TextObj hpText;
	bool threeLasersActive = false;
	int currTimeFire, prevTimeFire;
	int currTimeThreeLasersBonus, prevTimeThreeLasersBonus;
	int prevTimeShieldBonus;
	Shield shield;
	bool shieldActive = false;

public:
	Player();

	void fire();

	void update(); 

	void draw(sf::RenderWindow& window);

	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	
	int getHp() { return hp; }

	bool isAlive() { return hp > 0; }

	void decreaseHp(int damage) { hp -= damage; }

	void increaseHp(int heal) { hp += heal; }

	std::list<Laser*>* getLaserSprites() { return &laserSprites; }

	void activateThreeLasers(); 

	void deactivateThreeLasers() { threeLasersActive = false; }

	bool isThreeLasersActive() { return threeLasersActive; }

	void activateShield();

	void deactivateShield() { shieldActive = false; }

	bool shieldIsActive() {	return shieldActive; }

	sf::FloatRect getShieldHitBox() { return shield.getHitBox(); }
};

Player::Player() : hpText(std::to_string(hp), sf::Vector2f{ 0.f, 0.f }),
shield(sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT + 140.f })
{
	texture.loadFromFile(IMAGES_FOLDER + PLAYER_FILE_NAME);
	sprite.setTexture(texture);
	sprite.setPosition(PLAYER_START_POS);
	timer.restart();
	prevTimeFire = timer.getElapsedTime().asMilliseconds();
}

void Player::fire() {
	currTimeFire = timer.getElapsedTime().asMilliseconds();
	if (currTimeFire - prevTimeFire > FIRE_COOLDOWN) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			sf::Vector2f pos = sprite.getPosition();
			sf::FloatRect bounds = sprite.getGlobalBounds();
			sf::Vector2f posCenter = sf::Vector2f{ pos.x + bounds.width / 2,	pos.y + bounds.height / 2 };
			Laser* laser = new Laser(posCenter);
			laserSprites.push_back(laser);
			if (threeLasersActive) {
				auto laserWidth = laser->getHitBox().width;
				sf::Vector2f posLeft = sf::Vector2f{
					pos.x,	pos.y + bounds.height / 2 };
				laser = new Laser(posLeft);
				laserSprites.push_back(laser);
				sf::Vector2f posRight = sf::Vector2f{
					pos.x + bounds.width - laserWidth,
					pos.y + bounds.height / 2
				};
				laser = new Laser(posRight);
				laserSprites.push_back(laser);
			}
			prevTimeFire = currTimeFire;
		}
	}
}

void Player::update() {

	speedx = 0.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		speedx = -PLAYER_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		speedx = PLAYER_SPEED;
	}
	sprite.move(speedx, 0.f);

	fire();
	for (auto laser : laserSprites) {
		laser->update();
	}
	hpText.update("HP:" + std::to_string(hp));

	int currTime = timer.getElapsedTime().asMilliseconds();
	if (threeLasersActive) {
		if (currTime - prevTimeThreeLasersBonus > THREE_LASERS_BONUS_COOLDOWN)
		{
			deactivateThreeLasers();
		}
	}
	sf::Vector2f shieldPos;
	if (shieldActive) {
		if (currTime - prevTimeShieldBonus > SHIELD_OPERATING_TIME) {
			deactivateShield();
		}
		else {
			auto playerBounds = getHitBox();
			shieldPos = sf::Vector2f{ playerBounds.left + playerBounds.width / 2, playerBounds.top + playerBounds.height / 2 };
		}
	}
	else {
		shieldPos = sf::Vector2f{ WINDOW_WIDTH / 2, WINDOW_HEIGHT + 140.f };
	}
	shield.setPosition(shieldPos);
}

void Player::draw(sf::RenderWindow& window) {
	shield.draw(window);
	for (const auto& laser : laserSprites) {
		window.draw(laser->getSprite());
	}
	window.draw(sprite);
	hpText.draw(window);
}

void Player::activateThreeLasers() {
	threeLasersActive = true;
	prevTimeThreeLasersBonus = timer.getElapsedTime().asMilliseconds();
}

void Player::activateShield() { 
	shieldActive = true;
	prevTimeShieldBonus = timer.getElapsedTime().asMilliseconds();
}