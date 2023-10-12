// Copyright Z.Z. Zengine (c)

#pragma once

#include <functional>

struct CollisionCallback
{
	std::function<void(class Collider*)> Callback;
	int ListenerID = 1;
};


