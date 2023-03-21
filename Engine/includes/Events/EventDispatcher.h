/*
 * File: EventDispatcher.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 21st March 2023 5:13:17 pm
 * Last Modified: Tuesday, 21st March 2023 11:14:31 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <string>
#include <string_view>
#include <map>

#include "Events/Event.h"

#define BIND_EVENT_LISTENER(fn) [this](auto&&... args) -> decltype(auto) {\
									return this->fn(std::forward<decltype(args)>(args)...);\
								}

struct EventDispatcher {
private:
	Event* m_Event;
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

