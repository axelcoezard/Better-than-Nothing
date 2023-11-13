#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class WindowCloseEvent: public Event
	{
	public:
		DECLARE_EVENT_NAME(WindowCloseEvent)
	};
};
