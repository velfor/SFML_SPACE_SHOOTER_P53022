#pragma once
#include "settings.h"
#include "meteor.h"
#include "player.h"
#include <vector>
#include "bonus.h"

class Game {

public:
	Game() {
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEORS_QTY);
		for (int i = 0; i < METEORS_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
	}

	void play() {
		while (window.isOpen() && player.isAlive()) {
			checkEvents();
			update();
			//if (player.getHp() <= 0) game_state = GAME_OVER;
			checkCollisions();
			draw();
		}
	}

private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteorSprites;
	std::list<Bonus*> bonusSprites;
	Player player;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		for (auto& meteor : meteorSprites) {
			meteor->update();
		}
		player.update();
		for (auto& bonus : bonusSprites) {
			bonus->update();
		}
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		auto laserSprites = player.getLaserSprites();
		//������� �� �����
		//���� ��� �������
		if (player.shieldIsActive()) {
			//�������� ������� ����
			sf::FloatRect shieldBounds = player.getShieldHitBox();
			//���� �� ��������� ��������
			for (auto& meteor : meteorSprites) {
				//�������� ������� �������� �������
				sf::FloatRect meteorBounds = meteor->getHitBox();
				//���� ������ ������������ �� �����
				if (meteorBounds.intersects(shieldBounds)) {
					//������ ������ �� ����� ��������� �������
					meteor->spawn();
				}
			}

		}
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->spawn();
				player.decreaseHp(meteor->getDamage());
			}
			for (auto& laser : *laserSprites) {
				sf::FloatRect laserBounds = laser->getHitBox();
				if (meteorBounds.intersects(laserBounds)) {
					meteor->spawn();
					laser->setHit();
					//� �����-�� ������ ���������� �����
					size_t chance = rand() % 30001;
					if (chance < 15000) {
						//���������� �����
						//��������� 2 �� ���-�� ������� ����� ��������
						size_t bonusType = rand() % Bonus::BonusType::TYPES_QTY;
						//�������� ������ � ������� ������ ������
						Bonus* bonus = new Bonus(
							(Bonus::BonusType)bonusType,
							meteor->getPosition()
						);
						bonusSprites.push_back(bonus);
					}
				}
				if (laser->getPosition().y < -laserBounds.height)
				{
					laser->setHit();
				}
			}
		}
		(*laserSprites).remove_if([](Laser* laser) {
			return laser->isHit(); });

		for (auto& bonus : bonusSprites) {
			sf::FloatRect bonusBounds = bonus->getHitBox();
			if (bonusBounds.intersects(playerBounds)) {
					bonus->act(player);
					bonus->setDel();
			}
			if (bonusBounds.top > WINDOW_HEIGHT) {
				bonus->setDel();
			}
			
		}
		bonusSprites.remove_if([](Bonus* bonus) { 
			return bonus->isToDel(); });

	}

	void draw() {
		window.clear();
		for (auto meteor : meteorSprites) {
			window.draw(meteor->getSprite());
		}
		player.draw(window);
		for (auto& bonus : bonusSprites) {
			bonus->draw(window);
		}
		window.display();
	}
};