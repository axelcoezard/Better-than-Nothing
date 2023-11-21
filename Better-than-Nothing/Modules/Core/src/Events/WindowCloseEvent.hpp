#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief The WindowCloseEvent class is an event that is dispatched when the window is closed
	 */
	class WindowCloseEvent: public Event
	{
	public:
		DECLARE_EVENT_NAME(WindowCloseEvent)
	};
};
