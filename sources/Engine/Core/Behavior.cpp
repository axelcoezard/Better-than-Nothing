/*
 * File: GameBehavior.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 10:31:26 pm
 * Last Modified: Tuesday, 7th March 2023 10:31:28 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <iostream>

#include "Core/GarbageCollector/GCObject.h"

#include "Core/Renderer.h"
#include "Core/Behavior.h"

Behavior::Behavior(void) {
	Renderer::Get()->RegisterBehavior(this);
}

Behavior::~Behavior(void) {
	Renderer::Get()->UnregisterBehavior(this);
}
