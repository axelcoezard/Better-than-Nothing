#pragma once

namespace BetterThanNothing
{
	#define DECLARE_EVENT_NAME(name)\
		static const char* GetStaticName() { return #name; }\
		virtual const char* GetName() const override { return GetStaticName(); }

	class Event
	{
	private:
		bool	m_Handled = false;
		void*	m_Context = nullptr;
	public:
		virtual ~Event() = default;

		[[nodiscard]] virtual const char* GetName() const = 0;

		void SetHandled(bool handled) { m_Handled = handled; }
		bool IsHandled() { return m_Handled; }

		void SetContext(void* pContext) { m_Context = pContext; }
		void* GetContext() { return m_Context; }
		bool HasContext() { return m_Context != nullptr; }
	};
};
