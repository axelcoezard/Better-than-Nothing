/*
 * File: Event.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Monday, 6th March 2023 4:47:21 pm
 * Last Modified: Tuesday, 7th March 2023 9:56:27 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "Core/GarbageCollector/GCObject.h"

class Event: public GCObject {
	private:
		bool m_handled = false;
	public:
		virtual ~Event(void) = default;

		virtual const char* GetName(void) const = 0;

		void SetHandled(bool handled) { m_handled = handled; }
		bool IsHandled(void) { return m_handled; }
};

#define DECLARE_EVENT_NAME(name)\
	static const char* GetStaticName() { return #name; }\
	virtual const char* GetName() const override { return GetStaticName(); }
