#pragma once
#include "SFML/Graphics.hpp"

const float WINDOW_WIDTH{ 800.f };
const float WINDOW_HEIGHT{ 800.f };
const std::string WINDOW_TITLE{ "SFML SPACE SHOOTER P53022" };
const size_t FPS{ 60 };

const std::string IMAGES_FOLDER{ "images\\" };
const std::string PLAYER_FILE_NAME{"playerShip2_orange.png"};
const sf::Vector2f PLAYER_START_POS{WINDOW_WIDTH/2, WINDOW_HEIGHT - 100.f};
const float PLAYER_SPEED{ 10.f };

const int METEORS_QTY{ 20 };

const std::string LASER_FILE_NAME{ "laserRed03.png" };
const float LASER_SPEED{ -15.f };
const int FIRE_COOLDOWN{ 200 };

const std::string FONT_FILE_NAME{ "DS-DIGIB.ttf" };
const int FONT_SIZE{ 32 };

const std::string MULTI_LASER_BONUS_FILE_NAME{ "things_gold.png" };
const float BONUS_SPEED{ 15.f };
const int THREE_LASERS_BONUS_COOLDOWN{ 1000 };
const std::string HP_BONUS_FILE_NAME{"pill_yellow.png"};
size_t HEAL{ 25 };
const std::string SHIELD_BONUS_FILE_NAME{ "shield_gold.png" };
const std::string SHIELD_FILE_NAME{ "shield3.png" };

const int SHIELD_OPERATING_TIME{ 5000 };