#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	class KeyEvent: public Event
	{
	protected:
		u32	m_Key;
		u32	m_ScanCode;
		u32	m_Mods;

	public:
		KeyEvent(u32 key, u32 scanCode, u32 mods)
			: m_Key(key), m_ScanCode(scanCode), m_Mods(mods) {}

		bool IsKey(u32 key) { return m_Key == key; }

		u32 GetKey() { return m_Key; }
		u32 GetScanCode() { return m_ScanCode; }
		u32 GetMods() { return m_Mods; }
	};

	class KeyPressEvent: public KeyEvent
	{
	public:
		KeyPressEvent(u32 key, u32 scanCode, u32 mods): KeyEvent(key, scanCode, mods) {}
		DECLARE_EVENT_NAME(KeyPressEvent)
	};

	class KeyReleaseEvent: public KeyEvent
	{
	public:
		KeyReleaseEvent(u32 key, u32 scanCode, u32 mods): KeyEvent(key, scanCode, mods) {}
		DECLARE_EVENT_NAME(KeyReleaseEvent)
	};
};
