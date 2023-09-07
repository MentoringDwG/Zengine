#pragma once

#include "ZenObject.h"

class ZenText : public ZenObject
{
public:
	ZenText(int inID, string inName, sf::Vector2f inSize) :ZenObject(inID, inName, inSize)
	{

	};

	void SetText(string text);
	void SetFont(string fontPath);
	void SetPosition(sf::Vector2f vector2f);
	void SetColor(sf::Color color);
	void SetSize(int size);
	sf::Text GetText();
	sf::Text* GetTextRaw();


private:
	sf::Text text;
	sf::Font font;
};

