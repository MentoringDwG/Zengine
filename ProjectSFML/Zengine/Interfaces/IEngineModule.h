#pragma once

class IEngineModule
{
public:
	virtual void Initialize() = 0;
	virtual void UnInitialize() = 0;
};

