#include "ZenShape.h"

ZenShape::ZenShape(int inID, string inName, sf::Vector2f inSize) :ZenObject(inID, inName, inSize)
{
	rectangleShape = new sf::RectangleShape();
	texture = new sf::Texture();
};

ZenShape::~ZenShape()
{
	delete rectangleShape;
	delete texture;
}

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
	position = vector;
	rectangleShape->setPosition(vector);
}

void ZenShape::SetSize(sf::Vector2f vector)
{
	rectangleShape->setSize(vector);
}

void ZenShape::MoveObject(sf::Vector2f vector)
{
	previousPosition = position;
	rectangleShape->move(vector);
	position = rectangleShape->getPosition();
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