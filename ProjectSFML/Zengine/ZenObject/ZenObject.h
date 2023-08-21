#pragma once

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class ZenObject
{
private:
	int ID;

public:
	ZenObject* Parent=nullptr;
	vector<ZenObject*> Children;
	string Name;
	sf::Vector2<float> Position;
	sf::Vector2<float> previousPosition;
	sf::Vector2<int> size;

	bool isJump = false;

	ZenObject(int inID, string inName, sf::Vector2f inSize) :ID(inID), Name(inName), size(inSize)
	{

	}
};

