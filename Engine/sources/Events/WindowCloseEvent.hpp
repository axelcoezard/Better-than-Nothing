#pragma once

#include "Events/Event.hpp"

class WindowCloseEvent: public Event {
public:
	DECLARE_EVENT_NAME(WindowCloseEvent)
};
