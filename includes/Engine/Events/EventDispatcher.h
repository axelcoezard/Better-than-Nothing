/*
 * File: EventHandler.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Monday, 6th March 2023 4:47:21 pm
 * Last Modified: Tuesday, 7th March 2023 9:56:33 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <string>
#include <string_view>
#include <map>

#include "Core/GarbageCollector/GCObject.h"

#include "Events/Event.h"
#include "Events/EventListener.h"

struct EventDispatcher: public GCObject {
	private:
		static EventDispatcher* m_instance;

		std::map<std::string, EventListener*> m_listeners;

	public:
		EventDispatcher(void);
		~EventDispatcher(void);

		EventDispatcher(EventDispatcher&) = delete;
		void operator=(const EventDispatcher&) = delete;

		void RegisterListener(std::string_view eventName, EventListener* eventListener);
		void DispatchEvent(std::string_view eventName, Event* event);

		static EventDispatcher* Get(void);
};
