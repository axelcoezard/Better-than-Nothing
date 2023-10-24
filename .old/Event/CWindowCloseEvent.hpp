#pragma once

#include "Event/CEvent.hpp"

namespace BetterThanNothing {
	class WindowCloseEvent: public CEvent {
	public:
		DECLARE_EVENT_NAME(WindowCloseEvent)
	};
};
