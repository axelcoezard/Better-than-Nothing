/*
 * File: EventHandler.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Monday, 6th March 2023 4:47:21 pm
 * Last Modified: Tuesday, 7th March 2023 9:56:33 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <string>
#include <string_view>
#include <map>

#include "Core/GarbageCollector/GCObject.h"
#include "Events/Event.h"

#define EVENT_LISTENER(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

struct EventDispatcher {
	private:
		Event* m_event;
	public:
		EventDispatcher(Event* event) : m_event(event) { };

		template<typename T, typename F>
		bool Dispatch(const F& listener) {
			if (m_event->GetName() == T::GetStaticName()) {
				bool handled = listener(static_cast<T*>(m_event));
				m_event->SetHandled(handled);
				return handled;
			}
			return false;
		}
};

