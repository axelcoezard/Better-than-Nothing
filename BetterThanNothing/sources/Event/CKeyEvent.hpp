#pragma once

#include "Event/CEvent.hpp"

namespace BetterThanNothing {
	class CKeyEvent: public CEvent {
	protected:
		uint32_t	m_Key;
		uint32_t	m_ScanCode;
		uint32_t	m_Mods;
	public:
		CKeyEvent(uint32_t key, uint32_t scanCode, uint32_t mods)
			: m_Key(key), m_ScanCode(scanCode), m_Mods(mods) {}

		bool IsKey(uint32_t key) { return m_Key == key; }

		uint32_t GetKey() { return m_Key; }
		uint32_t GetScanCode() { return m_ScanCode; }
		uint32_t GetMods() { return m_Mods; }
	};

	class CKeyPressEvent: public CKeyEvent {
	public:
		CKeyPressEvent(uint32_t key, uint32_t scanCode, uint32_t mods): CKeyEvent(key, scanCode, mods) {}
		DECLARE_EVENT_NAME(CKeyPressEvent)
	};

	class CKeyReleaseEvent: public CKeyEvent {
	public:
		CKeyReleaseEvent(uint32_t key, uint32_t scanCode, uint32_t mods): CKeyEvent(key, scanCode, mods) {}
		DECLARE_EVENT_NAME(CKeyReleaseEvent)
	};
};
