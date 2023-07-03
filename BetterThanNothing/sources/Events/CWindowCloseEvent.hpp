#pragma once

#include "Events/CEvent.hpp"

class CWindowCloseEvent: public CEvent {
public:
	DECLARE_EVENT_NAME(CWindowCloseEvent)
};
