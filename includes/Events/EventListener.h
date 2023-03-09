/*
 * File: EventListener.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Monday, 6th March 2023 4:47:21 pm
 * Last Modified: Tuesday, 7th March 2023 9:58:18 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "Events/Event.h"

struct EventListener {
	virtual ~EventListener(void) {}
	virtual void onEvent(Event* event) = 0;
};
