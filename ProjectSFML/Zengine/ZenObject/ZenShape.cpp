#include "ZenShape.h"

void ZenShape::SetTexture(string texcurePath)
{
	texture->loadFromFile(texcurePath);
	rectangleShape->setTexture(texture);
}

void ZenShape::SetTexture(sf::Texture* texture)
{
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
	previousPosition = Position;
	rectangleShape->move(vector);
	Position = rectangleShape->getPosition();
}

void ZenShape::SetOrigin(sf::Vector2f vector)
{
	rectangleShape->setOrigin(vector);
}

sf::Vector2f ZenShape::GetSize()
{
	return rectangleShape->getSize();
}

void ZenShape::SetScale(sf::Vector2f vector)
{
	rectangleShape->setScale(vector);
}

sf::RectangleShape* ZenShape::Draw()
{
	return rectangleShape;
}

sf::Vector2f ZenShape::GetOrigin()
{
	return rectangleShape->getOrigin();
}

sf::Vector2f ZenShape::GetPosition()
{
	return rectangleShape->getPosition();
}

sf::FloatRect ZenShape::GetGlobalBounds()
{
	return rectangleShape->getGlobalBounds();
}