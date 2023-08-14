#pragma once

#include <functional>

struct CollisionCallback
{
public:
	std::function<void(class Collider*)> Callback;
	int ListenerID;
};


