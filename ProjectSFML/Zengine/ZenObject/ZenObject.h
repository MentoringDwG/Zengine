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
	sf::Vector2<int> size;

	ZenObject(int IDIn, string NameIn, sf::Vector2f sizeIn) :ID(IDIn), Name(NameIn), size(sizeIn)
	{

	}
};

