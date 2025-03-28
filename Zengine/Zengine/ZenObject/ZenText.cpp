// Copyright Z.Z. Zengine (c)

#include "ZenText.h"

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
	position = vector2f;
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

sf::Text ZenText::GetText()
{
	return text;
}

sf::Text* ZenText::GetTextRaw()
{
	return &text;
}
