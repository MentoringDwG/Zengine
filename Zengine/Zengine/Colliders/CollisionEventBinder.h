#pragma once

#include <vector>
#include "CollisionCallback.h"

struct CollisionEventBinder
{
public:
	template <class _Fx, class _Types>
	int AddListener(_Fx&& _Func, _Types&& _Args)
	{
		ListenerIndex++;
		CollisionCallback collisionCallback;
		collisionCallback.Callback = std::bind(_Func, _Args, std::placeholders::_1);
		collisionCallback.ListenerID = ListenerIndex;
		Callbacks.push_back(collisionCallback);
		return ListenerIndex;
	}

	void RemoveListener(int listenerIndex);
	void RemoveAllListeners();
	void Invoke(class Collider* collider);

private:
	std::vector<struct CollisionCallback> Callbacks;
	int ListenerIndex = 0;
};