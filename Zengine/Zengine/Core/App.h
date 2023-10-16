// Copyright Z.Z. Zengine (c)

#pragma once

class App
{
public:
	virtual void Initialize(class Zengine* zengine) = 0;
	virtual void Uninitialize() = 0;
	virtual void Tick(float DeltaTime) = 0;
};