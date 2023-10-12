// Copyright Z.Z. Zengine (c)

#pragma once

#include <functional>

struct WidgetCallback
{
	std::function<void(int)> Callback;
	int ListenerID;
}; 
