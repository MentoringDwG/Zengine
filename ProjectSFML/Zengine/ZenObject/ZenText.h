#pragma once

#include "ZenObject.h"

class ZenText:public ZenObject
{
public:
	ZenText(int IDIn, string NameIn, sf::Vector2f sizeIn) :ZenObject(IDIn, NameIn, sizeIn)
	{

	};

	void SetText(string text);
	void SetFont(string fontPath);
	void SetPosition(sf::Vector2f vector2f);
	void SetColor(sf::Color color);
	void SetSize(int size);
	sf::Text Draw();

private:
	sf::Text text;
	sf::Font font;
};

