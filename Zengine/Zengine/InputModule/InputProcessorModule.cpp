#include "InputProcessorModule.h"

void InputProcessorModule::Initialize()
{
	// TODO
}

void InputProcessorModule::UnInitialize()
{
	// TODO
}

void InputProcessorModule::ProcessInput(sf::Event& event, sf::RenderWindow* inWindow)
{
	for (int i = 0; i < InputHandlers.size(); i++)
	{
		bool bConsumedInput = InputHandlers[i]->ProcessInput(event, inWindow);
		if (InputHandlers[i]->CanConsumeInput() && bConsumedInput)
		{
			return;
		}
	}
}

void InputProcessorModule::RegisterInputHandler(InputHandler* InInputHandler)
{
	InputHandlers.push_back(InInputHandler);
}
