#pragma once
#include "settings.h"

class TextObj {
private:
	sf::Font font;
	sf::Text text;

public:
	TextObj(std::string str, sf::Vector2f position) {
		font.loadFromFile(FONT_FILE_NAME);
		text.setFont(font);
		text.setString(str);
		text.setCharacterSize(FONT_SIZE);
		text.setPosition(position);
	}

	void update(std::string str) {
		text.setString(str);
	}

	void draw(sf::RenderWindow& window){
		window.draw(text);
	}

};