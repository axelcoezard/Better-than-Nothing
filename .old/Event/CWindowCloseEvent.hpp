#pragma once

#include "Event/CEvent.hpp"

namespace BetterThanNothing {
	class CWindowCloseEvent: public CEvent {
	public:
		DECLARE_EVENT_NAME(CWindowCloseEvent)
	};
};
