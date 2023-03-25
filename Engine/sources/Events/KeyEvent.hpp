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
	int m_Key;
	int m_ScanCode;
	int m_Mods;
public:
	KeyEvent(int key, int scanCode, int mods)
		: m_Key(key), m_ScanCode(scanCode), m_Mods(mods) {}

	bool IsKey(int key) { return m_Key == key; }

	int GetKey(void) { return m_Key; }
	int GetScanCode(void) { return m_ScanCode; }
	int GetMods(void) { return m_Mods; }
};

class KeyPressEvent: public KeyEvent {
public:
	KeyPressEvent(int key, int scanCode, int mods): KeyEvent(key, scanCode, mods) {}
	DECLARE_EVENT_NAME(KeyPressEvent)
};

class KeyReleaseEvent: public KeyEvent {
public:
	KeyReleaseEvent(int key, int scanCode, int mods): KeyEvent(key, scanCode, mods) {}
	DECLARE_EVENT_NAME(KeyReleaseEvent)
};
