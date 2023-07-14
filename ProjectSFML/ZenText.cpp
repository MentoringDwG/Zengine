#include "Zengine/ZenObject/ZenText.h"

void ZenText::SetText(string text)
{
	this->text.setString(text);
}

void ZenText::SetFont(string fontPath)
{
	font.loadFromFile(fontPath);
	text.setFont(font);
}

void ZenText::SetPosition(sf::Vector2f vector2f)
{
	Position = vector2f;
	text.setPosition(vector2f);
}

void ZenText::SetColor(sf::Color color)
{
	text.setFillColor(color);
}

void ZenText::SetSize(int size)
{
	text.setCharacterSize(size);
}

sf::Text ZenText::Draw()
{
	return text;
}