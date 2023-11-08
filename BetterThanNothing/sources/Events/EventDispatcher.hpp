#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class EventDispatcher
	{
	private:
		Event*	m_pEvent;
		void*	m_pContext;
	public:
		EventDispatcher(Event* event, void* context)
			: m_pEvent(event), m_pContext(context) { };

		template<typename T, typename F>
		bool Dispatch(const F& listener) {
			if (m_pEvent->GetName() == T::GetStaticName()) {
				m_pEvent->SetContext(m_pContext);
				bool handled = listener(static_cast<T*>(m_pEvent));
				m_pEvent->SetHandled(handled);
				return handled;
			}
			return false;
		}
	};
};
