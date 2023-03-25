/*
 * File: WindowCloseEvent.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Saturday, 11th March 2023 12:33:28 am
 * Last Modified: Saturday, 11th March 2023 12:33:31 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "Events/Event.h"

class WindowCloseEvent: public Event {
public:
	DECLARE_EVENT_NAME(WindowCloseEvent)
};
