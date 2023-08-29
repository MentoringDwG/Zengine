#pragma once

#include <functional>

struct WidgetCollback
{
	std::function<void(int)> Callback;
	int ListenerID;
}; 
