#pragma once
#include "../Interfaces/IEngineModule.h"
#include <vector>
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
