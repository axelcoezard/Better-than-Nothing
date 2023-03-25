/*
 * File: KeyEvent.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 12:33:28 am
 * Last Modified: Saturday, 11th March 2023 12:33:31 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */
#pragma once

#include "Events/Event.hpp"

class KeyEvent: public Event {
protected:
	uint32_t	m_Key;
	uint32_t	m_ScanCode;
	uint32_t	m_Mods;
public:
	KeyEvent(uint32_t key, uint32_t scanCode, uint32_t mods)
		: m_Key(key), m_ScanCode(scanCode), m_Mods(mods) {}

	bool IsKey(uint32_t key) { return m_Key == key; }

	uint32_t GetKey(void) { return m_Key; }
	uint32_t GetScanCode(void) { return m_ScanCode; }
	uint32_t GetMods(void) { return m_Mods; }
};

class KeyPressEvent: public KeyEvent {
public:
	KeyPressEvent(uint32_t key, uint32_t scanCode, uint32_t mods): KeyEvent(key, scanCode, mods) {}
	DECLARE_EVENT_NAME(KeyPressEvent)
};

class KeyReleaseEvent: public KeyEvent {
public:
	KeyReleaseEvent(uint32_t key, uint32_t scanCode, uint32_t mods): KeyEvent(key, scanCode, mods) {}
	DECLARE_EVENT_NAME(KeyReleaseEvent)
};
