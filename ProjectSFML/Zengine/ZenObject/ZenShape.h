#pragma once

#include "ZenObject.h"

class ZenShape: public ZenObject
{
public:
	ZenShape(int IDIn, string NameIn) :ZenObject(IDIn, NameIn)
	{
		rectangleShape = new sf::RectangleShape();
		texture = new sf::Texture();
	};

	void SetTexture(string texcurePath);
	void SetTexture(sf::Texture* texture);
	void SetPosition(sf::Vector2f vector);
	void SetSize(sf::Vector2f vector);
	void SetScale(sf::Vector2f vector);
	void MoveObject(sf::Vector2f vector);
	void SetOrigin(sf::Vector2f vector);
	sf::RectangleShape* Draw();
	sf::Vector2f GetSize();

private:
	sf::RectangleShape* rectangleShape = nullptr;
	sf::Texture* texture = nullptr;
};

