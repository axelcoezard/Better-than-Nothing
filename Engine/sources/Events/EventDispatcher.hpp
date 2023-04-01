#pragma once

#include <string>
#include <string_view>
#include <map>

#include "Events/Event.hpp"

#define BIND_EVENT_LISTENER(fn) [this](auto&&... args) -> decltype(auto) {\
									return this->fn(std::forward<decltype(args)>(args)...);\
								}

struct EventDispatcher {
private:
	Event*	m_Event;
public:
	EventDispatcher(Event* event) : m_Event(event) { };

	template<typename T, typename F>
	bool Dispatch(const F& listener) {
		if (m_Event->GetName() == T::GetStaticName()) {
			bool handled = listener(static_cast<T*>(m_Event));
			m_Event->SetHandled(handled);
			return handled;
		}
		return false;
	}
};

