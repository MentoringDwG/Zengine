#pragma once
#include "../Interfaces/IEngineModule.h"
#include <vector> 
#include <SFML/Graphics/Drawable.hpp>

namespace sf
{
	class RenderWindow;
}

struct RenderObject
{
	sf::Drawable* drawable;
	int zOrder = 0;
	// Do przekminienia przez ¯anetê jak zrobiæ dalej - layerowanie. :)
	int layerId = 0;
};

struct RenderingStack
{
	std::vector<RenderObject> renderQueue;
};

class Renderer : IEngineModule
{
public:
	void Initialize(sf::RenderWindow* inWindow);
	void ProcessDrawingElements(RenderingStack *renderStack);

	virtual void Initialize() override {}
	virtual void UnInitialize() override {}

private:
	sf::RenderWindow* window;
};

