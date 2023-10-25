#pragma once

#include "Events/Event.hpp"

#define BIND_EVENT_LISTENER(fn) [this](auto&&... args) -> decltype(auto) {\
									return this->fn(std::forward<decltype(args)>(args)...);\
								}

namespace BetterThanNothing
{
	class EventDispatcher
	{
	private:
		Event*	m_pEvent;
	public:
		EventDispatcher(Event* event) : m_pEvent(event) { };

		template<typename T, typename F>
		bool Dispatch(const F& listener) {
			if (m_pEvent->GetName() == T::GetStaticName()) {
				bool handled = listener(static_cast<T*>(m_pEvent));
				m_pEvent->SetHandled(handled);
				return handled;
			}
			return false;
		}
	};
};
