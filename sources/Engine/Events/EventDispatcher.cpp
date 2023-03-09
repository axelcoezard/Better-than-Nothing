/*
 * File: EventHandler.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Monday, 6th March 2023 4:47:21 pm
 * Last Modified: Tuesday, 7th March 2023 9:59:02 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include "Events/EventDispatcher.h"

EventDispatcher* EventDispatcher::m_instance = nullptr;

EventDispatcher::EventDispatcher(void) = default;
EventDispatcher::~EventDispatcher(void)	{ m_listeners.clear(); }

void EventDispatcher::RegisterListener(std::string_view eventName, EventListener* eventListener) {
	m_listeners[std::string(eventName)] = eventListener;
}

void EventDispatcher::DispatchEvent(std::string_view eventName, Event* event) {
	auto search = m_listeners.find(std::string(eventName));
	if (search != m_listeners.end()) {
		search->second->onEvent(event);
	}
}

EventDispatcher* EventDispatcher::Get(void) {
	if (m_instance == nullptr) {
		m_instance = new EventDispatcher();
	}
	return m_instance;
}

void EventDispatcher::Destroy(void) {
	if (m_instance != nullptr) {
		delete m_instance;
	}
}
