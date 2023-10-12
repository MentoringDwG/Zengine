// Copyright Z.Z. Zengine (c)

#pragma once

#include <vector>
#include "WidgetCallback.h"

class WidgetEventHandler
{
public:
	template <class _Fx, class _Types>
	int AddListener(_Fx&& _Func, _Types&& _Args)
	{
		ListenerIndex++;
		WidgetCallback widgetCallback;
		widgetCallback.Callback = std::bind(_Func, _Args, std::placeholders::_1);
		widgetCallback.ListenerID = ListenerIndex;
		Callbacks.push_back(widgetCallback);
		return ListenerIndex;
	}

	void RemoveListener(int listenerIndex);
	void RemoveAllListeners();
	void Invoke();

private:
	std::vector<struct WidgetCallback> Callbacks;
	int ListenerIndex = 0;
};

