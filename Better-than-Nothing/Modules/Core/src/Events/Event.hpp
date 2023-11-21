#pragma once

namespace BetterThanNothing
{
	/**
	 * @brief Macro to declare the name of an event
	 */
	#define DECLARE_EVENT_NAME(name)\
		static const char* GetStaticName() { return #name; }\
		virtual const char* GetName() const override { return GetStaticName(); }
	/**
	 * @brief The Event class is the base class of all events
	 */
	class Event
	{
	private:
		/**
		 * @brief Whether the event has been handled yet or not
		 */
		bool	m_Handled = false;

		/**
		 * @brief The context of the event
		 */
		void*	m_Context = nullptr;

	public:

		/**
		 * @brief Destroy the Event object
		 */
		virtual ~Event() = default;

		/**
		 * @brief Get the name of the event
		 * @return The name of the event
		 */
		[[nodiscard]] virtual const char* GetName() const = 0;

		/**
		 * @brief Set whether the event has been handled or not
		 *
		 * @param handled Whether the event has been handled or not
		 *
		 * @note This function should only be called by the EventDispatcher
		 */
		void SetHandled(bool handled) { m_Handled = handled; }

		/**
		 * @brief Whether the event has been handled or not
		 *
		 * @return Whether the event has been handled or not
		 */
		bool IsHandled() { return m_Handled; }

		/**
		 * @brief Set the context of the event
		 *
		 * @param context The context of the event
		 *
		 * @note This function should only be called by the EventDispatcher
		 * @note The context is used to pass data between the current context and the static listener.
		 */
		void SetContext(void* context) { m_Context = context; }

		/**
		 * @brief Get the context of the event
		 *
		 * @return The context of the event
		 */
		void* GetContext() { return m_Context; }

		/**
		 * @brief Whether the event has a context or not
		 *
		 * @return Whether the event has a context or not
		 */
		bool HasContext() { return m_Context != nullptr; }
	};
};
