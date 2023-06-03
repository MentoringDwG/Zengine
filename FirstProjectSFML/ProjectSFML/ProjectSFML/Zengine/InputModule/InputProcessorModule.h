#pragma once

#include "../Main_class_of_modules/IEngineModule.h"
#include <vector>
#include <SFML/Window/Event.hpp>
#include "InputHandler.h"

class InputProcessorModule : IEngineModule
{
public:
	virtual void Initialize() override;
	virtual void UnInitialize() override;

	void ProcessInput(sf::Event& event);

	void RegisterInputHandler(InputHandler* InInputHandler);
	std::vector<InputHandler*> InputHandlers;
};
