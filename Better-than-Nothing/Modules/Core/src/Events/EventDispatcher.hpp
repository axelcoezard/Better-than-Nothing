#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class EventDispatcher
	{
	private:
		Event*	m_Event;
		void*	m_Context;
	public:
		EventDispatcher(Event* event, void* context)
			: m_Event(event), m_Context(context) { };

		template<typename T, typename F>
		bool Dispatch(const F& listener) {
			if (m_Event->GetName() == T::GetStaticName()) {
				m_Event->SetContext(m_Context);
				bool handled = listener(static_cast<T*>(m_Event));
				m_Event->SetHandled(handled);
				return handled;
			}
			return false;
		}
	};
};
