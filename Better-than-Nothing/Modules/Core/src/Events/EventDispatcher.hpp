#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class EventDispatcher
	{
	private:
		/**
		 * @brief The event to dispatch
		 */
		Event*	m_Event;

		/**
		 * @brief The context of the event
		 */
		void*	m_Context;

	public:
		/**
		 * @brief Construct a new Event Dispatcher object
		 *
		 * @param event The event to dispatch
		 * @param context The context of the event
		 */
		EventDispatcher(Event* event, void* context)
			: m_Event(event), m_Context(context) { };

		/**
		 * @brief Dispatch the event to the listener
		 *
		 * @param listener The listener to dispatch the event to
		 *
		 * @return Whether the event was handled or not
		 */
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
