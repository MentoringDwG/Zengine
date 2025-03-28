// Copyright Z.Z. Zengine (c)

#pragma once

#include "ZenObject.h"

class ZenShape: public ZenObject
{
public:
	ZenShape(int inID, string inName, sf::Vector2f inSize);
	~ZenShape();

	void SetTexture(string texcurePath);
	void SetTexture(sf::Texture* texture);
	void SetPosition(sf::Vector2f vector);
	void SetSize(sf::Vector2f vector);
	void SetScale(sf::Vector2f vector);
	void MoveObject(sf::Vector2f vector);
	void SetOrigin(sf::Vector2f vector);
	sf::RectangleShape* Draw();
	sf::Vector2f GetSize();
	sf::Vector2f GetOrigin();
	sf::Vector2f GetPosition();
	sf::FloatRect GetGlobalBounds();

private:
	sf::RectangleShape* rectangleShape = nullptr;
	sf::Texture* texture = nullptr;
};

