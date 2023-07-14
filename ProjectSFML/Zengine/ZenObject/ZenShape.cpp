#include "ZenShape.h"

void ZenShape::SetTexture(string texcurePath)
{
	texture->loadFromFile(texcurePath);
	rectangleShape->setTexture(texture);
}

void ZenShape::SetPosition(sf::Vector2f vector)
{
	Position = vector;
	rectangleShape->setPosition(vector);
}

void ZenShape::SetSize(sf::Vector2f vector)
{
	rectangleShape->setSize(vector);
}

void ZenShape::MoveObject(sf::Vector2f vector)
{
	rectangleShape->move(vector);
}

sf::RectangleShape* ZenShape::Draw()
{
	return rectangleShape;
}