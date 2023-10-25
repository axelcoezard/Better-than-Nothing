#pragma once

namespace BetterThanNothing
{
	#define DECLARE_EVENT_NAME(name)\
		static const char* GetStaticName() { return #name; }\
		virtual const char* GetName() const override { return GetStaticName(); }

	class Event
	{
	private:
		bool	m_bHandled = false;
	public:
		virtual ~Event() = default;

		[[nodiscard]] virtual const char* GetName() const = 0;

		void SetHandled(bool handled) { m_bHandled = handled; }
		bool IsHandled() { return m_bHandled; }
	};
};
