#pragma once

#include "Events/Event.hpp"

namespace BetterThanNothing
{
	/**
	 * @brief The KeyEvent class is the base class of all key events
	 */
	class KeyEvent: public Event
	{
	protected:
		/**
		 * @brief The key
		 */
		u32	m_Key;

		/**
		 * @brief The scan code
		 * @note The scan code is the physical location of the key on the keyboard
		 */
		u32	m_ScanCode;

		/**
		 * @brief The modifiers
		 * @note The modifiers are the keys that are pressed at the same time as the key
		 */
		u32	m_Mods;

	public:
		/**
		 * @brief Construct a new Key Event object
		 *
		 * @param key The key
		 * @param scanCode The scan code
		 * @param mods The modifiers
		 */
		KeyEvent(u32 key, u32 scanCode, u32 mods)
			: m_Key(key), m_ScanCode(scanCode), m_Mods(mods) {}

		/**
		 * @brief Whether the key is the same as the key of the event
		 *
		 * @param key The key to compare to the key of the event
		 */
		bool IsKey(u32 key) { return m_Key == key; }

		/**
		 * @brief Get the key of the event
		 */
		u32 GetKey() { return m_Key; }

		/**
		 * @brief Get the scan code of the event
		 */
		u32 GetScanCode() { return m_ScanCode; }

		/**
		 * @brief Get the modifiers of the event
		 */
		u32 GetMods() { return m_Mods; }
	};

	/**
	 * @brief The KeyPressEvent class is the event that is dispatched when a key is pressed
	 */
	class KeyPressEvent: public KeyEvent
	{
	public:
		KeyPressEvent(u32 key, u32 scanCode, u32 mods): KeyEvent(key, scanCode, mods) {}
		DECLARE_EVENT_NAME(KeyPressEvent)
	};

	/**
	 * @brief The KeyReleaseEvent class is the event that is dispatched when a key is released
	 */
	class KeyReleaseEvent: public KeyEvent
	{
	public:
		KeyReleaseEvent(u32 key, u32 scanCode, u32 mods): KeyEvent(key, scanCode, mods) {}
		DECLARE_EVENT_NAME(KeyReleaseEvent)
	};
};
