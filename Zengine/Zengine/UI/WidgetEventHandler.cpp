// Copyright Z.Z. Zengine (c)

#include "WidgetEventHandler.h"

void WidgetEventHandler::RemoveListener(int listenerIndex)
{
	for (auto itr = Callbacks.begin(); itr != Callbacks.end(); itr++)
	{
		if (itr->ListenerID == listenerIndex)
		{
			Callbacks.erase(itr);
		}
	}
}

void WidgetEventHandler::RemoveAllListeners()
{
	Callbacks.clear();
}

void WidgetEventHandler::Invoke()
{
	for (auto& callback : Callbacks)
	{
		callback.Callback(1);
	}
}