#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class ZenObject
{
private:
	int ID;

public:
	ZenObject(int inID, string inName, sf::Vector2f inSize) :ID(inID), name(inName), size(inSize) {};

	string name;
	sf::Vector2f position;
	sf::Vector2i size;
	ZenObject* parent = nullptr;
	vector<ZenObject*> children;
	bool isJump = false;
};

