// Copyright Z.Z. Zengine (c)

#include "CollisionEventBinder.h"

void CollisionEventBinder::RemoveListener(int listenerIndex)
{
	for (auto itr = Callbacks.begin(); itr != Callbacks.end(); itr++)
	{
		if (itr->ListenerID == listenerIndex)
		{
			Callbacks.erase(itr);
		}
	}
}

void CollisionEventBinder::RemoveAllListeners()
{
	Callbacks.clear();
}

void CollisionEventBinder::Invoke(Collider* collider)
{
	for (auto& callback : Callbacks)
	{
		callback.Callback(collider);
	}
}